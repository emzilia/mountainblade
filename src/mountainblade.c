#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "actions.h"
#include "entities.h"
#include "display.h"
#include "logic.h"
#include "gtime.h"
#include "text.h"

int debug = 0;

void input_mainloop()
{
	int response = wgetch(win);
	switch (response) {
		case 'k': case KEY_UP:
			move_north(&p);
			break;
		case 'j': case KEY_DOWN:
			move_south(&p);
			break;
		case 'h': case KEY_LEFT:
			move_west(&p);
			break;
		case 'l': case KEY_RIGHT:
			move_east(&p);
			break;
	}
	
	if (p.intown) {
		switch (response) {
			case '1':
				action_enter_city(&currenttown);
				break;
			case '2': 
				action_contact_noble(&currenttown);
				break;
			case '3':
				action_hire_mercs(&currenttown);
				break;
		}
	} else if (!p.intown) {
		switch (response) {
			case '1':
				action_setup_camp();
				break;
			case '2':
				action_draft_letter();
				break;
		}
	}
	
	switch (response) {
		case 'c':
			action_view_character();
			break;
		case 'p':
			action_view_party();
			break;
		case 'i':
			action_view_inventory();
			break;
		case 'r':
			action_view_relations();
			break;
		case 'q':
			action_view_quests();
			break;
		case 'd':
			action_view_debug(&p, &gtime);
			break;
	        case '>':
			action_save_game();
			break;
	        case '/':
			action_quit_game();
	}
}

int main(void)
{
	srand(time(NULL));

	init_window();
	init_gamelists();

	print_title();

	int running = 1;
	while (running) {
		season_check(&p);
		update_partyupkeep(&party);
		set_user_rank(&p);
		int currentlocation = print_map(map, rows, columns);
		set_location(&p);
		print_userinfo(currentlocation);
		print_time();
		print_actions();
		input_mainloop();
		wrefresh(win);
		werase(win);
	};

	endwin();

	return 0;
}

