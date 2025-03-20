#ifndef LOGIC_H
#define LOGIC_H

#include "entities.h"

void init_citylist();
void init_noblelist();
void init_buddylist();
void init_partylist();
void init_gamelists();

void move_north(User* p);
void move_south(User* p);
void move_west(User* p);
void move_east(User* p);

void update_partyupkeep();

int check_location(City* town);
void set_location(User* p);
void calc_city_wealth(City* city);
void set_user_rank(User* list);

void add_to_inventory(Inventory* inventory, Item* thing);

void generate_quest1(City* city);
void generate_quest2(City* city);

void logic_draft_letter(Noble* noble);

#endif
