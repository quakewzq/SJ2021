// /kungfu/class/nshaolin/da-chi.c 大痴
// looklove 2001.7.21

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("大痴大师", ({
                "dachi dashi",
                "dachi",
                "dashi",
        }));
        set("long",
                "他鹤发童颜，笑容可掬，举手投足间显然身怀高深武功。\n"
        );

        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");
	set("title", "藏经阁主座");

        set("age", 62);
        set("shen_type", 100);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 3800);
        set("max_jing", 2200);
        set("neili", 18000);
        set("max_neili", 8000);
        set("jiali", 250);
        set("combat_exp", 2600000);

        set_skill("force", 260);
        set_skill("yijin-jing", 260);
        set_skill("dodge", 260);
        set_skill("shaolin-shenfa", 260);
        set_skill("parry", 260);
        set_skill("leg", 260);
        set_skill("hand", 260);
        set_skill("qianye-shou", 260);
        set_skill("ruying-suixingtui", 260);
        set_skill("buddhism", 200);
        set_skill("literate", 160);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "ruying-suixingtui");
        map_skill("leg", "ruying-suixingtui");
        map_skill("hand", "qianye-shou");

        prepare_skill("leg", "ruying-suixingtui");
        prepare_skill("hand", "qianye-shou");

	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: perform_action, "hand.qianshou" :),
		(: perform_action, "leg.ruying" :),
	}));

        create_family("南少林", 22, "弟子");

        setup();

	carry_object("/d/shaolin/obj/xuan-cloth")->wear();
	carry_object("/d/shaolin/obj/sengxie")->wear();
}

