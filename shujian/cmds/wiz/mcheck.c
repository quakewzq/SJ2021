// mcheck.c
// Created by bbb@SJ
// modified by snowman@SJ 28/06/2000
// added ip check and player check.
// modify by spiderii fix bug

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int i, j, k, count = 0;
        object *lob, obj, *obs;
        string ip, tmp, str = HIR"\n  …… 检查多重登录(ML) …… "NOR;
        mixed groups;
        int ip1,ip2,ip3,ip4,n,myip,yourip;
        string arg1;

        obs = filter_array(objects(), (: interactive :));
        obs = filter_array(obs, (:environment:));
        obs = filter_array(obs, "visible", me);
        obs = sort_array(obs, (:strcmp(query_ip_number($2), query_ip_number($1)):));
        i = sizeof(obs);
        if( stringp(arg) )
        {
                if( objectp(obj = LOGIN_D->find_body(arg)) && me->visible(obj) && interactive(obj))
                {
                        arg = query_ip_number(obj);
                        tmp = "\n"+ obj->name(1) +"("+ obj->query("id") +")\nIP："+ arg +"\nPort：[]\n";
                        tmp += "目前和此人从相同IP连入的玩家有：\n\t";
                }
                else
                        tmp = "\n目前通过 " + arg + " 连入的玩家有：\n\t";
                n=sscanf(arg,"%d.%d.%d.%d",ip1,ip2,ip3,ip4);
                myip=(ip1<<24)+(ip2<<16)+(ip3<<8)+ip4;
                while(i--)
                {
                        if( obs[i] == obj )
                                continue;
                        arg1=query_ip_number(obs[i]);
                        sscanf(arg1,"%d.%d.%d.%d",ip1,ip2,ip3,ip4);
                        yourip=(ip1<<24)+(ip2<<16)+(ip3<<8)+ip4;
                        if (query_ip_number(obs[i]) == arg || (myip>>(8*(4-n)))==(yourip>>(8*(4-n))))
                        {
                                tmp += sprintf("%-25s ", obs[i]->query("name") + "("+obs[i]->query("id")+")");
                                count++;
                                if( count % 3 == 0 )
                                {
                                        tmp += "\n\t";
                                        count = 0;
                                }
                        }
                }
                write(tmp+"\n");
                return 1;
        }

        groups = unique_array(obs, (: query_ip_number($1) :));
        if ( !k = sizeof(groups) )
                return notify_fail(HIR"\n  …… 完毕 …… \n"NOR);

        for(i = 0; i < k; i++)
        {
                if( sizeof( groups[i])  <= 1)
                        continue;
                obs = groups[i];
                lob = obs->query_temp("link_ob") - ({0});
                ip = query_ip_number(obs[0]);
                tmp = sprintf("\n"HIY"%-16s"WHT" → "NOR, ip);
                for( j = 0; j < sizeof(obs); j++ )
                {
                        if( j > 0 && j % 4 == 0 )
                                tmp += "\n\t\t    ";
                        tmp += sprintf("%-16s", obs[j]->query("id"));
                }

                str += tmp;
                lob = sort_array(lob, (:strcmp($1->query("password"), $2->query("password")):));
                count = sizeof(lob);
                ip = j = 0;
                tmp = arg = "";
                while(count--)
                {
                        if (lob[count]->query("password") != ip)
                        {
                                if (j > 1)
                                        arg += "(" +tmp+") ";
                                ip = lob[count]->query("password");
                                j = 0;
                                tmp = "";
                        }
                        tmp += lob[count]->query("id")+", ";
                        j++;
                }
                if (j > 1)
                        arg += "(" +tmp+") ";
                if( arg != "" )
                        str += HIG"\n\t\t    口令相同的有："+arg+NOR;
                lob = sort_array(lob, (:strcmp($1->query("email"), $2->query("email")):));
                count = sizeof(lob);
                ip = j = 0;
                tmp = arg = "";
                while(count--)
                {
                        if (lob[count]->query("email") != ip)
                        {
                                if (j > 1)
                                        arg += "(" +tmp+") ";
                                ip = lob[count]->query("email");
                                j = 0;
                                tmp = "";
                        }
                        tmp += lob[count]->query("id")+", ";
                        j++;
                }
                if (j > 1)
                        arg += "(" +tmp+") ";
                if( arg != "" )
                        str += HIC"\n\t\t    Email相同的有："+arg+NOR;
        }

        str += HIR"\n  …… 完毕 …… \n"NOR;
        str += sprintf(HIR"\n  实际在线IP地址数：%d\n"NOR, k);
        me->start_more(str);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：mcheck [ip|某人]

例：
        mcheck 61.137.155.126   -> 列出从此ip连入的玩家。
        mcheck 61.137.          -> 列出从此ip范围内连入的玩家。
        mcheck snowman          -> 列出和次玩家相同ip的其它玩家。
        mcheck                  -> 列出所有相同ip的列表，附带相同 email， passwd列表。
HELP
        );
        return 1;
}


