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
	borderwin = newwin(45, 55, 1, 1);
	win = newwin(42, 50, 2, 2);
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
		"realm as local nobles grow to fill the void.\n"
	);
	if (wgetch(win) == 'p') debug = 1;
	werase(win);
}

void print_map(char arr[][28], int rows, int columns) {
	mvwprintw(win, 0, 17, "Dutchy of Tania\n");
	for (int r = 0; r < rows; r++) {
		wprintw(win, "           ");
		for (int c = 0; c < columns; c++) {
			if (r == p.y && c == p.x)
				waddch(win, '@');
			else
				wprintw(win, "%c", arr[r][c]);
		}
	waddch(win, '\n'); }
	if (debug) wprintw(win, "  %d, %d\n", p.x, p.y);
}

void print_userinfo()
{
    	if (p.intown) mvwprintw(win, 9, 17, "%s\n\n", p.location);
    	if (!p.intown) mvwprintw(win, 9, 17, "Plains of Castamere\n\n");

	mvwprintw(win, 11, 9, "Rank: %s", p.title);
	mvwprintw(win, 11, 29, "Denars: %i", p.denars);
	mvwprintw(win, 12, 8, "Party: %zu/%zu", party.total, p.armycap);
	mvwprintw(win, 12, 29, "Upkeep: %zu", party.totalupkeep);
}

void print_time()
{

	mvwprintw(win, 14, 9, "Hour: %zu", gtime.hour);
	mvwprintw(win, 14, 29, " Week:  %zu", gtime.week);
	mvwprintw(win, 15, 9, "Day:  %zu", gtime.day);
	mvwprintw(win, 15, 30, "Month: %zu", gtime.month);
}

void print_actions()
{
    	mvwprintw(win, 17, 9, "Actions:\n");
	if (p.intown) {
		mvwprintw(win, 18, 9, "1. Enter city"); 
		mvwprintw(win, 19, 9, "2. Contact constable");
    		mvwprintw(win, 20, 9, "3. Hire local mercenaries");
	} else if (!p.intown) {
		mvwprintw(win, 18, 9, "1. Setup fortified camp");
    		mvwprintw(win, 19, 9, "2. Draft correspondence");
	}
	mvwprintw(win, 22, 9, "p. View Party\n"); 
	mvwprintw(win, 23, 9, "i. View Inventory\n"); 
	mvwprintw(win, 24, 9, "r. View Relevant Nobles\n"); 
	mvwprintw(win, 25, 9, "q. View Current Quests\n");
}

void print_event(char* text)
{
	wclear(win);
	wprintw(win, text);
	wgetch(win);
}

void print_event_args(char* text, char* args)
{
	wclear(win);
	wprintw(win, text, args);
	wgetch(win);
}
