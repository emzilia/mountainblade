#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include "actions.h"
#include "entities.h"

void look();
void city_all();
void print_userinfo();

int debug = 0;

void update_pxy()
{
	char px[2];
	char py[2];
	char pxy[5];

	sprintf(px, "%d", p.x);
	sprintf(px, "%d", p.x);
	
//	pxy = strcat(px, py);
	p.xy = atoi(pxy);
}

char map[8][14] = {
	"o============o",
	"|.....c./....|",
	"|.t..../.....|",
	"|..___/....t.|",
	"|./...c......|",
	"|/.....\"\"t\"\"\"|",
	"|..c..\"\"\"\"\"\"\"|",
	"o============o"
};
	

int rows = sizeof(map) / sizeof(map[0]);
int columns = sizeof(map[0]) / sizeof(map[0][0]);

void title_screen()
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
	city_all();
}

void print_userinfo()
{
	printw("Your title is %s\n", p.title);
	printw("You have $%i in silver coins\n", p.denars);
	printw("You have %zu warriors in your employ\n\n", p.army);	
}

int city_look(City town)
{
	if (p.x == town.x && p.y == town.y) {
		p.intown = 1;
		strcpy(p.location, town.location);
		printw("%s\nPopulation of %zu\n\n", town.location, town.pop);
		return 1;
	}
	return 0;
}

void city_all()
{
	if (city_look(zander)) {
		return;
	} else if (city_look(talis)) {
		return;
	} else if (city_look(adriin)) {
		return;
	} else if (city_look(doxoun)) {
		return;
	} else if (city_look(calia)) {
		return;
	} else if (city_look(grelin)) {
		return;

	} else if ((p.x > 6 && p.y > 4) || (p.x == 6 && p.y == 6)) {
		p.intown = 0;
		printw("Forest of Grensdale\n\n\n");
	} else if (p.x == 1 && p.y == 5) {
		p.intown = 0;
		printw("The King's River\n\n\n");
	} else {
		p.intown = 0;
		printw("Plains of Castamere\n\n\n");
	}

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

void movement()
{
	int response = getch();
	switch (response) {
		case 'k':
		case KEY_UP:
			if (p.y > 1)
				p.y--;
				//update_pxy();
			break;
		case 'j':
		case KEY_DOWN:
			if (p.y < rows - 2)
				p.y++; 
				//update_pxy();
			break;
		case 'h':
		case KEY_LEFT:
			if (p.x > 1)
				p.x--;
				//update_pxy();
			break;
		case 'l':
		case KEY_RIGHT:
			if (p.x < columns - 2)
				p.x++;
				//update_pxy();
			break;
	}
	
	if (p.intown) {
		switch (response) {
			case '1':
				action_enter_city();
				break;
			case '2': 
				action_contact_noble();
				break;
			case '3':
				action_hire_mercs();
				break;
		}
	} else if (!p.intown) {
		switch (response) {
			case '1':
				//action_setup_camp();
				break;
			case '2':
				//action_draft_letter();
				break;
		}
	}
	
	switch (response) {
		case 'i':
			action_view_inventory();
			break;
		case 'r':
			action_view_relations();
			break;
		case 'q':
			action_view_quests();
			break;
	}
}

int main(void)
{
	initscr();
	noecho();	
	curs_set(0);
	keypad(stdscr, TRUE);
	
	title_screen();

	int running = 1;
	while (running) {
		print_map(map, rows, columns);
		print_userinfo();
		print_actions();
		movement();
		refresh();
		clear();
	};

	endwin();

	return 0;
}

