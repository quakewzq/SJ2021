// Room: /city/yamen.c
// YZC 1995/12/04 
inherit ROOM;
void create()
{
	set("short", "破旧大门");
	set("long", @LONG
	这里是一处古战场的遗迹，如今荒乱不堪野草丛生，传言有僵尸出没，害人性命。

LONG
	);
	set("exits", ([
		"south" : __DIR__"xidajie1",
		"north" : __DIR__"ymzhengting",
	]));
	setup();
}

//是镜像
int is_mirror() { return 1; }
