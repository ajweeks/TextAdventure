
#
# Actions
#

action go {
	names = { "go", "move", "walk", "run" };
}

action help {
	names = { "help", "?" };
}

action commands {
	names = { "commands" };
}

action inventory {
	names = { "inventory", "e" };
}

action take {
	names = { "take" };
}

action drop {
	names = { "drop" };
}

action equip {
	names = { "equip" };
}

action eat {
	names = { "eat", "consume", "chow down", "gobble down" };
}

action drink {
	names = { "drink", "glug", "slurp", "chug" };
}

action trade {
	names = { "trade", "swap" };
}

action give {
	names = { "give", "gift" };
}

action speak {
	names = { "speak" };
}

action look {
	names = { "look", "look at", "watch" };
}

action inspect {
	names = { "inspect", "study", "examine" };
}

action read {
	names = { "read" };
}

action attack {
	names = { "attack" };
}

action throw {
	names = { "throw", "huck", "chuck", "hurl" };
}

action yes {
	names = { "yes", "y" };
}

action no {
	names = { "no", "n" };
}

action quit {
	names = { "quit", "exit" };
}


#
# Item definitions
#

item apple {
	name = "apple";
	descriptions = {
		"An appley apple indeed",
		"What a disgusting apple",
		"What an apple. Eh."
	};
	actions = { "eat" };
}

item cheese_block {
	name = "cheese block";
	descriptions = { "A block of emmental cheese" };
	actions = { "eat" };
}

item map {
	name = "map";
	descriptions = { "A map" };
	actions = { "read" };
}


#
# Areas
#

area Bedroom {
	name = "Bedroom";
	neighbors = { "0", "Area 2", "Area 3", "Area 4" };
	description = "Bedroom desc";
	items = { "apple" };
}

area Area2 {
	name = "Area 2";
	neighbors = { "0", "0", "Area 5", "Bedroom" };
	description = "Area 2 desc";
	items = { "apple" };
}

area Area3 {
	name = "Area 3";
	neighbors = { "Bedroom", "Area 5", "0", "0" };
	description = "Area 3 desc";
	items = { "apple" };
}

area Area4 {
	name = "Area 4";
	neighbors = { "0", "Bedroom", "0", "0" };
	description = "Area 4 desc";
	items = { "apple" };
}

area Area5 {
	name = "Area 5";
	neighbors = { "Area 2", "0", "0", "Area 3" };
	description = "Area 5 desc";
	items = { "apple" };
}

#
# Player
#

player Player {
	name = "Lancelot";
	inventory = "cheese block";
}
