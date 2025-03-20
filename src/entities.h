#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdlib.h>

struct User;
struct Buddy;
struct Noble;
struct City;

typedef struct User {
	unsigned int level;
	unsigned int prowess;
	unsigned int army;
	unsigned int armycap;
	unsigned int charisma;
	unsigned int denars;
	unsigned int renown;
	unsigned int honor;
	unsigned int kills;
	unsigned int intown;
	unsigned int x;
	unsigned int y;
	char season[10];
	char name[13]; 
	char title[20];
	char location[30];
} User;

typedef struct Buddy {
	unsigned int level;
	unsigned int prowess;
	unsigned int inparty;
	unsigned int x;
	unsigned int y;
	char name[13];
	char location[20];
} Buddy;

typedef struct {
	unsigned int size;
	Buddy buddies[6];
} BuddyList;

typedef struct{
	unsigned int maa;
	unsigned int maaupkeep;
	unsigned int pspear;
	unsigned int pspearupkeep;
	unsigned int pbow;
	unsigned int pbowupkeep;
	unsigned int total;
	unsigned int totalupkeep;
	char maaname[20];
	char pspearname[20];
	char pbowname[20];
} PartyList;

typedef struct City {
	unsigned int pop;
	unsigned int danger;
	unsigned int wealth;
	unsigned int iscity;
	unsigned int x;
	unsigned int y;
	unsigned int hasdel;
	unsigned int hassla;
	char name[10];
	char location[30];
	char gm[10];
	char wealthnote[100];
	struct Noble* owner;
} City;

typedef struct {
	unsigned int size;
	City* cities[12];
} CityList;

typedef struct Noble{
	unsigned int totalfiefs;
	unsigned int relations;
	City* fiefs[3];
	char name[20];
} Noble;

typedef struct {
	unsigned int size;
	Noble* nobles[7];
} NobleList;

typedef struct {
	unsigned int questid;
	unsigned int quantity;
	unsigned int quality;
	Noble* recipient1;
	City* recipient2;
	char info[50];
	char name[50];
} Item;

typedef struct {
	unsigned int size;
	Item items[10];	
} Inventory;

typedef struct {
	unsigned int relation_buff;
	unsigned int renown_gain;
	unsigned int questid;
	Noble* giver;
	Noble* target;
} Quest1;

typedef struct {
	unsigned int to_kill;
	unsigned int relation_buff;
	unsigned int renown_gain;
	unsigned int questid;
	City* giver;
} Quest2;

typedef struct {
	unsigned int totaldel;
	unsigned int totalsla;
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
