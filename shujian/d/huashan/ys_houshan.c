// Room: /d/huashan/ys_houshan.c
//by daidai 

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "后山");
        set("long", @LONG
这是华山后山里的一个山谷，两边是陡峭光滑的山壁。谷底阴暗潮湿，
似乎很适合蛇类动物生长，高耸的峭壁上偶尔传来几声鹰鸣。
LONG    );      set("outdoors", "华山");
        set("coor/x",30);
  set("coor/y",70);
   set("coor/z",-10);
   setup();
}

void init()
{
     object me = this_player();
       
       if(me->query_temp("quest/华山派/鹰蛇生死搏/start2")){     
          me->start_busy(5);
          write(HIC"\n你走到此处突然听到远处隐约传来一声鹰鸣。\n"NOR);
          write(HIC"你心中一动，立即停下来侧耳仔细聆听。\n"NOR);
          call_out("do_wait", 4+random(4), me);
          }                               
}
void do_wait()
{
        object me = this_player();
         if(environment(me) && me->query_temp("quest/华山派/鹰蛇生死搏/start2")){
          write(HIW"\n突然间又传来一声鹰鸣，你仔细辨认似乎是从东北方向传来的。\n"NOR);
          write(HIY"\n你不再延迟，爬上东北方向的一块岩石，四下瞭望。\n"NOR);       
           me->move("/d/huashan/yanshi");      
          }
}
