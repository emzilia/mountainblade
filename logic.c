#include <ncurses.h>
#include <string.h>

#include "entities.h"
#include "logic.h"

int check_location(City town)
{
	if (p.x == town.x && p.y == town.y) {
		p.intown = 1;
		strcpy(p.location, town.location);
		printw("%s\nPopulation of %zu\n\n", town.location, town.pop);
		return 1;
	}
	return 0;
}

void set_location()
{
	if (check_location(zander)) {
		return;
	} else if (check_location(talis)) {
		return;
	} else if (check_location(adriin)) {
		return;
	} else if (check_location(doxoun)) {
		return;
	} else if (check_location(calia)) {
		return;
	} else if (check_location(grelin)) {
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
