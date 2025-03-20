#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdlib.h>

typedef struct {
	char name[13]; 
	size_t level;
	size_t prowess;
	size_t army;
	size_t armycap;
	size_t charisma;
	int denars;
	int renown;
	char title[10];
	char location[20];
	int intown;
	int x;
	int y;
	int xy;
} User;

typedef struct {
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

typedef struct {
	char name[7];
	char location[25];
	char noble[20];
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

typedef struct {
	char name[20];
	City* fiefs[3];
	size_t totalfiefs;
} Noble;

typedef struct {
	Noble* nobles[8];
	size_t size;
} NobleList;

extern User p;
extern Buddy gren;

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
