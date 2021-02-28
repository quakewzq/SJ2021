// /d/xiangyang/qinglongmen.c

#include <ansi.h>
inherit ROOM;
string look_gaoshi();

void create()
{
        set("short", YEL"������"NOR);
        set("long", @LONG
�����Ǿ������������ǵĶ��ţ���ʱ���ж�����׵�ʿ��������ȥ����
���߿��Խ��밲�ա����վ��ڡ��������������ս������������ʧ��������˴�Ƭ�Ļ�
�أ�����ϡ�١����Ž����ع��ţ��ó峵�忪(chong chengmen)����ʧ�Ǹ��ð취��
LONG

        );
  set("no_save", 1);

        set("outdoors", "����");
                set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));

        set("exits", ([
                "east" : __DIR__"outeroad1",
                "west" : __DIR__"eroad1",
        ]));

        set("objects", ([
          "d/hudong/xiangyang/obj/doorql" : 1,
            //    NPC_D("guanfu/bing") : 2,
        ]));


	set("incity",1);
	setup();
}



void init()
{
object env = this_object();
object me = this_player();
int i;
object ob;
add_action( "do_back", "goback" );
if (ob = present("qinglong chengmen", env)){
 this_object()->set("no_fight",1);
return ;
}
else 
{
this_object()->delete("no_fight");
return ;
}
 if(wizardp(me)) message_vision(HIG"ͬ־�ǣ�ɱѽ������һ��\n"NOR, me);
    
   
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n��������ʹ\n���ĵ�\n";
}

int valid_leave(object me, string dir)
{
object ob;
object env = this_object();
        if (dir == "east"){
                if ( me->query_temp("��������/������ս/��Ӫ"))
                        return notify_fail("�������ڻ�������������ս�����뿪ս����\n");
        }


if (dir == "west"){
if ( me->query_temp("��������/������ս/��Ӫ") == 2 && ob = present("qinglong chengmen", env) )

                        return notify_fail("���Ż�δ���ƣ����ܽ��롣\n");
        }



        return ::valid_leave(me, dir);
}
int do_back(string arg)
{
	object me = this_player();

	if(!living(me) ) return 0;

        if (me->is_busy() || me->is_fighting())
	return notify_fail("����æ���ģ�\n");

	if(!arg || arg == "" || arg != "Ӫ����")	
return notify_fail("����ȥ���\n");
if(arg == "Ӫ����")
{
if ( me->query_temp("��������/������ս/��Ӫ") == 2)
{
message_vision("$N���˴��������ϣ�ֻ���ȳ�����ͼ���㡣\n", me);
me->move("/d/hudong/xiangyang/zhangwai");
return 1;
}
if ( me->query_temp("��������/������ս/��Ӫ") == 1)
{
return notify_fail("�����ؾ����������ﳷ��\n");

}
else
return notify_fail("�����Ĳ��ֵģ�����\n");

}
return 1;
}