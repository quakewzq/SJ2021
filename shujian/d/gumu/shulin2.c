// Room: /d/gumu/shulin2.c
#include <ansi.h>
inherit ROOM;
void create()
{
     set("short", GRN"灌木丛"NOR);
     set("long", @LONG
好不容易走出了大树林，你已置身于一片灌木丛中，荆棘满地，蛇虫遍
布，令你举步维艰。你茫然四顾，依稀一条小路蜿蜒下行。
LONG);
     set("exits", ([
         "east" : __DIR__"shengou",
         "west" : __DIR__"sl4",
     ]));    
     setup();
}

void init()
{
   int i,j = 0;
   object* ppl;
   object me = this_player();       
ppl=users();
   i = sizeof(ppl);
   while(i--){
   if( userp(ppl[i])&& !wizardp(ppl[i])&& ppl[i]->query("oyf/hamagong"))
                j++;
}

if(me->query("oyf/son")) {
me->delete("oyf/son");
me->set("oyf_son",1);
}
      	if(me->query_skill("hamagong", 1) > 64 &&
           me->query_skill("hamagong", 1) < 800 &&
           me->query("age") >= 18 &&
           random(10)==9  && 
           me->query("oyf_son") && 
           me->query("oyf/hamagong") < 2 &&
           random(me->query("kar")) >=25 
//          ( (!me->query("buyvip")&& j<= 2 )|| me->query("buyvip")) 
//           && time() - me->query("quest/hama2/time") > 86400
            )
           	call_out("do_wait", 5, me);
}

void do_wait(object me)
{
	if( !me ) return;
	if( environment(me) != this_object() ) return;
        write("\n你突然觉得心中烦恼之极，便坐在草地上发起呆来。\n");
        me->set_temp("oyf_wait", 1);
        call_out("do_idle", 30, me);
}

void do_idle(object me)
{   
	if( !me ) return;
	if( environment(me) != this_object() 
	|| !me->query_temp("oyf_wait") ) return;
	   
   //     if (random((int)me->query("kar")) > 22 && (int)me->query("con") > 24 && me->query("buyvip")) {
    if (random((int)me->query("kar")) > 22 && (int)me->query("con") > 24 ) {
          	write("\n突然你隐隐听得呼呼风响，声音劲急，非同寻常。侧耳听去，正是有人相斗的拳声掌风。\n");
          	write("你心下一惊，听出那掌声熟悉之极。\n");
          	message_vision(GRN"\n$N猛地跳了起来，两个起落，已窜进了树林深处。\n"NOR,me);                 
          	me->delete_temp("oyf_wait");
          	me->move(__DIR__"shulin");
        }
       	else{
          	write("你猛然想起江湖世界变幻莫测，义父又不知道去了哪里，一阵伤感涌上心头。\n");
          	me->delete_temp("oyf_wait");
                me->set("quest/hama2/time",time());
          	message_vision(CYN"$N深深地叹了口气。\n"NOR,me);
       }                      
}

int valid_leave(object me, string dir)
{
        if (me->query_temp("oyf_wait"))
                me->delete_temp("oyf_wait");     
        return ::valid_leave(me);
}
