// Room: /city/wumiao.c
#include <room.h>
inherit ROOM;
void create()
{
    set("short", "武庙");
    set("long", @LONG
这里是岳王庙的正殿，内有岳飞像，像上方悬挂岳飞手书“还我河山”的
横匾。殿两侧壁上嵌着“尽忠报国”四个大字。武人到此，都放下武器，毕恭
毕敬地上香礼拜。旁边似乎有一道侧门。

                           [1;31m岳王庙[2;37;0m

LONG
    );

    set("exits", ([
        "east" : __DIR__"beidajie2",
    ]));
        setup();
}
//是镜像
int is_mirror() { return 1; }