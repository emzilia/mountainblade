#include <stdlib.h>
#include <ncurses.h>

#include "entities.h"
#include "actions.h"
#include "display.h"
#include "logic.h"

void action_enter_city(City* town)
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
		mvwprintw(win, 1, 0, "%s", town->wealthnote);
		mvwprintw(win, 4, 0, "Who would you like to see?");
		mvwprintw(win, 6, 0, "1. Guild Master");
		mvwprintw(win, 7, 0, "2. Tailor");
		mvwprintw(win, 8, 0, "3. Blacksmith");
		mvwprintw(win, 9, 0, "4. Stablekeeper");
		mvwprintw(win, 12, 0, "(b) to go back");
		int response = wgetch(win);
		switch (response) {
			case '1':
				action_enter_city_guildmaster(town);
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

void action_enter_city_guildmaster(City* town)
{
	wclear(win);
	int guildloop = 1;
	while (guildloop) {
		wprintw(win,
			"Guild Master:\n\nIt's good to see you %s, "
			"how can we help you\non this fine day?\n\nThere is work to do"
			", if you're interested...\n\n"
			"1. Accept some work\n2. Inquire about business\n\n(b) to go back",
			p.name
		);
		int response = wgetch(win);
		switch (response) {
			case '1':
				generate_quest2(town);
				wprintw(win, "\n\nGreat! I'll send the details over to your aid."); 
				wgetch(win);
				guildloop = 0;
				break;
			case '2':
				guildloop = 0;
				break;
			case 'b':
				guildloop = 0;
				break;
		};
	};
}

void action_enter_city_tailor()
{
	wclear(win);
	wprintw(win,
		"Tailor:\n\nGreetings %s, "
		"you have an impeccable style,\nbut if I may make some suggestions...",
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

void action_contact_noble(City* town)
{
	int contactloop = 1;

	while (contactloop) {
		wclear(win);
		wprintw(win, "You approach the estate of the local\nnoble, %s\n\n", town->owner->name);
		wprintw(win, "1. Request an audience\n2. Deliver a letter\n\n(b) to go back");
		int response = wgetch(win);
		switch (response) {
			case '1':
				generate_quest1(town);
				wprintw(win, "\n\nGreat! I'll send the details over to your aid."); 
				wgetch(win);
				contactloop = 0;
				break;
			case '2':
				break;
			case 'b':
				contactloop = 0;
				break;
		}
	}
}

void action_contact_noble_audience(City* town)
{
}

void action_hire_mercs(City* town)
{
	print_event("You send messengers to the local taverns,\nhoping to find some troops to hire.");
	if (town->iscity) action_hire_mercs_maa();
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
	if (cost > p.denars) {
		print_event("You can't afford that price right now.");
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
		print_event("You can't afford that price right now.");
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
	print_event("You order your troops to construct some\nhasty fortifications");
}

void action_draft_letter()
{
	wclear(win);
	wprintw(win, "You sit down to draft a letter, who will\nyou address it to?\n\n");
	for (size_t i = 0; i < allnobles.size; ++i) {
		wprintw(win, "%zu. %s\n", i + 1, allnobles.nobles[i]->name);	
	}
	int response = wgetch(win);
	switch (response) {
		case '1':
			logic_draft_letter(allnobles.nobles[0]);
			break;
		case '2':
			logic_draft_letter(allnobles.nobles[1]);
			break;
		case '3':
			logic_draft_letter(allnobles.nobles[2]);
			break;
		case '4':
			logic_draft_letter(allnobles.nobles[3]);
			break;
		case '5':
			logic_draft_letter(allnobles.nobles[4]);
			break;
		case '6':
			logic_draft_letter(allnobles.nobles[5]);
			break;
		case '7':
			logic_draft_letter(allnobles.nobles[6]);
			break;

	}
	wprintw(win, "\nYou finish drafting the letter and add it to your bag.");
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
	mvwprintw(win, 6, 0, "Level:\t %zu", p.level);
	mvwprintw(win, 16, 0, "Prowess: %zu", p.prowess);
	mvwprintw(win, 18, 0, "Kills:\t %d", p.kills);
	mvwprintw(win, 10, 0, "Renown:\t %d", p.renown);
	mvwprintw(win, 12, 0, "Honor:\t %d", p.honor);
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
			mvwprintw(
				win, row, 0, "%zu. %s  \t- %s\n", i + 1, 
				bag.items[i].name, bag.items[i].info
			);
			row += 3;
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
	if (allquests.totaldel == 0 && allquests.totalsla == 0) 
		wprintw(win, "You don't currently have any quests.\n\n");
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
				allquests.slayings[i].to_kill, allquests.slayings[i].giver->location
			);
		}
	}

	wgetch(win);
}

void action_enter_debug(User* p, Time* gtime)
{
	wclear(win);
	int debugloop = 1;
	while (debugloop) {
		wclear(win);
		wprintw(win,
			"debug menu\n\n"
			"1. give 125 denars\n2. advance time 1 month\n\n(b) to go back"
		);
		int response = wgetch(win);
		switch (response) {
			case '1':
				p->denars += 125;
				break;
			case '2':
				++gtime->month;
				break;
			case 'b':
				debugloop = 0;
				break;
		};
	};
}
