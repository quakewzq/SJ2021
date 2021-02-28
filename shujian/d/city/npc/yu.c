// gongzi.c
// Lklv modify 2001.9.27

inherit NPC;

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

void getyu()
{

	int i,j;
       object me = this_player();
       object obj;
       i = random(4)?4:5 ; 
        obj = new("/d/zhiye/obj/othermaterial");
        if(obj && obj->set_level(i+1,1))
        {
                obj->move(this_player());
                message_vision(HIW"$N从宝盒中得到了一"+obj->query("unit")+obj->name()+"。\n\n"NOR,me); 
        }
                destruct(this_object());
                return 1;
}