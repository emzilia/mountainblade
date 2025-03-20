#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <ncurses.h>

//int display(char *text);
void look();
void city_all();
void print_userinfo();

void action_enter_city();
void action_contact_noble();
void action_hire_mercs();
void action_view_inventory();
void action_view_relations();
void action_view_quests();

typedef struct {
	char name[6]; 
	size_t army;
	size_t charisma;
	int denars;
	char title[8];
	char location[20];
	int intown;
	int x;
	int y;
	int xy;
} User;

typedef struct {
	char name[7];
	char location[20];
	char noble[20];
	size_t pop;
	size_t danger;
	size_t wealth;
	int x;
	int y;
	int xy;
} City;

User p = {
	.name = "Elena",
	.army = 40,
	.charisma = 5,
	.denars = 120,
	.title = "Esquire",
	.x = 1,
	.y = 1,
};

const City zander = {
	.name = "Zander",
	.location = "Town of Zander",
	.noble = "Baron Balder",
	.pop = 3300,
	.danger = 5,
	.wealth = 3,
	.x = 2,
	.y = 2,
	.xy = 2 + 2,
};

const City talis = {
	.name = "Talis",
	.location = "City of Talis",
	.noble = "Marquise Alinna",
	.pop = 7430,
	.danger = 3,
	.wealth = 7,
	.x = 3,
	.y = 6,
	.xy = 3 + 6,
};

const City adriin = {
	.name = "Adriin",
	.location = "Castle of Adrin",
	.noble = "The Viscountess",
	.pop = 11570,
	.danger = 1,
	.wealth = 5,
	.x = 6,
	.y = 4,
	.xy = 6 + 4,
};

const City doxoun = {
	.name = "Doxoun",
	.location = "City of Doxoun",
	.noble = "Baroness Raegai",
	.pop = 5620,
	.danger = 7,
	.wealth = 9,
	.x = 6,
	.y = 1,
	.xy = 6 + 1,
};

const City calia = {
	.name = "Calia",
	.location = "Town of Calia",
	.noble = "Sir Kieran",
	.pop = 2350,
	.danger = 2,
	.wealth = 2,
	.x = 9,
	.y = 5,
	.xy = 9 + 5,
};

const City grelin = {
	.name = "Grelin",
	.location = "Town of Grelin",
	.noble = "Marquise Alinna",
	.pop = 870,
	.danger = 4,
	.wealth = 1,
	.x = 11,
	.y = 3,
	.xy = 11 + 3,
};

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

	getch();
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
	//printw(" %d, %d\n%d\n", p.x, p.y, p.xy);
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

void action_enter_city()
{
	clear();
	printw(
		"You approach the gates to the %s\nThe guard ushers"
		" your party through without complaint.",
		p.location);
	refresh();
	getch();

	int cityloop = 1;
	while (cityloop) {
		clear();
		printw(
			"%s\n\nWho would you like to see?\n\n"
			"1. Guild Master\n2. Blacksmith\n3. Stablekeeper",
			p.location
		);	
		refresh();
		int response = getch();
		switch (response) {
			case '1':
				clear();
				printw(
					"Guild Master:\n\n Hello %s, "
					"how can we help you today?",
					p.name
				);
				refresh();
				break;
			case '2':
				action_contact_noble();
				break;
			case 'q':
				cityloop = 0;
				break;
		}
	}
}

void action_contact_noble()
{
	clear();
	printw("You send your aid to the estate of the local\nnoble, hoping to arrange a meeting.");
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

void action_view_inventory()
{
	clear();
	printw("Notable trinkets:\n\nYour father's sword\nGold engraved locket");
	refresh();
	getch();
}

void action_view_relations()
{
	clear();
	printw("Relations:\n\n%s\n%s\n\n%s\n%s, %s\n\n%s\n%s\n\n%s\n%s\n\n%s\n%s\n",
		zander.noble, zander.location,
		talis.noble, talis.location, grelin.location,
		adriin.noble, adriin.location,
		doxoun.noble, doxoun.location,
		calia.noble, calia.location
	);
	refresh();
	getch();
}

void action_view_quests()
{
	clear();
	printw("Quests:\n\nDeliver letter to %s\n- For %s", zander.noble, adriin.noble);
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

