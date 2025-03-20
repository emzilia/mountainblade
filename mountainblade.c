#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

int display(char *text);
void look();

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
	.pop = 45000,
	.danger = 5,
	.wealth = 3,
	.x = 2,
	.y = 2,
};

City talis = {
	.name = "Talis",
	.pop = 103000,
	.danger = 3,
	.wealth = 7,
	.x = 3,
	.y = 6,
};

City adriin = {
	.name = "Adriin",
	.pop = 122500,
	.danger = 1,
	.wealth = 5,
	.x = 6,
	.y = 4,
};

City doxoun = {
	.name = "Doxoun",
	.pop = 241000,
	.danger = 7,
	.wealth = 9,
	.x = 6,
	.y = 1,
};

City calia = {
	.name = "Calia",
	.pop = 23500,
	.danger = 2,
	.wealth = 2,
	.x = 9,
	.y = 5,
};

City grelin = {
	.name = "Grelin",
	.pop = 12000,
	.danger = 4,
	.wealth = 1,
	.x = 11,
	.y = 3,
};

char user = '@';
size_t army = 235;

int posX = 1;
int posY = 1;

char map[8][16] = {
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

void main_display()
{
	char world[6] = "Tania";
	printw("Hello and welcome to %s", world);

	getch();
	clear();
}

void print2DArray(char arr[][16], int rows, int columns) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			if (r == posY && c == posX)
				addch('@');
			else
				printw("%c", arr[r][c]);
		}
	addch('\n');
	}
	//printw(" %d, %d\n", posX, posY);
	look();
}

void look()
{
	if (posX == zander.x && posY == zander.y) {
		printw("Town of %s\nPopulation of %zu\n\n", zander.name, zander.pop);	
		printw("You have %zu warriors in your band", army);
	} else if (posX == talis.x && posY == talis.y) {
		printw("City of %s\nPopulation of %zu\n\n", talis.name, talis.pop);	
		printw("You have %zu warriors in your band", army);
	} else if (posX == adriin.x && posY == adriin.y) {
		printw("City of %s\nPopulation of %zu\n\n", adriin.name, adriin.pop);	
		printw("You have %zu warriors in your band", army);
	} else if (posX == doxoun.x && posY == doxoun.y) {
		printw("City of %s\nPopulation of %zu\n\n", doxoun.name, doxoun.pop);	
		printw("You have %zu warriors in your band", army);
	} else if (posX == calia.x && posY == calia.y) {
		printw("Town of %s\nPopulation of %zu\n\n", calia.name, calia.pop);	
		printw("You have %zu warriors in your band", army);
	} else if (posX == grelin.x && posY == grelin.y) {
		printw("Town of %s\nPopulation of %zu\n\n", grelin.name, grelin.pop);	
		printw("You have %zu warriors in your band", army);

	} else {
		printw("Plains of Castamere\n\n\n");
		printw("You have %zu warriors in your band", army);
	}
	
}

void movement()
{
	int response = getch();

	switch (response) {
		case KEY_UP:
			if (posY > 1)
				posY--;
			break;
		case KEY_DOWN:
			if (posY < columns - 2)
				posY++; 
			break;
		case KEY_LEFT:
			if (posX > 1)
				posX--;
			break;
		case KEY_RIGHT:
			if (posX < columns - 2)
				posX++;
			break;
	}
}



char *story0 = (
	"\n Siege of Tania\n\n A feudal management simulator\n\n\n\n\n\n\n\n"
	" Press enter to continue..."
);

char *story1 = (
	"\n    Twelve hundred of Elara's roughest and most savage bandits\n"
	" have united under the banner of the fierce warrior Usagi. He has\n"
	" promised them the bounty of Tania's heartland and unopposed they\n"
	" threaten the prosperity of the realm.\n\n"
	"    Outriders have spotted their host lumbering down the windy\n"
	" Sari river. We estimate we have perhaps two weeks before the full\n"
	" weight of their forces are brought to bear upon us.\n\n"
	" \"We must adopt a plan of action. How do we proceed, Princess?\"\n\n"
	" Oh bother. You're going to need more tea. \"Assemble the council.\""
	" \n\n\n Press enter to continue..."
);

int main(void)
{
	initscr();
	noecho();	
	curs_set(0);
	keypad(stdscr, TRUE);
	
	main_display();

	int running = 1;
	while (running) {
		print2DArray(map, rows, columns);
		movement();
		refresh();
		clear();
	};

	endwin();

	return 0;
}

