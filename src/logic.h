#ifndef LOGIC_H
#define LOGIC_H

#include "entities.h"

void init_citylist();
void init_noblelist();
void init_buddylist(BuddyList* buddies);
void init_partylist(PartyList* party);
void init_gamelists();

char* convert_string(int number);

void move_north(User* p);
void move_south(User* p);
void move_west(User* p);
void move_east(User* p);

void update_partyupkeep(PartyList* party);
void weekly_partyupkeep(User* p);

int check_location(City* town, User* p);
void set_location(User* p);
void calc_city_wealth(City* city);
void set_user_rank(User* list);

void add_to_inventory(Inventory* inventory, Item* thing);

int generate_unique_questid();
char* generate_quest1(City* city);
void complete_quest(City* city, Inventory* bag, int num);

void generate_quest2(City* city);

void logic_draft_letter(Noble* noble);

#endif
