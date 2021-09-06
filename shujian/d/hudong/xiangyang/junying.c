inherit ROOM;

void create()
{
        set("short", "蒙古军营");
        set("long", @LONG
这里是蒙古攻击襄阳的临时军营，时时有士兵来回巡逻。
往西南便能到达襄阳。
LONG
        );
        set("xyjob", 1);
        set("outdoors", "襄阳");
        set("objects", ([
                __DIR__"npc/weishi" : 3,
        ]));

        set("exits", ([
		"southwest" : __DIR__"outnroad2",
                "enter" : __DIR__"yingzhang",
        ]));

	setup();
}
int valid_leave(object me, string dir)
{
      if ((dir == "enter") 
      && (me->query_temp("xyjob/xy_defend")) 
      && (present("weishi", this_object())))
      return notify_fail("你还是先杀掉门口的卫士再说吧。\n");
      return ::valid_leave(me, dir);
}
