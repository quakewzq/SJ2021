// dating.c 大厅
// By Spiderii@ty 加入yttlg quest
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "武当大厅");
	set("long", @LONG
这是武当山紫宵宫的大厅,因为今天是武当派祖师张三丰的九十寿辰之日,所以
四周被人布置的很有气氛。正中间一个大大的寿字,透露着喜庆。可惜此时此刻
却让人生出悲凉之意。只见大厅上一人背负着双手，不停步地走来走去。
LONG
	);

        setup();
}
void init()
{
  object me;
  me = this_player();
  if (me->query_temp("quest/yttlg/story2"))
  {
     remove_call_out("bihua");
     call_out("bihua", 3, me);      
     write(CYN"\n你见大厅中这人身长背厚，步履凝重，正是师父。\n"NOR);
}
}
void bihua(object me)
{
  if(!me) return;

   tell_object(me,HIC"\n只见张三丰走了一会，仰视庭除，忽然伸出右手，在空中一笔一划的写起字来。\n"NOR); 
   tell_object(me,HIC"\n张三丰文武兼资，吟诗写字，弟子们司空见惯，也不以为异。\n"NOR);
   tell_object(me,HIC"\n你顺着他手指的笔划瞧去，原来写的是“丧乱”两字，连写了几遍，跟着又写“荼毒”两字。\n"NOR); 
   tell_object(me,HIC"\n你心中一动：“师父是在空临‘丧乱帖’。”\n"NOR);
   tell_object(me,HIC"\n这时你躲在柱后见师父以手指临空连书“羲之顿首：丧乱之极，先墓再离荼毒，追惟酷甚”这十八个字。\n"NOR); 
   tell_object(me,HIC"\n一笔一划之中充满了拂郁悲愤之气，登时领悟了王羲之当年书写这“丧乱帖”时的心情。\n"NOR);
   remove_call_out("bihua1");
   call_out("bihua1", 10, me);      
}
void bihua1(object me)
{
  if(!me) return;

   tell_object(me,HIC"\n王羲之是东晋时人，其时中原板荡，沦于异族，王谢高门，南下避寇，于丧乱之余，\n"NOR); 
   tell_object(me,HIC"\n先人坟墓惨遭毒手，自是说不出满腔伤痛，这股深沉的心情，尽数隐藏在“丧乱帖”中。\n"NOR);
   tell_object(me,HIC"\n此时你身遭师兄存亡莫测的大祸，方懂得了“丧乱”两字、“荼毒”两字、“追惟酷甚”四字。\n"NOR); 
   tell_object(me,HIC"\n张三丰写了几遍，长长叹了口气，步到中庭，沉吟半晌，伸出手指，又写起字来。这一次写的字体又自不同。\n"NOR);
   tell_object(me,HIC"\n你顺着师父的手指走势看去,但看第一字是个“武”字，第二个写了个“林”字，一路写下来，共是二十四字。\n"NOR); 
   tell_object(me,HIC"\n正是适才提到过的那几句话：“武林至尊、宝刀屠龙。号令天下，莫敢不从。倚天不出，谁与争锋？”\n"NOR);
   remove_call_out("bihua2");
   call_out("bihua2", 10, me);      
   write(CYN"\n你暗暗猜想,师父定是琢磨这二十四个字中所含的深意，来推想俞师哥因何受伤。\n"NOR);


}
void bihua2(object me)
{
  if(!me) return;

   tell_object(me,HIC"\n只见张三丰写了一遍又是一遍，那二十四个字翻来覆去的书写，笔划越来越长，手势却越来越慢。\n"NOR); 
   tell_object(me,HIC"\n到后来纵横开阖，宛如施展拳脚一般。\n"NOR);
   tell_object(me,HIC"\n你凝神观看，心下又惊又喜，师父所写的二十四个字合在一起，分明是套极高明的武功。\n"NOR); 
   tell_object(me,HIC"\n每一字包含数招，便有数般变化。“龙”字和“锋”字笔划甚多，“刀”字和“下”字笔划甚少。\n"NOR);
   tell_object(me,HIC"\n但笔划多的不觉其繁，笔划少的不见其陋，其缩也凝重，似尺蠖之屈，其纵也险劲，如狡兔之脱。\n"NOR); 
   tell_object(me,HIC"\n淋漓酣畅，雄浑刚健，俊逸处如风飘，如雪舞，厚重处如虎蹲，如象步。”\n"NOR);
   remove_call_out("bihua3");
   call_out("bihua3", 10, me);      
   write(CYN"\n你于目眩神驰之际，随即潜心记忆。。\n"NOR);


}
void bihua3(object me)
{
  if(!me) return;

   tell_object(me,HIC"\n这二十四个字中共有两个“不”字，两个“天”字。\n"NOR); 
   tell_object(me,HIC"\n但两字写来形同而意不同，气似而神不似，变化之妙，又是另具一功。\n"NOR);
   tell_object(me,HIC"\n张三丰寿诞之日,遭此大变,情之所至，将这二十四个字演为一套武功。\n"NOR); 
   tell_object(me,HIC"\n这一套拳法，张三丰一遍又一遍的翻覆演展，足足打了两个多时辰。\n"NOR);
   tell_object(me,HIC"\n待到月涌中天，他长啸一声，右掌直划下来，当真是星剑光芒。\n"NOR); 
   tell_object(me,HIC"\n如矢应机，霆不暇发，电不及飞，这一直乃是“锋”字的最后一笔。”\n"NOR);
   tell_object(me,HIC"\n张三丰仰天遥望，说道：“徒儿，这一路书法如何？”。\n"NOR); 
   tell_object(me,HIC"\n你吃了一惊，想不到自己躲在柱后，师父虽不回头，却早知道了。”\n"NOR);
   tell_object(me,HIC"\n你当即走到厅口，说道：“弟子得窥师父绝艺，真是大饱眼福。我去叫大师哥他们出来一齐瞻仰，好么？”\n"NOR);
   tell_object(me,HIC"\n张三丰摇头道：“我兴致已尽，只怕再也写不成那样的好字了。远桥、松溪他们不懂书法，便是看了，也领悟不多。”\n"NOR);
   tell_object(me,HIC"\n张三丰袍袖一挥，说道:你也下去吧。说罢进了内堂。\n"NOR);
   me->set_temp("quest/yttlg/ask",1);
   me->delete_temp("quest/yttlg/story2",1);   
   me->move("/d/wudang/sanqing");

}
