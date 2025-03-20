#ifndef DISPLAY_H
#define DISPLAY_H

void print_title();
void print_map(char arr[][14], int rows, int columns);
void print_userinfo();
void print_actions();

extern int debug;
extern char map[8][14];
extern int rows;
extern int columns;

#endif
