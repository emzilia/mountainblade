#ifndef GTIME_H
#define GTIME_H

#include <stdlib.h>

#include "entities.h"
#include "logic.h"

typedef struct {
	size_t hour;
	size_t day;
	size_t week;
	size_t month;
} Time;

extern Time gtime;

void advance_hour(Time* gtime, int value);
void advance_day(Time* gtime, int value);
void advance_week(Time* gtime, int value, User* p);
void advance_month(Time* gtime, int value);

void season_check(User* p);

#endif
