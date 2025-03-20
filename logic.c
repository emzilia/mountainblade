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
	allcities.cities[1] = adriin;
	allcities.cities[2] = doxoun;
	allcities.cities[3] = calia;
	allcities.cities[4] = grelin;
	allcities.cities[5] = amelo;
	allcities.cities[6] = yefhold;
	allcities.cities[7] = grii;
	allcities.cities[8] = todt;
	allcities.cities[9] = joeton;
	allcities.cities[10] = salls;
	allcities.size = 11;
}

void init_buddylist()
{
	buddies.buddies[0] = gren;
	buddies.size = 1;
}

void init_partylist()
{
	party.maa = 4;
	party.maaupkeep = 10;
	strcpy(party.maaname, "Men-at-arms");

	party.pspear = 4;
	party.pspearupkeep = 2;
	strcpy(party.pspearname, "Peasant spearmen");

	party.pbow = 4;
	party.pbowupkeep = 2;
	strcpy(party.pbowname, "Peasant bowmen");

	party.total = party.maa + party.pspear + party.pbow + buddies.size;
}

void update_partyupkeep()
{
	party.total = party.maa + party.pspear + party.pbow + buddies.size;
	party.totalupkeep = (party.maa * party.maaupkeep) + (party.pspear * party.pspearupkeep) + (party.pbow * party.pbowupkeep);
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

void set_user_rank(User* list)
{
	if (list->rank == 1) strcpy( p.title, "Esquire");	
	if (list->rank == 2) strcpy( p.title, "Knight");	
	if (list->rank == 3) strcpy( p.title, "Baron");	
	if (list->rank == 4) strcpy( p.title, "Viscount");	

	if (!strcmp(p.title, "Knight")) p.armycap = 75;
	if (!strcmp(p.title, "Baron")) p.armycap = 150;
	if (!strcmp(p.title, "Viscount")) p.armycap = 350;
}
