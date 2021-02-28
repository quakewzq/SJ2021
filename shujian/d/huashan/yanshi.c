// Room: /d/huashan/yanshi.c
// by daidai 

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIG"岩石"NOR);
        set("long", @LONG
这是华山山涧中一块巨大岩石的顶部，距离地面很高，站在此处可以看到
很远的地方。周围常有蛇蟒出没，耳边时常传来一声鹰鸣。
LONG    );
        set("exits", ([ 
        "down" :   __DIR__"shentan"
        ]));
        set("outdoors", "华山");
        set("no_fight", 1);
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
          write(HIC"\n你四下瞭望，突然发现远处山谷中盘踞着一条巨大的蟒蛇，蛇头竖立向上，\n"NOR);
          write(HIC"蛇信吞吐不定，嗤嗤作响。你抬头而望，天空中一头巨鹰盘旋欲下。\n"NOR);
          call_out("do_wait", 4, me);
          } else 
          {   write(HIY"突然一阵恶风刮来，你站立不稳跌下了岩石。\n"NOR);  
              me->move("/d/huashan/shentan"); // 闲人莫入 by daidai
          }                           
}
void do_wait()
{
        object me = this_player();
         if(environment(me) && me->query_temp("quest/华山派/鹰蛇生死搏/start2")){
      if(me->query_temp("quest/华山派/鹰蛇生死搏/thinking")<(5+random(5))){
           me->start_busy(5);
          if(random(2)) {
          write(HIW"\n你看到那巨鹰在半空盘旋，突然翅膀一缩急冲而下，鹰爪闪电般抓向蟒蛇，凌厉无比。\n"NOR);
     if ( random((int)me->query("kar")) > 18) {
          write(HIG"\n你心中一动，似乎有所明悟，手中不自觉的成鹰爪之状比划了几下。\n"NOR);
             me->add_temp("quest/华山派/鹰蛇生死搏/mingwu", 1);
               }
       } else {
          write(HIC"\n你看到那巨蟒盘身成阵，蛇头摇摆不定，随时欲击，防守的滴水不漏，又暗藏反击之相。\n"NOR);
     if ( random((int)me->query("kar")) > 18) {
          write(HIG"\n你心中一动，似乎有所明悟，右手不自觉的聚指成蛇形之姿，比划了几下。\n"NOR);
             me->add_temp("quest/华山派/鹰蛇生死搏/mingwu", 1);
               }
      }
             me->add_temp("quest/华山派/鹰蛇生死搏/thinking", 1);
                call_out("do_wait", 4+random(2), me);
  }
   else {
          write(HIW"\n你观看着远处鹰蛇相争，心中隐约有所领悟，但是又难以捉摸。似乎有一层薄雾挡在眼前。\n"NOR);
          write(HIW"你感到只要拨开这层薄雾，自设武学修养必定大进，当下紧皱眉头苦苦思索。\n"NOR);
             me->delete_temp("quest/华山派/鹰蛇生死搏/thinking");
          call_out("do_wait2", 4, me);     
          }
    }
}
void do_wait2()
{
        object me = this_player();
        int i,l,j;
        i= me->query("quest/华山派/鹰蛇生死搏/fail");
        l=500+random(300);
        j=10+random(20); 
         if(environment(me) && me->query_temp("quest/华山派/鹰蛇生死搏/start2")
           && me->query_temp("quest/华山派/鹰蛇生死搏/mingwu")+random((int)me->query("kar")) > 23){
           me->start_busy(2);
          write(HIG"\n你心中一动，站了起来，双手模仿鹰蛇相斗之姿比划着。你双手舞动，由杂乱渐成规律，隐约\n"NOR);
          write(HIG"形成了一些粗陋的招式。你比划一阵，感觉自己修为大为精进，加以时日就可凭今日所见创出\n"NOR);
          write(HIG"一门精妙的绝学，或许穆人清所藏武学残本会对自己大有帮助！\n"NOR); 
          me->set("quest/华山派/鹰蛇生死搏/over",1);
          me->delete_temp("quest/华山派/鹰蛇生死搏/start2");
          me->add("combat_exp", l);
          me->add("max_neili", j); 
 tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"观看鹰蛇相斗有所心得，武学修为精进，获得"+l+"点经验奖励、"+j+"点最大内力。\n"NOR);
 log_file("quest/hsys", sprintf("%s(%s) 失败%d次后观看鹰蛇相斗有所心得，武学修为精进。奖励：%d点经验，%d点最大内力。\n", me->name(1),me->query("id"), i,l,j ) );
     
          }
         else {
          write(HIR"\n你苦思冥想，依然无所收获，只好长叹一声站了起来。\n"NOR);
          me->delete_temp("quest/华山派/鹰蛇生死搏/start2");
          me->add("quest/华山派/鹰蛇生死搏/fail",1);
     log_file("quest/hsys", sprintf("%s(%s) 第%d次观看鹰蛇相斗一无所获。\n", me->name(1),me->query("id"), i));
}
             me->delete_temp("quest/华山派/鹰蛇生死搏/mingwu");
}
