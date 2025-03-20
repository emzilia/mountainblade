#ifndef ACTIONS_H
#define ACTIONS_H

#include "entities.h"

extern City currenttown;

void action_enter_city(City town);
void action_enter_city_guildmaster();
void action_enter_city_tailor();
void action_enter_city_blacksmith();
void action_enter_city_stablekeeper();

void action_contact_noble();

void action_hire_mercs();

void action_setup_camp();

void action_draft_letter();

void action_view_inventory();
void action_view_relations();
void action_view_quests();

#endif
