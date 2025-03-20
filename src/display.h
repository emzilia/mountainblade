#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

void init_window();

void print_title();
int print_map(char map[][28], int rows, int columns);
void print_userinfo(int currentlocation);
void print_time();
void print_actions();

typedef struct {
	int response;
	char* text;
	char* arg;
} Event1;

typedef struct {
	int response;
	char* text;
	char* arg1;
	char* arg2;
} Event2;

void print_event(char* text, char* flavor);
char print_event_small(char* text, char* args);
char print_event_args(char* text, char* args);
char print_event_args2(char* text, char* textargs1, char* textargs2);
void print_eventnew(char* text, char* textargs, char* flavor);
void print_event_long(
        char* title, char* titleargs, 
        char* body, char* bodyargs, 
        char* foot, char* footargs);


extern WINDOW* win;
extern int debug;
extern char map[8][28];
extern int rows;
extern int columns;

#endif
