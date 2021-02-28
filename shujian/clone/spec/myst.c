// By Spiderii@yt bt��Ʒ
#include <ansi.h>
inherit SPEC;

string *valid_type = ({
"force", "parry",  "dodge", "unarmed","claw",
"cuff",  "finger", "strike","hand",   "leg",
"sword", "blade",  "dagger","brush",  "spear",
"hook",  "stick",  "staff", "club",   "throwing",
"whip",  "axe",    "hammer","bow",
});

int sort_skill2(string sk) 
{
	return (SKILL_D(sk)->type() == "knowledge" && SKILL_D(sk)->type2() == "worker");
}

int sort_skill(string sk)
{
	return (SKILL_D(sk)->type() != "martial" && SKILL_D(sk)->type() != "array");
}

int sort_basic(string sk)
{
	return member_array(sk, valid_type)!=-1;
}

void create()
{
        set_name(HIR"����ؼ�"HIW"(�꿨ר��)"NOR, ({ "mbook","book" }) );
        set_weight(10);
                set("unit", "��");
                set("long", "һ�������ؼ���\n��˵����������������������������Ķ����ܼ������������ѧ���ܡ�\n");
                set("material", "paper");
                set("no_drop", "����������������㻹�ǿ���һ�°ɡ�\n");
                set("no_get", "�������������뿪�Ƕ���\n");
   //             set("no_give", "����������������㻹�ǿ���һ�°ɡ�\n");
                set_weight(100);
                set("value",30000000);
                set("treasure",1);
                set("degree",1);
                set("rest",4);
                set("flag","spec/myst");
                set("desc","�Ķ����ܼ���������ѧ���ܡ�");
                set("credit",5000);  

       setup();
}
void init()
{
        add_action("do_open", "read");
}



int do_open(string arg)
{

 	
       object ob = this_player();
	mapping skl, lrn, map;
	string *sname, *mapped, *allskills, str = "";
	int i, j;


    if (!arg|| arg!="mbook")
            return notify_fail("��Ҫ��ʲô��\n");
            
     if (!ob->query("y-card-vip"))
            return notify_fail("�㻹�����꿨�������ʱ����ʹ�������Ʒ��\n");     
         
            
	if (!restrict()) {return notify_fail("�������Ѿ�����ʹ��"+this_object()->query("name")+"�ˡ�\n");}

 skl = ob->query_skills();

 allskills  = sort_array( keys(skl), (: strcmp :) );


	sname=filter_array( allskills, (: sort_skill2 :) );

	allskills-=sname;

	sname=filter_array( allskills, (: sort_skill :) );
	allskills-=sname;

//�����ǻ���

	sname=filter_array( allskills, (: sort_basic :) );
	allskills-=sname;


	j = sizeof(sname);

         if(j>0)   for(i=0; i<j; i++) {
                             ob->set_skill(sname[i], ob->query("max_pot",1)-100);
                  }


//����������
	sname=allskills;

	j = sizeof(sname);
         if(j>0)   for(i=0; i<j; i++) {

                           if ( ob->query_skill(sname[i],1) >=1 )

                              if(sname[i]!="liumai-shenjian" )
                                  if(sname[i]!="pixie-jian" )
                                     if(sname[i]!="jiuyin-zhengong") 
                                //        if(sname[i]!="jiuyin-shenfa")
                                           if(sname[i]!="shenzhao-jing")
                                //             if(sname[i]!="wuxing-zhen")
                                               if(sname[i]!="wuhu-duanmendao")
                                //                 if(sname[i]!="qianzhu-wandushou")
                                                   if(sname[i]!="lengquan-shengong")
                                //              if(sname[i]!="hamagong")
                                            if(sname[i]!="kuihua-shengong")
                                 //        if(sname[i]!="qianzhu-wandushou")
                                      if(sname[i]!="xuanyin-jian")
 //                                   if(sname[i]!="wuhu-duanmendao")
 //                                   if(sname[i]!="wuhu-duanmendao") 
 //                                 if(sname[i]!="wuhu-duanmendao")
 //                               if(sname[i]!="wuhu-duanmendao")
 //                             if(sname[i]!="wuhu-duanmendao")
 //                           if(sname[i]!="wuhu-duanmendao")

                             ob->set_skill(sname[i], ob->query("max_pot",1)-100);
                  }
CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + ob->name(1) + "�Ķ���һ��"HIR"����ؼ�"HIC"�����������еļ��ܣ�\n"NOR);


	degree();
	return 1;

}
