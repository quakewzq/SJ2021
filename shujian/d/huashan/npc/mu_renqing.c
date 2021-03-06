// NPC: /d/huashan/npc/mu_renqing.c
// Date: Look 99/03/25
// Modify by Lklv 2001.10.18
#define QUESTDIR "quest/华山派/鹰蛇生死搏/"

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_quest1();
string ask_quest2();
string ask_miji();

void create()
{
        set_name("穆人清",({"mu renqing", "mu", "renqing"}));
        set("nickname","神剑轩辕");
        set("long", "这就是在江湖中侠名远播，疾恶如仇，华山派神剑轩辕穆人清。\n");
        set("age", 70);
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("per", 26);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 9000);
        set("max_jing", 7800);
        set("eff_jingli", 7500);
        set("max_neili", 16000);
        set("neili", 16500);
        set("jiali", 100);
        set("combat_exp", 4200000);
        set("score", 29000);

        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
               (: perform_action, "sword.jianzhang" :),
        }));
        set_skill("sword",  350);
        set_skill("dodge",  350);
        set_skill("force",  360);
        set_skill("cuff", 350);
        set_skill("poyu-quan", 340);
        set_skill("huashan-jianfa", 350);
        set_skill("parry",  360);
        set_skill("literate", 230);
        set_skill("huashan-qigong", 350);
        set_skill("strike", 350);
        set_skill("hunyuan-zhang", 350);
        set_skill("huashan-shenfa", 350);
        set_skill("zhengqi-jue", 200);

        map_skill("dodge", "huashan-shenfa");
        map_skill("force","huashan-qigong");
        map_skill("cuff","poyu-quan");
        map_skill("strike","hunyuan-zhang");
        map_skill("parry","huashan-jianfa");
        map_skill("sword","huashan-jianfa");
        prepare_skill("strike", "hunyuan-zhang");

	set_temp("apply/damage", 80);
        set_temp("apply/dodge", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/armor", 80);
        create_family("华山派",12,"弟子");

    set("inquiry", ([
         "鹰蛇相争" : (: ask_quest1 :),
         "鹰蛇生死搏" : (: ask_quest2 :),
         "秘籍" : (: ask_miji :),
        ]));
        setup();
        carry_object(BINGQI_D("sword"))->wield();
        carry_object(ARMOR_D("cloth"))->wear();
}
void init()
{
     add_action("do_go", "gensui");
     add_action("do_go", "goto");
}


void attempt_apprentice(object ob)
{
        mapping fam;
        if (mapp(fam=ob->query("family")) && (string)fam["family_name"] != "华山派"  && (int)ob->query("is/huashan")==1 ) {
                message_vision(CYN "$N！你这个华山派的叛徒还回来干什么 ？？？\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
        }
	if (ob->query("fengset")) {
		command("say 你不是已经拜了风清扬他老人家为师了么？");
		return;
	}
	        if(ob->query("quest/huashan")=="剑宗"){
                command("heng");
                command("say 哼哼！剑宗弟子早已离开华山，不再是华山派弟子，你又来这里，难道是想争夺这掌门之位？");
                return;
        }
        if (ob->query_skill("zixia-gong",1) < 100 ) if(ob->query_skill("huashan-qigong",1)<100 ) {
		command("say 你的紫霞功修为太差，抓紧修炼吧。");
		return;
	}
        if ((int)ob->query("shen") <= 0) {
	        command("say 我华山派乃是堂堂名门正派，对弟子要求极严。");
	        command("say 在德行方面，" + RANK_D->query_respect(ob)+"是否还做得不够？");
	        return;
        }
        if ((int)ob->query("max_pot") < 230) {
	        command("say " + RANK_D->query_respect(ob)+"现在不需要我来指导，回去安心找你师傅学艺去吧。");
	        return;
        }
        command("say 好吧，我就收下你了,你可要为我们华山派气宗争口气。");
        command("recruit " + ob->query("id"));
        ob->set("title",HIW"华山派气宗亲传弟子"NOR);
        ob->set("quest/huashan","气宗");
}

string ask_quest1()
{
        mapping fam;
        object me;
        int exp, exp2, i;
        me = this_player();
        exp = (int)me->query("combat_exp", 1);
        exp2 = (int)me->query(QUESTDIR+"combat_exp", 1);
        i = (int)me->query("job_time/华山",1);
        fam = me->query("family");
        
        if (!fam || fam["family_name"] !="华山派")
                return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？\n";

      if (!me->query(QUESTDIR+"归辛树/over"))
        return "我华山派有位前辈观看鹰蛇相争，创出一门鹰蛇生死搏的绝学！\n";

        if(me->query_temp(QUESTDIR+"start2"))
                return "我不是已经和你说过了吗？\n";

        if( i < 2000 )
                return "你为我华山派做出的贡献微薄，怎能告诉你这等机密要事？\n";
         //华山任务至少完成1000次 by daidai

        if(exp2 && exp-exp2 < 200000 && !me->query("cw_exp"))
                return "你当前的经验恐怕还是难以有所帮助，还是抓紧去练功去吧。\n";
         //经验间隔200k by daidai

        if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<86400)
                return "今天就到这里吧，你明天再来吧。\n";
        
        if(me->query(QUESTDIR+"pass"))
                return "你不是已经会了吗？\n";

        if(me->query(QUESTDIR+"fail")>=3 && me->query("registered")<3)
                return "我已经和你讲过多次了，你年纪不比我大，为何记性如此差啊？\n";
        me->set_temp(QUESTDIR+"start2", 1);
        me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
        me->set(QUESTDIR+"time",time());
         message_vision(CYN"\n穆人清挥手招来一位仆人！\n"NOR, me);
        return "这松树林后面的山涧里常有鹰蛇出没，我华山派七十二路鹰蛇生死搏便是前辈高手在那里观看鹰蛇相斗有感而创。
你若有兴趣就让仆人带你去吧(gensui)，说不定有所收获呢！\n";
}

string ask_quest2()
{
        mapping fam;
        object me;
        me = this_player();
        fam = me->query("family");

        if (!fam || fam["family_name"] !="华山派")
                return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？\n";

        if(!me->query(QUESTDIR+"over"))
          return "那是我华山派的绝学，自从第九代掌门丧命于光明顶之后就失传了，只留下一本无人能参透的秘籍残本。\n";
 
        tell_object(me,HIC"\n你将刚才所见以及自己的感悟一一告诉了穆人清。\n"NOR);
        me->set(QUESTDIR+"pass",1);
        me->delete(QUESTDIR+"over");
        return "既然如此，我这里有本鹰蛇生死搏的秘籍残本，也许你能从中学到点东西。\n";
}
string ask_miji()
{
        mapping fam;
        object me,book;
	int exp, exp2;
        me = this_player();
        fam = me->query("family");

        if (!fam || fam["family_name"] !="华山派")
                return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？\n";

       if(me->query_temp(QUESTDIR+"归辛树/over"))
                return "你已经拿到秘籍了，还不快给我？\n";

      if(!me->query(QUESTDIR+"归辛树/over")){
                exp = (int)me->query("combat_exp", 1);
                exp2 = (int)me->query(QUESTDIR+"combat_exp", 1);

      if(exp2 && exp-exp2 < 200000)
                return "你当前的经验恐怕还是难以有所帮助，还是抓紧去练功去吧。\n";
         //经验间隔200k by daidai

        if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<86400)
                return "今天就到这里吧，你明天再来吧。\n";

        if(me->query_temp(QUESTDIR+"start"))
                return "我不是已经和你说过了吗，你还不去杭州找我徒儿？\n";

          me->set_temp(QUESTDIR+"start", 1);
                return "秘籍残本我交给我徒儿归辛树了，他在杭州一带，你去问他取回秘籍吧。\n";
          
           }
       if(!me->query(QUESTDIR+"pass"))
          return "秘籍？什么秘籍？我这里只有一本武学残篇，你可看不懂哦！\n";

        book = unew("/d/huashan/npc/obj/yingshe-book.c"); 
        if(!clonep(book)) return "你来晚了，鹰蛇生死搏的秘籍残本已被本派其他弟子拿走了。";
         
        if(clonep(book) && book->violate_unique()){
               destruct(book);
               return "你来晚了，鹰蛇生死搏的秘籍残本已被本派其他弟子拿走了。";
        }
        book->move(this_player());
        return "我这里有本「鹰蛇生死搏秘籍残本」，你拿回去好好钻研，务必重现本派绝学。";
}

int do_go(string arg)
 {
      object me;
      me = this_player();
      if(!living(me) ) return 0;
      if(! me->query_temp(QUESTDIR+"start2")) return 0;        
      if (me->is_busy() || me->is_fighting())
        return notify_fail("你正忙着哪！\n");
      if( !arg || arg != "puren")
        return notify_fail("你要跟谁走啊？\n"); 

         message_vision(CYN"\n仆人说道：“跟我来吧！”，然后向外走去，$N急忙跟上！\n"NOR, me);
          me->move("/d/huashan/ys_houshan");     
        return 1;
}


int accept_object(object who, object ob,object me)
{
        me= this_object();

        if( ob->query("id") != "muxia"){
                command("say 你给我这东西干吗？");
                return 0;
        }
        if( ob->query("owner") != who->query("id")
         || !who->query_temp(QUESTDIR+"归辛树/over")){
                command("haha");
                command("say 多谢"+RANK_D->query_respect(who) + "把我派秘籍找回，太感谢了。");
                who->delete_temp("limochou");
                call_out("dest", 1, ob);
                return 1;
        }
        command("say 太好了，你终于把这本秘籍残本取回来了。");

            command("say 近几日老是听到后山有鹰鸣之声，不知道.......");
        who->set(QUESTDIR+"归辛树/over", 1);
        who->delete_temp(QUESTDIR+"归辛树/over");
        call_out("dest", 1 ,ob);
        return 1;
}

void dest(object obj)
{
        if(! obj) return;
        destruct(obj);
}

