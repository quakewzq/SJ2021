#include <ansi.h>
#include <job_mul.h>
inherit NPC;

mapping *quest = ({
  (["name":                "yilihe",
    "start" :              "/d/xingxiu/yili/yilihe",
    "place" :              "�����", ]),    
  (["name":                "jygw",
    "start" :              "/d/xingxiu/jygw",
    "place" :              "������������",]), 
  (["name":                "silk",
    "start" :              "/d/xingxiu/silk",
    "place" :              "������������˿��֮·",]),
  (["name":                "silk1b",
    "start" :              "/d/xingxiu/silk1b",
    "place" :              "������",]),
  (["name":                "yili",
    "start" :              "/d/xingxiu/yili/yili",
    "place" :              "����",]),
  (["name":                "shanjiao",
    "start" :              "/d/xingxiu/shanjiao",
    "place" :              "��ɽ����",]),
  (["name":                "silk5b",
    "start" :              "/d/xingxiu/silk5b",
    "place" :              "��¡ɽ",]),  
  (["name":                "silk3a",
    "start" :              "/d/xingxiu/silk3a",
    "place" :              "��ɳɽ",]), 
  (["name":                "silk8",
    "start" :              "/d/xingxiu/silk8",
    "place" :              "�¹Ȼ��ٹ��",]), 
});    

string ask_job();

void create()
{
        set_name("��Ȼ��", ({ "anran zi", "anran", "zi" }) );
        set("gender", "����" );
        set("nickname", "��������ʦ��");
        set("age", 31);
        set("location", 1);
        set("unique", 1);
        set("long", "��Ȼ�������޶���ʮ���������е�����\n"+
		"�������������书��Щ������������ǳ��\n");
        set("env/wimpy", 40);
        set("str", 29);
        set("dex", 26);
        set("con", 24);
        set("int", 22);
        set("per", 18);
        set("shen", -7500);

        set_skill("force", 105);
        set_skill("huagong-dafa", 115);
        set_skill("dodge", 110);
        set_skill("zhaixingshu", 110);
        set_skill("strike", 110);
        set_skill("chousui-zhang", 110);
        set_skill("poison", 110);
        set_skill("parry", 110);
        set_skill("staff", 110);
        set_skill("tianshan-zhang", 110);
        set_skill("literate", 70);
        set_skill("claw", 110);
        set_skill("sanyin-zhua", 110);
        map_skill("claw", "sanyin-zhua");
        prepare_skill("claw", "sanyin-zhua");
        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixingshu");
        map_skill("strike", "chousui-zhang");
        map_skill("parry", "chousui-zhang");
        map_skill("staff", "tianshan-zhang");
        prepare_skill("strike", "chousui-zhang");

        set("max_qi", 2800);
        set("max_jing", 2700);
        set("eff_jingli", 1800);
        set("score", -14000);
        set("combat_exp", 750000);
        set("chat_chance_combat", 5);
        set("chat_msg_combat", ({
                (: exert_function, "huagong" :),
                (: perform_action, "strike.biyan" :),
        }));
        create_family("������", 2, "����");
        set("attitude", "peaceful");
        set("inquiry", ([
                "������" : "������룬�Ͱ���Ϊʦ��",
                "���޺�" : "ȥ���޺���ʲô������Ϊʦ�͹���ѧ���ˡ�",
                "������" : "����������е���û��ûС�ġ��Ժ�����ɣ�",
                "��ɱ" : (: ask_job :),
                "����" : (: ask_job :),
                "����" : "Сʦ����������ϲ������ȥ�����ɡ�",
        ]));        
        setup();
        carry_object(BINGQI_D("gangzhang"))->wield();
        carry_object(ARMOR_D("changpao"))->wear();
        add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
    	command("consider");
    	command("say �������и��˶���רְ��Ҫ��ʦ��ȥ����ʦ�ֵܰɣ�");
    	return;
}

int accept_object(object me, object obj)
{
   	object ob=this_object();

   	if(!me || environment(me) != environment() || !objectp(obj)) return 0;

   	if(!present(obj, me)) return notify_fail("��û�����������");   
   	     
   	if(userp(obj)){
       		command("consider "+(string)me->query("id"));
       		command("say ���ø�����������ƭ�ң�");
       		return 0;
       	}
   	if(!me->query_condition("xx_task2")){
       		command("shake "+(string)me->query("id"));
       		command("say ��ô�òŻ������һ������ұ������ɣ�");
       		return 0;
       	}
   	if(obj->query("id") == "prize" && obj->query("owner") == me->query("id")){
       		command("nod "+(string)me->query("id"));
       		command("say �����ģ���������������ɵ����磡\n");
       		message_vision(HIY"$N��$n"HIY"�𿪣��ó���һ��ѽ����Ʊ���\n"NOR,ob, obj);
       		call_out("destroying", 5, obj, ob, me);                       
       		return 1;
       	}
   	if(obj->query("money_id")) {
       		command("pat " + me->query("id"));
       		command("say Ǯ���е��ǣ����Ժ��������Լ��ɡ�");
       		return 0;
       	}
   	if(obj->query("owner") != me->query("id")){
       		command("hehe "+(string)me->query("id"));
       		command("say �������������ɲ�����ɵġ�");
       		return 1;
       	}
   	else return 0;       
}

void destroying(object obj, object ob, object me)
{   
   	object n_money;
   	int exp;
   	
   	if(obj) destruct(obj);
   	
   	if(!ob) return;
   	
   	if(!me || environment(me) != environment()){
      		command("say �ף����أ�");
      		return;
      	}
   	command("pat "+me->query("id"));
   	message_vision(HIY"$N��$n˵������������ü�Ϊ��ɫ��������õõĲ��֣���ȥ�ɣ�\n"NOR,ob, me);
   	n_money = new("/clone/money/gold");
   	n_money->move(me); 
   	n_money->add_amount(1+random(2));
   	
   	exp = 100+(me->query_temp("xx2/biaoshi")*(random(50)+50));   	   	
   	exp = me->add_exp_combat(exp,ob,"����");
   	exp = exp/5;
   	me->set("job_name", "��������");
   	me->add("potential", exp);
   	if(me->query("potential") > me->query("max_pot"))
   		me->set("potential", me->query("max_pot"));

   	tell_room(environment(me), me->name()+"����Ǯ����Ľ��ӣ����ϵļ��ⲻס�ز������۾�ɢ����һ����ֵĹ�â��\n" NOR, ({ me }));     
   	tell_object(me, "�ٺ٣����ˣ�\n");
   	log_file("job/qiangjie",sprintf("%-18s���������٣�ɱ��%2d����ʦ���õ���%4d��EXP��%3d��POT���־��飺%d��\n",
      		me->name(1)+"("+getuid(me)+")", me->query_temp("xx2/biaoshi"), exp, exp/5,me->query("combat_exp")),me);
   	me->delete_temp("xx2");
   	return;
}

string ask_job()
{
  	object me, ob;
  	mapping aquest;
  	int exp, j;
  	aquest = quest[random(sizeof(quest))];
  	me = this_player();
  	ob = this_object();
  	exp = me->query("combat_exp"); 
 
    	if(ob->is_busy() || ob->is_fighting()) 
    		return "û��������æ����һ�ߵ���ȥ��";
    		
    	if (!me->query("family")) 
    		return "���ó��������̬�ȹ������β��������������أ�";
    		
    	if (me->query("family/family_name") != "������" && !me->query_temp("ding_flatter"))
            	return "������ɵ�̬�ȿ���ȥ��̫��������";
            	
    	if (me->query_condition("wait_xx_task"))
            	return "�ϴΰ���ʦ�ָ�����������ˣ������͵ȵȰɡ�";
            	
    	if (me->query_condition("xx_task2")
    	 || me->query("job_name") == "��������" )
            	return "�����ڻ�û�еõ��κ���Ϣ����Ȼ�������ɡ�";
            	
    	if (me->query_condition("job_busy"))
            	return "�����ڻ��������������Ȼ�������ɡ�";      
            	 
    	if (ob->query_temp("xx2/job_asked") == me->query("id")) 
            	return "���ǽ�����ȥ�����������ô���������";
            	
    	if (ob->query_temp("xx2/job_asked")) 
            	return "�ٺ٣��������ˣ�����һ�ΰɡ�";
            	
    	if (exp < 200000) 
    		return "�����������ټӰ��������ɡ�";
    		
    	if (exp >= 750000) 
    		return "��Ĺ����Ѿ��������ˣ����ø��ҳ�ȥ���£�";
    		
    	if (me->query("shen") > -10000) 
    		return "�ߣ���������ĳ��������ڰ����������㲻��Ҳ�ա�";
    		
    	if (exp >= 600000) j=6;
    	else if (exp>=500000) j=5;
    	else if (exp>=400000) j=5;
    	else if (exp>=300000) j=4;   
    	else j=3;   

    	me->delete_temp("xx2");
    	message_vision(CYN"\n$N����һЦ��˵�������������һ�������̶Ӿ������㹻���ͺ���һ��ȥ�����ɡ�\n"NOR, ob, me);
    	ob->set_temp("xx2/job_asked", me->query("id"));
    	ob->set_temp("xx2/dest", aquest["name"]);
    	ob->set_temp("xx2/start_place", aquest["start"]);
    	ob->set_temp("xx2/place", aquest["place"]);
    	me->set_temp("xx2/j", j);
    	me->apply_condition("xx_task2", 60+(j*20));
    	me->apply_condition("job_busy", 15);
    	me->start_busy(1);
    	call_out("going", 30, ob); 
    	return "�һ���Щ��Ҫ�죬����ȥ"+ob->query_temp("xx2/place")+"���ҡ�\n";    
}

void going(object me)
{
       message_vision("$N����ææ�����˳�ȥ��\n", me);       
       me->move(me->query_temp("xx2/start_place"));
       message_vision("$N����ææ�����˹�����\n", me);       
}

void init()
{
   	object ob, where, me;
   	::init();
   	ob=this_object();
   	where = environment(ob);
   	if(ob->query_temp("xx2/dest")){
     		if(interactive(me = this_player()) && me->query_temp("xx2/j")
        	&& ob->query_temp("xx2/job_asked") == me->query("id")
        	&& file_name(where) == ob->query_temp("xx2/start_place")) {
           		remove_call_out("waiting");
           		call_out("do_back", 120, ob);
           		call_out("waiting", 1, ob, me);
        	}
     		else{
         		remove_call_out("do_back");
         		call_out("do_back", 90, ob);
         	}
     	}
}

void waiting(object ob, object me)
{   
    	if(!ob || !living(me)) return;
    	command("nod "+me->query("id"));
    	command("say �ã����Ǿ�����������������ɡ�");
    	ob->set_temp("wait_target", 1);
    	me->set_temp("wait_target", 1);
    	remove_call_out("wait_target");
    	call_out("wait_target", 30, ob, me);
    	return; 
}

void do_back(object me)
{
        me->delete_temp("wait_target");
        me->delete_temp("xx2");
        message_vision("$Nת��ɽ�𣬼�������Ͳ����ˡ�\n", me);
        me->move("/d/xingxiu/ryd1");  
        message_vision("$N����ææ�����˹�����\n", me);           
}

int wait_target(object ob, object me)
{
   	object obj;
   	if(!objectp(present(me, environment(ob)))){
       		message_vision("$N˵����Ү���Ǽһ���ô�����ˣ�\n", ob);
       		remove_call_out("do_back");
       		do_back(ob);
       		return 1;
       	}
   	if(!objectp(ob = present("anran zi", environment(me)))){ 
       		tell_object(me,"�㷢����Ȼ�Ӳ����ˣ�ֻ�û������ת���뿪��\n");
       		tell_room(environment(me), me->name()+"ͻȻһ��ãȻ�ı��飬��������Ҫ�뿪�ˡ�\n", ({ me }));
       		me->delete_temp("xx2");
       		me->clear_condition("xx_task2");
       		me->delete_temp("wait_target");
       		return 1;
       	}

    	obj = new(__DIR__"shangdui");
    	obj->move(environment(me)); 
    	obj->set("arg", ob->query_temp("xx2/dest"));
    	message_vision(HIY"\nֻ��һ�����շ�����������һֻ�����̶ӳ�������ǰ��\n\n"NOR, ob);
    	tell_object(me,"�������ڳ����ˣ�\n"); 
    	message_vision(HIY"$N����$n����������������(qiang)�̶ӣ������Ը������ˣ�\n"NOR, ob, me); 
    	message_vision("˵��$N�ͳ���ǰȥ���ͼ���������ʦ��׷���ˡ�\n", ob);   
    	remove_call_out("do_back");
    	do_back(ob);
    	me->delete_temp("wait_target");
    	obj->set_temp("robber", me);
    	return 1;
}