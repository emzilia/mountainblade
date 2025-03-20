#include <stdlib.h>
#include <ncurses.h>

#include "entities.h"
#include "actions.h"
#include "display.h"
#include "logic.h"

void action_enter_city(City town)
{
	werase(win);
	mvwprintw(win, 0, 0,
		"You approach the gates to the %s\nThe guard ushers"
		" your party through without\ncomplaint.",
		p.location);
	wgetch(win);

	int cityloop = 1;
	while (cityloop) {
		werase(win);
		mvwprintw(win, 0, 0, "%s", p.location);
		mvwprintw(win, 1, 0, "%s", town.wealthnote);
		mvwprintw(win, 4, 0, "Who would you like to see?");
		mvwprintw(win, 6, 0, "1. Guild Master");
		mvwprintw(win, 7, 0, "2. Tailor");
		mvwprintw(win, 8, 0, "3. Blacksmith");
		mvwprintw(win, 9, 0, "4. Stablekeeper");
		mvwprintw(win, 12, 0, "(b) to go back");
		int response = wgetch(win);
		switch (response) {
			case '1':
				action_enter_city_guildmaster();
				generate_quest1(&town);
				break;
			case '2':
				action_enter_city_tailor();
				break;
			case '3':
				action_enter_city_blacksmith();
				break;
			case '4':
				action_enter_city_stablekeeper();
				generate_quest2(&town);
				break;
			case 'b':
				cityloop = 0;
				break;
			case 'm':
				if (debug) {
					p.denars += 125;
					wprintw(win, "\nshow me the money\n");
					wgetch(win);
				}
				break;
		}
	}
}

void action_enter_city_guildmaster()
{
	wclear(win);
	wprintw(win,
		"Guild Master:\n\nIt's good to see you %s, "
		"how can we help you\non this fine day?\n",
		p.name
	);
	wgetch(win);
}

void action_enter_city_tailor()
{
	wclear(win);
	wprintw(win,
		"Tailor:\n\nGreetings %s, "
		"you have an impeccable style, but\nif I may make some suggestions...",
		p.name
	);
	wgetch(win);
}
void action_enter_city_blacksmith()
{
	wclear(win);
	wprintw(win,
	"Blacksmith:\n\nHello %s, "
	"we have arms and armor that would be\nmost suitable for you.",
	p.name
	);
	wgetch(win);
}

void action_enter_city_stablekeeper()
{
	wclear(win);
	wprintw(win,
	"Stablekeeper:\n\nHowdy %s, "
	"interested in the finest horses in\nthe realm?",
	p.name
	);
	wgetch(win);
}

void action_contact_noble()
{
	wclear(win);
	wprintw(win, "You send your aid to the estate of the local\nnoble, hoping to arrange a meeting.");
	wgetch(win);
}

void action_hire_mercs(City town)
{
	wclear(win);
	wprintw(win, "You send messengers to the local taverns,\nhoping to find some troops to hire.");
	wgetch(win);
	if (town.iscity) action_hire_mercs_maa();
	else action_hire_mercs_peasants();
	wgetch(win);
}

void action_hire_mercs_peasants()
{
	int peasants = (rand() % 3) + 2;
	int cost = peasants * 5;
	size_t weeklycost = peasants * party.pspearupkeep;
	wprintw(win, 
		"\n\n%i locals seem adventurous enough.\n\n"
		"It'll cost %i denars to equip them,\nas well as an extra %zu denars weekly.\n(Your total: %i)\n\n"
		"How does that sound?\n\n1. Sure thing\n2. No thanks\n",
		peasants, cost, weeklycost, p.denars
	);
	int response = wgetch(win);
	switch (response) {
		case '1':
			action_hire_mercs_peasants_yes(peasants, cost);
			break;
		case '2':
			break;
	}
}

void action_hire_mercs_peasants_yes(int peasants, int cost)
{
	if (cost > p.denars) {
		wclear(win);
		wprintw(win, "You can't afford that price right now.");
		wgetch(win);
		return;
	}
	int chance = rand() % 11;
	if (chance > 2) {
		party.pspear += peasants;
		wclear(win);
		wprintw(win, " %i %s have joined your party.", peasants, party.pspearname);
		if (debug) wprintw(win, "\n%i\n", chance);
		wgetch(win);
	} else { 
		party.pbow += peasants;
		wclear(win);
		wprintw(win, " %i %s have joined your party.", peasants, party.pbowname);
		if (debug) wprintw(win, "\n%i\n", chance);
		wgetch(win);
	}
	p.denars -= cost;
}

void action_hire_mercs_maa()
{
	int maa = (rand() % 3) + 2;
	int cost = maa * 15;
	size_t weeklycost = maa * party.maaupkeep;
	wprintw(win, 
		"\n\n%i veteran soldiers are seeking work.\n\n"
		"It'll cost %i denars to equip them,\nas well as an extra %zu denars weekly.\n(Your total: %i)\n\n"
		"How does that sound?\n\n1. Sure thing\n2. No thanks\n",
		maa, cost, weeklycost, p.denars
	);
	int response = wgetch(win);
	switch (response) {
		case '1':
			action_hire_mercs_maa_yes(maa, cost);
			break;
		case '2':
			break;
	}

}

void action_hire_mercs_maa_yes(int maa, int cost)
{
	if (cost > p.denars) {
		wclear(win);
		wprintw(win, "You can't afford that price right now.");
		wgetch(win);
		return;
	}
	party.maa += maa;
	wclear(win);
	wprintw(win, " %i %s have joined your party.", maa, party.maaname);
	wgetch(win);
	p.denars -= cost;
}

void action_setup_camp()
{
	wclear(win);
	wprintw(win, "You send messengers to the local taverns,\nhoping to find some troops to hire.");
	wgetch(win);
}

void action_draft_letter()
{
	wclear(win);
	wprintw(win, "You send messengers to the local taverns,\nhoping to find some troops to hire.");
	wgetch(win);
}

void action_view_party()
{
	wclear(win);
	wprintw(win, "Your party:\nYourself, of course\n\nCompanions:\n");
	for (size_t i = 0; i < buddies.size; ++i) wprintw(win, "%s\n", buddies.buddies[i].name);
	wprintw(win, "\nTroops:\n");
	if (!(party.maa == 0)) for (size_t i = 0; i < buddies.size; ++i) wprintw(win, "%zux Men-at-arms\n", party.maa);
	if (!(party.pspear == 0)) for (size_t i = 0; i < buddies.size; ++i) wprintw(win, "%zux Peasant spearmen\n", party.pspear);
	if (!(party.pbow == 0))for (size_t i = 0; i < buddies.size; ++i) wprintw(win, "%zux Peasant bowmen", party.pbow);
	wprintw(win, "\n\nTotal: %zu", buddies.size + party.maa + party.pspear + party.pbow + 1);
	wprintw(win, "\n\n\n\nPress (b) to go back");
	int partyloop = 1;
	while (partyloop) {
		int response = wgetch(win);		
		switch (response) {
			case 'b': 
				partyloop = 0;
		}
	}
}

void action_view_character()
{
	wclear(win);
	mvwprintw(win, 0, 0, "Character Info:");
	mvwprintw(win, 2, 0, "Name:\t %s", p.name);
	mvwprintw(win, 4, 0, "Rank:\t %s", p.title);
	mvwprintw(win, 6, 0, "Renown:\t %d", p.renown);
	mvwprintw(win, 8, 0, "Honor:\t %d", p.honor);
	mvwprintw(win, 10, 0, "Level:\t %zu", p.level);
	mvwprintw(win, 12, 0, "Prowess: %zu", p.prowess);
	wgetch(win);
}

void action_view_inventory()
{
	wclear(win);
	mvwprintw(win, 0, 0, "Notable trinkets:");
	if (bag.size == 0) { 
		mvwprintw(win, 2, 0, "Your bag is currently empty.");
	} else {
		int row = 2;
		for (size_t i = 0; i < bag.size; ++i) {
			mvwprintw(win, row, 0, "%zu. %s\t%s", i + 1, bag.items[i].name, bag.items[i].info);
			row += 2;
		}

	};
	wgetch(win);
}

void action_view_relations()
{
	wclear(win);
	wprintw(win, "Relevant Nobles:\n\n");
	for (size_t i = 0; i < allnobles.size; ++i) {
		Noble* noble = allnobles.nobles[i];
		wprintw(win, "%s\n", noble->name);	
		for (size_t f = 0; f < noble->totalfiefs; ++f) {
			wprintw(win, "\t - %s\n", (*allnobles.nobles[i]).fiefs[f]->location);
		}; 
		wprintw(win, "\n");
	};
	wgetch(win);
	add_to_inventory(&bag, &sword1);
}

void action_view_quests()
{
	wclear(win);
	wprintw(win, "Quests:\n\n");
	if (allquests.totaldel > 0) {
		for (size_t i = 0; i < allquests.totaldel; ++i) {
			wprintw(
				win, "Deliver a letter to %s\n\t- From %s\n\n", 
				allquests.deliveries[i].target->name, allquests.deliveries[i].giver->name
			);
		}
	}
	if (allquests.totalsla > 0) {
		for (size_t i = 0; i < allquests.totalsla; ++i) {
			wprintw(
				win, "Slay %i bandits on the road\n\t- For %s\n\n", 
				allquests.slayings[i].to_kill, allquests.slayings[i].giver->name
			);
		}
	}

	wgetch(win);
}
