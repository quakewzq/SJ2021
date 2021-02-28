// qload.c

inherit F_CLEAN_UP;

int main()
{
   object me=this_player();
    write(query_load_average() + "  "+me +"\n");
    return 1;
}

int help(object me)
{
write(@HELP
指令格式 : qload 

这个指令显示出目前 CPU 的负担, cmds/s 是每秒编译几个 cmds
comp lines/s 是每秒几行。
HELP
    );
    return 1;
}
