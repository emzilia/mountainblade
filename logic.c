#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "entities.h"
#include "logic.h"
#include "display.h"
#include "actions.h"

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
		if (p.intown) {
			currenttown = allcities.cities[i];
			calc_city_wealth(&currenttown);
			break;
		}	
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

City currenttown;

void calc_city_wealth(City* city)
{
	char wealth1[35] = "The local economy is booming";
	char wealth2[35] = "The local economy is alright";
	char wealth3[35] = "The local economy sucks dick";

	if (city->wealth > 8) strcpy(city->wealthnote, wealth1); 
	if (city->wealth > 4 && city->wealth < 8) strcpy(city->wealthnote, wealth2); 
	if (city->wealth < 4) strcpy(city->wealthnote, wealth3); 
}

void set_user_rank()
{
	if (allranks.rank == 1) strcpy( p.title, "Esquire");	
}
