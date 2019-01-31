// updateip.c 

int help(object me);

int main(object me, string arg)
{
	int start;
	int count;
	if (!arg)
	{
		return help(me);
	}

	if (sscanf(arg, "%s %d %d", arg, start, count) == 3)
	{
//                return IP_D->update_ip(me, arg, start, count);
                return "/adm/daemons/ipd2.c"->update_ip(me, arg, start, count);
	}

//        return IP_D->update_ip(me, arg);
        return "/adm/daemons/ipd2.c"->update_ip(me, arg);
}

int help(object me)
{
	write(@HELP
指令格式：updateip [<文件名>|<目录名> <开始文件> <文件数>]

指令说明：用IP文件更新系统IP库。

HELP);

	return 1;
}

