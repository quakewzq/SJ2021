// Room: /d/hengshan/hufengkou.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "�����");
        set("long", @LONG
�� "������" �� "����ͤ" ���͵���һ�����·ת�Ķ���·�ڣ�������һ
����ڣ�������������绢Х���ȱ�ǿ����࣬����������
LONG);
        set("exits", ([ /* sizeof() == 4 */
           "southwest" : __DIR__"daziling",
           "west"      : __DIR__"xgsong",
           "northeast" : __DIR__"guolaoling",
        ]));
        set("outdoors", "��ɽ");
        set("no_clean_up", 0);
        setup();
}