//plan.c by XiaoYao 2/8/2k
                        
inherit F_DBASE;

#include <ansi.h>
int help(object me);
void do_plan(string me,string path, string text);
void do_note(string me,string path, string text);
void do_user_motd(object me,string path, string text);
void do_wiz_motd(object me,string path, string text);

void create() 
{
        seteuid(getuid());
        set("channel_id", "计划精灵");
}

int main(object me,string arg)
{
        string target,path;
        if(!user_path(geteuid(me)))
                return notify_fail("你并没有家目录\n");
        if(!arg){
                path = user_path(geteuid(me)) + "wiz_plan";
                write(CLR"");
                if( file_size(path) > 0 ){       
                 write(HIW"目前的计划档:\n"NOR);
                 write(read_file(path));
                 }
                write(HIY"\n\n编辑自己的计划档\n"NOR);
                me->edit((: do_plan, geteuid(me),path :));
                return 1;
                }
        if (arg == "none")
        {
                path = user_path(geteuid(me)) + "wiz_plan";
                if( file_size(path) <= 0 )
                 return notify_fail("你没有计划档啊。\n");
                rm(path);
                write("清除计划档。\n");
                CHANNEL_D->do_channel( this_object(), "sys",
                sprintf("%s(%s)清除计划档在%s。", me->query("name"),me->query("id"), ctime(time()) ) );
                log_file("wiz_log/wiz_plan",
                        sprintf("%s(%s)清除计划档于%s\n"NOR,me->query("name"),me->query("id"), ctime(time()) ));
                return 1;
        }
        if(arg == "note none")
        {
                path = user_path(geteuid(me)) + "wiz_note";
                if( file_size(path) <= 0 )
                 return notify_fail("你没有留言记录喔。\n");
                rm(path);
                write("清除留言记录。\n");
                return 1;
        }
        if(arg == "user none")
        {
           path = "/adm/etc/motd";

           if(wizhood(me) != "(admin)" && wizhood(me) != "(arch)" )
              return notify_fail("只有大巫师以上才能删除每日讯息\n");
           if( file_size(path) <= 0)
             return notify_fail("没有使用者公告!\n");
           rm(path);
           write("清除使用者公告\n");
           CHANNEL_D->do_channel( this_object(), "sys",
                sprintf("%s(%s)清除使用者公告在%s。", me->query("name"),me->query("id"), ctime(time()) ) );
           log_file("wiz_log/user_motd",
                sprintf(HIC"%s(%s)清除使用者公告于%s\n"NOR,me->query("name"),me->query("id"), ctime(time()) ));
           return 1;
        }
if(arg == "wiz none")
        {
          path = "/adm/etc/wiz_motd";
          if(wizhood(me) != "(admin)")
            return notify_fail("只有天神才能删除巫师每日讯息\n");
          if( file_size(path) <= 0)
            return notify_fail("没有巫师公告!\n");
           rm(path);
           write("清除巫师公告\n");
           CHANNEL_D->do_channel( this_object(), "sys",
                sprintf("%s(%s)清除巫师公告在%s。", me->query("name"),me->query("id"), ctime(time()) ) );
           log_file("wiz_log/wiz_motd",
                        sprintf(HIC"%s(%s)清除巫师公告于%s\n"NOR,me->query("name"),me->query("id"), ctime(time()) ));
           return 1;
        }
        if(arg == "user motd"){
         path = "/adm/etc/motd";
         if( file_size(path) > 0){
                write(CLR""+HIW"目前的使用者公告\n"NOR);
                write(read_file(path));
}else
                write(CLR""+HIR"目前没有使用者公告\n"NOR);
                
        if(wizhood(me) == "(admin)" || wizhood(me) == "(arch)" ){ 
         write(HIY"\n编辑使用者公告\n\n"NOR);
         me->edit((: do_user_motd ,me ,path :));
         }
         return 1;
        }
        if(arg == "wiz motd"){
          if(wizhood(me) != "(admin)")
            return notify_fail("只有天神才能公布巫师每日讯息\n");
          else path = "/adm/etc/wiz_motd"; //条件通过再指定变数

         write("编辑巫师公告\n");
            if( file_size(path) > 0){
             write(CLR""+HIW"目前的巫师公告\n"NOR);
             write(read_file(path));
                                            }
           write(HIY"\n编辑巫师每日公告\n\n"NOR);
      me->edit((: do_wiz_motd , me ,path:));
            return 1;
            }
       if(sscanf(arg,"-w %s",target) == 1){
           target = replace_string(arg,"-w ","");
           if( wiz_level(target) == 0){
             write("他不是巫师,不需要使用【计划】交待留言!\n");
             return 1;
           }else path = user_path(target) + "wiz_plan";
           if(file_size(path) > 0){
            write(HIY+target+"的计划档 :\n"NOR);
            me->start_more(read_file(path));
           }else write(target+"并没有计划档!!\n"); 
           return 1;
        }    
        if(sscanf(arg,"-n %s",target) == 1){
           target = replace_string(arg,"-n ","");
           if( wiz_level(target) == 0)
            {
               write("他不是巫师,不需要使用【计划】交待留言!\n");
       return 1;
             }else path = user_path(target) + "wiz_note";

           write("给"+target+"这个巫师留言\n");
            me->edit((: do_note , target ,path: ));
            return 1;
                         }
        if(sscanf(arg, "%s",arg) == 1 ){
                
                if(SECURITY_D->get_status(me) != "(arch)"
                        && SECURITY_D->get_status(me) != "(admin)" )
                                return notify_fail("只有 (arch) 以上的巫师才能指派任务\n");
                if( wizhood(arg) == "(player)"){
                        write("他不是巫师,不需要使用【计划】交待留言!\n");
                        return 1;
                }else path = user_path(arg) + "wiz_plan";
                me->edit((: do_plan, arg ,path:));
                return 1;
                }
        else return help(me);
        return 1;
}


void do_plan(string planer,string path, string text)
{
        string msg;
        msg = "提案人 ("+this_player()->query("id")+") "+ctime(time()) +"\n"+text;
        if (planer)
        {
           write_file(path,msg,1);
           write(HIW"计划档设定完成。\n"NOR);
           CHANNEL_D->do_channel( this_object(), "sys",
                sprintf("%s(%s)计划档设定完成在%s。", this_player()->query("name"),geteuid(this_player()), ctime(time()) ) );
           log_file("wiz_log/wiz_plan",
                        sprintf(HIC"%s(%s)计划档设定完成于%s\n"NOR,this_player()->query("name"),geteuid(this_player()), ctime(time()) ));
        }
        else{
           write(HIR"计划档设定失败。\n"NOR);
           CHANNEL_D->do_channel( this_object(), "sys",
sprintf(HIR"%s(%s)计划档设定失败在%s。"NOR, this_player()->query("name"),geteuid(this_player()), ctime(time()) ) );
           log_file("wiz_log/wiz_plan",
                        sprintf(HIR"%s(%s)计划档设定失败于%s\n"NOR,this_player()->query("name"),geteuid(this_player()), ctime(time()) ));
       }
}

void do_note(string planer,string path, string text)
{
        object me = this_player();
        string msg;
        msg = "留言者:("+me->query("id")+") "+ctime(time())+"\n"NOR+ text;

        if (planer)
        {
                write_file(path,msg);
                write(HIW"留言完毕。\n"NOR);
                CHANNEL_D->do_channel( this_object(), "cic",
                sprintf("%s(%s)留言给%s在%s。", me->query("name"),me->query("id"),planer,ctime(time()) ) );
                log_file("wiz_log/note_message",
                        sprintf("%s(%s)留言给%s于%s\n",me->query("name"),me->query("id"),planer, ctime(time()) ));
}
        else{
            write(HIR"留言失败。\n"NOR);
            CHANNEL_D->do_channel( this_object(), "cic",
                sprintf(HIR"%s(%s)留言给%s失败在%s。"NOR, me->query("name"),me->query("id"),planer,ctime(time()) ) );
             log_file("wiz_log/note_message",
                     sprintf(HIR"%s(%s)留言给%s失败于%s\n"NOR,me->query("name"),me->query("id"),planer, ctime(time()) ));
        }
}

void do_user_motd(object me,string path,string text)
{
        string msg;
        msg = HIW"公布者:("+me->query("id")+") "NOR+ctime(time())+"\n"+text;      
 
        if(me)
        {
          write_file(path,msg);
          write("使用者公告完毕\n");
          CHANNEL_D->do_channel( this_object(), "sys",
          sprintf("%s(%s)在%s发布使用者公告。", me->query("name"),me->query("id"),ctime(time()) ) );
          log_file("wiz_log/user_motd",
                        sprintf("%s(%s)于%s发布使用者公告\n",me->query("name"),me->query("id"), ctime(time()) ));

        }else{
            write("公告失败\n");
          CHANNEL_D->do_channel( this_object(), "sys",
                sprintf("%s(%s)在%s发布使用者公告失败。", me->query("name"),me->query("id"),ctime(time()) ) );
          log_file("wiz_log/user_motd",
                        sprintf(HIR"%s(%s)于%s发布使用者公告失败\n"NOR,me->query("name"),me->query("id"), ctime(time()) ));
         }
}
void do_wiz_motd(object me,string path,string text)
{
       string msg;
       msg = HIW"公布者:("+me->query("id")+") "NOR+ctime(time())+"\n"+text;

       if(me)
       {
        write_file(path,msg);
        write("巫师公告完毕\n");
        CHANNEL_D->do_channel( this_object(), "sys",
                sprintf("%s(%s)在%s发布巫师公告。", me->query("name"),me->query("id"),ctime(time()) ) );
        log_file("wiz_log/wiz_motd",
                        sprintf("%s(%s)于%s发布巫师公告\n",me->query("name"),me->query("id"), ctime(time()) ));
        }else{
           write("公告失败\n");
           CHANNEL_D->do_channel( this_object(), "sys",
                sprintf("%s(%s)在%s发布巫师公告失败。", me->query("name"),me->query("id"),ctime(time()) ) );
           log_file("wiz_log/wiz_motd",
                        sprintf(HIR"%s(%s)于%s发布巫师公告失败\n"NOR,me->query("name"),me->query("id"), ctime(time()) ));
          }
}

int help(object me)
{
 write(@HELP
指令格式 : plan           =>不加参数时是编辑自己的计画档
           plan    [none] => 清除自己的计划档
           plan    [note none] => 清除留言
           plan -n [想交待留言的巫师的id] => 留言给其它巫师
           plan    [user motd] => 阅读使用者每日公告
           plan -w [WIZ id] =>观看巫师计划

以下是大巫师以上才可以使用的参数:
           plan    [想交待任务给巫师的id] => 交待任务给指定的巫师
           plan    [user motd] => 公布使用者每日公告
           plan    [user none] => 清除使用者公告
           plan    [wiz motd]  => 巫师公告
           plan    [wiz none]  => 清除巫师公告
用途:
提示自己上线该做的事,大巫师以上会使用这个指令指派任务给巫师
让你在上线时就看到最新交付任务以及该做的事,大巫师以上公布事
项会连同之前的公告一起出现,只有使用none指令才会将档案清除,编
辑计划档也是,所以请小心使用none参数,别误删了重要记录!

这个指令可以编辑自己的计划，plan none 可以清除设定。

HELP
    );
  return 1;
}

