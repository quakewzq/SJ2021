//�ڷ�կ��ɽ��
#include <room.h>
#include <ansi.h>

inherit ROOM;
void create()
{
      set("short", CYN"��ɽ��"NOR);
      set("long", @LONG
������Ǵӹ㳡ͨ��ǰկ����ɽʯ·����ɽ�佨���˵�
����Ҫ�ޱȡ�һ�Ӷӵ�Ѳɽආ������߹�������Ĵ�������Χ��
LONG);
      set("outdoors","�ڷ�կ");
      set("exits", ([
            "southdown" : "/quest/hfz/guangchang",
            "westup" : "/quest/hfz/panshan2",
      ]));

      setup();
//  replace_program(ROOM);
}
//�Ǿ���
int is_mirror() { return 1; }