// /d/xingxiu/silk1.c
// June 97
// by pishou

inherit ROOM;

void create()
{
        set("short", "丝绸之路");
        set("long", @LONG
这是闻名中外的丝绸商道。迎面而来的是一个个沙包，星罗棋布於荒原之
上。一阵风沙吹过，象刀割一样撕裂着你的脸。东南过仇池山通往嘉峪关，西
面则是颂摩崖。
LONG);
        set("outdoors", "yili");

        set("exits", ([
                //"westup" : __DIR__"silk3",
                "south" : __DIR__"silk1",
        ]));

        set("objects", ([
                __DIR__"npc/shangren" : 1,
        ]));

        set("coor/x",-240);
  set("coor/y",90);
   set("coor/z",-10);
   set("coor/x",-240);
  set("coor/y",90);
   set("coor/z",-10);
   set("coor/x",-240);
 set("coor/y",90);
   set("coor/z",-10);
   setup();
}

void init()
{
	object memory;
	string start_room;
	object me=this_player();
	
	memory = me->query_temp("mirror/mirror_memory");
	
	if (!me->query_temp("smy_job"))
	{
		set("exits/westup", __DIR__"silk3");
	}
	
	if (memory && me->query_temp("fuben/smy")=="start" && memory->query("user_id/1")==me->query("id"))
	{
		//start_room = me->query_temp("mirror/start_room");
		start_room = me->query_temp("mirror/start_room")+"";
		//你一看东边有一座高山，山势险峻，正是鲁长老所说的颂摩崖，便不再犹豫，毅然提气飞纵而上！
		//tell_object(me,HIG"你一看东边有一座高山，山势险峻，正是鲁长老所说的颂摩崖，便不再犹豫，毅然提气飞纵而上！\n"NOR);
		set("exits/westup",start_room);
	
	}
	else
		if (me->query_temp("fuben/smy")!="start" || !memory || memory->query("user_id/1") != me->query("id"))
		set("exits/westup", __DIR__"silk3");
	
}

#include "/d/xingxiu/job2.h";
