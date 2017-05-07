
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

action open {
	names = { "open" };
}


#
# Item definitions
#

item bedroomWindow {
	name = "window";
	descriptions = { "Through the windows you see an vast ocean, far below. Where could you possibly be?",
		"Out the window you see a seemingly endless ocean, with no land in sight."};
	actions = { "eat" };
}

item shinyObject {
	name = "shiny object";
	descriptions = { "An intensly glowing metalic sphere",
		"A hot, glowing, metalic sphere. Your skin would probably melt off in milliseconds if you went near it."};
	actions = { "eat" };
}

item lockedDoors {
	name = "locked doors";
	descriptions = { "You try the doors, but they won't budge.",
		"You push the doors with all your strength, but the don't move an inch."};
	actions = { "open", "enter" };
}

item unlockedDoors {
	name = "unlocked doors";
	descriptions = { "You push open the doors.", "You turn the handle and slowly open the door." };
	actions = { "open", "enter" };
}

item largeWindows {
	name = "large windows";
	descriptions = { "Through the windows you see an immense ocean, far below.", 
	"You look out the window and see ocean as far as you can see." };
	actions = { "look" };
}


#
# Areas
#

area Bedroom {
	name = "Bedroom";
	neighbors = { "0", "0", "0", "Main hallway" };
	description = "The year is 2029. You are awoken by a blaring alarm. You look around the room - you see a  metal object sitting on the counter. It seems to be hot - you can see heat waves emanating from it. Across from the strange shiny object you see a semi-reflective window. From the window you see a vast body of water - but something is off about it, there are no waves. Is it an ocean? A lake? A pool?\nSuddenly - there's a loud knock on the door. *BANG* *BANG* *BANG* Before you have a chance to react the door slides open and the alarm stops. Your eyes are still adjusting to the brightness of the sunlight pouring into your room so you can't quite make out the figure standing in the doorway. Their silhouette is large and intimidating. The mysterious figure barks loudly 'Get out of bed subject 213! It's time for your weekly inspection. You have five minutes to make your way to auditorium 11. If you're late again there will be consequences.'\nThe figure exits the room and heads left. You now see that the hot object across from you is now violently shaking. It's lost its shine, the heat has caused the object to begin to glow white. Then, suddenly, silence. The object instantly seemed to be back to normal. You slowly walk over to it and inch your hand towards it. You ever so gently touch the object, its surface cool to the touch. You try picking it up, but it must have an incredible mass as you can't make it budge.\nYou better get going to this auditorium if you know whats good for you though.";
	items = { "shiny object", "window" };
}

area MainHallway {
	name = "Main hallway";
	neighbors = { "Doors to the right", "Bedroom", "Doors to the left", "0" };
	description = "You cautiously walk into the hallway, and see a seemingly-endless row of doors that look identical to the one you emerge from. You notice that the doors are numbered, with a small white plate, the door next to yours is 212, the one on the other side - 214. But which way is it to the auditorium?";
	#  items = {  };
}

area DoorsRight {
	name = "Doors to the right";
	neighbors = { "0", "0", "Main hallway", "0" };
	description = "You walk to the right. Even though the figure from before seemed to go to the left, he's probably not going to the auditorium. You walk for what feels like 10 minutes, passing by dozens of identical doors, along a slightly curved hallway. Eventually you reach a set of doors with a sign on them saying 'Empoloyees only'. You try the doors anyway - no budge.";
	items = { "locked doors" };
}

area DoorsLeft {
	name = "Doors to the left";
	neighbors = { "Main hallway", "0", "Large room", "0" };
	description = "You walk to the left, the auditorium is probably that direction, since that's the way the figure went earlier. You walk for minutes before seeing anything new. The entire way you see seemingly identical doors, one after another, and the only sound you hear is an almost silent buzzing sound coming from tiny round speakers placed above every door. You eventually come to the end of the hallway. You're confronted with a set of large double-doors, with a label above them 'Wing 0'.";
	#  items = {  };
}

area LargeRoom {
	name = "Large room";
	neighbors = { "Doors to the left", "0", "Doors across the room", "Large windows" };
	description = "You attempt to push the doors open, and with all your strength - you just budge them open enough to squeeze through. On the other side you immediately feel a warm, humid air surround you. You see that you now stand in a large, empty room. There seems to be another set of doors across the room, and a small window halfway along the wall to your right.";
	#  items = {  };
}

area LargeWindows {
	name = "Large windows";
	neighbors = { "Large room", "0", "Doors across the room", "0" };
	description = "You walk up to the window and look out to see an endless sea. You appear to be hundreds of meters above it. Where in the world could you possibly be?";
	items = { "large windows" };
}

area DoorsAcross {
	name = "Doors across the room";
	neighbors = { "Doors to the left", "0", "0", "Large windows" };
	description = "You walk across the large room towards the other door. But before you can get there, you hear a loud siren begin to blare. You frantically scan the room, but there is nothing. You run to the other side.";
	#  items = {  };
}

#
# Player
#

player Player {
	name = "Lancelot";
	# inventory = "";
}
