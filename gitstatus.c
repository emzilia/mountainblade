#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <dirent.h>

#define INITIAL_CAPACITY 10

typedef struct {
	char** strings;
	size_t size;
	size_t capacity;
} VarList;

char *get_home(void);
char *combine_home(char const *home);
void init_safearray(VarList* listRepo);
void append_safearray(VarList* listRepo, const char* repo);
VarList get_repos(char const *home, VarList listRepo);
VarList get_gitfetchcommands(VarList listRepo, VarList listFetchCommand);
VarList get_gitstatuscommands(VarList listRepo, VarList listStatusCommand);
void run_gitfetch(VarList listFetchCommand, VarList listRepo);
void run_gitstatus(VarList listStatusCommand, VarList listRepo);
void send_notif(char* gitFinalResult, VarList listRepo, size_t i);

// Gets home by echoing $HOME'.
char *get_home(void)
{
	const int bufferSize = 128;
	char buffer[bufferSize];
	char *result = NULL;
	size_t resultSize = 0;

	FILE *p = popen("echo $HOME", "r");
	if (p == NULL) return NULL;

	while (fgets(buffer, bufferSize, p) != NULL) {
		size_t fragmentSize = strlen(buffer);
		char *newResult = realloc(
			result, resultSize + fragmentSize + 1
		);
		result = newResult;
		memcpy(result + resultSize, buffer, fragmentSize);
		resultSize += fragmentSize;
	}	

	int status = pclose(p);
	if (status == -1)
		free(result);

	char *finalResult = realloc(result, resultSize + 1);
	finalResult[resultSize] = '\0';

	return finalResult;
}

// Adds username between /home/ and /repos/, returns full path to repos dir.
char *combine_home(char const *home)
{
	const char* repos = "/repos/";

	char *pch = strstr(home, "\n");
	if(pch != NULL) strncpy(pch, "\0", 1);

	size_t resultSize = (
		strlen(home) + strlen(repos) + 1
		);
	char* result = (char*)malloc(resultSize);

	sprintf(result, "%s%s", home, repos);
	
	return result;
}

// Initializes a list of indeterminate size, for repo list and command list.
void init_safearray(VarList* list)
{
	list->strings = (char**)malloc(INITIAL_CAPACITY * sizeof(char*));
	list->size = 0;
	list->capacity = INITIAL_CAPACITY;
}

// Appends an item to a list of indeterminate size.
void append_safearray(VarList* list, const char* repo)
{
	if (list->size >= list->capacity) {
		list->capacity *= 3;
		list->strings = (char**)realloc(list->strings, list->capacity * sizeof(char*));
	}
	list->strings[list->size] = strdup(repo);
	list->size++;
}

// Using the full repo path returned by combine_home(), each dir path within is
// added to the list of repos and the list is returned.
VarList get_repos(char const *home, VarList list)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(home);
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			char *p = dir->d_name;
			size_t resultSize = (
				strlen(home) + strlen(p) + 1
				);
			char* result = (char*)malloc(resultSize);
			sprintf(result, "%s%s", home, p);

			append_safearray(&list, result);
		}
	closedir(d);
	}
	return list;
}

VarList get_gitfetchcommands(VarList listRepo, VarList listFetchCommand)
{
	const char* git1 = "git -C ";
	const char* git2 = " fetch &";
	char* commandResult;

	for (size_t i = 0; i < listRepo.size; i++) {
		size_t resultSize = (
			strlen(git1) + strlen(listRepo.strings[i]) + strlen(git2) + 1
			);
		commandResult = (char*)malloc(resultSize);
		sprintf(commandResult, "%s%s%s", git1, listRepo.strings[i], git2);
		append_safearray(&listFetchCommand, commandResult);
	}
	return listFetchCommand;

}
// Using the list completed by get_repos(), each path is placed between two
// strings to form the full git command, each full git command is then
// appended to the listStatusCommand which is returned.
VarList get_gitstatuscommands(VarList listRepo, VarList listStatusCommand)
{
	const char* git1 = "git -C ";
	const char* git2 = " status &";
	char* commandResult;

	for (size_t i = 0; i < listRepo.size; i++) {
		size_t resultSize = (
			strlen(git1) + strlen(listRepo.strings[i]) + strlen(git2) + 1
			);
		commandResult = (char*)malloc(resultSize);
		sprintf(commandResult, "%s%s%s", git1, listRepo.strings[i], git2);
		append_safearray(&listStatusCommand, commandResult);
	}
	return listStatusCommand;

}

void run_gitfetch(VarList listFetchCommand, VarList listRepo)
{
    for (size_t i = 0; i < listFetchCommand.size; i++) {
        system(listFetchCommand.strings[i]);
        puts("How long does this take exactly?");
    }
}

// Using the listStatusCommand returned by get_gitcommands(), a loop is run and each
// command opens a pipe and saves the output of git status to the variable
// gitFinalResult. This variable, along with the original path list and
// the list index is passed to the send_notif() function.
void run_gitstatus(VarList listStatusCommand, VarList listRepo)
{
	const int bufferSize = 128;
	char buffer[bufferSize];
	char *gitResult = NULL;
	size_t gitResultSize = 0;

	for (size_t i = 0; i < listStatusCommand.size; i++) {
		char *gitFinalResult = NULL;

		FILE *p = popen( listStatusCommand.strings[i], "r");
		if (p == NULL) exit(1);

		while (fgets(buffer, bufferSize, p) != NULL) {
			size_t fragmentSize = strlen(buffer);
			char *newResult = realloc(
				gitResult, gitResultSize + fragmentSize + 1
			);
			gitResult = newResult;
			memcpy(gitResult + gitResultSize, buffer, fragmentSize);
			gitResultSize += fragmentSize;
		}	

		int status = pclose(p);
		if (status == -1) free(gitResult);

		gitFinalResult = malloc(gitResultSize + 1);
		memcpy(gitFinalResult, gitResult, gitResultSize);
		gitFinalResult[gitResultSize] = '\0';
	
		send_notif(gitFinalResult, listRepo, i);

		free(gitFinalResult);
		gitResultSize = 0;
	}
	free(gitResult);

}

// With the gitFinalResult from run_gits(), the string is compared and if the
// status contains specific strings, a notification is sent describing it.
// The original path list and index are included to give context to the notif.
void send_notif(char* gitFinalResult, VarList listRepo, size_t i)
{
    	printf("\n\n%s\n***************\n", gitFinalResult);	

	const char *behind = "Your branch is behind";
	const char *ahead = "Your branch is ahead";
	const char *diverged = "have diverged";
	const char *unstaged = "Changes not staged";

	const char *behindNotif = "notify-send 'Branch behind' '";
	const char *aheadNotif = "notify-send 'Branch ahead' '";
	const char *divergedNotif = "notify-send 'Branch diverged' '";
	const char *unstagedNotif = "notify-send 'Branch unstaged' '";

	const char *apos = "'";
	char *fullNotif;

	char *checkBehind = strstr(gitFinalResult, behind);
	char *checkAhead = strstr(gitFinalResult, ahead);
	char *checkDiverged = strstr(gitFinalResult, diverged);
	char *checkUnstaged = strstr(gitFinalResult, unstaged);

	if (checkBehind != NULL) {
		size_t resultSize = (
			strlen(behindNotif) + strlen(listRepo.strings[i]) + strlen(apos) + 1
			);
		fullNotif = (char*)malloc(resultSize);
		sprintf(fullNotif, "%s%s%s", behindNotif, listRepo.strings[i], apos);
		
		system(fullNotif);
	}
	if (checkAhead != NULL) {
		size_t resultSize = (
			strlen(aheadNotif) + strlen(listRepo.strings[i]) + strlen(apos) + 1
			);
		fullNotif = (char*)malloc(resultSize);
		sprintf(fullNotif, "%s%s%s", aheadNotif, listRepo.strings[i], apos);
		
		system(fullNotif);

	}
	if (checkDiverged != NULL) {
		size_t resultSize = (
			strlen(divergedNotif) + strlen(listRepo.strings[i]) + strlen(apos) + 1
			);
		fullNotif = (char*)malloc(resultSize);
		sprintf(fullNotif, "%s%s%s", divergedNotif, listRepo.strings[i], apos);
		
		system(fullNotif);

	}
	if (checkUnstaged != NULL) {
		size_t resultSize = (
			strlen(unstagedNotif) + strlen(listRepo.strings[i]) + strlen(apos) + 1
			);
		fullNotif = (char*)malloc(resultSize);
		sprintf(fullNotif, "%s%s%s", unstagedNotif, listRepo.strings[i], apos);
		
		system(fullNotif);

	}
}

// TODO: Rename some vague variables
int main(void)
{
	char *home, *homerepo;
	VarList listRepo, listStatusCommand, listFetchCommand;

	init_safearray(&listRepo);
	init_safearray(&listStatusCommand);
	init_safearray(&listFetchCommand);

	home = get_home();
	homerepo = combine_home(home);

	listRepo = get_repos(homerepo, listRepo);
	listFetchCommand = get_gitfetchcommands(listRepo, listFetchCommand);
	listStatusCommand = get_gitstatuscommands(listRepo, listStatusCommand);

	run_gitfetch(listFetchCommand, listRepo);
	run_gitstatus(listStatusCommand, listRepo);
}

