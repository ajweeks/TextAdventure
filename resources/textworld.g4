
grammar textworld;

world: item*;

item: 	ITEM ID LCB
			assignment*
		RCB;
		
assignment: ID EQ value SC;

value: STRING | INT;

ITEM : 'item';
LCB : '{';
RCB : '}';
EQ : '=';
SC : ';';
ID : [a-zA-Z][a-zA-Z0-9_]*;
STRING : '"' ~('"')* '"';
INT : [+-]?[0-9]+;
WS : [ \t\r\n]+ -> skip;