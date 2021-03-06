//chutou.c 锄头，采矿专用
//Modified By ChinaNet
//By 2004/1/11

//增加mining技能与次数的关系。
//增加放弃次数与采矿成功的关系。
//增加采矿成功率与技能的关系
//Modified By ChinaNet
//by 2004/3/10
// add exp By ChinaNet
//by 2004/4/28
// By Spiderii 修改mining为caikuang
#include <weapon.h>
inherit STAFF;
#include "../place.h"

void create()
{
        set_name("锄头", ({ "chu tou", "tou", "chu" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("unit", "把");
                set("long", "这是一把锄头，用来开山凿地(mine)是最好不过的了。\n");
                set("value", 1);
                set("material", "steel");
                set("wield_msg", "$N拿出一把$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n抗在肩上。\n");
                set("no_drop","现在是扔的时候嘛？");
                set("no_get","一个破锄头你也拣？");
        }
        init_staff(4);
        setup();
}

void init()
{
 	add_action("do_wield","wield");
 	add_action("do_mine","mine");
}

int do_wield(string arg)
{
	object me, ob;
	me = this_player();
	ob = this_object();
	
	if( !arg ) 
		return 0;
	if (arg == "all" )
		return 1;
		
	if (arg == "chu" || arg == "tou" || arg == "chu tou") 	
	{
		if(ob->query("user")!= me->query("id") )
		{
			tell_object(me,"这位" + RANK_D->query_respect(me) +"不要乱动别人的东西，这个习惯不好。\n");
			return 1;
		}
	}
	return 0;
}

int do_mine(string arg)
{
	object me, ob, item, mine, where;
	object killer;
	string level, str;
	int times, count, fail, success,i,j,k,exp;
	
	ob = this_object();
	me = this_player();
	where = environment(me);
	item = me->query_temp("weapon");
	level = me->query_temp("minejob/level");
	
	if (arg) 
		return notify_fail("你要做什么？\n");
	if (ob->query("user") != me->query("id")) 
		return notify_fail("你要做什么？\n");
	
	if (!item || item->query("id") != "chu tou")
		return notify_fail("你要用手挖吗？\n");
		
	if (!me->query_temp("minejob/ask"))
		return notify_fail("没事挖地做什么？\n");

	if (file_name(where) != me->query_temp("minejob/area"))
		return notify_fail("此地并无什么特别之处，你要做什么？\n");
		
	if (me->is_busy())
		return notify_fail("你现在正忙着呢。\n");
		
	if (me->query_temp("minejob/type") != "开采")
		return notify_fail("你～你～～你～～～还是算了吧。\n");
	
	if (me->query_temp("minejob/find"))
		return notify_fail("你已经开采完了矿石，速回冯铁匠处。\n");
	
	if (me->is_fighting())
		return notify_fail("你～你～～你～～～还是忙完了再说吧。\n");
		
	if (me->query("jingli") < 500)
		return notify_fail("你的精力不够。\n");
		
	if (me->query("neili") < 500)
		return notify_fail("你的内力不够。\n");

	str="\n$N朝手心啐了两口唾沫，举起锄头，用起全身的力气，抡圆了胳膊一锄头砸了下去。\n";
	
	me->add_temp("minejob/times",1);
	
//成功与失败对比。
	i = me->query("minejob")/10;
	j = me->query("minejob_failed");
//add exp by chinanet
	if ( i > j && j < 500)
		exp = i - j;
	else 	exp = 1;
	
	if( exp > 10 ) exp = 10 ;
	if( exp < 0 ) exp = 1;

//采矿成功率与技能的关系
   k = me->query_skill("caikuang",1);
   if (k > 300)
   { 
   me->add_temp("minejob/success",1);
   me->add("combat_exp",exp );
   }
   else if (random(20) > 10 && me->query_temp("minejob/level") == "veryhard" && k > 200)
	{		
		me->add_temp("minejob/success",1);
		me->improve_skill("caikuang", i + random(i) );
		me->add("combat_exp",exp );
	}
	else if	(random(20) > 8 && me->query_temp("minejob/level") == "hard" && k > 150)
	{		
		me->add_temp("minejob/success",1);
		me->improve_skill("caikuang", i + random(i) );
		me->add("combat_exp",exp );
	}
	else if	(random(20) > 5 && me->query_temp("minejob/level") == "normal" && k > 200)
	{		
		me->add_temp("minejob/success",1);
		me->improve_skill("caikuang", i + random(i) );
		me->add("combat_exp",exp );
	}
	else
	{
		me->add_temp("minejob/fail",1);
            me->improve_skill("caikuang", 10);
		me->add("combat_exp",1 );
	}
//
	fail = me->query_temp("minejob/fail");
	success = me->query_temp("minejob/success");
	times = me->query_temp("minejob/times");
	count = me->query("con") + random(me->query_con());
	me->add("neili", -count);
	me->add("jingli", -count*3/2);
	
	switch (level)
	{		
		case "veryhard":
			str += "似乎没什么变化，但$N信心十足，毫不气馁。\n";
			if (success > 20 && success > fail && i > j && random(20) > 10)
			{
				str += "$N觉得眼前一亮，一块闪亮的矿石露了出来。$N兴奋地将锄头扔掉了。\n";
				mine = new(__DIR__"mine.c");
				mine = settings_mine(level, mine);
				mine->move(me);
				me->set_temp("minejob/find",1);
				log_file("job/minejob",sprintf("%s %s(%s)挖到了%s级别的矿石。成功%i次，失败%i次。\n",
					ctime(time())[4..19],me->name(1),capitalize(me->query("id")),mine->query("level"),success,fail));
			}
			else if (fail > 20 || success > 30 && success>fail)
			{
				str += "在飞溅的沙尘当中$N好像看到了一块乌黑的东西，就随手捡了起来。$N想都没想就将锄头扔掉了。\n";
				mine = new(__DIR__"mine.c");
				mine->move(me);
				me->set_temp("minejob/find",1);
				log_file("job/minejob",sprintf("%s %s(%s)挖%s级别的矿石失败。成功%i次，失败%i次。\n",
					ctime(time())[4..19],me->name(1),capitalize(me->query("id")),mine->query("level"),success,fail));
			}
			break;
		case "hard":
			str += "顿时尘土飞扬，路边众人不由得皱起了眉头，可$N仍然视而不见。\n";
			if (success > 16 && random(20) > 8 && i > j && success > fail)
			{
				str += "尘土渐渐散去，地上隐约有一块光彩的石头。$N高兴地将锄头扔掉了\n";
				me->set_temp("minejob/find",1);
				mine = new(__DIR__"mine.c");
				mine = settings_mine(level,mine);
				mine->move(me);
				log_file("job/minejob",sprintf("%s %s(%s)挖到了%s级别的矿石。成功%i次，失败%i次。\n",
					ctime(time())[4..19],me->name(1),capitalize(me->query("id")),mine->query("level"),success,fail));

			}
			else if (fail > 30 || success > 30)
			{
				str += "在飞溅的沙尘当中$N好像看到了一块乌黑的东西，就随手捡了起来。$N想都没想就将锄头扔掉了。\n";
				mine = new(__DIR__"mine.c");
				mine->move(me);
				me->set_temp("minejob/find",1);
				log_file("job/minejob",sprintf("%s %s(%s)挖%s级别的矿石失败。成功%i次，失败%i次。\n",
					ctime(time())[4..19],me->name(1),capitalize(me->query("id")),mine->query("level"),success,fail));
			}
			break;
		case "normal":
			str += "看来$N力气不小，地上居然被$N砸了一个无底洞。\n";
			if (success > 8 && i > j && random(20) > 6)
			{
				str += "洞中依稀可以看到一块金属光泽的石头。$N随手地将锄头扔掉了。\n";
				me->set_temp("minejob/find",1);
				mine = new(__DIR__"mine.c");
				mine = settings_mine(level,mine);							
				mine->move(me);
			}
			else if (fail > 20 || success > 20)
			{
				str += "在飞溅的沙尘当中$N好像看到了一块乌黑的东西，就随手捡了起来。$N想都没想就将锄头扔掉了。\n";
				mine = new(__DIR__"mine.c");
				mine->move(me);
				me->set_temp("minejob/find",1);
			}
			break;
		case "easy" :
			str += "结果“咣噹”一声锄到了地上，震得$N手臂发麻。\n";
			if (fail > 10 || success > 10)
			{
				str += "在飞溅的沙尘当中$N好像看到了一块乌黑的东西，就随手捡了起来。$N想都没想就将锄头扔掉了。\n";
				mine = new(__DIR__"mine.c");
				mine->move(me);
				me->set_temp("minejob/find",1);
			}
			break;
	}
	
	message_vision(str,me);

	if (!wizardp(me)) 
		me->start_busy(1+random(3));
	if (wizardp(me)) 
		tell_object(me,"你本次" + me->query_temp("minejob/level") + "级任务已经采了" + times + "次矿石。成功次数："
			+ me->query_temp("minejob/success") + "。失败次数：" + me->query_temp("minejob/fail") + "。\n");


	if (me->query_temp("minejob/find")) 
	{
//添加材质描述 2004/2/1 by ChinaNet
		mine->set("long",mine->query("long")+"看起来是由"+mine->query("material")+"构成。\n");
//添加抢矿人
//by ChinaNet 2004/1/29

		if (me->query_temp("minejob/killer") == 1)
		{
			killer = new(__DIR__"robber.c");
			killer->set_temp("target",me->query("id"));
			killer->set_temp("level",mine->query("level"));
			killer->move(where);		
			killer->set("long",killer->query("long")+"他高高兴兴的样子，看起来是刚刚抢劫了"+me->query("name")+"("+me->query("id")+")的矿石。\n");
			mine->add("value",random(50000)+50000);
			mine->move(killer);
			str = HIR"\n$N正在欣喜，突然之间，一个身影在眼前掠过，$N猛然醒觉，身上的"+mine->query("name")+HIR"已经不见了。\n"NOR;
			message_vision(str,me);
		}
	destruct(ob);
	}
	return 1;
}
