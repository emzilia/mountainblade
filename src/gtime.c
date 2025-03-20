#include <string.h>
#include "gtime.h"
#include "entities.h"

Time gtime = {
	.hour = 0,
	.day = 1,
	.week = 1,
	.month = 1,
	.year = 874,
};

void advance_hour(Time* gtime, int value)
{
	gtime->hour += value;
	if (gtime->hour > 24) advance_day(gtime, 1);
}

void advance_day(Time* gtime, int value)
{
	gtime->hour = 1;
	gtime->day += value;
	if (gtime->day > 7) advance_week(gtime, 1, &p);
}

void advance_week(Time* gtime, int value, User* p)
{
	weekly_partyupkeep(p);
	gtime->day = 1;
	gtime->week += value;
	if (gtime->week > 4) advance_month(gtime, 1);
}

void advance_month(Time* gtime, int value)
{
	gtime->week = 1;
	gtime->month += value;
	if (gtime->month > 12) advance_year(gtime, 1);
}

void advance_year(Time* gtime, int value)
{
	gtime->month = 1;
	gtime->year += value;
	if (gtime->month > 12) gtime->month = 1;
}

void season_check(User* p)
{
	char season1[10] = "Summer";
	char season2[10] = "Autumn";
	char season3[10] = "Winter";
	char season4[10] = "Spring";

	if (gtime.month == 1 || gtime.month == 2 || gtime.month == 3)
		strncpy(p->season, season1, (sizeof(p->season) - 1));	

	if (gtime.month == 4 || gtime.month == 5|| gtime.month == 6)
		strncpy(p->season, season2, (sizeof(p->season) - 1));	

	if (gtime.month == 7 || gtime.month == 8 || gtime.month == 9)
		strncpy(p->season, season3, (sizeof(p->season) - 1));	

	if (gtime.month == 10 || gtime.month == 11 || gtime.month == 12)
		strncpy(p->season, season4, (sizeof(p->season) - 1));	
}

