// Modified by Darken@SJ for tsjob

#include <ansi.h>;
inherit NPC;

int ask_tsjob();
int ask_tsjobtime();
int ask_tsj();

void create()
{
        object ob;
        set_name("天门道人", ({ "tianmen daoren", "daoren", "tianmen" }) );
        set("gender", "男性");
        set("title", HIW"泰山派第十三代掌门"NOR);
        set("class", "taoist");
        set("age", 55);
        set("attitude", "peaceful");
        set("unique", 1);
        set("str", 28);
        set("con", 18);
        set("dex", 20);
        set("int", 18);

        set("jiali", 120);
        set("combat_exp", 4450000);
        set("shen_type", 1);
        set("inquiry", ([
                "左冷禅" : "这厮想让五岳同盟，是想让我们帮他效命罢了。。\n",
                "东灵道人" : "大胆，你尽干直呼我祖师爷的名字，\n",
//                "叛徒" : (: ask_tsjob :),
                "功劳" : (: ask_tsjobtime :),
                "泰山剑法" : (: ask_tsj :),
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
         	"天门道人怒不可遏，大声道：“我只是一时的气话，本派掌门人之位，岂能如此草草……草草传授。\n",
         	"天门道人叹息道：象玉玑子这种人，我是万万不能传授他为掌门。\n",
         	"天门道人怒吼：“你们真要打？那就来拚个你死我活。\n",
        	(: command("sneer") :),
        	(: command("pei") :),
        }) );

        set_skill("sword", 350);
        set_skill("force", 350);
        set_skill("parry", 350);
        set_skill("dodge", 320);
        set_skill("cuff", 300);
        set_skill("yinyun-ziqi", 350);
        set_skill("taizu-quan", 280);
        set_skill("taishan-jianfa", 350);
        set_skill("qingmang-jianfa", 320);
        set_skill("literate", 200);
        set_skill("jingmai-xue", 160);
        set_skill("medicine", 160);

        map_skill("sword", "taishan-jianfa");
        map_skill("parry", "taishan-jianfa");
        map_skill("dodge", "qingmang-jianfa");
        map_skill("force","yinyun-ziqi");
        map_skill("cuff","taizu-quan");
        prepare_skill("cuff", "taizu-quan");

        create_family("泰山派", 13, "掌门");
        setup();
        if (clonep())
        {
                ob = unew(BINGQI_D("sword/dongling_jian"));
                if (!ob)
                	ob = new(BINGQI_D("changjian"));
                ob->move(this_object());
                ob->wield();
                carry_object("/d/wudang/obj/white-robe")->wear();
        }
}

void attempt_apprentice(object ob)
{
        command("shake");
        command("say 泰山派现弟子近二三百人，贫道我暂不想收徒。");
        return;
}

int ask_tsjob()
{
        int i;
        object me = this_player();
        object target;

        if (me->query("combat_exp") < 1000000)
        {
                command("shake");
                command("whisper " + me->query("id") + " 这个工作并不适合你，不用麻烦了。");
                return 1;
        }
        if (me->query_condition("tsjob_busy"))
        {
                command("whisper " + me->query("id") + " 你刚帮我截下一名叛徒，先休息一下吧。");
                command("pat "+ me->query("id"));
                return 1;
        }
        if (me->query_condition("job_busy"))
        {
                command("whisper " + me->query("id") + " 你刚帮我截下一名叛徒，先休息一下吧。");
                command("pat "+ me->query("id"));
                return 1;
        }
        if (me->query_temp("tsjob/asked"))
        {
                command("push");
                command("whisper " + me->query("id") + " 快去追啊，晚了就来不及了！");
                return 1;
        }

        target = new(__DIR__"runner");
        me->set_temp("tsjob/target", target);
        me->set_temp("tsjob/asked", 1);
        me->apply_condition("tsjob",30);
        target->set("long", target->query("long") + "似乎是从"+me->query("name")+"手上逃脱的。\n");
        target->set_name("泰山派叛徒", ({ me->query("id")+"'s pantu"}) );
        i = me->query("max_pot")-100;
        if (me->query("combat_exp") > 2000000)
        {
	        target->add_temp("apply/defense", i);
	        target->add_temp("apply/attack", i);
        }
        target->set_skill("taishan-jianfa", i);
        target->set_skill("sword", i);
        target->set_skill("qingmang-jianfa", i);
        target->set_skill("dodge", i);
        target->set_skill("parry", i);
        target->set_skill("taizu-quan", i);
        target->set_skill("cuff", i);
        target->set_skill("yinyun-ziqi", i);
        target->set_skill("force", i);
        TASK_D->copy_status(me, target, 1);
        target->move(environment(this_object()));
        target->movement(0);
        command("whisper " + me->query("id") + " 左冷禅这家伙从各派收买了人，企图怂恿并派，刚才抓到一个叛徒却给跑了。");
        command("whisper " + me->query("id") + " 你就快快帮我追去，不用多说杀了便是，他必然是往嵩山去了。");
        return 1;
}

int ask_tsj()
{
        object me = this_player();
        int i = me->query("ts_job");

        if (i < 1)
        {
                command("ugly " + me->query("id"));
                command("say 你为我泰山派做了什么了？");
                return 1;
        }
        if (i < me->query("tsjf"))
        {
                command("hmm");
                command("say 能教你的都已经教你了，其他的嘛。。。");
                return 1;
        }
        command("ok tianmen");
        message_vision("$N对$n指导了一些泰山剑法的剑诀。\n", this_object(), me);
        me->add("tsjf",1);
        if (me->query_skill("taishan-jianfa",1) < 1)
                me->set_skill("taishan-jianfa",1);
        return 1;
}

int ask_tsjobtime()
{
        object me = this_player();
        int i = me->query("ts_job");
        string str;

        if (i < 1)
        {
                command("crazy " + me->query("id"));
                command("say 你根本没帮我追过叛徒。");
                return 1;
        }
        command("wa2");
        str = "你总共帮我截下了"+CHINESE_D->chinese_number(i)+"名叛徒。";
        command("say "+str);
        return 1;
}
