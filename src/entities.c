#include "entities.h"

User p = {
	.level = 1,
	.xp = 0,
	.prowess = 1,
	.army = 13,
	.armycap = 35,
	.charisma = 5,
	.denars = 300,
	.renown = 0,
	.honor = 0,
	.kills = 0,
	.intown = 0,
	.x = 1,
	.y = 1,
	.season = "Summer",
	.name = "Louie",
	.title = "Esquire",
};

QuestList allquests = {
	.totaldel = 0,
	.totalsla = 0,
};

Inventory bag = {
	.size = 0,
};

Item sword1 = {
	.quantity = 1,
	.quality = 1,
	.name = "Heirloom blade",
	.info = "+3 Prowess",
};


Buddy gren = {
	.level = 1,
	.prowess = 2,
	.inparty = 1,
	.name = "Gren of Halix",
};


PartyList party = {
	.maa = 4,
	.pspear = 2,
	.pbow = 4,
};

City zander = {
	.pop = 3300,
	.danger = 5,
	.wealth = 3,
	.iscity = 0,
	.x = 2,
	.y = 3,
	.hasdel = 0,
	.hassla = 0,
	.desc = "A small, densely built town sitting on the\n"
			"shores of the Tanian river. Cramped roads "
			"snake\nbetween tall white-brick buildings.",
	.name = "Zander",
	.location = "Town of Zander",
	.gm = "Berguson",
};

City adriin = {
	.pop = 11570,
	.danger = 1,
	.wealth = 5,
	.iscity = 1,
	.x = 11,
	.y = 3,
	.hasdel = 0,
	.hassla = 0,
	.desc = "A large stone castle lumbering atop a\n"
			"small hill. It's girth dominates the center of\n"
			"the valley.",
	.name = "Adriin",
	.location = "Castle of Adriin",
	.gm = "Grinvald",
};

City doxoun = {
	.pop = 5620,
	.danger = 7,
	.wealth = 9,
	.iscity = 1,
	.x = 6,
	.y = 1,
	.hasdel = 0,
	.hassla = 0,
	.desc = " ",
	.name = "Doxoun",
	.location = "City of Doxoun",
	.gm = "Torien",
};

City calia = {
	.pop = 2350,
	.danger = 2,
	.wealth = 2,
	.iscity = 0,
	.x = 9,
	.y = 5,
	.hasdel = 0,
	.hassla = 0,
	.desc = " ",
	.name = "Calia",
	.location = "Town of Calia",
	.gm = "Talyiana",
};

City grelin = {
	.pop = 870,
	.danger = 4,
	.wealth = 1,
	.iscity = 0,
	.x = 3,
	.y = 6,
	.hasdel = 0,
	.hassla = 0,
	.desc = " ",
	.name = "Grelin",
	.location = "Town of Grelin",
	.gm = "Jon",
};

City amelo = {
	.pop = 1780,
	.danger = 4,
	.wealth = 9,
	.iscity = 0,
	.x = 19,
	.y = 5,
	.hasdel = 0,
	.hassla = 0,
	.desc = " ",
	.name = "Amelo",
	.location = "Town of Amelo",
	.gm = "Yellena",
};

City yefhold = {
	.pop = 11430,
	.danger = 4,
	.wealth = 5,
	.iscity = 0,
	.x = 16,
	.y = 2,
	.hasdel = 0,
	.hassla = 0,
	.desc = " ",
	.name = "Yefhold",
	.location = "Village of Yefhold",
	.gm = "Harnaby",
};

City grii = {
	.pop = 9340,
	.danger = 4,
	.wealth = 5,
	.iscity = 0,
	.x = 15,
	.y = 4,
	.hasdel = 0,
	.hassla = 0,
	.desc = " ",
	.name = "Grii",
	.location = "Village of Grii",
	.gm = "Larun",
};

City todt = {
	.pop = 2380,
	.danger = 4,
	.wealth = 9,
	.iscity = 0,
	.x = 24,
	.y = 1,
	.hasdel = 0,
	.hassla = 0,
	.desc = " ",
	.name = "Todt",
	.location = "Town of Todt",
	.gm = "Kierre",
};

City joeton = {
	.pop = 11430,
	.danger = 4,
	.wealth = 9,
	.iscity = 1,
	.x = 25,
	.y = 3,
	.hasdel = 0,
	.hassla = 0,
	.desc = " ",
	.name = "Joeton",
	.location = "City of Joeton",
	.gm = "Rossia",
};

City salls = {
	.pop = 9340,
	.danger = 4,
	.wealth = 5,
	.iscity = 0,
	.x = 24,
	.y = 6,
	.hasdel = 0,
	.hassla = 0,
	.desc = " ",
	.name = "Salls",
	.location = "Town of Salls",
	.gm = "Salador",
};

Noble viscountess = {
	.totalfiefs = 3,
	.relations = 0,
	.name = "The Viscountess",
};

Noble alinna = {
	.totalfiefs = 2,
	.relations = 0,
	.name = "Marquise Alinna",
};

Noble balder = {
	.totalfiefs = 1,
	.relations = 0,
	.name = "Baron Balder",
};
Noble raegai = {
	.totalfiefs = 1,
	.relations = 0,
	.name = "Baroness Raegai",
};

Noble torace = {
	.totalfiefs = 2,
	.relations = 0,
	.name = "Baron Torace",
};

Noble kieran = {
	.totalfiefs = 1,
	.relations = 0,
	.name = "Sir Kieran",
};

Noble usoro = {
	.totalfiefs = 1,
	.relations = 0,
	.name = "Sir Usoro",
};

CityList allcities;
NobleList allnobles;
BuddyList buddies;
PartyList party;
