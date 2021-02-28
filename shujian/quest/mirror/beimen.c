// Room: /city/beimen.c
// YZC 1995/12/04 
#include <room.h>
inherit ROOM;
string look_gaoshi();
void create()
{
	set("short", "北门");
	set("long", @LONG
	这是北城门，因为曾经失火，到现在城墙还是黑乎乎的，因此白
纸黑字的官府告示(gaoshi)就显得特别现眼。北方是一片崇山峻岭，一条
黄土小径在山里蜿蜒而上。
LONG
	);
	set("item_desc", ([
		"gaoshi" : (:look_gaoshi:),
	]));
	set("exits", ([
		"south" : __DIR__"beidajie2",
                "west" : __DIR__"postoffice",
          "east" : __DIR__"work2",
	]));
	set("outdoors", "city");
	setup();
}

//是镜像
int is_mirror() { return 1; }