// work.c modified by system_3

inherit ROOM;

int cot;
void create()
{
        set("short", "破旧手工厂");
        set("long", @LONG
这里是一处古战场的遗迹，如今荒乱不堪野草丛生，传言有僵尸出没，害人性命。

LONG
        );
        set("exits", ([ /* sizeof() == 1 */
    "west" : __DIR__"beimen",
]));
        set("item_desc", ([
                "sign": @TEXT
现在正紧缺人手，急需雇佣一批短工来干活。
work     开始工作。
TEXT
        ]) );

        setup();
}
//是镜像
int is_mirror() { return 1; }