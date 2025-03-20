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

int debug = 0;

void input_mainloop()
{
	int response = wgetch(win);
	switch (response) {
		case 'k':
		case KEY_UP:
			if (p.y > 1)
				p.y--;
				advance_hour((rand() % 2) + 2);
			break;
		case 'j':
		case KEY_DOWN:
			if (p.y < rows - 2)
				p.y++; 
				advance_hour((rand() % 2) + 2);
			break;
		case 'h':
		case KEY_LEFT:
			if (p.x > 1)
				p.x--;
				advance_hour((rand() % 2) + 2);
			break;
		case 'l':
		case KEY_RIGHT:
			if (p.x < columns - 2)
				p.x++;
				advance_hour((rand() % 2) + 2);
			break;
	}
	
	if (p.intown) {
		switch (response) {
			case '1':
				action_enter_city(currenttown);
				break;
			case '2': 
				action_contact_noble();
				break;
			case '3':
				action_hire_mercs(currenttown);
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
		case '/':
			endwin();
			exit(0);
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
		update_partyupkeep();
		set_user_rank(&p);
		print_map(map, rows, columns);
		set_location();
		print_userinfo();
		print_time();
		print_actions();
		input_mainloop();
		wrefresh(win);
		werase(win);
	};

	endwin();

	return 0;
}

