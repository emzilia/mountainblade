#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdlib.h>

struct User;
struct Buddy;
struct Noble;
struct City;

typedef struct User {
	int level;
	int xp;
	int prowess;
	int army;
	int armycap;
	int charisma;
	int denars;
	int renown;
	int honor;
	int kills;
	int intown;
	int x;
	int y;
	char season[10];
	char name[13]; 
	char title[20];
	char location[30];
} User;

typedef struct Buddy {
	int level;
	int prowess;
	int inparty;
	int x;
	int y;
	char name[13];
	char location[20];
} Buddy;

typedef struct {
	int size;
	Buddy buddies[6];
} BuddyList;

typedef struct{
	int maa;
	int maaupkeep;
	int pspear;
	int pspearupkeep;
	int pbow;
	int pbowupkeep;
	int total;
	int totalupkeep;
	char maaname[20];
	char pspearname[20];
	char pbowname[20];
} PartyList;

typedef struct City {
	int pop;
	int danger;
	int wealth;
	int iscity;
	int x;
	int y;
	int hasdel;
	int hassla;
	char name[10];
	char location[30];
	char gm[10];
	char wealthnote[100];
	struct Noble* owner;
} City;

typedef struct {
	int size;
	City* cities[12];
} CityList;

typedef struct Noble{
	int totalfiefs;
	int relations;
	City* fiefs[3];
	char name[20];
} Noble;

typedef struct {
	int size;
	Noble* nobles[7];
} NobleList;

typedef struct {
	int questid;
	int quantity;
	int quality;
	Noble* recipient1;
	City* recipient2;
	char info[50];
	char name[50];
} Item;

typedef struct {
	int size;
	Item items[10];	
} Inventory;

typedef struct {
	int relation_buff;
	int renown_gain;
	int questid;
	Noble* giver;
	Noble* target;
} Quest1;

typedef struct {
	int starting_kills;
	int to_kill;
	int relation_buff;
	int renown_gain;
	int questid;
	City* giver;
} Quest2;

typedef struct {
	int totaldel;
	int totalsla;
	Quest1 deliveries[5];
	Quest2 slayings[5];
} QuestList;


extern User p;
extern Buddy gren;

extern Inventory bag;
extern Item sword1;

extern City zander;
extern City talis;
extern City adriin;
extern City doxoun;
extern City calia;
extern City grelin;
extern City amelo;
extern City yefhold;
extern City grii;
extern City todt;
extern City joeton;
extern City salls;

extern Noble balder;
extern Noble viscountess;
extern Noble raegai;
extern Noble kieran;
extern Noble alinna;
extern Noble torace;
extern Noble usoro;
extern Noble nazia;

extern PartyList party;
extern CityList allcities;
extern NobleList allnobles;
extern BuddyList buddies;
extern QuestList allquests;

#endif
