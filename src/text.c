#include "display.h"
#include "entities.h"

// Display
char map[8][28] = {
	"o==========================o",
	"|.....c./^^^^^^^^^^^^^^^t..|",
	"|....../........v^^^^^^^...|",
	"|.t___/....C.............c.|",
	"|./............v...........|",
	"|/.....**t*******..t.......|",
	"|..t..************......t..|",
	"o==========================o"
};

char titlescreen[200] = "    Hello and welcome to Tania!\n\n"
	"    The Duke has been gone for three years now,\n"
	"fighting heathens abroad. Unrest grows across the\n"
	"realm as local nobles grow to fill the void left\n"
	"in his absence.";

// Actions
Event1 event_city1 = {
	.text = "You approach the gates to the %s\n\n"
		"The guard ushers your party through without\n"
		"complaint.",
	.arg = p.location
};

Event2 event_city2 = {
	.response = 4,
	.text = "%s\n\n%s\n\n"
			"Who would you like to see?\n\n"
			"1. Guild Master\n2. Tailor\n3. Blacksmith\n4. Stablekeeper"
			"\n\n\n(b) to go back",
	.arg1 = p.location,
	.arg2 = "                                                           "
			"                                                           "
};
