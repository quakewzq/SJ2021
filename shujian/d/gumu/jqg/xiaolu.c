// xiaolu.c

inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", HIY"����С·"NOR);
	set("long", @LONG
���̤��������ݣ�����һ��С·���档��������Ӱ��涣������˱ǡ�ӭ
����һ��Сé�ݣ��ſڵ����ϳ�������̦��������������ܾ����ĵģ�������
�����Ψ����������΢�졣
LONG
	);

	set("outdoors", "�����");

	set("objects", ([
		"/d/gumu/obj/guo" : 2,
	]));

	set("exits", ([
		"south" : __DIR__"tanan",
		"east" : __DIR__"huacong",
		"enter" : __DIR__"zhongtang",
	]));
	setup();
}