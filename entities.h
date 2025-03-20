#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdlib.h>

typedef struct {
	char name[6]; 
	size_t army;
	size_t armycap;
	size_t charisma;
	int denars;
	int rank;
	char title[10];
	char location[20];
	int intown;
	int x;
	int y;
	int xy;
} User;

typedef struct {
	char name[7];
	char location[20];
	char noble[20];
	size_t pop;
	size_t danger;
	size_t wealth;
	char wealthnote[35];
	int x;
	int y;
	int xy;
} City;

typedef struct {
	City cities[12];
	size_t size;
} CityList;

extern User p;
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

extern CityList allcities;

#endif
