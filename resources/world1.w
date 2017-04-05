
#
# Actions
#

action inspect {
	names = { "inspect", "study", "examine" };
}

action help {
	names = { "help" };
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

action speak {
	names = { "speak" };
}

action enter {
	names = { "enter" };
}

action exit {
	names = { "exit" };
}

action go {
	names = { "go", "move", "walk", "run" };
}

action equip {
	names = { "equip" };
}

action give {
	names = { "give", "gift" };
}

action look {
	names = { "look", "look at", "watch" };
}

action throw {
	names = { "throw", "huck", "chuck", "hurl" };
}

action eat {
	names = { "eat", "consume", "chow down", "gobble down" };
}

action drink {
	names = { "drink", "glug", "slurp", "chug" };
}

action read {
	names = { "read" };
}

action trade {
	names = { "trade", "swap" };
}

action attack {
	names = { "attack" };
}


#
# Items
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

item map {
	name = "map";
	descriptions = { "A map" };
	actions = { "read" };
}


#
# Areas
#

area mainArea {
	name = "Main Area";
	neighbors = { "0", "Area 2", "Area 3", "Area 4" };
	description = "Main Area desc";
	items = { "apple" };
}

area Area2 {
	name = "Area 2";
	neighbors = { "0", "0", "Area 5", "Main Area" };
	description = "Area 2 desc";
	items = { "apple" };
}

area Area3 {
	name = "Area 3";
	neighbors = { "Main Area", "Area 5", "0", "0" };
	description = "Area 3 desc";
	items = { "apple" };
}

area Area4 {
	name = "Area 4";
	neighbors = { "0", "Main Area", "0", "0" };
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
	name = "Player name";
	inventory = "cheese block";
}
