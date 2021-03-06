#include <ansi.h>

int update_condition(object me, int duration)
{
        if (duration < 1)
        {
                if (me->query_temp("was_job/asked"))
                {
                        tell_object(me, HIR"宝塔的火势已然遍及整塔，营救行动已然失败，你只好迅速撤离。\n"NOR);
                        me->move("/d/nanyang/kedian1");
                        me->delete_temp("was_job");
                        me->apply_condition("job_busy", 10);
                }
                return 0;
        }
        if (me->query_temp("was_job/asked"))
        {
                if (duration < 5)
                        tell_object(me, HIR"宝塔的火势已经凶猛异常，抓紧时间！\n"NOR);
                else if (duration < 10)
                        tell_object(me, HIR"宝塔的火势已经迅速扩大，抓紧时间！\n"NOR);
                else
                        tell_object(me, HIR"宝塔的火势已经慢慢扩散，抓紧时间！\n"NOR);
        }
        me->apply_condition("was_job", duration - 1);
        return 1;
}

string query_type()
{
        return "job";
}
