#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdlib.h>

struct User;
struct Buddy;
struct Noble;
struct City;

typedef struct User {
	size_t level;
	size_t prowess;
	size_t army;
	size_t armycap;
	size_t charisma;
	int denars;
	int renown;
	int honor;
	int kills;
	int intown;
	int x;
	int y;
	char name[13]; 
	char title[20];
	char location[30];
} User;

typedef struct Buddy {
	size_t level;
	size_t prowess;
	int inparty;
	int x;
	int y;
	char name[13];
	char location[20];
} Buddy;

typedef struct {
	size_t size;
	Buddy buddies[6];
} BuddyList;

typedef struct{
	size_t maa;
	size_t maaupkeep;
	size_t pspear;
	size_t pspearupkeep;
	size_t pbow;
	size_t pbowupkeep;
	size_t total;
	size_t totalupkeep;
	char maaname[20];
	char pspearname[20];
	char pbowname[20];
} PartyList;

typedef struct City {
	size_t pop;
	size_t danger;
	size_t wealth;
	int iscity;
	int x;
	int y;
	char name[10];
	char location[30];
	char gm[10];
	char wealthnote[100];
	struct Noble* owner;
} City;

typedef struct {
	size_t size;
	City* cities[12];
} CityList;

typedef struct Noble{
	size_t totalfiefs;
	City* fiefs[3];
	char name[20];
} Noble;

typedef struct {
	size_t size;
	Noble* nobles[7];
} NobleList;

typedef struct {
	size_t quantity;
	size_t quality;
	Noble* recipient1;
	City* recipient2;
	char info[50];
	char name[50];
} Item;

typedef struct {
	size_t size;
	Item items[10];	
} Inventory;

typedef struct {
	int relation_buff;
	int renown_gain;
	Noble* giver;
	Noble* target;
} Quest1;

typedef struct {
	int to_kill;
	int relation_buff;
	int renown_gain;
	City* giver;
} Quest2;

typedef struct {
	size_t totaldel;
	size_t totalsla;
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
