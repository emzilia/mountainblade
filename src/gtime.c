#include "gtime.h"
#include "display.h"
#include "entities.h"

Time gtime = {
	.hour = 0,
	.day = 1,
	.week = 1,
	.month = 1,
};

void advance_hour(int value)
{
	gtime.hour += value;
	if (gtime.hour > 24) advance_day(1);
}

void advance_day(int value)
{
	gtime.hour = 1;
	gtime.day += value;
	if (gtime.day > 7) advance_week(1, &p);
}

void advance_week(int value, User* p)
{
	weekly_partyupkeep(p);
	gtime.day = 1;
	gtime.week += value;
	if (gtime.week > 4) advance_month(1);
}

void advance_month(int value)
{
	gtime.week = 1;
	gtime.month += value;
	if (gtime.month > 12) gtime.month = 1;
}
