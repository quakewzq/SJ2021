// By Spiderii@yt bt��Ʒ
#include <ansi.h>
inherit SPEC;
void create()
{
        set_name(HIW"���񱦺�"NOR, ({ "dpbox","dpbaohe" }) );
        set_weight(10);
                set("unit", "��");
                set("long", "һ�����ص���ʺ��ӡ�\n�Ǵ�˵���������䷲��ı�������ܸ����Ǵ������˺Ͷ��˵�ħ��֮�С�\n�ǲ��Ǿ����������ջ��أ��ǾͿ�򿪣�open�����ɡ�����\n");
                set("value", 0);
                set("material", "wood");
                set("no_drop", "�������صĶ�����ô������Ҷ��ء�\n");
                set("no_get", "�������������뿪�Ƕ���\n");
                set("no_beg",1);
                set("no_steal",1);
                set("no_give",1);
                set_weight(100);
                set("value",3000000);
                //set("treasure",1);
                set("degree",1);
                set("flag","spec/dpbaohe");
                set("desc","��˵�򿪺��ӻ��з���������֡�");
                set("credit",1200);  

       setup();
}
void init()
{
        add_action("do_open", "open");
}

int do_open(string arg)
{        
       int i,j;
       object me = this_player();
       object obj;
       if(arg!="dpbox" && arg!="dpbaohe")
                    return notify_fail("��Ҫ��ʲô?\n");
      i = random(4)?4:5 ; 
        obj = new("/d/zhiye/obj/othermaterial");
        if(obj && obj->set_level(i+1,2))
        {
                obj->move(this_player());
                message_vision(HIW"$N�ӱ����еõ���һ"+obj->query("unit")+obj->name()+"��\n\n"NOR,me); 
        }
                destruct(this_object());
                return 1;
                
}