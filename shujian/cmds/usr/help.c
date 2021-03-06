//Modifyed BY LinuX@SJ 增加颜色显示
// Modified by Ciwei@SJ 优化
/*
help map xxxx    显示/help/map/下的文件 xxxx 对应文件名
help job xxxx    显示/help/job/下的文件 xxxx 对应文件名
help group xxxx  显示/help/group/下的文件 xxxx 对应文件名
help dazao xxxx  显示/help/dazao/下的文件 xxxx 对应文件名
help quest xxxx  显示/help/quest/下的文件 xxxx 对应文件名
help party xxxx  显示/help/party/下的文件 xxxx 对应文件名
help xxxx        显示/help/topic/ 或者 /help/misc/下的对
		 应 xxxx 对应文件名，优先考虑/topic/

*/
inherit F_CLEAN_UP;
#include <ansi.h>
#include <mudlib.h>
#include "/doc/help.h"

private int show_the_help(object me,string file);
private string color_filter(string content);
private string get_title(string str);
string *default_search = DEFAULT_SEARCH_PATHS;

int main(object me, string arg )
{
        int i;
        string file, *search, dir;

        if( !arg ) 
        {
                if(show_the_help(me,HELP_DIR + "topics")) return 1;
                error("help topics 被非法移动了");
                return 1;
                //write(color_filter(read_file(HELP_DIR + "topics")));
                //return 1;
        }
        
        seteuid( getuid() );
        if( sscanf(arg, "map %s", arg) ) 
        {
                if( file_size("/help/map/"+arg) > 0 ){
                	if(show_the_help(me,"/help/map/" + arg)) return 1;
                //me->start_more(color_filter( read_file("/help/map/" + arg) ));
                //return 1;	
                }
                else
                	return notify_fail("目前还没有 "+HIY+arg+NOR+ " 这个地图帮助文件。\n");          
          
        } 
        
        
        if( sscanf(arg, "quest %s", arg) ) 
        {
                if( file_size("/help/quest/"+arg) > 0 ){
                	if(show_the_help(me,"/help/quest/" + arg)) return 1;
                //me->start_more(color_filter( read_file("/help/quest/" + arg) ));
                //return 1;	
                }
                else
                	return notify_fail("目前还没有 "+HIY+arg+NOR+ " 这个江湖秘密帮助文件。\n");          
          
        } 
        
        if( sscanf(arg, "group %s", arg) ) 
        {
                if( file_size("/help/group/"+arg) > 0 ){
                	if(show_the_help(me,"/help/group/" + arg)) return 1;
                //me->start_more(color_filter( read_file("/help/group/" + arg) ));
                //return 1;	
                }
                else
                	return notify_fail("目前还没有 "+HIY+arg+NOR+ " 这个帮派帮助文件。\n");  
        } 
        
        if( sscanf(arg, "dazao %s", arg) ) 
        {
                if( file_size("/help/dazao/"+arg) > 0 ){
                	if(show_the_help(me,"/help/dazao/" + arg)) return 1;
                //me->start_more(color_filter( read_file("/help/dazao/" + arg) ));
                //return 1;	
                }
                else
                	return notify_fail("目前还没有 "+HIY+arg+NOR+ " 这个打造系统帮助文件。\n");  
        } 
        /*
        if( sscanf(arg, "career %s", arg) ) 
        {
                if( file_size("/help/career/"+arg) > 0 ){
                me->start_more(color_filter( read_file("/help/career/" + arg) ));
                return 1;	
                }
                else
                	return notify_fail("目前还没有 "+HIY+arg+NOR+ " 这个职业系统帮助文件。\n");
                
                
          
        } */
        
	if( sscanf(arg, "job %s", arg) ) 
        {
                dir = "/help/job/";
                if( file_size("/help/job/"+arg) > 0 ){
                	if(show_the_help(me,"/help/job/" + arg)) return 1;
                //me->start_more(color_filter( read_file("/help/job/" + arg) ));
                //return 1;
       		 }
       		else
       			 return notify_fail("目前尚没有 "+HIY+arg+NOR+" 这个任务或是这个任务尚没有帮助文件。\n");
        }
		
	if( sscanf(arg, "party %s", arg) ) 
        {
                dir = "/help/party/";
                if( file_size("/help/party/"+arg) > -1 ){                	
                	if(show_the_help(me,"/help/party/" + arg)) return 1;
                //me->start_more(color_filter( read_file("/help/party/" + arg) ));
                //return 1;
        	}
        	else
        	return notify_fail("目前尚没有 "+HIY+arg+NOR+" 这个门派的资料。\n");
        } 

        arg = ALIAS_D->process_global_alias( arg );
        if( stringp( file = me->find_command( arg )) ) 
        {
                notify_fail("有这个指令存在，并没有说明文件。\n");
                return write( HIG"◎"HIW+CHINESE_MUD_NAME+HIG" ◎"NOR"\n") + file->help( me );
        }

        if( pointerp( search = me->query( "help_search_path" ) ) ) 
        {
                i = sizeof(search);
                while( i-- )
                {
                        if( file_size( search[i] + arg) > 0 ) 
                        {
                                if(show_the_help(me,search[i] + arg)) return 1;
                        }
                }
        }

        sscanf(arg, "%s()", arg);
        if( pointerp(default_search) ) 
        {
                i = sizeof(default_search);
                while(i--) 
                {
                        if( file_size(default_search[i] + arg)>0 ) 
                        {
				if(show_the_help(me,default_search[i] + arg)) return 1;
                        }
                }
        }

        return notify_fail("没有针对 "HIY+arg+NOR" 这项主题的说明文件。\n");
}
private int show_the_help(object me,string file)
{
	if(file_size(file)<0) return 0;
	if (me->query("env/fastread"))
		if (file_size(file) > 8192 )
		{
			tell_object(me,
                	HIY"很抱歉，因为您所查阅的文件比较大，只能一页页显示。\n"NOR);
			me->start_more( color_filter( read_file(file) ) );
		}
		else write(color_filter( read_file(file) ));
	else me->start_more( color_filter( read_file(file) ) );
	return 1;
}

private string color_filter(string msg)
{
        string *output;
        int i;
        string content = "";
        if (! msg)
                return "";
	
	output = explode(msg,"\n");
	
	for(i=0;i<sizeof(output);i++)
	{
		if(strsrch(output[i],"$TITLE$") < 0)
		{
			content += (output[i] + "\n"); 
			continue;
		}
		else
		{
			output[i]= replace_string(output[i],"$TITLE$","");
			content += replace_string(output[i],output[i],get_title(output[i]));
		}
	}

        /*  Foreground Colors  */

	content = replace_string(content, "$BLK$", BLK);		/* Black   */
	content = replace_string(content, "$RED$", RED);		/* Red     */
	content = replace_string(content, "$GRN$", GRN);		/* Green   */
	content = replace_string(content, "$YEL$", YEL);		/* Yellow  */
	content = replace_string(content, "$BLU$", BLU);		/* Blue    */
	content = replace_string(content, "$MAG$", MAG);		/* Magenta */
	content = replace_string(content, "$CYN$", CYN);		/* Cyan    */
	content = replace_string(content, "$WHT$", WHT);		/* White   */

	/*  Hi Intensity Foreground Colors  */

	content = replace_string(content, "$HIR$", HIR);		/* Red     */
	content = replace_string(content, "$HIG$", HIG);		/* Green   */
	content = replace_string(content, "$HIY$", HIY);		/* Yellow  */
	content = replace_string(content, "$HIB$", HIB);		/* Blue    */
	content = replace_string(content, "$HIM$", HIM);		/* Magenta */
	content = replace_string(content, "$HIC$", HIC);		/* Cyan    */
	content = replace_string(content, "$HIW$", HIW);		/* White   */

        /*  Background Colors  */

	content = replace_string(content, "$BBLK$", BBLK);		/* Black   */
	content = replace_string(content, "$BRED$", BRED);		/* Red     */
	content = replace_string(content, "$BGRN$", BGRN);		/* Green   */
	content = replace_string(content, "$BYEL$", BYEL);		/* Yellow  */
	content = replace_string(content, "$BBLU$", BBLU);		/* Blue    */
	content = replace_string(content, "$BMAG$", BMAG);		/* Magenta */
	content = replace_string(content, "$BCYN$", BCYN);		/* Cyan    */

	/*  Hi Intensity Background Colors  */

	content = replace_string(content, "$HBRED$", HBRED);	/* Red     */
	content = replace_string(content, "$HBGRN$", HBGRN);	/* Green   */
	content = replace_string(content, "$HBYEL$", HBYEL);	/* Yellow  */
	content = replace_string(content, "$HBBLU$", HBBLU);	/* Blue    */
	content = replace_string(content, "$HBMAG$", HBMAG);	/* Magenta */
	content = replace_string(content, "$HBCYN$", HBCYN);	/* Cyan    */

	content = replace_string(content, "$NOR$", NOR);	/* Puts everything back to normal */

	/*  Additional  */

	content = replace_string(content, "$U$", U);		/* Initialize underscore mode */		
	content = replace_string(content, "$BLINK$", BLINK);	/* Initialize blink mode */
	content = replace_string(content, "$REV$", REV);	/* Turns reverse video mode on */
	content = replace_string(content, "$HIREV$", HIREV);	/* Hi intensity reverse video  */
	content = replace_string(content, "$BOLD$", BOLD);	/* Turn on bold mode */

        return content;
}
string get_title(string str)
{
        string arg;
	arg = sprintf("$BBLU$$HIW$%|60s$NOR$\n",str);
        return arg;
} 

int help(object me)
{
        write(@HELP
----------------------------------------
指令格式：help <主题>

help <函数名称>
      
例如：> help cmds

这个指令提供你针对某一主题的详细说明文件，若是不指定主题，
则提供你有关主题的文件。

/*help map
查看地图

help group <帮派名称>
查看帮派简介*/
----------------------------------------
HELP
        );
        return 1;
}
