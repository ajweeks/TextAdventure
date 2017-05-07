
grammar textworld;

world: (area | action | item)* player;

item: 	ITEM ID LCB
			assignment*
		RCB;

area:	AREA ID LCB
			assignment*
		RCB;

action:	ACTION ID LCB
			assignment*
		RCB;
		
player: PLAYER ID LCB
			assignment*
		RCB;

assignment: ID EQ value SC;

value: STRING | INT | (LCB value (COMMA value)* RCB);

AREA : 'area';
ITEM : 'item';
ACTION : 'action';
PLAYER : 'player';
LCB : '{';
RCB : '}';
EQ : '=';
SC : ';';
ID : [a-zA-Z][a-zA-Z0-9_]*;
STRING : '"' ~('"')* ('\n')* '"';
INT : [+-]?[0-9]+;
WS : [ \t\r\n]+ -> skip;
COMMA : ',';
COMMENT : '#' ~('\r'|'\n')* -> skip;