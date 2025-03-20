#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <dirent.h>

#define INITIAL_CAPACITY 15

typedef struct {
	char** strings;
	size_t size;
	size_t capacity;
} RepoList;

char *get_user(void);
char *get_home(char const *user);
RepoList get_repos(char const *home, RepoList list);
void run_gits(RepoList commandlist, RepoList list);
RepoList get_gitcommands(RepoList list, RepoList commandlist);
void send_notif(char* gitfinalResult, RepoList list, size_t i);
void init_repolist(RepoList* list);
void append_repolist(RepoList* list, const char* repo);

char *get_user(void)
{
	const int bufferSize = 128;
	char buffer[bufferSize];
	char *result = NULL;
	size_t resultSize = 0;

	FILE *p = popen("whoami", "r");
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

char *get_home(char const *user)
{
	const char* home = "/home/";
	const char* repos = "/repos/";

	char *pch = strstr(user, "\n");
	if(pch != NULL) strncpy(pch, "\0", 1);

	size_t resultSize = (
		strlen(home) + strlen(user) + strlen(repos) + 1
		);
	char* result = (char*)malloc(resultSize);

	sprintf(result, "%s%s%s", home, user, repos);
	
	return result;
}

void init_repolist(RepoList* list)
{
	list->strings = (char**)malloc(INITIAL_CAPACITY * sizeof(char*));
	list->size = 0;
	list->capacity = INITIAL_CAPACITY;
}

void append_repolist(RepoList* list, const char* repo)
{
	if (list->size >= list->capacity) {
		list->capacity *= 3;
		list->strings = (char**)realloc(list->strings, list->capacity * sizeof(char*));
	}
	list->strings[list->size] = strdup(repo);
	list->size++;
}

RepoList get_repos(char const *home, RepoList list)
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

			append_repolist(&list, result);
		}
	closedir(d);
	}
	return list;
	for (size_t i = 0; i < list.size; i++) {
		printf("%s\n", list.strings[i]);
	}
}

RepoList get_gitcommands(RepoList list, RepoList commandlist)
{
	const char* git1 = "git -C ";
	const char* git2 = " status";
	char* command_result;

	for (size_t i = 0; i < list.size; i++) {
		size_t resultSize = (
			strlen(git1) + strlen(list.strings[i]) + strlen(git2) + 1
			);
		command_result = (char*)malloc(resultSize);
		sprintf(command_result, "%s%s%s", git1, list.strings[i], git2);
		append_repolist(&commandlist, command_result);
		printf("%s", command_result);
	}
	return commandlist;

}

void send_notif(char* gitfinalResult, RepoList list, size_t i)
{
    	printf("%s \n\n\n\n\n", gitfinalResult);	

	const char *behind = "Your branch is behind";
	const char *ahead = "Your branch is ahead";
	const char *diverged = "have diverged";
	const char *unstaged = "Changes not staged";

	const char *behindNotif = "notify-send 'Branch behind' '";
	const char *aheadNotif = "notify-send 'Branch ahead' '";
	const char *divergedNotif = "notify-send 'Branch diverged' '";
	const char *unstagedNotif = "notify-send 'Branch unstaged' '";

	const char *apostrophe = "'";
	char *fullNotif;

	char *checkBehind = strstr(gitfinalResult, behind);
	char *checkAhead = strstr(gitfinalResult, ahead);
	char *checkDiverged = strstr(gitfinalResult, diverged);
	char *checkUnstaged = strstr(gitfinalResult, unstaged);

	if (checkBehind != NULL) {
		size_t resultSize = (
			strlen(behindNotif) + strlen(list.strings[i]) + strlen(apostrophe) + 1
			);
		fullNotif = (char*)malloc(resultSize);
		sprintf(fullNotif, "%s%s%s", behindNotif, list.strings[i], apostrophe);
		
		system(fullNotif);
	}
	if (checkAhead != NULL) {
		size_t resultSize = (
			strlen(aheadNotif) + strlen(list.strings[i]) + strlen(apostrophe) + 1
			);
		fullNotif = (char*)malloc(resultSize);
		sprintf(fullNotif, "%s%s%s", aheadNotif, list.strings[i], apostrophe);
		
		system(fullNotif);

	}
	if (checkDiverged != NULL) {
		size_t resultSize = (
			strlen(divergedNotif) + strlen(list.strings[i]) + strlen(apostrophe) + 1
			);
		fullNotif = (char*)malloc(resultSize);
		sprintf(fullNotif, "%s%s%s", divergedNotif, list.strings[i], apostrophe);
		
		system(fullNotif);

	}
	if (checkUnstaged != NULL) {
		size_t resultSize = (
			strlen(unstagedNotif) + strlen(list.strings[i]) + strlen(apostrophe) + 1
			);
		fullNotif = (char*)malloc(resultSize);
		sprintf(fullNotif, "%s%s%s", unstagedNotif, list.strings[i], apostrophe);
		
		system(fullNotif);

	}
}

void run_gits(RepoList commandlist, RepoList list)
{
	const int bufferSize = 128;
	char buffer[bufferSize];
	char *gitresult = NULL;
	size_t gitresultSize = 0;

	for (size_t i = 0; i < commandlist.size; i++) {
		char *gitfinalResult = NULL;

		FILE *p = popen( commandlist.strings[i], "r");
		if (p == NULL) exit(1);

		while (fgets(buffer, bufferSize, p) != NULL) {
			size_t fragmentSize = strlen(buffer);
			char *newResult = realloc(
				gitresult, gitresultSize + fragmentSize + 1
			);
			gitresult = newResult;
			memcpy(gitresult + gitresultSize, buffer, fragmentSize);
			gitresultSize += fragmentSize;
		}	

		int status = pclose(p);
		if (status == -1) free(gitresult);

		gitfinalResult = malloc(gitresultSize + 1);
		memcpy(gitfinalResult, gitresult, gitresultSize);
		gitfinalResult[gitresultSize] = '\0';
	
		send_notif(gitfinalResult, list, i);

		free(gitfinalResult);
		gitresultSize = 0;
	}
	free(gitresult);

}

int main(void)
{
	char *home;
	char *user;
	RepoList list;
	RepoList commandlist;
	init_repolist(&list);
	init_repolist(&commandlist);

	user = get_user();
	home = get_home(user);

	list = get_repos(home, list);
	commandlist = get_gitcommands(list, commandlist);

	run_gits(commandlist, list);
}

