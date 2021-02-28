#include <ansi.h>

int main(object me)
{
// 最低损失
        int cost = 5;

        if (functionp(me->is_busy()) 
         || (me->is_busy() < 5 && me->is_perform() < 3 && me->is_exert() < 3) 
         || me->query_temp("chongxue"))
                return notify_fail("别乱用，小心走火入魔。\n");
        if (me->query_skill("force") < 400)
                return notify_fail("你的内功等级不够。\n");
        if (me->query("family/family_name") == "桃花岛" && me->query_skill("tanzhi-shentong", 1) < 300)
                return notify_fail("你的弹指神通还不够纯熟。\n");
        if (me->query("max_neili", 1) < 5000 || me->query("neili", 1) < 3000)
                return notify_fail("你的内力不够。\n");
 
        if (me->is_busy())   
                cost += me->is_busy();
        if (me->is_perform()) 
                cost += me->is_perform();
        else
                cost += 2;
        if (me->is_exert()) 
                cost += me->is_exert();
        else
                cost += 2;
        me->set_temp("last_damage_from","走火入魔");
        if (me->query("family/family_name") == "桃花岛") 
        {
                message_vision(HBMAG HIC"\n$N用弹指神通向身上真气受阻处一弹，勉强解开了自己真气不纯处。\n"NOR, me);
                me->receive_wound("jing", cost * 30 + random(cost * 30));
                me->add("neili", - cost * 50 - random(cost * 50));
                if (!random(3)) me->start_perform(0);
        }
        else
        {
                message_vision(HBMAG HIG"\n$N强运真气在体内游走，终于冲破了受阻的穴道以及真气不灵活处。\n"NOR, me);
                me->receive_wound("jing", cost * 60);
                me->add("neili", - cost * 100);
        } 
        message_vision(HIR"$N吐出一口鲜血。\n"NOR, me);
        if (random(2)) me->set("neili", 0);
        me->add("max_neili", - cost * 2);
        me->set_temp("chongxue",1);
        me->interrupt_me();
        me->start_busy(1, 2);
        me->interrupt_me();
        me->start_exert(0);
        log_file("skills/chongxue",sprintf("[%s] %s(%s)强行冲穴，造成 %d 点内力损伤。\n",
                ctime(time())[4..19], me->name(), getuid(me), cost * 2 ));
        call_out("finish", 300, me);
        return 1;
} 
 
void finish(object me)
{
        if (!me || !me->query_temp("chongxue"))
                return;
        write(HIY"$N长长的舒了口气，内息渐渐调整均匀了。\n");
        me->delete_temp("chongxue");
}

