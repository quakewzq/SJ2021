// Room: /u/beyond/ningbo/shilu.c 石路
// Beyond make 1997.6.8
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", "石路");
	set("long", @LONG
你走在一条青石路上，两旁是一片茂密的柳树林，头上小喜鹊唧唧喳喳的
叫个不停。一阵微风吹过，使你感觉到一股潮湿的空气扑面而来，也许是因为
宁波城是个港口吧。不远处的山上就是鼎鼎有名的报国寺了。往南便是天封塔。
LONG
	);
	set("outdoors", "宁波");
	set("exits", ([
		"east" : __DIR__"tianyige",
		"northwest" : "/d/group/entry/nbqsddao",
		"south" : __DIR__"tianfengta",
		"southup" : __DIR__"baoguosi",
	]));
	setup();
}
