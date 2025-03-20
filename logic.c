#include <ncurses.h>
#include <string.h>

#include "entities.h"
#include "logic.h"

void init_citylist()
{
	allcities.cities[0] = zander;
	allcities.cities[1] = talis;
	allcities.cities[2] = adriin;
	allcities.cities[3] = doxoun;
	allcities.cities[4] = calia;
	allcities.cities[5] = grelin;
	allcities.cities[6] = amelo;
	allcities.cities[7] = yefhold;
	allcities.cities[8] = grii;
	allcities.cities[9] = todt;
	allcities.cities[10] = joeton;
	allcities.cities[11] = salls;
	allcities.size = 12;
}

int check_location(City town)
{
	if (p.x == town.x && p.y == town.y) {
		p.intown = 1;
		strcpy(p.location, town.location);
		return 1;
	}

	return 0;
}

void set_location()
{
	for (size_t i = 0; i < allcities.size; ++i) {
		p.intown = check_location(allcities.cities[i]);
		if (p.intown) break;
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
