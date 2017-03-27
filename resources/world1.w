
#
# Areas
#

area mainArea {
	name = "Main Area";
	neighbors = "0, Area 2, Area 3, Area 4";
	description = "Main Area desc";
}

area Area2 {
	name = "Area 2";
	neighbors = "0, 0, Area 5, Main Area";
	description = "Area 2 desc";
}

area Area3 {
	name = "Area 3";
	neighbors = "Main Area, Area 5, 0, 0";
	description = "Area 3 desc";
}

area Area4 {
	name = "Area 4";
	neighbors = "0, Main Area, 0, 0";
	description = "Area 4 desc";
}

area Area5 {
	name = "Area 5";
	neighbors = "Area 2, 0, 0, Area 3";
	description = "Area 5 desc";
}

#
# Actions
#

action Inspect {
	names = "inspect, study, examine";
}

action Go {
	names = "go, move, walk, run";
}

action Equip {
	names = "equip";
}

action Give {
	names = "give, gift";
}

action Look {
	names = "look, look at, watch";
}

action Throw {
	names = "throw, huck, chuck, hurl";
}

action Eat {
	names = "eat, consume, chow down, gobble down";
}

action Drink {
	names = "drink, glug, slurp, chug";
}

action Read {
	names = "read";
}

action Trade {
	names = "trade, swap";
}

#
# Items
#

item Apple {
	name = "Apple";
	descriptions =
		"An appley apple indeed
		What a disgusting apple
		What an apple. Eh.";
}

item Map {
	name = "Map";
	descriptions = 
		"A map";
}



