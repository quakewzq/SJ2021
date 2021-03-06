// Room: /d/huashan/fanting.c
// Date: Look 99/03/25
// By Spiderii@ty 取消主动送饭
inherit ROOM;

#include <ansi.h>

void create()
{
	set("short", "饭厅");
	set("long", @LONG
这里便是华山派弟子用饭的地方。饭厅不是很大，但窗明几净。桌上摆着
一些食物，让人垂涎欲滴。不时有一些华山弟子走来走去，想是在忙些什么。
LONG
	);

	set("exits", ([
		"north" : __DIR__"yaofang",
		"east" : __DIR__"celang3",
	]));
	set("objects",([
			__DIR__"npc/puren" : 1,
        	__DIR__"obj/qingshui-hulu" : 1,
	]));
	set("indoors", "华山" );
	setup();
}

int not_at_all(string arg)
{
	if (arg == "all") {
		write("仆人说道：这里地方本来就小，动作轻点。\n");
		return 1;
	}
	return 0;
}

int valid_leave(object me, string dir)
{
	if ( present("pu ren", environment(me))
       && (present("rice", me)
	  || present("fanqie yaoliu", me) || present("kousansi", me)
	  || present("niurou", me) || present("huasheng", me)
	  || present("tangcu liyu", me) || present("zhuachao liji", me)
	  || present("jitui", me) || present("rou pian", me)
	  || present("doufu", me) || present("douhua", me)
	  || present("liangxi cuishan", me) )
	  && ( dir == "east" || dir == "north" ) )
	{
		return notify_fail("仆人说道：就在这里趁热吃吧，带走干什么？\n");
	}
	return ::valid_leave(me, dir);
}
