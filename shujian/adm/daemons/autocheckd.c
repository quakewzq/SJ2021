//#pragma optimize all

#include <ansi.h>

inherit F_DBASE;

void auto_check(int duration);


void create()
{
        seteuid(getuid());
        set("name", "监控精灵");
        set("channel_id", "监控精灵(ROOT)");
        set("id", "autocheck");

        CHANNEL_D->do_channel( this_object(), "sys", "监控精灵已经启动。\n");

        remove_call_out("auto_check");
        call_out("auto_check", 10, 0);
}

void auto_check(int duration)
{
/*
            object *list;
	    int t;
	    int j;
	    int i;
	    int flag;
		
	    list = filter_array(objects(), (: userp :));
	    j=sizeof(list);
	    while( j-- ) {
	        if( !environment(list[j]) 
	        || !interactive(list[j])  ) continue;
	        //auto record pot 异常
	        
	        if(list[j]->query("potential")>list[j]->query("max_pot"))
	        	log_file("nosave/autocheck",
	        	sprintf("%-23s pot:%-10d max_pot:%-10d",
	        	list[j]->name(1)+"("+list[j]->query("id")+")",
	        	list[j]->query("potential"),
	        	list[j]->query("max_pot")
	        	)
	        	);
	        	
	        if((list[j]->query("kar")>30||list[j]->query("pur")>30)&&!wizardp(list[j]))
	        	log_file("nosave/autocheck",
	        	sprintf("%-23s kar:%-10d kur:%-10d",
	        	list[j]->name(1)+"("+list[j]->query("id")+")",
	        	list[j]->query("kar"),
	        	list[j]->query("pur")
	        	)
	        	);
	        
	        if((list[j]->query("mud_age") - list[j]->query_temp("mud_age"))<=0) continue;
	        //因为在char.c 里控制了8M
	        if(list[j]->query("combat_exp") < 8000000) continue;
	        i = (list[j]->query("combat_exp") - list[j]->query_temp("combat_exp")) * 60
	                / (list[j]->query("mud_age") - list[j]->query_temp("mud_age"));
	        if (i < 120) continue;
	        t = list[j]->query("mud_age") - list[j]->query_temp("mud_age");
	                   
	        log_file("nosave/autocheck",
					sprintf("%-23s%-16d %-16d%-3d／%-16d%s\n",
						                (list[j]->is_robot()?(HIG+list[j]->name(1)+NOR):list[j]->name(1))+"("+list[j]->query("id")+")",
						                list[j]->query_temp("combat_exp"), 
						                list[j]->query("combat_exp"),
						                i,
						                i*60,
						                CHINESE_D->chinese_time(t)
						            )
						);
						flag = 1;
	

	        
	    }      
        if (flag)
        	        CHANNEL_D->do_channel( this_object(), "sys",sprintf("系统发现玩家速度异常，请检查。"));
*/
        CHANNEL_D->do_channel( this_object(), "sys",sprintf("系统自动清除 " + reclaim_objects() + " 个变数。"));
        remove_call_out("auto_check");
        call_out("auto_check", 50+random(10), duration); //轮一次的时间是35*13
}
