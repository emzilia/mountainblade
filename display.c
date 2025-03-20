#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "entities.h"
#include "display.h"
#include "logic.h"

char map[8][14] = {
	"o============o",
	"|.....c./^^^^|",
	"|.t..../.....|",
	"|..___/....t.|",
	"|./...c......|",
	"|/.....**t***|",
	"|..c..*******|",
	"o============o"
};
	

int rows = sizeof(map) / sizeof(map[0]);
int columns = sizeof(map[0]) / sizeof(map[0][0]);

void print_title()
{
	printw(
		"Hello and welcome to Tania!\n\n"
		"The Duke has been gone for three years now,\n"
		"fighting heathens abroad. Unrest grows across the\n"
		"realm as local nobles centralize their power."
	);

	if (getch() == 'p') debug = 1;
	clear();
}

void print_map(char arr[][14], int rows, int columns) {
	printw("Dutchy of Tania\n");
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			if (r == p.y && c == p.x)
				addch('@');
			else
				printw("%c", arr[r][c]);
		}
	addch('\n'); }
	if (debug) printw(" %d, %d\n", p.x, p.y);
	set_location();
}

void print_userinfo()
{
	printw("Your title is %s\n", p.title);
	printw("You have $%i in silver coins\n", p.denars);
	printw("You have %zu warriors in your employ\n\n", p.army);	
}

void print_actions()
{
    	printw("Actions:\n");
	if (p.intown) {
	printw("1. Enter city\n2. Contact nobleman\n3. Hire local mercenaries\n\n"); 
	} else if (!p.intown) {
	printw("1. Setup fortified camp\n2. Draft correspondence\n\n");
	}
	printw("i. View Inventory\n"); 
	printw("r. View Relations\n"); 
	printw("q. View Current Quests\n");
}
