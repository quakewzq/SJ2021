// Write By Yanyang@SJ 2001.9.20
// Room: /d/changan/northchq3.c

inherit ROOM;

void create()
{
        set("short", "����ǽ");
        set("long", @LONG
�������ĳ�ǽ�ָ��ֺ񣬸���һ�ְ�ȫ�ĸо���������ǽ����ʯ�ҡ�����
Ŵ��֭������ɣ��������沼���˶�������������֮�á���ǽ�ϣ���������
��ǽ�⻤�ǺӶ����һ��һ����
LONG
        );
        set("outdoors", "����");

        set("exits", ([
                "east"  : __DIR__"northjl1",
                "west"  : __DIR__"northchq2",
        ]));

        set("incity",1);
	setup();
}

