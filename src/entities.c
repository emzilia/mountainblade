#include "entities.h"

User p = {
	.name = "Louie",
	.level = 1,
	.prowess = 1,
	.army = 13,
	.armycap = 35,
	.charisma = 5,
	.denars = 300,
	.renown = 1,
	.honor = 0,
	.title = "Esquire",
	.intown = 0,
	.x = 1,
	.y = 1,
};

QuestList allquests = {
	.totaldel = 0,
	.totalsla = 0,
};

Inventory bag = {
	.size = 0,
};

Item sword1 = {
	.name = "Heirloom blade",
	.info = "+3 Prowess",
	.quantity = 1,
	.quality = 1,
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
	.iscity = 0,
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
	.iscity = 1,
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
	.iscity = 1,
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
	.iscity = 0,
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
	.iscity = 0,
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
	.iscity = 0,
	.pop = 1780,
	.danger = 4,
	.wealth = 9,
	.x = 19,
	.y = 5,
	.xy = 11 + 3,
};

City yefhold = {
	.name = "Yefhold",
	.location = "Village of Yefhold",
	.iscity = 0,
	.pop = 11430,
	.danger = 4,
	.wealth = 5,
	.x = 16,
	.y = 2,
	.xy = 11 + 3,
};

City grii = {
	.name = "Grii",
	.location = "Village of Grii",
	.iscity = 0,
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
	.iscity = 0,
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
	.iscity = 1,
	.pop = 11430,
	.danger = 4,
	.wealth = 9,
	.x = 25,
	.y = 3,
	.xy = 11 + 3,
};

City salls = {
	.name = "Salls",
	.location = "Town of Salls",
	.iscity = 0,
	.pop = 9340,
	.danger = 4,
	.wealth = 5,
	.x = 24,
	.y = 6,
	.xy = 11 + 3,
};

Noble viscountess = {
	.name = "The Viscountess",
	.totalfiefs = 3,
};

Noble alinna = {
	.name = "Marquise Alinna",
	.totalfiefs = 2,
};

Noble balder = {
	.name = "Baron Balder",
	.totalfiefs = 1,
};
Noble raegai = {
	.name = "Baroness Raegai",
	.totalfiefs = 1,
};

Noble torace = {
	.name = "Baron Torace",
	.totalfiefs = 2,
};

Noble kieran = {
	.name = "Sir Kieran",
	.totalfiefs = 1,
};

Noble usoro = {
	.name = "Sir Usoro",
	.totalfiefs = 1,
};

CityList allcities;
NobleList allnobles;
BuddyList buddies;
PartyList party;
