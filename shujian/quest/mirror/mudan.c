// 牡丹宴会厅.c

#include <ansi.h>
#include <room.h>
inherit ROOM;

// amount: 单位是gold

void create()
{
        set("short", HIR"牡丹宴厅"NOR);
        set("long", @LONG
进门绕过一道淡红绸屏风，迎面墙上挂着一副『牡丹争艳』图，牡丹是
中国国花，素以富贵著称。图侧对联: 幽径天姿呈独秀，古园国色冠群芳。
衬托了那一茎牡丹分外精神。厅内陈列奢华，正中央一张雕花楠木青漆嵌玉
大圆桌，四周十二张镶银象牙扶手红木椅，杯碗勺箸，入眼生辉。
    这里便是醉仙楼的玫瑰厅，桌上平铺着一份菜单(menu)。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "north" : __DIR__"zxlpath",
        ]));

        set("item_desc", ([
                "menu": @TEXT
承办各式酒席, 欢迎惠顾：

        order marry:    豪门订婚宴        (1万两黄金)

        order end:      结  束

TEXT
        ]) );

        setup();
}
//是镜像
int is_mirror() { return 1; }