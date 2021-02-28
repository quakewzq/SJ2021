// jianzhong.c
// By River 98.08.29
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIW"剑冢"NOR);
        set("long", @LONG
搬开冢上石块，露出并列著的三柄长剑。在第一、第二两把剑之间，另有
一块长条石片。三柄剑和石片并列於一块大青石之上。  
LONG
        );
        set("item_desc", ([        
           "shipian" : "紫薇软剑，三十岁前所用，误伤义不祥，乃弃之深谷。\n",
        ]));

        setup();
}

void init()
{
        add_action("do_ti", "ti");
        add_action("do_ti", "na");
        add_action("do_tui", "tui");               
}

int do_ti(string arg)
{
        object me,sword,ob;
        int i;
        me = this_player();
        if (!arg ) return 0;         
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");
        if(!present("fire", me))
                return notify_fail("你身上没有点火之物，看得清楚提什么吗？\n");
        if ( arg == "gangjian" ){
           ob = unew(BINGQI_D("sword/wuming-jian"));
           if(!clonep(ob))
              return notify_fail(HIR"你来晚了，无名宝剑已经给人取走了。\n"NOR);              
           if(clonep(ob) && ob->violate_unique()){
              destruct(ob);
              return notify_fail(HIR"你来晚了，无名宝剑已经给人取走了。\n"NOR);
           }
           tell_object(me,HIY"你提起右首第一柄剑，只见剑下的石上刻有两行小字：\n"+
                             "「凌厉刚猛，无坚不摧，弱冠前以之与河朔群雄争锋。」\n"NOR);
           tell_room(environment(me), me->name() + "附下身躯，伸手提起右首第一柄剑。\n"NOR, ({ me }));
           ob->move(me);
           return 1;
        }
        else
        if ( arg == "xuantiejian" ){
           if (!me->query("ygpass")){
             if (me->query_str() < 35 )
                  return notify_fail("你用力想提起玄铁剑，但力不从心。\n");
           }
           else if (me->query_str() < 32 )
                  return notify_fail("你用力想提起玄铁剑，但力不从心。\n");
           if (me->query("max_neili") < 2000 ){
                tell_object(me,HIY"你再伸手去提第二柄剑，只提起数尺，呛啷一声，竟然脱手掉下，在石上一碰，\n"+
                                  "火花四溅，不禁吓了你一跳。\n"NOR);
                tell_room(environment(me), me->name() + "再伸手去提第二柄剑，只提起数尺，呛啷一声，竟然脱手掉下。\n"NOR, ({ me }));
                return 1;
            }
            sword= unew(BINGQI_D("sword/xuantiejian"));
            if(!clonep(sword))
                return notify_fail(HIR"你来晚了，玄铁剑已经给人取走了。\n"NOR);
            if(clonep(sword) && sword->violate_unique()){
                destruct(sword);
                return notify_fail(HIR"你来晚了，玄铁剑已经给人取走了。\n"NOR);
            } 
            if(me->query("neili") >= 300 )
                me->add("neili", -300);
            else
                me->set("neili", 0);
                me->delete_temp("sword");
                tell_object(me,HIY"於是你再俯提起，这次有了防备，提起七八十斤的重物自是不当一回事。见那\n"+
                                  "剑两边剑锋都是钝口，剑尖更圆圆的似是个半球。看剑下的石刻时，见两行小\n"+
                                  "字道：「重剑无锋，大巧不工。四十岁前恃之横行天下。」\n"NOR);
                tell_room(environment(me), me->name() + "吸了口气，伸手提起第二柄剑。\n"NOR, ({ me }));
                sword->move(me);
                return 1;
        }
        else if( arg == "mujian") {
                tell_object(me,HIY"你力运左臂去取第三柄剑。那知拿在手中却轻飘飘的浑似无物，凝神一看，原\n"+
                                  "来是柄木剑，年深日久，剑身剑柄均已腐朽，但见剑下的石刻道：「四十岁後，\n"+
                                  "不滞於物，草木竹石均可为剑。自此精修，渐进於无剑胜有剑之境。」\n"NOR);

                if(me->query_temp("quest/wuzhao/over")){
                
                i = me->query_temp("quest/wuzhao/over");
                
                
                 if(me->query_skill("dugu-jiujian",1)>=451
                                   && me->query("int")>35
                                   &&random(me->query("kar"))>=28
                                   &&random(15-i)==10
                                   &&!me->query("quest/pass/dugu-jiujian/wuzhao")
                       || me->query("id")=="master"){
                tell_object(me,HBMAG"你对着石刻下的字沉默良久，心中若有所悟。\n"+
                                  MAG"独孤九剑有招如无招，存招式之意，而无招式之形。“独孤九剑”精微奥妙，达于\n"+
                                   "极点，但毕竟一招一式，尚有迹可寻，待得再将“以无招胜有招”的剑理加入运\n"+
                                   "用，那就更加的空灵飘忽，令人无从捉摸。敌招倘若只有一招，我也只有一招，\n"+
                                   "敌招有千招万招，他也有千招万招，随敌招之来而自然应接。\n"+
                                  HBRED"恭喜，你成功的领悟了独孤九剑“无剑胜有剑，无招胜有招！”的奥秘精义！！！\n"NOR);               
                                 me->set("quest/pass/dugu-jiujian/wuzhao",1);
                                 me->delete_temp("quest/wuzhao");
                                 
                                 
                if( !me->query("quest/pass/dugu-jiujian/wuzhao"))
                       log_file("quest/wuzhao", 
                                  sprintf("%-18s在剑冢领悟无招无式，福：%d，悟：%d。\n",
                                           me->name(1)+"("+capitalize(getuid(me))+")",
                                         me->query("kar"), 
                                           me->query("int") 
                                   ), me
                            );                                
                                 
                                   }
                 else me->delete_temp("quest/wuzhao");
                }
          
                return 1;
              }
}

int do_tui(string arg)
{
        object me;
        me = this_player();
        if (me->is_busy() || me->is_fighting())
             return notify_fail("你正忙着哪！\n");
        if ( !arg || arg !="shi" )
             return notify_fail("你要推什么？\n");
          message_vision(YEL"$N深深地吸了口气，缓缓推动青石。\n"NOR,me);
          write(HIG"\n你把青石推开！露出了剑冢的出口。\n"NOR);
          set("exits/out", __DIR__"pingtai");
          remove_call_out("close");
          call_out("close", 5, this_object());
          return 1; 
}      

void close(object room)
{
        message("vision",HIY"青石慢慢移回了原位，又挡住了出口。\n"NOR, room);
        room->delete("exits/out");
}

