// who2.c

inherit F_CLEAN_UP;
#include <ansi.h>
int main(object me, string str)
{
    object where, ob, *ob_list;
    int i;
    seteuid(getuid());

    ob_list = users();
    ob_list = sort_array(users(), "sort_user", this_object());
    str = HIG" 螺社    定槍 贋錘           仇峽               侭壓       殻會       \n"NOR;
    str += "！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！\n";
    for(i=0; i<sizeof(ob_list); i++)
    {
        ob = ob_list[i];
        where = environment(ob);

        str += sprintf(WHT"%-8s:  ",ob->name());
        str += sprintf(HIR"%-2d ", ob->query("age"));
        str += sprintf(HIG"%-10d ", ob->query("balance"));
        str += sprintf(HIY"%-20s ", query_ip_name(ob));
    if (where) str += sprintf(HIM"%-10s ", where->query("short"));
    if (!where) str += sprintf("\n"NOR);
       else str += sprintf(HIC"%s\n"NOR, file_name(where));
    }
    str += "！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！\n";
    str = sprintf("%s慌嗤 %d 了聞喘宀銭�炒弌�\n", str, sizeof(ob_list));
    me->start_more(str);
    return 1;
}
int sort_user(object ob1, object ob2)
{
	if( wizardp(ob1) && !wizardp(ob2) ) return -1;
	if( wizardp(ob2) && !wizardp(ob1) ) return 1;
	if( wizardp(ob1) && wizardp(ob2) )
		return (int)SECURITY_D->get_wiz_level(ob2) 
			- (int)SECURITY_D->get_wiz_level(ob1);
	
	return (int)ob2->query("mud_age") - (int)ob1->query("mud_age");
}
int help(object me)
{
        write(@HELP
峺綜鯉塀��who2

螺社佚連臥儂。
HELP
        );
        return 1;
}
