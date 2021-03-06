// 芙蓉宴会厅.c

#include <ansi.h>
#include <room.h>
inherit ROOM;
// amount: 单位是gold

void create()
{
        set("short", HIY"芙蓉宴厅"NOR);
        set("long", @LONG
进门绕过一道淡绿绸屏风，迎面墙上挂着一副『芙蓉出水』图，工笔彩
绘，状极清雅，气质卓绝。厅内陈列奢华，正中央一张雕花楠木青漆嵌玉大
圆桌，四周十二张镶银象牙扶手红木椅，杯碗勺箸，入眼生辉。
    这里便是醉仙楼的玫瑰厅，桌上平铺着一份菜单(menu)。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "south" : __DIR__"zxlpath",
        ]));

        set("item_desc", ([
                "menu": @TEXT
承办各式酒席, 欢迎惠顾：

        order birthday: 祝寿宴        (400两黄金)

        order marry:    订婚宴        (800两黄金)

        order player:   群豪宴        (1000两黄金)

        order end:      结  束

TEXT
        ]) );

        setup();
}
//是镜像
int is_mirror() { return 1; }