// /d/wudang/tandi1.c  ˮ̶��

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIB"ˮ̶��"NOR);
        set("long", @LONG
����������̶ˮ�У�̶ˮ�峺��ˮ���̹ǣ���Χ��Ϻ���������������һ
�㡣
LONG                           
        );
	set("outdoors", "�䵱");

        setup();

}

void init()
{
       add_action("do_qian",({"qian","dive"}) );
}

int do_qian(string arg)
{
	object me;
        me = this_player();

        if ( !arg || (arg != "down" && arg != "up" ))
            return notify_fail("�����������ˮ��������ȥ!\n");

        if ( me->is_busy() || me->is_fighting())
            return notify_fail("����æ���ء�\n");

        if (arg =="down") {
            message_vision("$Nһ�����ԣ�Ǳ����ȥ��\n", me);
            me->receive_damage("jingli", 60-(int)me->query_skill("dodge", 1)/20);
            me->move(__DIR__"tandi2");
            tell_room(environment(me), me->name() + "������Ǳ��������\n", ({ me }));
            return 1;
        }
        else {
           message_vision("$Nһ���ȣ�������ȥ��\n", me);
           me->receive_damage("jingli", 50-(int)me->query_skill("dodge", 1)/20);
           me->move(__DIR__"shuitan");
           me->clear_condition("diving");
           tell_room(environment(me), me->name() + "��ˮ��ð��������\n", ({ me }));
           return 1;
        }
        return 1;
}