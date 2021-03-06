// baoziwang.c 包子王
// Lklv 2001.9.24

inherit NPC;
inherit F_VENDOR;
void create()
{
        set_name("包子王", ({"baozi wang", "wang"}) );
        set("gender", "男性" );
        set("age", 34+random(10));
        set("long", "他白白胖胖，脸上带着微笑。\n");
        set("attitude","heroism");
        set("combat_exp", 120000 + random(50000) );
        set("shen_type", 0);
        set("per", 21 + random(5));
        set("str", 19);
        set("dex", 24);
        set("con", 25);
        set("int", 12);
        set("env/wimpy", 30);

	set_skill("unarmed", 60);
        set_skill("dodge", 65);
        set_skill("parry", 60);

        set("vendor_goods", ({
                (["name":FOOD_D("baozi"),"number": 30]),
        }));

        setup();
        carry_object(ARMOR_D("cloth"))->wear();
        carry_object(ARMOR_D("shoes"))->wear();
}
void init()
{
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
