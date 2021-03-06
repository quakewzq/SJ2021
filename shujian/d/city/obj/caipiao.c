// by lsxk@hsbbs 2007/9/26
inherit ITEM;
inherit F_AUTOLOAD;
#include <ansi.h>

string strSN;
void mapping_sn(object);

void create(object me,string arg)
{
        set_name(HIY "彩票联" NOR, ({"cai piao","caipiao"}));
        set("unit", "张");
        set("long", "这是一您购买的摸彩凭证，你可以在上面查看(read)到您所有购买的排列序号。\n");
        set("value", 0);
        set("no_drop","请用drop [caipiao|cai piao]来丢弃!");
        set("no_give",1);
        setup();
}

void init()
{
    object me = this_player();
    add_action("do_drop","drop");
    if(!me->query("caipiao")) return;

    mapping_sn(me);
    add_action("do_check","read");
}

int do_drop(string arg)
{
     object me = this_player();

     if(!arg) return notify_fail("你要仍什么?\n");

     if(arg!="caipiao" && arg!="cai piao") return 0;

     me->delete("caipiao");
     me->delete("caipiao_id");
     message_vision(HIC"$N随手仍掉了一张"+HIY+"彩票联"+HIC+"!\n"NOR,me);
     destruct(present("cai piao", me));

    return 1;
}

void mapping_sn(object me)
{
    int i, k;
    mapping my_caipiao;
    //string strTemp;

    my_caipiao = me->query("caipiao");
    i = sizeof(me->query("caipiao"));
    strSN = "您购买了以下排列序号的彩票：\n";

    for(k = 0;k<i;k++){
        strSN += "第"+chinese_number(k+1)+"张，序号："+HIC+me->query("caipiao/第"+chinese_number(k+1)+"张/my_caipiao")+NOR+"  购买货币："+HIY+me->query("caipiao/第"+chinese_number(k+1)+"张/huobi")+"\n"NOR;
    }
}

int do_check(string arg)
{
    object me = this_player();

    if(!arg) return notify_fail("你要看什么?\n");

    if(arg!="caipiao" && arg!="cai piao") return notify_fail("你要看什么?\n");

    if(!me->query("caipiao")){
        message_vision("$N看了看这张彩票，发现不是自己买的，随手就仍在了街边。\n",me);
        destruct(this_object());
        return 1;
    }

    mapping_sn(me);
    tell_object(me, strSN);
    return 1;
}

int query_autoload() { return 1; }

