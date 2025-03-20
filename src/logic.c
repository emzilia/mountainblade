#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "entities.h"
#include "logic.h"
#include "display.h"
#include "actions.h"
#include "gtime.h"
#include "text.h"

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
		if (diff == 1) wprintw(win, "Dissatisfied, %i man has deserted the party", diff); 
		else wprintw(win, "Dissatisfied, %i men have deserted the party", diff); 
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
	sprintf(change, "%d", party.totalupkeep);
	int wagesloop = 1;
	wclear(win);
	print_event_args("Weekly wages have been paid out: %s denars\n\n(b) to accept begrudgingly", change);
	while (wagesloop) {
		int response = wgetch(win);
		switch (response) {
			case 'b':
				wagesloop = 0;
				break;
		}
	}
	p->denars -= party.totalupkeep;
}

// check if user is in a town or not. if so, copy over the location string
int check_location(City* town, User* p)
{
	if (p->x == town->x && p->y == town->y) {
		strcpy(p->location, town->location);
		return 1;
	}

	return 0;
}

// if user is in a town, set it as the currenttown and calc some city flavor text
void set_location(User* p)
{
	for (int i = 0; i < allcities.size; ++i) {
		p->intown = check_location(allcities.cities[i], p);
		if (p->intown) {
			currenttown = *allcities.cities[i];
			calc_city_wealth(&currenttown);
			break;
		}	
	}
}

City currenttown;

// based on city wealth attribute, print some flavor text
void calc_city_wealth(City* city)
{
	char wealth3[100] = "The streets are bustling with laborers and\ntraders going about their daily business.";
	char wealth2[100] = "The streets are quiet and well-kept, the\nlocals seem content.";
	char wealth1[100] = "The streets are dirty and the locals squint at\nyou with suspicious eyes.";

	if (city->wealth > 0 || city->wealth < 4) strncpy(city->wealthnote, wealth1, 100); 
	if (city->wealth > 4 || city->wealth < 8) strncpy(city->wealthnote, wealth2, 100); 
	if (city->wealth > 8) strncpy(city->wealthnote, wealth3, 100); 
	//strncpy(event_city2.arg2, city->wealthnote, 100);
}

// set users rank daily based on their renown
// TODO maybe only check rank when renown changes?
void set_user_rank(User* player)
{
	char rank1[20] = "Esquire";
	char rank2[20] = "Knight";
	char rank3[20] = "Baron";
	char rank4[20] = "Viscount";
	char rank5[20] = "Duke";

	if (player->renown >= 0 && player->renown < 75) strncpy( player->title, rank1, (sizeof(player->title) - 1));	
	if (player->renown > 75 && player->renown < 200) strncpy( player->title, rank2, (sizeof(player->title) - 1));	
	if (player->renown > 200 && player->renown < 400) strncpy( player->title, rank3, (sizeof(player->title) - 1));	
	if (player->renown > 400 && player->renown < 600) strncpy( player->title, rank4, (sizeof(player->title) - 1));	
	if (player->renown > 600) strncpy( player->title, rank5, (sizeof(player->title) - 1));	

	if (!strcmp(player->title, rank2)) p.armycap = 75;
	if (!strcmp(player->title, rank3)) p.armycap = 150;
	if (!strcmp(player->title, rank4)) p.armycap = 350;
	if (!strcmp(player->title, rank5)) p.armycap = 500;

	player->title[sizeof(player->title) - 1] = '\0';
}

// add any item object to any inventory object with a cap
void add_to_inventory(Inventory* inventory, Item* thing)
{
	if (inventory->size < 10) {
		inventory->items[inventory->size] = *thing;
		++inventory->size;
	} else {
		print_event("The inventory is full.", "to continue");
	}
}

// self explanatory
int generate_unique_questid()
{
	// generates a random number to id the quest
	// if it generates a number that's already being used,
	// the function is run recursively until a unique value is chosen
	int questid = (rand() % 100);
	for (int i = 0; i < allquests.totaldel; ++i) {
		if (allquests.deliveries[i].questid == questid) {
			questid = generate_unique_questid();
		}
	}

	return questid;
}

// generate delivery quest
char* generate_quest1(City* city)
{
	// max of 4 delivery quests at a time
	if (allquests.totaldel > 4) return city->owner->name;
	
	// target is random, if its the questgiver then its someone else
	int questtarget = (rand() % 7);
	if (allnobles.nobles[questtarget] == city->owner)
		--questtarget;

	// generate a random number as a simple identifier
	int questid = generate_unique_questid();

	// delivery quest is generated
	Quest1 latestdel = {
		.renown_gain = 3,
		.relation_buff = 1,
		.questid = questid,
		.giver = city->owner,	
		.target = allnobles.nobles[questtarget],
	};

	// quest target is given a flag to accept delivery
	allnobles.nobles[questtarget]->fiefs[0]->hasdel = 1;

	allquests.deliveries[allquests.totaldel] = latestdel;
	++allquests.totaldel;

	// quest item is generated
	Item quest_letter = {
		.questid = questid,
		.name = "Elegant Letter",
		.info = "Bearing noble insignia",
		.recipient1 = city->owner,
	};

	add_to_inventory(&bag, &quest_letter);

	// returns the name of the quest targer
	return allnobles.nobles[questtarget]->name;
}

// generate bandit slaying quest
void generate_quest2(City* town)
{
	// loops through the whole city list to ensure we're operating
	// on the global city struct
	int city;
	for (int i = 0; i < allcities.size; ++i) {
		if (!strcmp(allcities.cities[i]->name, town->name)) {
			city = i;
		}
	};

	// max of 4 bandit slaying quests at a time
	if (allquests.totalsla > 4) return;
	
	// random amount of bandits to kill
	int questtarget = (rand() % 5) + 3;

	// random id to id the quest
	int questid = generate_unique_questid();

	// bandit slaying quests are given by city guildmasters
	Quest2 latestsla = {
		.starting_kills = p.kills,
		.to_kill = questtarget,
		.questid = questid,
		.renown_gain = 3,
		.relation_buff = 1,
		.giver = allcities.cities[city],	
	};

	// city given a flag to denote the active quest
	allcities.cities[city]->hassla = 1;

	// quest is added to quest list
	allquests.slayings[allquests.totalsla] = latestsla;
	++allquests.totalsla;
}

// turn in either a delivery or slaying quest
void complete_quest(City* city, Inventory* bag, int num)
{
	// if turning in a delivery quest
	if (num == 1)
		// first we loop through the current delivery quest list
		for (int i = 0; i < allquests.totaldel; ++i) {
			// then we loop through the user's inventory
			for (int j = 0; j < bag->size; ++j) {
				// we're looking for an inventory item with a questid that matches the
				// questid of a current quest, if nothing found, don't do anything
				// if there's a match, remove it from both the quest list and inventory
				if (allquests.deliveries[i].questid == bag->items[i].questid) {
					for(int k = j; k < allquests.totaldel - 1; ++k) {
						allquests.deliveries[k] = allquests.deliveries[k + 1];
					}
					--allquests.totaldel;
					for(int k = j; k < bag->size - 1; ++k) {
						bag->items[k] = bag->items[k + 1];
					}
					--bag->size;

					// remove quest target's flag
					allquests.deliveries[i].target->fiefs[0]->hasdel = 0;

					// after quest is complete, increase relations with quest giver
					allquests.deliveries[i].giver->relations += allquests.deliveries[i].relation_buff;
				}
			}
		}
	// else if turning in a slaying quest
	else if (num == 2)
		// first we loop through the current slaying quest list
		for (int i = 0; i < allquests.totalsla; ++i) {
			// we add the target number of kills specified in the quest
			// to the number of kills the player had at the start of the quest
			// if the player currently has more kills, complete the quest
			// pretty dumb placeholder logic
			if (allquests.slayings[i].starting_kills + allquests.slayings[i].to_kill
					>= p.kills) {
				for(int j = 0; j < allquests.totalsla - 1; ++j) {
					allquests.slayings[i] = allquests.slayings[i + 1];
				}
				--allquests.totalsla;
				// after quest is complete, increase relations with quest giver
				allquests.slayings[i].giver->owner->relations += allquests.slayings[i].relation_buff;
			}
		}
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
