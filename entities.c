#include "entities.h"

User p = {
	.name = "Tony",
	.level = 1,
	.prowess = 2,
	.army = 13,
	.armycap = 35,
	.charisma = 5,
	.denars = 120,
	.rank = 1,
	.title = "Esquire",
	.intown = 0,
	.x = 1,
	.y = 1,
};

Buddy gren = {
	.name = "Gren of Halix",
	.level = 1,
	.prowess = 2,
	.inparty = 1,
};


PartyList party = {
	.maa = 4,
	.pspear = 2,
	.pbow = 4,
};

City zander = {
	.name = "Zander",
	.location = "Town of Zander",
	.noble = "Baron Balder",
	.pop = 3300,
	.danger = 5,
	.wealth = 3,
	.x = 2,
	.y = 3,
	.xy = 2 + 2,
};

City adriin = {
	.name = "Adriin",
	.location = "Castle of Adrin",
	.noble = "The Viscountess",
	.pop = 11570,
	.danger = 1,
	.wealth = 5,
	.x = 11,
	.y = 3,
	.xy = 6 + 4,
};

City doxoun = {
	.name = "Doxoun",
	.location = "City of Doxoun",
	.noble = "Baroness Raegai",
	.pop = 5620,
	.danger = 7,
	.wealth = 9,
	.x = 6,
	.y = 1,
	.xy = 6 + 1,
};

City calia = {
	.name = "Calia",
	.location = "Town of Calia",
	.noble = "Sir Kieran",
	.pop = 2350,
	.danger = 2,
	.wealth = 2,
	.x = 9,
	.y = 5,
	.xy = 9 + 5,
};

City grelin = {
	.name = "Grelin",
	.location = "Town of Grelin",
	.noble = "Marquise Alinna",
	.pop = 870,
	.danger = 4,
	.wealth = 1,
	.x = 3,
	.y = 6,
	.xy = 11 + 3,
};

City amelo = {
	.name = "Amelo",
	.location = "Town of Amelo",
	.noble = "Baron Torace",
	.pop = 1780,
	.danger = 4,
	.wealth = 9,
	.x = 19,
	.y = 5,
	.xy = 11 + 3,
};

City yefhold = {
	.name = "Yefhold",
	.location = "City of Yefhold",
	.noble = "Marquise Alinna",
	.pop = 11430,
	.danger = 4,
	.wealth = 5,
	.x = 16,
	.y = 2,
	.xy = 11 + 3,
};

City grii = {
	.name = "Grii",
	.location = "City of Grii",
	.noble = "The Viscountess",
	.pop = 9340,
	.danger = 4,
	.wealth = 5,
	.x = 15,
	.y = 4,
	.xy = 11 + 3,
};

City todt = {
	.name = "Todt",
	.location = "Town of Todt",
	.noble = "Sir Usoro",
	.pop = 2380,
	.danger = 4,
	.wealth = 9,
	.x = 24,
	.y = 1,
	.xy = 11 + 3,
};

City joeton = {
	.name = "Joeton",
	.location = "City of Joeton",
	.noble = "Lady Nazia",
	.pop = 11430,
	.danger = 4,
	.wealth = 9,
	.x = 25,
	.y = 3,
	.xy = 11 + 3,
};

City salls = {
	.name = "Salls",
	.location = "City of Salls",
	.noble = "Baron Octirion",
	.pop = 9340,
	.danger = 4,
	.wealth = 5,
	.x = 24,
	.y = 6,
	.xy = 11 + 3,
};

CityList allcities;
BuddyList buddies;
PartyList party;
