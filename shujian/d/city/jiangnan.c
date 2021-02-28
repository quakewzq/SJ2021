// By Spiderii ����robot
#include <ansi.h>
inherit ROOM;
#define SHIP_TO __DIR__"jiangbei"
#define BOAT __DIR__"boat"

void create()
{
        set("short", "�����ϰ�");
        set("long", @LONG
��ǰ��һ�����η����Ĵ�(river)�� �������������۾����������ɴ���
������������һ�����������̯����Ҿͽ������ڰ��ߣ�֧һ��ľ�壬���ϰ�
���˻�����������㡣��Զ����һ���ڶɣ����ٹ����Ͷ�������ȴ��ɴ���
LONG);
        set("exits", ([
                "south" : __DIR__"sroad1",
                "east" : __DIR__"jiangnan2",
                "west" : __DIR__"jiangnan1",
        ]));
        set("outdoors", "����");
        set("coor/x",100);
  set("coor/y",-160);
   set("coor/z",0);
   setup();
}

void init()
{
        add_action("do_yell", "yell");
        add_action("du_jiang", "dujiang");
}

int do_yell(string arg)
{
	object room, me;
	me = this_player();

	if (arg == "boat") arg = "����";
	if (arg != "����") arg = "��";
	if (me->query("age") < 16  )
		message_vision("$Nʹ�����̵���������һ������" + arg + "��\n", me);
	else if (me->query("neili") > 500)
		message_vision("$N���˿�����һ����" + arg + "������������ƽ�͵�ԶԶ���˳�ȥ��\n", me);
	else
		message_vision("$N������������Хһ������" + arg + "����\n", me);
	if (arg == "����")
	{
		if (room = load_object(BOAT))
		if (!room->query("start"))
			room->arrive("jiangnan");
		else if (query("exits/enter"))
			message_vision("����һֻ�ɴ��ϵ�������˵�������������أ������ɡ�\n", me);
		else message_vision("������ԶԶ����һ�������ȵȰ���������ˡ�������\n", me);
	} else message_vision("������ԶԶ����һ���������" + arg + "��������\n", me);
	return 1;
}

int valid_leave(object me, string dir)
{
	if( dir =="enter" ){
		if (me->query("can_ride")) return 0;
		if (me->query_temp("ride_horse"))
			return notify_fail("�����ϴ����㲻�´����ˣ�\n");
		me->set_temp("side", "jiangnan");
	}

	return ::valid_leave(me, dir);
}

int du_jiang()
{
        object me = this_player();
        object room;
        int cost = 600;

        if (!living(me)) return 0;
	room = load_object(BOAT);

        if (me->is_busy() || me->is_fighting())
                return notify_fail("����æ���أ�\n");
	if(me->query_temp("ride_horse"))
		return notify_fail("���������㲻��ʩչ��һέ�ɽ����ľ��� ��\n");
        if (me->query_skill("dodge") < 270)
                return notify_fail("�����Ϊ������\n");
        if (me->query("max_neili") < 3500)
                return notify_fail("���������Ϊ����������֧�֣���\n");
        if (me->query("neili") < 1000)
                return notify_fail("������������ˣ�\n");
        if (me->query("jingli") < 1200)
                return notify_fail("��ľ��������ˣ�\n");

        if(me->query_encumbrance()/100 > me->query("neili") + cost)
                return notify_fail("�����ô�صİ�������·�������⣬��˵���ˣ�\n");

        if(query("exits/enter")) return notify_fail("�д������������Cool����\n");

	if(room->query("exits/out") ) return notify_fail("����̫���ˣ����û����;�����ĵط�����û����Խ��ȥ��\n");

        me->receive_damage("neili", 300);
        me->receive_damage("jingli", 150);
        tell_room(environment(me), YEL+me->name()+"���˽�������Ʒ�������ų���ƮƮ������Ծ�ɳ�����\n" NOR, ({me}));
        write("��һ����Ϣ����׼�˽��жɴ�λ�ã�ʹ����һέ�ɽ����Ṧ��Ҫ��Խ������\n");
        me->move(BOAT);
        me->start_busy(3);
	if (me->query("neili") < 1000 || me->query("jingli") < 1200) {
                write("�㻹��������ȴ�������������ˡ�\n");
                tell_room(environment(me), YEL+me->name()+"����ƮƮ���ӽ����Ϸ�Ծ������վ�ڴ��ϣ���ڴ�ڴ�������\n" NOR, ({me}));
                return 1;
	}
//         tell_room(environment(me), YEL"ֻ��"+me->name()+"���ڴ���һ�㣬" NOR, ({me}));
        if (me->query("neili") > 100000000){
                me->start_busy(5);
                tell_room(environment(me), YEL"����Ҫ��Ծ����ͻ�����ϴ�һ����ɨ��������"YEL+me->name()+"�����ڽ��У�\n" NOR, ({me}));
                tell_object(me, "����Ҫ����Ծ����ͻȻС��һ�ۣ�����ͨ��һ��������ˮ֮�У�̧��ͷ�ŷ����Ǵ��ϴ��ø��ӽ���ɨ�´��ġ�����������\n");
                message_vision(HIC"���ϴ���ɤ���������" + RANK_D->query_rude(me) + "Ҳ�������ۿ����������ػ���ô������è��ɫ�����⴬����������ƴ�������Ǻ��ǵģ�������\n", me);
                tell_object(me, "������һ��������ͷ�������������������԰���Զ��ֻ���������ˣ�\n");
                me->receive_damage("neili", 300);
                me->receive_damage("jingli", 150);
                me->move(__FILE__);
                message_vision(HIC"$Nʪ�����شӽ������ϰ�������������Խ��жɴ�ߴߴ���������ͣ��������������\n"NOR,me);
        }

        else {
                me->start_busy(3);
                 tell_room(environment(me), YEL"ֻ��"+me->name()+"����ƮƮ���ӽ����Ϸ�Ծ����������Ծ����\n" NOR, ({me}));
                write("���ڽ��жɴ�������һ�㣬�����������򱱰���\n");
                me->move(SHIP_TO);
                tell_room(environment(me), YEL"ֻ��"+me->name()+"����ƮƮ�Ӷ԰�Ծ������̬���������ڰ��ߡ�\n"NOR, ({me}));
        }

        me->receive_damage("neili", 300);
        me->receive_damage("jingli", 150);
        return 1;
}