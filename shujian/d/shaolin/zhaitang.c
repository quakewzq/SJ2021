// Room: /d/shaolin/zhaitang.c
// Date: YZC 96/01/19
// by zqb

inherit ROOM;
#include <ansi.h>

void create()
{
       set("short", HIG"ի��"NOR);
       set("long", @LONG
����ǰ��һ��˶���ޱȵķ��ݣ������������ȫ����ɮ��ի��ի�á���
��ʮ���䷿���������ɣ���������ȫ�µ�ɮ��һͬ��ի����ǰ��Ժ��������
��������ÿ�����¶���һ���޴�����ף�����ʢ������ˮ������ɮ��������
æµ�ţ���Ժ�ڴ�ɨ��ʮ�ָɾ���
LONG
       );

       set("exits", ([
               "west" : __DIR__"celang-4",
               "east" : __DIR__"fanting1",
               "north" :__DIR__"xjchu",
        ]));
        set("objects",([
               CLASS_D("shaolin") + "/hui-jie" : 1,
       ]));

       set("coor/x",70);
  set("coor/y",240);
   set("coor/z",110);
   setup();
}

int valid_leave(object me, string dir)
{

       if (  (dir == "west")
          && ( present("mizhi tianou", me)
               || present("mala doufu", me) 
                || present("furong huagu", me)) 
          && objectp(present("huijie zunzhe", environment(me))) )
       switch ( random(2) ) 
       {
       case 0: 
        return notify_fail
               ("�۽����߰���һ�죬˵����ʳ�ﲻ�ô���ի�ã��������еĹ涨��\n");
        break;
       case 1:
        message_vision("�۽����߶�$N�������˸�Ҿ�������ַ��ɷԸ�����ʳ�ﲻ�ô���ի�á�", me);
        return notify_fail("\n");
        break;
       }
       
       me->delete_temp("marks/sit");
       me->delete_temp("tea_cup");
       return ::valid_leave(me, dir);
}