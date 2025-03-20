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
	wrefresh(win);
	getch();

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
		wrefresh(win);
		int response = getch();
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
	wrefresh(win);
	getch();
}

void action_enter_city_tailor()
{
	wclear(win);
	wprintw(win,
		"Tailor:\n\nHello %s, "
		"how can we help you today?",
		p.name
	);
	wrefresh(win);
	getch();
}

void action_enter_city_blacksmith()
{
	wclear(win);
	wprintw(win,
	"Blacksmith:\n\nHello %s, "
	"how can we help you today?",
	p.name
	);
	wrefresh(win);
	getch();
}

void action_enter_city_stablekeeper()
{
	wclear(win);
	wprintw(win,
	"Stablekeeper:\n\nHello %s, "
	"how can we help you today?",
	p.name
	);
	wrefresh(win);
	getch();
}

void action_contact_noble()
{
	wclear(win);
	wprintw(win, "You send your aid to the estate of the local\nnoble, hoping to arrange a meeting.");
	wrefresh(win);
	getch();
}

void action_hire_mercs()
{
	wclear(win);
	wprintw(win, "You send messengers to the local taverns,\nhoping to find some troops to hire.");
	wrefresh(win);
	getch();
}

void action_setup_camp()
{
	wclear(win);
	wprintw(win, "You send messengers to the local taverns,\nhoping to find some troops to hire.");
	wrefresh(win);
	getch();
}

void action_draft_letter()
{
	wclear(win);
	wprintw(win, "You send messengers to the local taverns,\nhoping to find some troops to hire.");
	wrefresh(win);
	getch();
}

void action_view_inventory()
{
	wclear(win);
	wprintw(win, "Notable trinkets:\n\nYour father's sword\nGold engraved locket");
	wrefresh(win);
	getch();
}

void action_view_relations()
{
	wclear(win);
	wprintw(win, "Relations:\n\n");
	for (size_t i = 0; i < allcities.size; ++i) {
		wprintw(win, "%s\n%s\n\n", allcities.cities[i].noble, allcities.cities[i].location);	
	}; 
	wrefresh(win);
	getch();
}

void action_view_quests()
{
	wclear(win);
	wprintw(win, "Quests:\n\nDeliver letter to %s\n- For %s", zander.noble, adriin.noble);
	wrefresh(win);
	getch();
}
