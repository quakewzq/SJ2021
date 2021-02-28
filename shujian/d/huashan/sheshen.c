// Room: /d/huashan/sheshen.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "舍身崖");
 set("long", @LONG
这是一段极窄极险的山崖，四周云雾飞绕，下面渊深无底。如不小心，一
失足掉下去，只怕连骨头都找不到。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "eastdown" : __DIR__"canglong",
 ]));

 set("no_die", 1);
        set("no_clean_up", 0);
        set("outdoors", "华山" );

        set("coor/x",60);
  set("coor/y",50);
   set("coor/z",70);
   setup();
}
void init()
{
        add_action("do_climb","climb");

}
int do_climb(string arg)
{
        object me = this_player();
        int time;
	 time = time() - me->query("quest/hama/time");

        if (arg!="up") 
        return notify_fail(HIG"这个方向没办法爬。\n"NOR);

        if (me->query_skill("dodge",1) < 200)
        return notify_fail(HIG"你爬了半天毫无进展，还是回去练练轻功在来吧。\n"NOR);
        
        
        if (me->query("oyf/hamagong") < 2)
        return notify_fail(HIG"你还是死了这条心吧。\n"NOR);     

        if (me->query("oyf/hamagong") == 3)
        return notify_fail(HIG"你已经见过你义父最后一面了。\n"NOR);     

/*	 if (me->query("quest/jiebai/super") >=3 && me->query("registered") < 3)
        return notify_fail(HIG"你义父都死了多年了，不要来这伤心地了。\n"NOR);  
*/
         if ( me->query("quest/hama/time") && time < 86400 ) 
        return notify_fail(HIG"你来的太勤了些吧。\n"NOR);  
        if ( me->query("combat_exp") < 6000000 ) 
        return notify_fail(HIG"你经验不足来了也没有用。\n"NOR);  
        
        if (me->query("jingli") < 1500)
        return notify_fail(HIG"你精神不好，还是歇歇再爬吧，小心送了小命！\n"NOR);

        me->add("jingli",-500);

        message_vision(HIG"$N手脚并用，使出了吃奶的力气终于爬了上来。\n"NOR,me);
        me->move("/d/huashan/hamasuperquest/jueding1");
        return 1;
}

