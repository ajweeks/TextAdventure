
grammar textworld;

world: (area | action | item)*;

item: 	ITEM ID LCB
			assignment*
		RCB;

area:	AREA ID LCB
			assignment*
		RCB;

action:	ACTION ID LCB
			assignment*
		RCB;

assignment: ID EQ value SC;

value: STRING | INT;

AREA : 'area';
ITEM : 'item';
ACTION : 'action';
LCB : '{';
RCB : '}';
EQ : '=';
SC : ';';
ID : [a-zA-Z][a-zA-Z0-9_]*;
STRING : '"' ~('"')* '"';
INT : [+-]?[0-9]+;
WS : [ \t\r\n]+ -> skip;
COMMENT : '#' ~('\r'|'\n')* -> skip;