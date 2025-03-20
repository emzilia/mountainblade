#include <stdlib.h>
#include <ncurses.h>

#include "entities.h"
#include "actions.h"
#include "display.h"
#include "logic.h"

void action_enter_city(City town)
{
	werase(win);
	wprintw(win,
		"You approach the gates to the %s\nThe guard ushers"
		" your party through without\ncomplaint.",
		p.location);
	wgetch(win);

	int cityloop = 1;
	while (cityloop) {
		werase(win);
		wprintw(win,
			"%s\n%s\n\nWho would you like to see?\n\n"
			"1. Guild Master\n2. Tailor\n"
			"3. Blacksmith\n4. Stablekeeper\n"
			"\n(b) to go back",
			p.location, town.wealthnote
		);	
		int response = wgetch(win);
		switch (response) {
			case '1':
				action_enter_city_guildmaster();
				break;
			case '2':
				action_enter_city_tailor();
				break;
			case '3':
				action_enter_city_blacksmith();
				break;
			case '4':
				action_enter_city_stablekeeper();
				break;
			case 'b':
				cityloop = 0;
				break;
		}
	}
}

void action_enter_city_guildmaster()
{
	wclear(win);
	wprintw(win,
		"Guild Master:      ($%d in your inventory)\n\nHello %s, "
		"how can we help you today?\n",
		p.denars, p.name
	);
	wgetch(win);
}

void action_enter_city_tailor()
{
	wclear(win);
	wprintw(win,
		"Tailor:\n\nHello %s, "
		"how can we help you today?",
		p.name
	);
	wgetch(win);
}
void action_enter_city_blacksmith()
{
	wclear(win);
	wprintw(win,
	"Blacksmith:\n\nHello %s, "
	"how can we help you today?",
	p.name
	);
	wgetch(win);
}

void action_enter_city_stablekeeper()
{
	wclear(win);
	wprintw(win,
	"Stablekeeper:\n\nHello %s, "
	"how can we help you today?",
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
	wprintw(win, "Your party:\n\nCompanions:\n");
	for (size_t i = 0; i < buddies.size; ++i) wprintw(win, "%s\n", buddies.buddies[i].name);
	wprintw(win, "\nTroops:\n");
	for (size_t i = 0; i < buddies.size; ++i) wprintw(win, "%zux Men-at-arms\n", party.maa);
	for (size_t i = 0; i < buddies.size; ++i) wprintw(win, "%zux Peasant spearmen\n", party.pspear);
	for (size_t i = 0; i < buddies.size; ++i) wprintw(win, "%zux Peasant bowmen", party.pbow);
	wprintw(win, "\n\nTotal: %zu", buddies.size + party.maa + party.pspear + party.pbow);
	wgetch(win);
}

void action_view_inventory()
{
	wclear(win);
	wprintw(win, "Notable trinkets:\n\nYour father's sword\nGold engraved locket");
	wgetch(win);
}

void action_view_relations()
{
	wclear(win);
	wprintw(win, "Relations:\n\n");
	for (size_t i = 0; i < allcities.size; ++i) {
		wprintw(win, "%s\n%s\n\n", allcities.cities[i].noble, allcities.cities[i].location);	
	}; 
	wgetch(win);
}

void action_view_quests()
{
	wclear(win);
	wprintw(win, "Quests:\n\nDeliver letter to %s\n- For %s", zander.noble, adriin.noble);
	wgetch(win);
}
