#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

int display(char *text);
void look();
void city_all();

typedef struct {
	char name[6]; 
	size_t army;
	size_t charisma;
	int denars;
	char title[6];
	char location[14];
	int intown;
	size_t x;
	size_t y;
} User;

typedef struct {
	char name[6];
	size_t pop;
	size_t danger;
	size_t wealth;
	size_t x;
	size_t y;
} City;

City zander = {
	.name = "Zander",
	.pop = 22300,
	.danger = 5,
	.wealth = 3,
	.x = 2,
	.y = 2,
};

City talis = {
	.name = "Talis",
	.pop = 27400,
	.danger = 3,
	.wealth = 7,
	.x = 3,
	.y = 6,
};

City adriin = {
	.name = "Adriin",
	.pop = 38500,
	.danger = 1,
	.wealth = 5,
	.x = 6,
	.y = 4,
};

City doxoun = {
	.name = "Doxoun",
	.pop = 11600,
	.danger = 7,
	.wealth = 9,
	.x = 6,
	.y = 1,
};

City calia = {
	.name = "Calia",
	.pop = 2350,
	.danger = 2,
	.wealth = 2,
	.x = 9,
	.y = 5,
};

City grelin = {
	.name = "Grelin",
	.pop = 870,
	.danger = 4,
	.wealth = 1,
	.x = 11,
	.y = 3,
};


User p = {
	.name = '@',
	.army = 235,
	.charisma = 5,
	.denars = 450,
	.title = "Knight",
	.x = 1,
	.y = 1,
};

int posX = 1;
int posY = 1;

char map[8][14] = {
	"o============o",
	"|.....c......|",
	"|.t..........|",
	"|..........t.|",
	"|.....c......|",
	"|........t...|",
	"|..c.........|",
	"o============o"
};
	

int rows = sizeof(map) / sizeof(map[0]);
int columns = sizeof(map[0]) / sizeof(map[0][0]);

void title_screen()
{
	printw("Hello and welcome to Tania!");

	getch();
	clear();
}

void user_display()
{
	
}

void print_map(char arr[][14], int rows, int columns) {
	printw("Realm of Tania\n");
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			if (r == p.y && c == p.x)
				addch('@');
			else
				printw("%c", arr[r][c]);
		}
	addch('\n'); }
	//printw(" %zu, %zu\n", p.x, p.y);
	city_all();
	printw("Actions:\n");
}

int city_look(City town)
{
	if (p.x == town.x && p.y == town.y) {
		p.intown = 1;
		printw("City of %s\nPopulation of %zu\n\n", town.name, town.pop);
		printw("Your title is %s\n", p.title);
		printw("You have $%i in silver coins\n", p.denars);
		printw("You have %zu warriors in your band\n\n", p.army);	
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
	} else {
		p.intown = 0;
		printw("Plains of Castamere\n\n\n");
		printw("Your title is %s\n", p.title);
		printw("You have $%i in silver coins\n", p.denars);
		printw("You have %zu warriors in your band\n\n", p.army);
	}

}

void actions()
{
	if (p.intown) {
	printw("1. Enter city\n2. Contact nobleman"); 
	} else if (!p.intown) {
	printw("1. Setup fortified camp\n2. Draft correspondence");
	}
}

void movement()
{
	int response = getch();
	switch (response) {
		case KEY_UP:
			if (p.y > 1)
				p.y--;
			break;
		case KEY_DOWN:
			if (p.y < columns - 2)
				p.y++; 
			break;
		case KEY_LEFT:
			if (p.x > 1)
				p.x--;
			break;
		case KEY_RIGHT:
			if (p.x < columns - 2)
				p.x++;
			break;
	}
	
	if (p.intown) {
		switch (response) {
			case 1:
				//enter_city();
				break;
			case 2: 
				//contact_noble;
				break;
		}
	} else if (!p.intown) {
		switch (response) {
			case 1:
				//setup_camp();
				break;
			case 2:
				//draft_letter();
				break;
		}
	}
}

char *story1 = (
	"\n    Twelve hundred of Elara's roughest and most savage bandits\n"
	" have united under the banner of the fierce warrior Usagi. He has\n"
	" promised them the bounty of Tania's heartland and unopposed they\n"
	" threaten the prosperity of the realm.\n\n"
	"    Outriders have spotted their host lumbering down the windy\n"
	" Sari river. We estimate we have perhaps two weeks before the full\n"
	" weight of their forces are brought to bear upon us.\n\n"
	" \"We must adopt a plan of action. How do we proceed?\"\n\n"
	" \n\n\n Press enter to continue..."
);

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
		actions();
		movement();
		refresh();
		clear();
	};

	endwin();

	return 0;
}

