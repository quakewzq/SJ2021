// Room: /city/neizain.c
// YZC 1995/12/04 
inherit ROOM;
void create()
{
	set("short", "内宅");
	set("long", @LONG
	这里是衙门的内宅，住着知府的家眷。外人到此就该止步了。
LONG
	);
	set("exits", ([
		"south" : __DIR__"ymzhengting",
	]));

	setup();
}

//是镜像
int is_mirror() { return 1; }