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

char *get_user();
char *get_home(char const *user);
void *get_repos(char const *home, RepoList list);

char *get_user()
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

void *get_repos(char const *home, RepoList list)
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
	for (size_t i = 0; i < list.size; i++) {
		printf("%s\n", list.strings[i]);
	}
}

void run_gits(RepoList list)
{
	const char* git1 = "git -C ";
	const char* git2 = "status";
}

int main()
{
	char *home;
	char *user;
	RepoList list;
	init_repolist(&list);

	user = get_user();
	home = get_home(user);

	get_repos(home, list);
}

