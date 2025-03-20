#include <ncurses.h>

#include "entities.h"
#include "display.h"
#include "text.h"
#include "gtime.h"

WINDOW *win;
WINDOW *borderwin;

void init_window()
{
	initscr();
	refresh();
	borderwin = newwin(37, 55, 1, 1);
	win = newwin(35, 50, 2, 3);
	noecho();	
	curs_set(0);
	keypad(win, TRUE);
	wborder(borderwin, '|', '|', '=', '=', 'o', 'o', 'o', 'o');
	wrefresh(borderwin);
	wrefresh(win);
	wmove(win, 2, 6);
}

int rows = sizeof(map) / sizeof(map[0]);
int columns = sizeof(map[0]) / sizeof(map[0][0]);

void print_title()
{
	wprintw(win, "%s", titlescreen);
	if (wgetch(win) == 'd') debug = 1;
	werase(win);
}

int print_map(char map[][28], int rows, int columns) {
	int currentlocation = 1;
	mvwprintw(win, 0, 17, "Dutchy of Tania\n");
	for (int r = 0; r < rows; r++) {
		wprintw(win, "           ");
		for (int c = 0; c < columns; c++) {
			if (r == p.y && c == p.x) {
				currentlocation = map[r][c];
				waddch(win, '@');
			} else
				wprintw(win, "%c", map[r][c]);
		}
	waddch(win, '\n'); }
	if (debug) wprintw(win, "  %d, %d\n  DEBUG", p.x, p.y);
	
	return currentlocation;
}

void print_userinfo(int currentlocation)
{
	char* locationtext;
	if (currentlocation == 42) locationtext = "The Old Red Forest";
	else if (currentlocation == 94) locationtext = "Cliffs of Bill";
	else if (currentlocation == 95 || currentlocation == 47)
		locationtext= "Tanian River Shore";
	else locationtext = "Plains of Castamere";

	if (p.intown) mvwprintw(win, 9, 17, "%s", p.location);
	else mvwprintw(win, 9, 17, "%s", locationtext);
	
	mvwprintw(win, 10, 22, "%s", p.season);

	mvwprintw(win, 12, 9, "Rank: %s", p.title);
	mvwprintw(win, 12, 29, "Denars: %i", p.denars);
	mvwprintw(win, 13, 8, "Party: %d/%d", party.total, p.armycap);
	mvwprintw(win, 13, 29, "Upkeep: %d", party.totalupkeep);
	mvwprintw(win, 13, 29, "Upkeep: %d", party.totalupkeep);
}

void print_time()
{

	mvwprintw(win, 15, 9, "Hour: %d", gtime.hour);
	mvwprintw(win, 15, 29, " Week:  %d", gtime.week);
	mvwprintw(win, 16, 9, "Day:  %d", gtime.day);
	mvwprintw(win, 16, 30, "Month: %d", gtime.month);
	mvwprintw(win, 17, 30, "Year: %d", gtime.year);
}

void print_actions()
{
    	mvwprintw(win, 18, 9, "Actions:\n");
	if (p.intown) {
		mvwprintw(win, 19, 9, "1. Enter city"); 
		mvwprintw(win, 20, 9, "2. Contact local noble");
    		mvwprintw(win, 21, 9, "3. Hire local mercenaries");
	} else if (!p.intown) {
		mvwprintw(win, 19, 9, "1. Setup fortified camp");
    		mvwprintw(win, 20, 9, "2. Draft correspondence");
	}
	mvwprintw(win, 23, 9, "c. View Character Info\n"); 
	mvwprintw(win, 24, 9, "i. View Inventory\n"); 
	mvwprintw(win, 25, 9, "p. View Party\n"); 
	mvwprintw(win, 27, 9, "q. View Current Quests\n");
	mvwprintw(win, 28, 9, "r. View Relevant Nobles\n"); 
	
	if (debug) mvwprintw(win, 32, 9, "d. View Debug Menu\n"); 
}

void print_event(char* text, char* flavor)
{
	int eventloop = 1;
	wclear(win);
	wprintw(win, "%s", text);
	wprintw(win, "\n\n\n\n(b) %s", flavor);
	while (eventloop) {
		int response = wgetch(win);
		switch (response) {
			case 'b':
				eventloop = 0;
				break;
		}
	}
}

char print_event_small(char* text, char* args)
{
	wprintw(win, text, args);
	int response = wgetch(win);
	return response;
}

char print_event_args1(char* text, char* args)
{
	werase(win);
	wprintw(win, text, args);
	int response = wgetch(win);
	return response;
}

char print_event_args2(char* text, char* textargs1, char* textargs2)
{
	char buffer[256];
	werase(win);
	sprintf(buffer, text, textargs1, textargs2);
	wprintw(win, "%s", buffer);
	int response = wgetch(win);
	return response;
}

char print_event_args3(
	char* text, char* textargs1, 
	char* textargs2, char*textargs3)
{
	char buffer[512];
	werase(win);
	snprintf(buffer, 512, text, textargs1, textargs2, textargs3);
	wprintw(win, "%s", buffer);
	int response = wgetch(win);
	return response;
}

char print_event_args4(
	char* text, char* textargs1, 
	char* textargs2, char* textargs3,
	char* textargs4)
{
	char buffer[512];
	werase(win);
	snprintf(buffer, 512, text, textargs1, textargs2, textargs3, textargs4);
	wprintw(win, "%s", buffer);
	int response = wgetch(win);
	return response;
}

void print_eventnew(char* text, char* textargs, char* flavor)
{
	int eventloop = 1;
	werase(win);
	wprintw(win, text, textargs);
	wprintw(win, "\n\n\n\n(b) %s", flavor);
	while (eventloop) {
		int response = wgetch(win);
		switch (response) {
			case 'b':
				eventloop = 0;
				break;
		}
	}
}

void print_event_long(
        char* title, char* titleargs, 
        char* body, char* bodyargs, 
        char* foot, char* footargs)
{
        wclear(win);
        wprintw(win, title, titleargs);
        wprintw(win, body, bodyargs);
        wprintw(win, foot, footargs);
}
