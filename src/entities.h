#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdlib.h>

typedef struct Noble Noble;
typedef struct City City;
typedef struct User User;
typedef struct Buddy Buddy;

typedef struct User {
	char name[13]; 
	size_t level;
	size_t prowess;
	size_t army;
	size_t armycap;
	size_t charisma;
	int denars;
	int renown;
	int honor;
	char title[10];
	char location[20];
	int intown;
	int x;
	int y;
	int xy;
} User;

typedef struct Buddy {
	char name[13];
	size_t level;
	size_t prowess;
	char location[20];
	int inparty;
	int x;
	int y;
} Buddy;

typedef struct {
	Buddy buddies[6];
	size_t size;
} BuddyList;

typedef struct{
	size_t maa;
	char maaname[20];
	size_t maaupkeep;
	size_t pspear;
	char pspearname[20];
	size_t pspearupkeep;
	size_t pbow;
	char pbowname[20];
	size_t pbowupkeep;
	size_t total;
	size_t totalupkeep;
} PartyList;

typedef struct City {
	char name[7];
	char location[25];
	Noble* owner;
	int iscity;
	size_t pop;
	size_t danger;
	size_t wealth;
	char wealthnote[100];
	int x;
	int y;
	int xy;
} City;

typedef struct {
	City* cities[12];
	size_t size;
} CityList;

typedef struct Noble{
	char name[20];
	City* fiefs[3];
	size_t totalfiefs;
} Noble;

typedef struct {
	Noble* nobles[7];
	size_t size;
} NobleList;

typedef struct {
	char name[20];
	size_t quantity;
	size_t quality;
	Noble* owner;
} Item;

typedef struct {
	Item items[10];	
	size_t size;
} Inventory;


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

#endif
