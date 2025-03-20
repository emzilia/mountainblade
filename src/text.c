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

char titlescreen[200] = {
	"    Hello and welcome to Tania!\n\n"
	"    The Duke has been gone for three years now,\n"
	"fighting heathens abroad. Unrest grows across the\n"
	"realm as local nobles grow to fill the void left\n"
	"in his absence."
};


//
//
// City Actions
//
//


Event1 event_city1 = {
	.text = "You approach the gates to the %s\n\n"
			"The guard ushers your party through without\n"
			"complaint.",
	.arg1 = p.location
};

Event3 event_city2 = {
	.response = 4,
	.text = "%s\n\n%s\n\n%s\n\n"
			"Who would you like to see?\n\n"
			"1. Guild Master\n2. Tailor\n3. Blacksmith\n4. Stablekeeper"
			"\n\n\n(b) to go back",
	.arg1 = p.location,
	.arg2 = " ", // town->desc
	.arg3 = " " // town->wealthnote
};


// Guild Master


Event2 event_city2_gm1_noquest = {
	.response = 3,
	.text = "Guild Master %s:\n\n"
			"It's good to see you %s, how can we help you\n"
			"on this fine day?\n\n"
			"There is work to do, if you're interested...\n\n"
			"1. Accept some work\n2. Inquire about business"
			"\n\n\n(b) to go back",
	.arg1 = " ", // town->gm
	.arg2 = p.name
};

Event2 event_city2_gm1_yesquest = {
	.response = 3,
	.text = "Guild Master %s:\n\n"
			"It's good to see you %s, how can we help you\n"
			"on this fine day?\n\n"
			"There is work to do, if you're interested...\n\n"
			"1. Accept some work\n2. Inquire about business\n"
			"3. Turn in some work"
			"\n\n\n(b) to go back",
	.arg1 = " ", // town->gm
	.arg2 = p.name
};

Event1 event_city2_gm1_small1 = {
	.response = 0,
	.text = "\n\nGreat! I'll send the details over to your aid.",
	.arg1 = " "
};

Event1 event_city2_gm1_small2 = {
	.response = 0,
	.text = "\n\nYeah, wouldn't you like to know, dickhead...",
	.arg1 = " " 
};

Event1 event_city2_gm1_small3 = {
	.response = 0,
	.text = "\n\nYo, sick. Thanks G",
	.arg1 = " " 
};


// Tailor


Event1 event_city2_ta1 = {
	.response = 0,
	.text = "Tailor:\n\nGreetings %s, you have an impeccable style,"
			"\nbut if I may make some suggestions..."
			"\n\n\n(b) to go back",
	.arg1 = p.name
};

Event1 event_city2_bs1 = {
	.response = 0,
	.text = "Blacksmith:\n\nHello %s, I've got arms and armament, if"
			"\nyou're looking for equipment..."
			"\n\n\n(b) to go back",
	.arg1 = p.name
};

Event1 event_city2_sk1 = {
	.response = 0,
	.text = "Stablekeeper:\n\nGood day %s! "
			"I've got the best goddamned\nhorses you've ever seen."
			"\n\n\n(b) to go back",
	.arg1 = p.name
};

// Nobles

Event1 event_city2_nb1_noquest = {
	.response = 3,
	.text = "You approach the estate of the local\nnoble, %s\n\n"
			"1. Request and audience\n2. Offer to deliver a letter\n"
			"\n\n\n(b) to go back",
	.arg1 = " " 
};

Event1 event_city2_nb1_yesquest = {
	.response = 3,
	.text = "You approach the estate of the local\nnoble, %s\n\n"
			"1. Request and audience\n2. Deliver a letter\n"
			"\n\n\n(b) to go back",
	.arg1 = " "
};

Event1 event_city2_nb1_small1 = {
	.response = 0,
	.text = "\n\n'Your request has been... DENIED!'",
	.arg1 = " "
};

Event1 event_city2_nb1_yesquest_small1 = {
	.response = 0,
	.text = "\n\n'How quaint, what a good little delivery boy.'",
	.arg1 = " "
};

Event1 event_city2_nb1_noquest_small1 = {
	.response = 0,
	.text = "\n\n'Oh, how convenient. Thank you."
			"\nPlease deliver this to %s",
	.arg1 = " " // recipient
};


// Hiring mercenaries


Event1 event_merc = {
	.response = 1,
	.text = "You send messengers to the local tavern\nhoping "
			"to find some troops to hire",
	.arg1 = "to wait patiently",
};

Event4 event_merc_p1 = {
	.response = 1,
	.text = "%s locals seem adventurous enough.\n\n"
			"It'll cost %s denars to equip them,\nas well as "
			"an extra %s denars weekly.\n(Your total: %s)\n\n"
			"How does that sound?\n\n1. Sure thing\n2. No thanks\n",
	.arg1 = " ",
	.arg2 = " ",
	.arg3 = " ",
	.arg4 = " "
};
