#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

int display(char *text);
void look();
void city_all();
void print_userinfo();

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
	char name[7];
	char location[15];
	char noble[15];
	size_t pop;
	size_t danger;
	size_t wealth;
	size_t x;
	size_t y;
} City;

const City zander = {
	.name = "Zander",
	.location = "Town of Zander",
	.noble = "Lord Balder",
	.pop = 22300,
	.danger = 5,
	.wealth = 3,
	.x = 2,
	.y = 2,
};

const City talis = {
	.name = "Talis",
	.location = "City of Talis",
	.noble = "Lady Alinna",
	.pop = 27400,
	.danger = 3,
	.wealth = 7,
	.x = 3,
	.y = 6,
};

const City adriin = {
	.name = "Adriin",
	.location = "City of Adriin",
	.noble = "Lady Merisa",
	.pop = 38500,
	.danger = 1,
	.wealth = 5,
	.x = 6,
	.y = 4,
};

const City doxoun = {
	.name = "Doxoun",
	.location = "City of Doxoun",
	.noble = "Lord Raegan",
	.pop = 11600,
	.danger = 7,
	.wealth = 9,
	.x = 6,
	.y = 1,
};

const City calia = {
	.name = "Calia",
	.location = "Town of Calia",
	.noble = "Lord Kieran",
	.pop = 2350,
	.danger = 2,
	.wealth = 2,
	.x = 9,
	.y = 5,
};

const City grelin = {
	.name = "Grelin",
	.location = "Town of Grelin",
	.noble = "Lady Alinna",
	.pop = 870,
	.danger = 4,
	.wealth = 1,
	.x = 11,
	.y = 3,
};


User p = {
	.name = '@',
	.army = 40,
	.charisma = 5,
	.denars = 120,
	.title = "Knight",
	.x = 1,
	.y = 1,
};

int posX = 1;
int posY = 1;

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

void action_enter_city()
{
	clear();
	printw("You approach the settlement gates and present\nyourself to the guard. He ushers your party\nthrough without complaint.");
	refresh();
	getch();
}

void action_hire_mercs()
{
	clear();
	printw("You send messengers to the local taverns,\nhoping to find some troops to hire.");
	refresh();
	getch();
}

void movement()
{
	int response = getch();
	switch (response) {
		case 'k':
		case KEY_UP:
			if (p.y > 1)
				p.y--;
			break;
		case 'j':
		case KEY_DOWN:
			if (p.y < rows - 2)
				p.y++; 
			break;
		case 'h':
		case KEY_LEFT:
			if (p.x > 1)
				p.x--;
			break;
		case 'l':
		case KEY_RIGHT:
			if (p.x < columns - 2)
				p.x++;
			break;
	}
	
	if (p.intown) {
		switch (response) {
			case '1':
				action_enter_city();
				break;
			case 2: 
				//action_contact_noble();
				break;
			case '3':
				action_hire_mercs();
				break;
		}
	} else if (!p.intown) {
		switch (response) {
			case 1:
				//action_setup_camp();
				break;
			case 2:
				//action_draft_letter();
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
		print_userinfo();
		print_actions();
		movement();
		refresh();
		clear();
	};

	endwin();

	return 0;
}

