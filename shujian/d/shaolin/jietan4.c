// Room: jietan4.c
// by bren

inherit ROOM;

void create()
{
	set("short", "戒坛");
	set("long", @LONG
这是一个正方形，四角攒尖顶的亭台式建筑。是寺中僧徒受戒的地方。
坛上正中放有佛身相连，向背而坐的双面铜铸佛像，面北的是药师佛，面南
的为阿弥陀佛。坛上空无一人，寂静无声，越发显得此处的庄严肃穆。
LONG
	);

	set("exits", ([
		
                "northwest" : __DIR__"fatang.c",
                "south" : __DIR__"jietan2",
                "west" : __DIR__"jietan3",
		]));
         

	set("outdoors", "shaolin");
	set("coor/x",60);
  set("coor/y",400);
   set("coor/z",130);
   set("coor/x",60);
 set("coor/y",400);
   set("coor/z",130);
   setup();
}



