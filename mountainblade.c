#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include "actions.h"
#include "entities.h"
#include "display.h"
#include "logic.h"

int debug = 0;

void input_mainloop()
{
	int response = getch();
	switch (response) {
		case 'k':
		case KEY_UP:
			if (p.y > 1)
				p.y--;
				//update_pxy();
			break;
		case 'j':
		case KEY_DOWN:
			if (p.y < rows - 2)
				p.y++; 
				//update_pxy();
			break;
		case 'h':
		case KEY_LEFT:
			if (p.x > 1)
				p.x--;
				//update_pxy();
			break;
		case 'l':
		case KEY_RIGHT:
			if (p.x < columns - 2)
				p.x++;
				//update_pxy();
			break;
	}
	
	if (p.intown) {
		switch (response) {
			case '1':
				action_enter_city();
				break;
			case '2': 
				action_contact_noble();
				break;
			case '3':
				action_hire_mercs();
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
		case 'i':
			action_view_inventory();
			break;
		case 'r':
			action_view_relations();
			break;
		case 'q':
			action_view_quests();
			break;
		case 'k':
			exit(0);
	}
}

int main(void)
{
	init_window();
	
	init_citylist();
	print_title();

	int running = 1;
	while (running) {
		print_map(map, rows, columns);
		print_userinfo();
		print_actions();
		wrefresh(win);
		input_mainloop();
		wrefresh(win);
		werase(win);
	};

	endwin();

	return 0;
}

