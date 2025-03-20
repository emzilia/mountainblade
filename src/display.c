#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "entities.h"
#include "display.h"
#include "logic.h"
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

char map[8][28] = {
	"o==========================o",
	"|.....c./^^^^^^^^^^^^^^^t..|",
	"|....../........v^^^^^^^...|",
	"|.t___/....C.............c.|",
	"|./............v...........|",
	"|/.....**t*******..t.......|",
	"|..t..************......t..|",
	"o==========================o"
};
	

int rows = sizeof(map) / sizeof(map[0]);
int columns = sizeof(map[0]) / sizeof(map[0][0]);

void print_title()
{
	wprintw(win,
		"    Hello and welcome to Tania!\n\n"
		"    The Duke has been gone for three years now,\n"
		"fighting heathens abroad. Unrest grows across the\n"
		"realm as local nobles grow to fill the void left\n"
		"in his absence."
	);
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
	if (debug) wprintw(win, "  %d, %d\n", p.x, p.y);
	
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

    	if (p.intown) mvwprintw(win, 9, 17, "%s\n\n", p.location);
	else { 
		mvwprintw(win, 9, 17, locationtext);
	}
	mvwprintw(win, 10, 22, "%s", p.season);

	mvwprintw(win, 12, 9, "Rank: %s", p.title);
	mvwprintw(win, 12, 29, "Denars: %i", p.denars);
	mvwprintw(win, 13, 8, "Party: %zu/%zu", party.total, p.armycap);
	mvwprintw(win, 13, 29, "Upkeep: %zu", party.totalupkeep);
}

void print_time()
{

	mvwprintw(win, 15, 9, "Hour: %zu", gtime.hour);
	mvwprintw(win, 15, 29, " Week:  %zu", gtime.week);
	mvwprintw(win, 16, 9, "Day:  %zu", gtime.day);
	mvwprintw(win, 16, 30, "Month: %zu", gtime.month);
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
}

void print_event(char* text)
{
	int eventloop = 1;
	wclear(win);
	wprintw(win, text);
	wprintw(win, "\n\n\n\n(b) to go back");
	while (eventloop) {
		int response = wgetch(win);
		switch (response) {
			case 'b':
				eventloop = 0;
				break;
		}
	}
}

void print_event_args(char* text, char* args)
{
	wclear(win);
	wprintw(win, text, args);
	wgetch(win);
}
