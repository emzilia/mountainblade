#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "entities.h"
#include "logic.h"
#include "display.h"
#include "actions.h"

void init_citylist()
{
	allcities.cities[0] = &zander;
	allcities.cities[1] = &adriin;
	allcities.cities[2] = &doxoun;
	allcities.cities[3] = &calia;
	allcities.cities[4] = &grelin;
	allcities.cities[5] = &amelo;
	allcities.cities[6] = &yefhold;
	allcities.cities[7] = &grii;
	allcities.cities[8] = &todt;
	allcities.cities[9] = &joeton;
	allcities.cities[10] = &salls;
	allcities.size = 11;
}

void init_noblelist()
{
	allnobles.nobles[0] = &viscountess;
	viscountess.fiefs[0] = &adriin;
	viscountess.fiefs[1] = &grii;

	allnobles.nobles[1] = &alinna;
	alinna.fiefs[0] = &yefhold;
	alinna.fiefs[1] = &grelin;

	allnobles.nobles[2] = &nazia;
	nazia.fiefs[0] = &joeton;

	allnobles.nobles[3] = &raegai;
	raegai.fiefs[0] = &doxoun;

	allnobles.nobles[4] = &torace;
	torace.fiefs[0] = &amelo;
	torace.fiefs[1] = &salls;

	allnobles.nobles[5] = &balder;
	balder.fiefs[0] = &zander;

	allnobles.nobles[6] = &usoro;
	usoro.fiefs[0] = &todt;

	allnobles.nobles[7] = &kieran;
	kieran.fiefs[0] = &calia;


	allnobles.size = 8;
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
	if (party.total > p.armycap) {
		int diff = party.total - p.armycap;
		party.pspear -= diff;

		wclear(win);
		if (diff == 1) wprintw(win, "Disatisfied, %i man has deserted the party", diff); 
		else wprintw(win, "Disatisfied, %i men have deserted the party", diff); 
		wgetch(win);
		wclear(win);

		party.total = party.maa + party.pspear + party.pbow + buddies.size;
	}
	party.totalupkeep = (party.maa * party.maaupkeep) + (party.pspear * party.pspearupkeep) + (party.pbow * party.pbowupkeep);
}

int check_location(City* town)
{
	if (p.x == town->x && p.y == town->y) {
		p.intown = 1;
		strcpy(p.location, town->location);
		return 1;
	}

	return 0;
}

void set_location()
{
	for (size_t i = 0; i < allcities.size; ++i) {
		p.intown = check_location(allcities.cities[i]);
		if (p.intown) {
			currenttown = *allcities.cities[i];
			calc_city_wealth(&currenttown);
			break;
		}	
	}
}

City currenttown;

void calc_city_wealth(City* city)
{
	char wealth3[100] = "The streets are bustling with laborers and\ntraders going about their daily business.";
	char wealth2[100] = "The streets are quiet but well-kept and the\nlocals seem content.";
	char wealth1[100] = "The streets are dirty and the locals squint at\nyou with suspicious eyes.";

	if (city->wealth > 8) strcpy(city->wealthnote, wealth3); 
	if (city->wealth > 4 && city->wealth < 8) strcpy(city->wealthnote, wealth2); 
	if (city->wealth < 4) strcpy(city->wealthnote, wealth1); 
}

void set_user_rank(User* list)
{
	if (list->renown > 0) strcpy( p.title, "Esquire");	
			if (list->renown > 75) strcpy( p.title, "Knight");	
				if (list->renown > 200) strcpy( p.title, "Baron");	
					if (list->renown > 400) strcpy( p.title, "Viscount");	

	if (!strcmp(p.title, "Knight")) p.armycap = 75;
	if (!strcmp(p.title, "Baron")) p.armycap = 150;
	if (!strcmp(p.title, "Viscount")) p.armycap = 350;
}
