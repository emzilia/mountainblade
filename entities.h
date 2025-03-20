#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdlib.h>

typedef struct {
	char name[6]; 
	size_t army;
	size_t charisma;
	int denars;
	char title[8];
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
	int x;
	int y;
	int xy;
} City;

extern User p;
extern City zander;
extern City talis;
extern City adriin;
extern City doxoun;
extern City calia;
extern City grelin;

#endif
