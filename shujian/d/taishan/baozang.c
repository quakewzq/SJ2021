// Room: /d/taishan/.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
������̩ɽ��һ����ʤ��������һ��״��ʨ�ӵľ�ʯ����Ϊʨ���¡����
���Ļ���Ҫ���ڶ�����Ķ�������Ҳ�����������ǹŴ������ĵط���������һ
�������ڵļ�̩ɽ����
LONG
	);

	set("exits", ([
		"westup" : __DIR__"weipin",
	]));

	set("outdoors", "̩ɽ");
	setup();
}