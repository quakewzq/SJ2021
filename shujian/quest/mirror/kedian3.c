// Room: /city/kedian3.c
// YZC 1995/12/04 
inherit ROOM;
void create()
{
	set("short", "客店二楼");
	set("long", @LONG
这是一间很大的客房，陈设十分简陋。靠墙放了十几张小木床，
不少客人正和衣而卧，满屋子都是呼呼的打酣声。西边有张床是空的，
你蹑手蹑脚地走了过去。
LONG
	);

	set("exits", ([
		"out" : __DIR__"kedian2",
	]));
	setup();
}
//是镜像
int is_mirror() { return 1; }