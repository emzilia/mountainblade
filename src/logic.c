#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "entities.h"
#include "logic.h"
#include "display.h"
#include "actions.h"
#include "gtime.h"

void init_citylist()
{
	zander.owner = &balder;
	allcities.cities[0] = &zander;

	adriin.owner = &viscountess;
	allcities.cities[1] = &adriin;

	doxoun.owner = &raegai;
	allcities.cities[2] = &doxoun;

	calia.owner = &kieran;
	allcities.cities[3] = &calia;

	grelin.owner = &usoro;
	allcities.cities[4] = &grelin;

	amelo.owner = &torace;
	allcities.cities[5] = &amelo;
		
	yefhold.owner = &viscountess;
	allcities.cities[6] = &yefhold;

	grii.owner = &viscountess;
	allcities.cities[7] = &grii;

	todt.owner = &alinna;
	allcities.cities[8] = &todt;

	joeton.owner = &alinna;
	allcities.cities[9] = &joeton;

	salls.owner = &torace;
	allcities.cities[10] = &salls;

	allcities.size = 11;
}

void init_noblelist()
{
	viscountess.fiefs[0] = &adriin;
	viscountess.fiefs[1] = &grii;
	viscountess.fiefs[2] = &yefhold;
	allnobles.nobles[0] = &viscountess;

	alinna.fiefs[0] = &joeton;
	alinna.fiefs[1] = &todt;
	allnobles.nobles[1] = &alinna;

	raegai.fiefs[0] = &doxoun;
	allnobles.nobles[2] = &raegai;

	torace.fiefs[0] = &amelo;
	torace.fiefs[1] = &salls;
	allnobles.nobles[3] = &torace;

	balder.fiefs[0] = &zander;
	allnobles.nobles[4] = &balder;

	usoro.fiefs[0] = &grelin;
	allnobles.nobles[5] = &usoro;

	kieran.fiefs[0] = &calia;
	allnobles.nobles[6] = &kieran;

	allnobles.size = 7;
}

void init_buddylist()
{
	buddies.buddies[0] = gren;
	buddies.size = 1;
}

void init_partylist()
{
	party.maa = 3;
	party.maaupkeep = 10;
	strcpy(party.maaname, "Men-at-arms");

	party.pspear = 4;
	party.pspearupkeep = 2;
	strcpy(party.pspearname, "Peasant spearmen");

	party.pbow = 4;
	party.pbowupkeep = 2;
	strcpy(party.pbowname, "Peasant bowmen");

	party.total = party.maa + party.pspear + party.pbow + buddies.size + 1;
}

void init_gamelists()
{
	init_citylist();
	init_noblelist();
	init_buddylist();
	init_partylist();
}

void move_north()
{
	if (p.y > 1) {
		p.y--;
		advance_hour((rand() % 2) + 2);
	}
}

void move_south()
{
	if (p.y < rows - 2) {
		p.y++;
		advance_hour((rand() % 2) + 2);
	}
}

void move_west()
{
	if (p.x > 1) {
		p.x--;
		advance_hour((rand() % 2) + 2);
	}
}

void move_east()
{
	if (p.x < columns - 2) {
		p.x++;
		advance_hour((rand() % 2) + 2);
	}
}

void update_partyupkeep()
{
	party.total = party.maa + party.pspear + party.pbow + buddies.size + 1;
	if (party.total > p.armycap) {
		int diff = party.total - p.armycap;
		party.pspear -= diff;

		wclear(win);
		if (diff == 1) wprintw(win, "Disatisfied, %i man has deserted the party", diff); 
		else wprintw(win, "Disatisfied, %i men have deserted the party", diff); 
		wgetch(win);
		wclear(win);

		party.total = party.maa + party.pspear + party.pbow + buddies.size + 1;
	}
	party.totalupkeep = (
		(party.maa * party.maaupkeep) +
		(party.pspear * party.pspearupkeep) +
		(party.pbow * party.pbowupkeep)
	);
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
	char wealth2[100] = "The streets are quiet and well-kept, the\nlocals seem content.";
	char wealth1[100] = "The streets are dirty and the locals squint at\nyou with suspicious eyes.";

	if (city->wealth > 0) strcpy(city->wealthnote, wealth1); 
		if (city->wealth > 4) strcpy(city->wealthnote, wealth2); 
			if (city->wealth > 8) strcpy(city->wealthnote, wealth3); 
}

void set_user_rank(User* list)
{
	if (list->renown > 0) strcpy( list->title, "Esquire");	
			if (list->renown > 75) strcpy( list->title, "Knight");	
				if (list->renown > 200) strcpy( list->title, "Baron");	
					if (list->renown > 400) strcpy( list->title, "Viscount");	

	if (!strcmp(list->title, "Knight")) p.armycap = 75;
	if (!strcmp(list->title, "Baron")) p.armycap = 150;
	if (!strcmp(list->title, "Viscount")) p.armycap = 350;
}

void add_to_inventory(Inventory* inventory, Item* thing)
{
	if (bag.size < 10) {
		bag.items[bag.size] = *thing;
		++bag.size;
	} else {
		print_event("The inventory is full.");
	}
}

void generate_quest1(City* city)
{
	if (allquests.totaldel > 4) return;
	
	int questtarget = (rand() % 7);

	Quest1 latestdel = {
		.giver = city->owner,	
		.target = allnobles.nobles[questtarget],
		.renown_gain = 3,
		.relation_buff = 1,
	};

	allquests.deliveries[allquests.totaldel] = latestdel;
	++allquests.totaldel;
}

void generate_quest2(City* city)
{
	if (allquests.totalsla > 4) return;
	
	int questtarget = (rand() % 5) + 3;

	Quest2 latestsla = {
		.giver = city->owner,	
		.to_kill = questtarget,
		.renown_gain = 3,
		.relation_buff = 1,
	};

	allquests.slayings[allquests.totalsla] = latestsla;
	++allquests.totalsla;
}
