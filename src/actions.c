#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#include "entities.h"
#include "actions.h"
#include "display.h"
#include "logic.h"
#include "text.h"

void action_enter_city(City* town)
{
	event_city2.arg2 = town->desc;
	event_city2.arg3 = town->wealthnote;

	print_event_args1(event_city1.text, event_city1.arg1);
	int cityloop = 1;
	while (cityloop) {
		int response = print_event_args3(
			event_city2.text, 
			event_city2.arg1, 
			event_city2.arg2,
			event_city2.arg3
		);
		switch (response) {
			case '1':
				action_enter_city_gm(town);
				break;
			case '2':
				action_enter_city_ta();
				break;
			case '3':
				action_enter_city_bs();
				break;
			case '4':
				action_enter_city_sk();
				break;
			case 'b':
				cityloop = 0;
				break;
		}
	}
}

void action_enter_city_gm(City* town)
{
	event_city2_gm1_noquest.arg1 = town->gm;
	event_city2_gm1_yesquest.arg1 = town->gm;
	int guildloop = 1;
	while (guildloop) {
		int response;
		if (town->hassla == 0) {
			response = print_event_args2(
				event_city2_gm1_noquest.text,
				event_city2_gm1_noquest.arg1,
				event_city2_gm1_noquest.arg2
			);
		} else {
			response = print_event_args2(
				event_city2_gm1_yesquest.text,
				event_city2_gm1_yesquest.arg1,
				event_city2_gm1_yesquest.arg2
			);
		}
		switch (response) {
			case '1':
				generate_quest2(town);
				print_event_small(event_city2_gm1_small1.text, " ");
				guildloop = 0;
				break;
			case '2':
				print_event_small(event_city2_gm1_small2.text, " ");
				guildloop = 0;
				break;
			case '3':
				complete_quest(town, &bag, 2);
				print_event_small(event_city2_gm1_small3.text, " ");
				guildloop = 0;
				break;
			case 'b':
				guildloop = 0;
				break;
		}
	}
}

void action_enter_city_ta()
{
	print_event_args1(
		event_city2_ta1.text,
		event_city2_ta1.arg1
	);
}

void action_enter_city_bs()
{
	print_event_args1(
		event_city2_bs1.text,
		event_city2_bs1.arg1
	);
}

void action_enter_city_sk()
{
	print_event_args1(event_city2_sk1.text, event_city2_sk1.arg1);
}

void action_contact_noble(City* town)
{
	event_city2_nb1_noquest.arg1 = town->owner->name;
	event_city2_nb1_yesquest.arg1 = town->owner->name;
	int contactloop = 1;

	while (contactloop) {
		if (town->hasdel == 1) {
			int response = print_event_args1(
				event_city2_nb1_yesquest.text,
				event_city2_nb1_yesquest.arg1
			);
			switch (response) {
				case '1':
					print_event_small(event_city2_nb1_small1.text, " ");
					contactloop = 0;
					break;
				case '2':
					print_event_small(event_city2_nb1_yesquest_small1.text, " ");
					wgetch(win);
					complete_quest(town, &bag, 1);
					contactloop = 0;
					town->hasdel = 0;
					break;
				case 'b':
					contactloop = 0;
					break;
			}
		} else {
			int response = print_event_args1(
				event_city2_nb1_yesquest.text,
				event_city2_nb1_yesquest.arg1
			);
			char* recipient;
			switch (response) {
				case '1':
					print_event_small(event_city2_nb1_small1.text, " ");
					contactloop = 0;
					break;
				case '2':
					recipient = generate_quest1(town);
					event_city2_nb1_noquest_small1.arg1 = recipient;
					print_event_small(
						event_city2_nb1_noquest_small1.text,
						event_city2_nb1_noquest_small1.arg1
					);
					contactloop = 0;
					break;
				case 'b':
					contactloop = 0;
					break;

			}
		}
	}
}

void action_contact_noble_audience(City* town)
{
}

void action_hire_mercs(City* town)
{
	print_event(event_merc.text, event_merc.arg1);
	if (town->iscity) action_hire_mercs_maa();
	else action_hire_mercs_peasants();
}

void action_hire_mercs_peasants()
{
	int peasants = (rand() % 3) + 2;
	int cost = peasants * 5;
	int weeklycost = peasants * party.pspearupkeep;

	char* str_peasants = convert_string(peasants);
	char* str_cost = convert_string(cost);
	char* str_weeklycost =  convert_string(weeklycost);
	char* str_denars =  convert_string(p.denars);

	event_merc_p1.arg1 = str_peasants;
	event_merc_p1.arg2 = str_cost;
	event_merc_p1.arg3 = str_weeklycost;
	event_merc_p1.arg4 = str_denars;

	int response = print_event_args4(
		event_merc_p1.text,
		event_merc_p1.arg1,
		event_merc_p1.arg2,
		event_merc_p1.arg3,
		event_merc_p1.arg4
	);

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
		print_event("You can't afford that price right now.", "to continue");
		return;
	}
	int chance = rand() % 11;
	if (chance > 2) {
		party.pspear += peasants;
		werase(win);
		wprintw(win, " %i %s have joined your party.", peasants, party.pspearname);
		if (debug) wprintw(win, "\n\n DEBUG: %i/10\n", chance);
		wgetch(win);
	} else { 
		party.pbow += peasants;
		werase(win);
		wprintw(win, " %i %s have joined your party.", peasants, party.pbowname);
		if (debug) wprintw(win, "\n\n DEBUG: %i/10\n", chance);
		wgetch(win);
	}
	p.denars -= cost;
}

void action_hire_mercs_maa()
{
	int maa = (rand() % 3) + 2;
	int cost = maa * 15;
	int weeklycost = maa * party.maaupkeep;
	werase(win);
	wprintw(win, 
		"%i veteran soldiers are seeking work.\n\n"
		"It'll cost %i denars to equip them,\nas well as an extra %d denars weekly.\n(Your total: %i)\n\n"
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
		print_event("You can't afford that price right now.", "to continue");
		return;
	}
	party.maa += maa;
	werase(win);
	wprintw(win, " %i %s have joined your party.", maa, party.maaname);
	wgetch(win);
	p.denars -= cost;
}

void action_setup_camp()
{
	print_event("You order your troops to construct some\nhasty fortifications", "to continue");
	werase(win);
	int camploop = 1;
	while (camploop) {
		werase(win);
		wprintw(win, 
			"Fortified Camp\n\n"
			"Your troops are waiting in defensive positions.\n\n1. Wait some time\n2. Break camp\n"
		);
		print_time();
		int response = wgetch(win);
		switch (response) {
			case '1':
				advance_hour(&gtime, 1);
				break;
			case '2':
				camploop = 0;
				break;
		}
	}
}

void action_draft_letter()
{
	int letterloop = 1;
	werase(win);
	wprintw(win, "You sit down to draft a letter, who will\nyou address it to?\n\n");
	for (int i = 0; i < allnobles.size; ++i) {
		wprintw(win, "%d. %s\n", i + 1, allnobles.nobles[i]->name);	
	}
	mvwprintw(win, 14, 0, "(b) to go back");
	while (letterloop) {
		int response = wgetch(win);
		switch (response) {
			case '1':
				letterloop = 0;
				logic_draft_letter(allnobles.nobles[0]);
				print_event("You carefully write out the letter and\n"
						"stow it in your bag", "to continue..."
				);
				break;
			case '2':
				letterloop = 0;
				logic_draft_letter(allnobles.nobles[1]);
				print_event("You carefully write out the letter and\n"
						"stow it in your bag", "to continue..."
				);
				break;
			case '3':
				letterloop = 0;
				logic_draft_letter(allnobles.nobles[2]);
				print_event("You carefully write out the letter and\n"
						"stow it in your bag", "to continue..." 
				);
				break;
			case '4':
				letterloop = 0;
				logic_draft_letter(allnobles.nobles[3]);
				print_event("You carefully write out the letter and\n"
						"stow it in your bag", "to continue..." 
				);
				break;
			case '5':
				letterloop = 0;
				logic_draft_letter(allnobles.nobles[4]);
				print_event("You carefully write out the letter and\n"
						"stow it in your bag", "to continue..." 
				);
				break;
			case '6':
				letterloop = 0;
				logic_draft_letter(allnobles.nobles[5]);
				print_event("You carefully write out the letter and\n"
						"stow it in your bag", "to continue..."  
				);
				break;
			case '7':
				letterloop = 0;
				logic_draft_letter(allnobles.nobles[6]);
				print_event("You carefully write out the letter and\n"
						"stow it in your bag", "to continue..."  
				);
				break;
			case 'b':
				letterloop = 0;
				break;
		}
	}
}


void action_view_party()
{
	werase(win);
	wprintw(win, "Party:\nYourself, of course\n\nCompanions:\n");
	for (int i = 0; i < buddies.size; ++i) wprintw(win, "%s\n", buddies.buddies[i].name);
	wprintw(win, "\nTroops:\n");
	if ((party.maa > 0)) {
		for (int i = 0; i < buddies.size; ++i) {
			wprintw(win, "%dx Men-at-arms\n", party.maa);
		}
	}
	if ((party.pspear > 0)) {
		for (int i = 0; i < buddies.size; ++i) {
			wprintw(win, "%dx Peasant spearmen\n", party.pspear);
		}
	}
	if ((party.pbow > 0)) {
		for (int i = 0; i < buddies.size; ++i) {
			wprintw(win, "%dx Peasant bowmen", party.pbow);
		}
	}
	wprintw(win, "\n\nTotal: %d", buddies.size + party.maa + party.pspear + party.pbow + 1);
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
	int characterloop = 1;
	werase(win);
	mvwprintw(win, 0, 0, "Character Info:");
	mvwprintw(win, 2, 0, "Name:\t %s", p.name);
	mvwprintw(win, 4, 0, "Rank:\t %s", p.title);
	mvwprintw(win, 6, 0, "Level:\t %d", p.level);
	mvwprintw(win, 8, 0, "XP:\t %d", p.xp);
	mvwprintw(win, 12, 0, "Renown:\t %d", p.renown);
	mvwprintw(win, 14, 0, "Honor:\t %d", p.honor);
	mvwprintw(win, 18, 0, "Prowess: %d", p.prowess);
	mvwprintw(win, 20, 0, "Kills:\t %d", p.kills);
	mvwprintw(win, 24, 0, "(b) to go back");
	while (characterloop) {
		int response = wgetch(win);
		switch (response) {
			case 'b':
				characterloop = 0;
				break;
		}
	}
}

void action_view_inventory()
{
	int inventoryloop = 1;
	int row;
	werase(win);
	mvwprintw(win, 0, 0, "Inventory:");
	if (bag.size == 0) { 
		row = 4;
		mvwprintw(win, 2, 0, "Your bag is currently empty.");
	} else {
		row = 2;
		for (int i = 0; i < bag.size; ++i) {
			mvwprintw(
				win, row, 0, "%d. %s  \t- %s\n", i + 1, 
				bag.items[i].name, bag.items[i].info
			);
			row += 3;
		}

	};
	mvwprintw(win, (row + 2), 0, "(b) to go back");
	while (inventoryloop) {
		int response = wgetch(win);
		switch (response) {
			case 'b':
				inventoryloop = 0;
				break;
		}
	}
}

void action_view_relations()
{
	int relationloop = 1;
	werase(win);
	wprintw(win, "Relevant Nobles:\n\n");
	for (int i = 0; i < allnobles.size; ++i) {
		Noble* noble = allnobles.nobles[i];
		wprintw(win, "%s\t\t      Relations: %d\n", noble->name, noble->relations);	
		for (int f = 0; f < noble->totalfiefs; ++f) {
			wprintw(win, "\t - %s\n", (*allnobles.nobles[i]).fiefs[f]->location);
		}; 
		wprintw(win, "\n");
	};
	wprintw(win, "\n\n(b) to go back");		
	while (relationloop) {
		int response = wgetch(win);
		switch (response) {
			case 'b':
				relationloop = 0;
				break;
		}
	}
}

void action_view_quests()
{
	int questloop = 1;
	werase(win);
	wprintw(win, "Current Quests:\n\n");
	if (allquests.totaldel == 0 && allquests.totalsla == 0) 
		wprintw(win, "You don't currently have any quests.\n\n");
	if (allquests.totaldel > 0) {
		for (int i = 0; i < allquests.totaldel; ++i) {
			wprintw(
				win, "Deliver a letter to %s\n\t- From %s\n\n", 
				allquests.deliveries[i].target->name, allquests.deliveries[i].giver->name
			);
			if (debug) wprintw(win, "\tQuestID: %d\n\n", allquests.deliveries[i].questid);
		}
	}
	if (allquests.totalsla > 0) {
		for (int i = 0; i < allquests.totalsla; ++i) {
			wprintw(
				win, "Slay %i bandits on the road\n\t- For %s\n\n", 
				allquests.slayings[i].to_kill, allquests.slayings[i].giver->location
			);
		}
	}
	wprintw(win, "\n\n(b) to go back");
	while (questloop) {
		int response = wgetch(win);
		switch (response) {
			case 'b':
				questloop = 0;
				break;
		}
	}

}

void action_view_debug(User* player, Time* gametime)
{
	werase(win);
	int debugloop = 1;
	while (debugloop) {
		wprintw(win,
		"debug menu\n\n"
		"d. view debug stats\n\n"
		"1. give 125 denars\n2. advance time 1 month\n3. teleport randomly\n"
		"4. get stronger\n5. kill a peasant with your bare hands\n"
		"6. increase renown\n"
		"7. payout weekly wages\n\n(b) to go back\n\n"
		);

		//werase(win);
		int response = wgetch(win);
		switch (response) {
			case 'd':
				action_view_debug_stats(player, gametime);
				break;
			case '1':
				wprintw(win, "money money money\t\t--> + $125 = $%d\n\npress any key to continue...",
					player->denars + 125);
				player->denars += 125;
				wgetch(win);
				werase(win);
				break;
			case '2':
				advance_month(gametime, 1);
				wprintw(win, "time flies...\t\t\t--> + 1 = %d\n\npress any key to continue...",
					gametime->month);
				wgetch(win);
				werase(win);
				break;
			case '3':
				player->x = (rand() % 25) + 1;
				player->y = (rand() % 5) + 1;
				wprintw(win, "wait what\t\t\t--> %d, %d\n\npress any key to continue...",
					player->x, player->y);
				wgetch(win);
				werase(win);
				break;
			case '4':
				wprintw(win, "i can BREAK these cuffs\t\t--> %d + 1 = %d\n\npress any key to continue...",
					player->prowess, player->prowess + 1);
				player->prowess += 1;
				wgetch(win);
				werase(win);
				break;
			case '5':
				wprintw(win, "nasty business, had to be done\t--> + 1 = %d\n\npress any key to continue...",
					player->kills + 1);
				player->kills += 1;
				wgetch(win);
				werase(win);
				break;
			case '6':
				wprintw(win, "basically, kind of a big deal\t --> + 5 = %d\n\npress any key to continue...",
					player->renown += 5);
				player->renown += 5;
				wgetch(win);
				werase(win);
				break;
			case '7':
				weekly_partyupkeep(player);
				//break; simpler without
			case 'b':
				debugloop = 0;
				break;
			default:
				werase(win);
				break;
		};
	};
}

void action_view_debug_stats(User* player, Time* gametime)
{
	werase(win);
	int debugloop = 1;
	while (debugloop) {
		werase(win);
		wprintw(win,
			"debug stats\n\n"
			"1. cities\n"
			"2. nobles\n"
			"3. quests\n"
			"4. player"
			"\n\n(b) to go back"
		);
		int response = wgetch(win);
		switch (response) {
			case 'b':
				debugloop = 0;
				werase(win);
				break;
			case '1':
				action_view_debug_cities();
				break;
			case '2':
				action_view_debug_nobles();
				break;
			case '3':
				action_view_debug_quests();
				break;
			case '4':
				action_view_debug_player();
				break;
		}
	}
	
}

void action_view_debug_cities()
{
	int counter = 0;
	werase(win);
	int debugloop = 1;
	while (debugloop) {
		if (counter == 11) counter = 0;
		werase(win);
		wprintw(win, "City ID: \t%d\n\n", counter);
		wprintw(win, "Name: \t\t%s\n", allcities.cities[counter]->name);
		wprintw(win, "Owner: \t\t%s\n", allcities.cities[counter]->owner->name);
		wprintw(win, "Location: \t%s\n", allcities.cities[counter]->location);
		wprintw(win, "GM: \t\t%s\n", allcities.cities[counter]->gm);
		wprintw(win, "WealthNote: \t\t%s\n", allcities.cities[counter]->wealthnote);
		wprintw(win, "Pop: \t\t%d\n", allcities.cities[counter]->pop);
		wprintw(win, "Danger: \t%d\n", allcities.cities[counter]->danger);
		wprintw(win, "Wealth: \t%d\n", allcities.cities[counter]->wealth);
		wprintw(win, "IsCity: \t%d\n", allcities.cities[counter]->iscity);
		wprintw(win, "X: \t\t%d\n", allcities.cities[counter]->x);
		wprintw(win, "Y: \t\t%d\n", allcities.cities[counter]->y);
		wprintw(win, "HasDel: \t%d\n", allcities.cities[counter]->hasdel);
		wprintw(win, "HasSla: \t%d\n", allcities.cities[counter]->hassla);
		wprintw(win, "\n1. next city\n\n(b) to go back");
		int response = wgetch(win);
		switch (response) {
			case 'b':
				debugloop = 0;
				break;
			case '1':
				counter += 1;
				break;
		}
	}
}

void action_view_debug_nobles()
{
	int counter = 0;
	werase(win);
	int debugloop = 1;
	while (debugloop) {
		if (counter == 7) counter = 0;
		werase(win);
		wprintw(win, "Noble ID: \t%d\n\n", counter);
		wprintw(win, "Name: \t\t%s\n", allnobles.nobles[counter]->name);
		wprintw(win, "TotalFiefs: \t%d\n", allnobles.nobles[counter]->totalfiefs);
		wprintw(win, "Relations: \t%d\n", allnobles.nobles[counter]->relations);
		wprintw(win, "\n1. next noble\n\n(b) to go back");
		int response = wgetch(win);
		switch (response) {
			case 'b':
				debugloop = 0;
				break;
			case '1':
				counter += 1;
				break;
		}
	}
	
}

void action_view_debug_quests()
{
	int counter = 0;
	werase(win);
	int debugloop = 1;
	while (debugloop) {
		werase(win);
		if (counter == allquests.totaldel) counter = 0;
		if (counter == allquests.totalsla) counter = 0;
		wprintw(win, "TotalDel: %d\n\n", allquests.totaldel);
		wprintw(win, "TotalSla: %d\n\n", allquests.totalsla);
		if (allquests.totaldel >= 1) {
			wprintw(win, "Counter: \t%d\n\n", counter);
			wprintw(win, "QuestID: \t%d\n", allquests.deliveries[counter].questid);
			wprintw(win, "RenownGain: \t%d\n", allquests.deliveries[counter].renown_gain);
			wprintw(win, "RelationBuff: \t%d\n", allquests.deliveries[counter].relation_buff);
			wprintw(win, "Giver: \t\t%s\n", allquests.deliveries[counter].giver->name);
			wprintw(win, "Target: \t%s\n\n", allquests.deliveries[counter].target->name);
			if (allquests.totalsla < 1) wprintw(win, "\n1. next quest\n\n(b) to go back");
		}
		if (allquests.totalsla >= 1) {
			wprintw(win, "Counter: \t%d\n\n", counter);
			wprintw(win, "QuestID: \t%d\n", allquests.slayings[counter].questid);
			wprintw(win, "RenownGain: \t%d\n", allquests.slayings[counter].renown_gain);
			wprintw(win, "RelationBuff: \t%d\n", allquests.slayings[counter].relation_buff);
			wprintw(win, "Giver: \t\t%s\n", allquests.slayings[counter].giver->name);
			wprintw(win, "StartingKills: \t%d\n", allquests.slayings[counter].starting_kills);
			wprintw(win, "ToKill: \t%d\n", allquests.slayings[counter].to_kill);
			wprintw(win, "\n1. next quest\n\n(b) to go back");
		}
		int response = wgetch(win);
		switch (response) {
			case 'b':
				debugloop = 0;
				break;
			case '1':
				counter += 1;
				werase(win);
				break;
		}
	}
	
}

void action_view_debug_player()
{
	werase(win);
	int debugloop = 1;
	while (debugloop) {
		werase(win);
		wprintw(win, "Player Attributes: \n\n"); 
		wprintw(win, "name: \t\t%s\n", p.name);
		wprintw(win, "title: \t\t%s\n", p.title);
		wprintw(win, "season: \t%s\n", p.season);
		wprintw(win, "level: \t\t%d\n", p.level);
		wprintw(win, "xp: \t\t%d\n", p.xp);
		wprintw(win, "prowess: \t%d\n", p.prowess);
		wprintw(win, "army: \t\t%d\n", p.army);
		wprintw(win, "armycap: \t%d\n", p.armycap);
		wprintw(win, "charisma: \t%d\n", p.charisma);
		wprintw(win, "denars: \t%d\n", p.denars);
		wprintw(win, "renown: \t%d\n", p.renown);
		wprintw(win, "honor: \t\t%d\n", p.honor);
		wprintw(win, "kills: \t\t%d\n", p.kills);
		wprintw(win, "intown: \t%d\n", p.intown);
		wprintw(win, "x \t\t%d\n", p.x);
		wprintw(win, "y \t\t%d\n", p.y);
		int response = wgetch(win);
		switch (response) {
			case 'b':
				debugloop = 0;
				break;
		}
	}
}