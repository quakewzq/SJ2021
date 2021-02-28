// yushizhe.c
// player modify 2018.11.1

inherit NPC;

#include "/d/zhiye/npc/forbook.c"
#define JADE    "/d/zhiye/obj/othermaterial" //玉
//#define JADE    "/d/zhiye/obj/buliao" 
void getyu(object me)//
{
       	object obj;
		//object me;
		int level = 1;
                
        if(!me) return;
        
        if(environment(me)!=environment(this_object())) return;
        
       // if(!random(2)) level+=1;
       // if(!random(3)) level+=1;
       // if(!random(4)) level+=1;
       // if(!random(5)) level+=1;
       // level = 2+random(4) ;
		level = 6 ;
        obj = new(JADE);
		obj->set_level(level);
        
        if(obj)
        {
                message_vision("$N翻箱到柜拿出一块"+obj->name()+"。\n",this_object());
                message_vision("$N给$n一块"+obj->name()+NOR"。\n",this_object(),this_player());
                command("say 我这儿也没什么好的东西，此物你可以拿去参详，上班时间还是少玩MUD，等将来你历练多了，或许能有多体会。");
                message_vision(HIY"$N背过身去，喃喃自语：「或许只有当时不玩，或者不被抓，那现在......」\n"NOR,this_object() );
                
               obj->move(this_player());
              // this_player()->start_busy(-1);
               //this_player()->interrupt_me();                
             //  this_object()->interrupt_me();
              // this_object()->start_busy(-1);
              // this_object()->interrupt_me();
			          }

}

void create()
{
        set_name("人间天使", ({ "renjian tianshi","renjian", "tianshi", "tian","shi" }) );
        set("gender", "男性" );
        set("age", 34);
		set("per", 40);
        set("long",
                "他因为上班时间玩MUD，被贬下凡,专门负责给玩家玉的天使。
看似普通得不能再普通了。
只是偶尔从他沧桑的双目中流露出对往日岁月的留恋。\n");
        set("combat_exp", 300);
        set("attitude", "peaceful");
        set("rank_info/respect", "玉天使");
        set("inquiry", ([
                "story" : "往事不要再提，人生已多风雨。\n",
                "宝玉": (: getyu :), 
        ]) );
        set("forg_type","all");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}


