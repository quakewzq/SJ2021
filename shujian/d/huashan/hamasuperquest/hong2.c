//��󡹦����Quest by server
//by spiderii@ty ����HAMA1���Ѷ���ߡ�����ȡ��3�λ�������ơ�expÿ����1M���µõ�һ�λ��ᣡ
//����rebootע��ID���Ѷ��ٴν��ͣ�server�ܱ�̬�����1����Ū�ˡ����3����ô�ѡ�tsk
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;
int do_chi(string arg);
int do_chaikai();

void create()
{
        set_name("���߹�", ({"hong qigong", "hong", "qigong"}));
        set("nickname", "��ָ��ؤ");
        set("gender", "����");
        set("age", 75);
        set("long", 
"��һ�ų����������΢�룬���ִ�ţ������·���һ����һ��Ĵ����˲�����
ȴϴ�øɸɾ��������ϸ��Ÿ������Ĵ��«��\n");
        set("attitude", "peaceful");
        
        set("str", 35);
        set("int", 24);
        set("con", 30);
        set("dex", 30);

        set("rank", 10);
        set("max_qi", 4000);
        set("max_jing", 3000);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 0);
        
        set("combat_exp", 3600000);
        set("score", 200000);
        set("death_times",180);

        set_skill("force", 400);             // �����ڹ�
        set_skill("huntian-qigong", 400);    // ��������
        set_skill("strike", 400);            // �����Ʒ�
        set_skill("xianglong-zhang", 400);   // ����ʮ����
        set_skill("hand", 360);              // �����ַ�
        set_skill("dodge", 400);             // ��������
        set_skill("xiaoyaoyou", 400);        // ��ң��
        set_skill("parry", 400);             // �����м�
        set_skill("stick", 400);             // ��������
        set_skill("dagou-bang", 400);        // �򹷰���
        set_skill("begging", 200);           // �л�����
        set_skill("checking", 200);          // ����;˵

        map_skill("force", "huntian-qigong");
        map_skill("strike","xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dagou-bang");
        map_skill("stick", "dagou-bang");
        
        prepare_skill("strike", "xianglong-zhang");

        create_family("ؤ��", 17, "����");
        setup();
        
                carry_object(ARMOR_D("bainayi"))->wear();
                carry_object(ARMOR_D("shoes"))->wear();
                carry_object("/kungfu/class/gaibang/obj/gb_budai10")->wear();

}
void init()
{
        object ob;
        
        ob = this_player();
        if (interactive(ob) && !is_fighting() && !ob->query("questwg"))
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
void greeting(object me)
{


  tell_object(me,HIW"���߹������:���������Ҳ��ᣬ���������˵ ��\n\n"NOR);
  tell_object(me,HIW"���߹�֧����������һ��ѩˮ���ִ�һ�����ʯ�ߵ��������ڳ�һֻ����������\n\n"NOR);
  tell_object(me,HIW"��������ѩ����ӳ���Ƶ÷�����ֻ��������ҧ���˰������߰˴糤�Ĵ���򼣬��ڡ�\n\n"NOR);
  tell_object(me,HIW"��䣬���ư�쵣�����������������߹���ס���β�ͣ�һ���������ڹ��\n\n"NOR);
  tell_object(me,HIW"��Щ�������һ�󣬱㶼�������ˡ�\n\n"NOR);
  tell_object(me,HIW"���߹��������͹��������ȥ��ը��΢��֮��������ϰ��ȣ��������������ˡ�\n\n"NOR);
  tell_object(me,HIW"һ������������У�������˼���������΢�գ�̾��һ������ֻ������֮���֡�\n\n"NOR);
  tell_object(me,HIW"�����ڴ��ӡ�\n\n"NOR);
  tell_object(me,HIW"���߹�����ʮ�����Ժ���������Ҽ�������Ӣ�ۺú���ɱͷ��Ѫ������ü��\n\n"NOR);
  tell_object(me,HIW"ͷ��ȴûһ���Ҹ����Ͻл���һ����򼡣С���ޣ���Ҳ��ҳԣ�chi������\n\n"NOR);
        
        add_action("do_chi","chi");
        
        return;
}
int do_chi(string arg)
{
        object me=this_player();
        object ob=this_object();
        if (!arg)
        return notify_fail(HIW"��Ҫ��ʲô��\n"NOR);
        if (arg == "wugong")
        {
                remove_action("do_chi","chi");

  tell_object(me,HIW"�㽫һ�������ڿ���һ����ֻһ������ȥ�����������������ִ����㣬����\n\n"NOR);
  tell_object(me,HIW"��Ũ��һ��֮�д�δ���������ζ���ٽ��˼��ڣ�һ��µ������ȥ����ȥЮ�ڡ�\n\n"NOR);
  tell_object(me,HIW"�������ԣ����ޣ�������\n\n"NOR);
                call_out("feng_out",5,ob,me);
        }
        else 
        return notify_fail(HIW"û������������\n"NOR);

        return 1;

}
void feng_out(object hong,object me)
{
        object feng;
        feng = new ("/d/huashan/hamasuperquest/feng");
        feng->move("/d/huashan/hamasuperquest/jueding5");

  tell_object(me,HIW"���������Ҷ�Ե���������ֻ���졢�졢�켸���죬ɽ�Ǻ�ת����һ�ˣ�����\n\n"NOR);
  tell_object(me,HIW"�ӵߵ���˫�ָ���ʯ�飬�ŵض��У���������ŷ���档ŷ���������˵����顣\n\n"NOR);
  tell_object(me,HIW"�߹����𹥻���\n\n"NOR);
        feng->kill_ob(hong);
        call_out("chai_out",10,hong,feng,me);

}

void chai_out(object hong,object feng,object me)
{


        
    feng->remove_all_killer();

  tell_object(me,HIW"ŷ����ͻȻ���������ȣ�˫��һ�䣬�������������һ����У������󡡣\n\n"NOR);
  tell_object(me,HIW"��������˫���뷢����ǰ�Ƴ�����һ��ʵ������������֮���ۡ����߹��;�����\n\n"NOR);
  tell_object(me,HIW"����������֪���Ҳ��˫����ǰƽ�ơ���һ������Ӳ��Ӳ��ɲ��֮�䣬���¡�\n\n"NOR);
  tell_object(me,HIW"�ﾹȻ��ס������\n\n"NOR);
  tell_object(me,HIW"���˽���һ�ᣬŷ����ͷ��͸��һ���Ƶİ���������Խ��ԽŨ����������һ�㡣\n\n"NOR);
  tell_object(me,HIW"���߹�Ҳ��ȫ�����������ۼ�������ɫ��䣬�������������յ�һʱ���̣��ǡ�\n\n"NOR);
  tell_object(me,HIW"ͬ���ھ����ɣ�������ǰ�𿪣�chaikai�����Լ��������������̫Զ ����롣\n\n"NOR);
  tell_object(me,HIW"�ֽⲻ�������������Լ�һ��������\n\n"NOR);
        add_action("do_chaikai","chaikai");
        call_out("chaikai_out",8,hong,feng,me);
}
int do_chaikai()
{
	      object* ppl;
        object me = this_player();
        object hong = this_object();
        object feng;
	      int i, time, total, j, h = 0;

 ppl = users();
 
	 i = me->query("combat_exp") - 500000;
	 i /= 500000;

	 time = time() - me->query("quest/hama/time");

        feng = present("ouyang feng", environment(me));

         j = sizeof(ppl);
        
 while(j--){
 if( userp(ppl[j])&& !wizardp(ppl[j])&&!ppl[j]->query("no_pk")&& ppl[j]->query("oyf/hamagong")>2 )
         h++;
          }

        


       if(me->query_skill("hamagong", 1) > 350 &&
           me->query("oyf_son") && 
           me->query("oyf/hamagong") == 2 &&
           random((int)me->query("kar")) > 28 && 
           random(me->query("con")) > 26 && 
     random(15)==10 &&
           me->query("max_neili") > 7500  &&
           me->query("neili") > 15000  &&
           me->query("combat_exp") > 2000000 &&
          ( me->query("quest/hama/super") <= i || me->query("cw_exp")) &&
                //( h<=3 ||random(h+1)>=h ) && 
				me->query("buyvip") &&
                time > 86400
                )
            {

  tell_object(me,HIC"������²��ã���æ���Ĵ�������\n\n"NOR);
  tell_object(me,HIC"������һ�����ɣ��ߵ�����֮����ϥ���£��˹���סȫ����һҧ����������������\n\n"NOR);
  tell_object(me,HIC"��֮����ȥ����һ����Ȼ�������������˵������������ϴ���������������һ����\n\n"NOR);
  tell_object(me,HIC"����жȥ��ԭ��ǿ��֮ĩ���ܴ�³�ɣ���ؤ������Ȼ���ǵ���֮�ۣ������Ķ�ʱ��\n\n"NOR);
  tell_object(me,HIC"���Ѿ����޶ࡣ\n"NOR,me);
        

        
  tell_object(me,HIG"ֻ�����常�ͺ���ǰ������һ�ɶ�Զ������ɷ��,���常���ź��߹����书��ǿ������ֱ���Ż�Ҫ�������䡣\n\n"NOR);
  tell_object(me,HIG"�����仰���ú��߹�Ҫ���㡸�򹷰�������������ȥ�������常��ʶ��\n\n"NOR);
  tell_object(me,HIG"ŷ���濴��֮�������̸�����ƽ�֮�������������������߹��������߹����������ƽ⣬�漴�ֽ����µ���ʽ����\n\n"NOR);
  tell_object(me,HIG"���һ��һ������������ʱ����ŷ�����ѽ������˺��߹���ʮ���У����������������֮����\n\n"NOR);
  tell_object(me,HIG"���߹�����е����ߣ��������ġ������޹��������常ڤ˼����˵��:Ϊ������ƽ��ѧ���һ�Դ������㣬�������ƽ��⡸�����޹�����\n\n"NOR);
  tell_object(me,HIG"���߹���ŷ�����ƽ������ġ������޹�����������ǿ���Ű���ŷ�����ǰ��������������������䡣\n\n"NOR);
  tell_object(me,HIG"ŷ���汻��ͻ�������ľٶ�һ������ʱ�����Լ���������ŷ���棬����ǰ�������ϳ�ұ�ؤ���߹���\n\n"NOR);
  tell_object(me,HIG"���ϻ�����ӵ����Ц����\n\n"NOR);
                       tell_object(me,HIM"��Ӻ��߹���ŷ�����ս���л����ǳ��\n"NOR,me);
                       tell_object(me,HIM"��ɹ�����常�ĸ�󡹦,��Ĺ�������ˣ�\n"NOR,me);
                       me->add("combat_exp",(30000+random(20000)));
                        me->add("oyf/hamagong",1);
me->set("title",HIW"����ɽׯ"BLU"����"HIW"����"NOR);
        log_file("quest/hamagong", sprintf("%8s%-10sѧ���ռ���ת���������õ�������\n",
                me->name(1), "("+me->query("id")+")" ), me);
                
                

  tell_object(me,HIR"ŷ����ͺ��߹�����ͻȻͬʱί���ڵأ�˫Ŀ���գ��������ң�һ��Ҳ�����ˡ�\n\n"NOR);
  tell_object(me,HIR"ԭ�������Ѻľ��������������������·�֮ǰ���ɸ�̾��\n\n"NOR);
  tell_object(me,HIR"�常�ͺ�����ǰ����Ȼ���Լ�������С�䰲������˻��룬�����컯Ū�ˡ�\n\n"NOR);
  tell_object(me,HIR"�����ˣ����Ĺ�����»���к�����? \n\n"NOR);
  tell_object(me,HIR"��ؤ������ʮ���������񶷣��������£���֪��ͬ��\n\n"NOR);
  tell_object(me,HIR"ʱ�ڻ�ɽ��������,��ֻ����Ȼ��ɽ��\n\n"NOR);
                      me->move("/d/huashan/sheshen");
                      destruct(feng);
                      destruct(hong);
        }
        else 
        {

  tell_object(me,HIC"������һ�����ɣ��ߵ�����֮����ϥ���£��˹���סȫ����һҧ��������������\n\n"NOR);
  tell_object(me,HIC"����֮����ȥ����ֻ��һ�ɴ����������ϴ����������������緭�������㣬�㡣\n\n"NOR);
  tell_object(me,HIC"������ߵķ��ݰ�ֱ׹��ɽ�¡�\n\n"NOR);
                me->move("/d/huashan/sheshen");
                me->add("quest/hama/super",1);
		  me->set("quest/hama/time", time());

                me->unconcious();
                destruct(feng);
                destruct(hong);
                if(random(me->query_kar()) < 15) {
                me->set_temp("last_damage_from", "׹��ɽ��");
                me->die();
             }
        }
              
        return 1;
}
void all_dest(object feng,object hong)
{
        destruct(feng);
        destruct(hong);

}