#ifndef GTIME_H
#define GTIME_H

#include <stdlib.h>

#include "entities.h"
#include "logic.h"

typedef struct {
	int hour;
	int day;
	int week;
	int month;
	int year;
} Time;

extern Time gtime;

void advance_hour(Time* gtime, int value);
void advance_day(Time* gtime, int value);
void advance_week(Time* gtime, int value, User* p);
void advance_month(Time* gtime, int value);
void advance_year(Time* gtime, int value);

void season_check(User* p);

#endif
