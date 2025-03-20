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
	borderwin = newwin(42, 55, 1, 1);
	win = newwin(40, 50, 2, 2);
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
	"|....../........c^^^^^^^...|",
	"|.t___/....C.............c.|",
	"|./............c...........|",
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
	wprintw(win, "  Dutchy of Tania\n");
	for (int r = 0; r < rows; r++) {
		wprintw(win, "  ");
		for (int c = 0; c < columns; c++) {
			if (r == p.y && c == p.x)
				waddch(win, '@');
			else
				wprintw(win, "%c", arr[r][c]);
		}
	waddch(win, '\n'); }
	if (debug) wprintw(win, " %d, %d\n", p.x, p.y);
}

void print_userinfo()
{
    	if (p.intown) wprintw(win, "  %s\n\n", p.location);
    	if (!p.intown) wprintw(win, "  Plains of Castamere\n\n");
	wprintw(win, "  Rank: %s            Denars: %i\n", p.title, p.denars);
	wprintw(win, "  Party: %zu/%zu troops      Weekly Upkeep: %zu\n", party.total, p.armycap, party.totalupkeep);	
}

void print_time()
{
	wprintw(win, "  Hour: %zu\tDays: %zu\t   Weeks: %zu\n\n", gtime.hour, gtime.day, gtime.week);
}

void print_actions()
{
    	wprintw(win, "  Actions:\n");
	if (p.intown) {
	wprintw(win, "  1. Enter city\n  2. Contact local noble\n  3. Hire local mercenaries\n\n"); 
	} else if (!p.intown) {
	wprintw(win, "  1. Setup fortified camp\n  2. Draft correspondence\n\n\n");
	}
	wprintw(win, "  p. View Party\n"); 
	wprintw(win, "  i. View Inventory\n"); 
	wprintw(win, "  r. View Relations\n"); 
	wprintw(win, "  q. View Current Quests\n");
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
