// kid.c

inherit NPC;

void create()
{
	set_name("小孩",({ "xiao hai", "xiaohai", "kid" }) );
        set("gender", "男性" );
        set("age", 7);
        set("long", "这是个农家小孩子\n");
        set("combat_exp", 500);
	set("str", 11);
	set("dex", 11);
	set("con", 11);
	set("int", 11);
        setup();
	carry_object("/clone/misc/cloth")->wear();
}