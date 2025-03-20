#ifndef LOGIC_H
#define LOGIC_H

#include "entities.h"

void init_citylist();
int check_location(City town);
void set_location();
void update_pxy();
void calc_city_wealth(City* city);
void set_user_rank(User* list);

#endif
