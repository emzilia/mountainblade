#include <stdlib.h>
#include <ncurses.h>

#include "entities.h"
#include "actions.h"

void action_enter_city()
{
	clear();
	printw(
		"You approach the gates to the %s\nThe guard ushers"
		" your party through without complaint.",
		p.location);
	refresh();
	getch();

	int cityloop = 1;
	while (cityloop) {
		clear();
		printw(
			"%s\n\nWho would you like to see?\n\n"
			"1. Guild Master\n2. Tailor\n"
            "3. Blacksmith\n4. Stablekeeper",
			p.location
		);	
		refresh();
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
			case 'q':
				cityloop = 0;
				break;
		}
	}
}

void action_enter_city_guildmaster()
{
    clear();
	printw(
	    "Guild Master:      ($%d in your inventory)\n\nHello %s, "
        "how can we help you today?\n",
	    p.denars, p.name
    );
    refresh();
    getch();
}

void action_enter_city_tailor()
{
    clear();
	printw(
	    "Tailor:\n\nHello %s, "
        "how can we help you today?",
	    p.name
    );
    refresh();
    getch();
}

void action_enter_city_blacksmith()
{
    clear();
	printw(
	    "Blacksmith:\n\nHello %s, "
        "how can we help you today?",
	    p.name
    );
    refresh();
    getch();
}

void action_enter_city_stablekeeper()
{
    clear();
	printw(
	    "Stablekeeper:\n\nHello %s, "
        "how can we help you today?",
	    p.name
    );
    refresh();
    getch();
}

void action_contact_noble()
{
	clear();
	printw("You send your aid to the estate of the local\nnoble, hoping to arrange a meeting.");
	refresh();
	getch();
}

void action_hire_mercs()
{
	clear();
	printw("You send messengers to the local taverns,\nhoping to find some troops to hire.");
	refresh();
	getch();
}

void action_view_inventory()
{
	clear();
	printw("Notable trinkets:\n\nYour father's sword\nGold engraved locket");
	refresh();
	getch();
}

void action_view_relations()
{
	clear();
	printw("Relations:\n\n%s\n%s\n\n%s\n%s, %s\n\n%s\n%s\n\n%s\n%s\n\n%s\n%s\n",
		zander.noble, zander.location,
		talis.noble, talis.location, grelin.location,
		adriin.noble, adriin.location,
		doxoun.noble, doxoun.location,
		calia.noble, calia.location
	);
	refresh();
	getch();
}

void action_view_quests()
{
	clear();
	printw("Quests:\n\nDeliver letter to %s\n- For %s", zander.noble, adriin.noble);
	refresh();
	getch();
}
