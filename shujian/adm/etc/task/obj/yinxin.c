

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("总镖头印信",({"yin","yinxin"}));
	set_weight(400);
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("task_owner","lin zhennan");
		set("task_owner_cname","林震南");
		set("reward_point",8);
		set("unit","个");
		set("no_sell",1);
                set("no_beg",1);
		set("value",2000);
	}
	
	setup();
	
}
