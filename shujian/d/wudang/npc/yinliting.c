// yinliting.c殷梨亭
// by ydh

inherit NPC;

int ask_me_1(string);

void create()
{
        set_name("殷梨亭", ({ "yin liting", "yin" }));
        set("nickname", "武当六侠");
        set("long", 
                "他就是张三丰的六弟子殷梨亭。\n"
                "长得一表人才，且精于武当剑法，就是生性较腼腆。\n");
        set("gender", "男性");
        set("age", 28);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 26);
        set("int", 30);
        set("con", 26);
        set("dex", 28);
        
        set("max_qi", 1200);
        set("max_jing", 800);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);
        set("combat_exp", 100000);
        set("score", 50000);

        set_skill("force", 80);
        set_skill("yinyun-ziqi", 60);
        set_skill("dodge", 80);
        set_skill("tiyunzong", 60);
        set_skill("cuff", 80);
        set_skill("taiji-quan", 60);
        set_skill("parry", 80);
        set_skill("sword", 80);
        set_skill("taiji-jian", 90);
        set_skill("taoism", 80);
        set_skill("literate", 80);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
        prepare_skill("cuff", "taiji-quan");
        create_family("武当派", 2, "弟子");
        set("inquiry", ([
                "纪晓芙" : (: ask_me_1 :),
        ]));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
}

int ask_me_1(object who)
{ object me;
  me=this_player();
  command("blush "+(string)me->query("id"));
  command("say 既然你是纪姑娘的朋友,那就给你行个方便吧!\n");
  message_vision("殷梨亭一侧身,把$N让进了小院。\n",me);
  me->move("/d/wudang/xiaoyuan");
  return 1;
}

