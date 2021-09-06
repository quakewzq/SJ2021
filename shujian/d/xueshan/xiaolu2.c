// Room: xiaolu2.c

inherit ROOM;

void create()
{
	set("short", "湖边小路");
	set("long", @LONG
天湖湖边的一条小路，向前望不到尽头，不知道通向那里。路边野花芬芳，
蝴蝶飞舞，除了你自己的脚步声，四下里只听见一声高一声低的鸟鸣。
LONG
	);

	set("exits", ([
		"east" : __DIR__"xiaolu3",
		"northwest" : __DIR__"xiaolu1",
	]));
        set("outdoors", "雪山");
	set("coor/x",-250);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}
