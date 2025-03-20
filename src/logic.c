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
	allcities.cities[0] = &zander;
	zander.owner = &balder;

	allcities.cities[1] = &adriin;
	adriin.owner = &viscountess;

	allcities.cities[2] = &doxoun;
	doxoun.owner = &raegai;

	allcities.cities[3] = &calia;
	calia.owner = &kieran;

	allcities.cities[4] = &grelin;
	grelin.owner = &usoro;

	allcities.cities[5] = &amelo;
	amelo.owner = &torace;
		
	allcities.cities[6] = &yefhold;
	yefhold.owner = &viscountess;

	allcities.cities[7] = &grii;
	grii.owner = &viscountess;

	allcities.cities[8] = &todt;
	todt.owner = &alinna;

	allcities.cities[9] = &joeton;
	joeton.owner = &alinna;

	allcities.cities[10] = &salls;
	salls.owner = &torace;

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

void init_buddylist(BuddyList* buddies)
{
	buddies->size = 1;
	buddies->buddies[0] = gren;
}

void init_partylist(PartyList* party)
{
	party->maa = 3;
	party->maaupkeep = 10;

	party->pspear = 4;
	party->pspearupkeep = 2;

	party->pbow = 4;
	party->pbowupkeep = 2;

	strcpy(party->maaname, "Men-at-arms");
	strcpy(party->pspearname, "Peasant spearmen");
	strcpy(party->pbowname, "Peasant bowmen");

	party->total = party->maa + party->pspear + party->pbow + buddies.size + 1;
}

void init_gamelists()
{
	init_citylist();
	init_noblelist();
	init_buddylist(&buddies);
	init_partylist(&party);
}

void move_north(User* p)
{
	int timebonus = 0;
	if (!strcmp(p->season, "Winter")) timebonus = 1;

	if (p->y > 1) {
		p->y--;
		advance_hour(&gtime, (rand() % 2) + 2 + timebonus);
	}
}

void move_south(User* p)
{
	int timebonus = 0;
	if (!strcmp(p->season, "Winter")) timebonus = 1;

	if (p->y < rows - 2) {
		p->y++;
		advance_hour(&gtime, (rand() % 2) + 2 + timebonus);
	}
}

void move_west(User* p)
{
	int timebonus = 0;
	if (!strcmp(p->season, "Winter")) timebonus = 1;

	if (p->x > 1) {
		p->x--;
		advance_hour(&gtime, (rand() % 2) + 2 + timebonus);
	}
}

void move_east(User* p)
{
	int timebonus = 0;
	if (!strcmp(p->season, "Winter")) timebonus = 1;

	if (p->x < columns - 2) {
		p->x++;
		advance_hour(&gtime, (rand() % 2) + 2 + timebonus);
	}
}

void update_partyupkeep(PartyList* party)
{
	party->total = party->maa + party->pspear + party->pbow + buddies.size + 1;
	if (party->total > p.armycap) {
		int diff = party->total - p.armycap;
		party->pspear -= diff;

		wclear(win);
		if (diff == 1) wprintw(win, "Disatisfied, %i man has deserted the party", diff); 
		else wprintw(win, "Disatisfied, %i men have deserted the party", diff); 
		wgetch(win);
		wclear(win);

		party->total = party->maa + party->pspear + party->pbow + buddies.size + 1;
	}
	party->totalupkeep = (
		(party->maa * party->maaupkeep) +
		(party->pspear * party->pspearupkeep) +
		(party->pbow * party->pbowupkeep)
	);
}

void weekly_partyupkeep(User* p)
{
	char change[6];
	sprintf(change, "%zu", party.totalupkeep);
	int wagesloop = 1;
	while (wagesloop) {
		wclear(win);
		print_event_args("Weekly wages have been paid out: %s denars\n\n(b) to go back", change);
		int response = wgetch(win);
		switch (response) {
			case 'b':
				wagesloop = 0;
				break;
		}
	}
	p->denars -= party.totalupkeep;
}

int check_location(City* town, User* p)
{
	if (p->x == town->x && p->y == town->y) {
		p->intown = 1;
		strcpy(p->location, town->location);
		return 1;
	}

	return 0;
}

void set_location(User* p)
{
	for (size_t i = 0; i < allcities.size; ++i) {
		p->intown = check_location(allcities.cities[i], p);
		if (p->intown) {
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
	char rank1[20] = "Esquire";
	char rank2[20] = "Knight";
	char rank3[20] = "Baron";
	char rank4[20] = "Viscount";

	if (list->renown > 0) strncpy( list->title, rank1, (sizeof(list->title) - 1));	
	if (list->renown > 75) strncpy( list->title, rank2, (sizeof(list->title) - 1));	
	if (list->renown > 200) strncpy( list->title, rank3, (sizeof(list->title) - 1));	
	if (list->renown > 400) strncpy( list->title, rank4, (sizeof(list->title) - 1));	

	if (!strcmp(list->title, rank2)) p.armycap = 75;
	if (!strcmp(list->title, rank3)) p.armycap = 150;
	if (!strcmp(list->title, rank4)) p.armycap = 350;

	list->title[sizeof(list->title) - 1] = '\0';
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

char* generate_quest1(City* city)
{
	if (allquests.totaldel > 4) return city->owner->name;
	
	size_t questtarget = (rand() % 7);
	if (allnobles.nobles[questtarget] == city->owner)
		--questtarget;

	int questid = (rand() % 200);

	Quest1 latestdel = {
		.renown_gain = 3,
		.relation_buff = 1,
		.questid = questid,
		.giver = city->owner,	
		.target = allnobles.nobles[questtarget],
	};

	allnobles.nobles[questtarget]->fiefs[0]->hasdel = 1;

	allquests.deliveries[allquests.totaldel] = latestdel;
	++allquests.totaldel;

	Item quest_letter = {
		.questid = questid,
		.name = "Elegant Letter",
		.info = "Bearing noble insignia",
		.recipient1 = city->owner,
	};

	add_to_inventory(&bag, &quest_letter);

	return allnobles.nobles[questtarget]->name;

}

void complete_quest(City* city, Inventory* bag, int num)
{
	if (num == 1)
		for (size_t i = 0; i < allquests.totaldel; ++i) {
			for (size_t j = 0; j < bag->size; ++j) {
				if (allquests.deliveries[i].questid == bag->items[i].questid) {
					for(size_t k = j; k < allquests.totaldel - 1; ++k) {
						allquests.deliveries[k] = allquests.deliveries[k + 1];
					}
					--allquests.totaldel;
					for(size_t k = j; k < bag->size - 1; ++k) {
						bag->items[k] = bag->items[k + 1];
					}
					--bag->size;

					city->owner->relations += allquests.deliveries[i].relation_buff;
				}
			}
		}
	else if (num == 2)
		for (size_t i = 0; i < allquests.totaldel; ++i) {
			if (allquests.deliveries[i].target == bag->items[i].recipient1) {
			}
		}
}

void generate_quest2(City* city)
{
	if (allquests.totalsla > 4) return;
	
	int questtarget = (rand() % 5) + 3;

	Quest2 latestsla = {
		.renown_gain = 3,
		.relation_buff = 1,
		.giver = city,	
		.to_kill = questtarget,
	};

	city->hassla = 2;

	allquests.slayings[allquests.totalsla] = latestsla;
	++allquests.totalsla;

	Item writ_justice = {
		.name = "Writ for Justice",
		.info = "By local authority",
		.recipient2 = city,
	};


	add_to_inventory(&bag, &writ_justice);
}

void logic_draft_letter(Noble* noble)
{
	Item letter = {
		.name = "Formal Letter",
		.info = "Written in fine hand",
		.recipient1 = noble,
	};

	add_to_inventory(&bag, &letter);
}
