
#include <net/socket.h>
#include <ansi.h>
#define SITE "202.106.184.193"
inherit F_DBASE;
int have_get=0;
int fail=0;
string msg="";
int check_time();
void close(int);
void write_s(int);
void create()
{
set("channel_id","天气预报");
seteuid(getuid());
check_time();
}
int check_time()
{
mixed* times=localtime(time());
int hours=times[2];
int fd,fc;
if(! have_get)//每天3点开始抓网页
{
 if(fd=socket_create(STREAM,"read_callback")<0)
        {
                write("socket_create error "+fd+"\n");
                return 1;
        }
        if((fc=socket_connect(fd,SITE+" 80","read_callback","write_callback"))!= EESUCCESS)
        {
         close(fd);
                write("socket_connect error "+fc+"\n");
                return 1;
        }
        remove_call_out("write_s");
        call_out("write_s",2,fd);
        remove_call_out("close");
        call_out("close",20,fd);//等待二十秒，过时认为连接失败。
}
if(hours==12)
{
 have_get=0;//12点清除标记
 msg="";
 fail=0;
}
remove_call_out("check_time");
call_out("check_time",10);
return 1;
}
void read_callback(int fd,mixed val)
{
       msg+=sprintf("%O",val);
}
void write_callback(int fd)
{
       return;
}
void close(int fd)
{
string sun;
       string gaowen;
       string diwen;
       string fengli;
       write("close start\n");
if(strsrch(msg,"HTTP/1.1 200 OK")!=-1) //成功读取
       {
        //这些字符串分析与具体网页相关。
        int index,index2;
        string* msgArray=({});
        index=strsrch(msg,"北京");
        msg=msg[index..sizeof(msg)];
        index2=strsrch(msg,"</tr>");
        msg=msg[0..index2-1];
        msg=replace_string(msg,"/","");
        msgArray=explode(msg,"<td>");
        msgArray=filter_array(msgArray,(:$1!="\r\n ":));
   if(sizeof(msgArray)!=7)
   {
    write("size:"+sizeof(msgArray)+"\n");
    for(int i=0;i<sizeof(msgArray);i++)
    {
     write(msgArray[i]);
    }
    write("格式错误！\n");
   }
        else
        {
         sun=msgArray[1];
         fengli=msgArray[2];
         diwen=msgArray[3];
         gaowen=msgArray[6];
   write_file("/adm/etc/weather.log","\n\t\t\t今日北京天气："+HIB+sun+NOR+"
\n\t\t\t最低气温:"+HIR+diwen+NOR+"\n\t\t\t最高气温:"+HIY+gaowen+NOR+"\n",1);

   write("OK!\n");
  }
       }
else
{
 write("读取错误！\n");
}
       socket_close(fd);
}
void write_s(int fd)
{
       int fw;
       if((fw=socket_write(fd,"GET http://"+SITE+" HTTP/1.0\r\n"+
       "accept: www/source; text/html; image/gif; image/jpeg; */*\r\n"+
       "User_Agent: myAgent\r\n\r\n"
       ))!=EESUCCESS)
       {
               if(fail < 3)
               {
                fail++;
                remove_call_out("write_s");
                call_out("write_s",2,fd);
               }
               else
               {
                       fail=0;
                       close(fd);
               }
       }
       else
       {
               write("socket_write sucess!\n");
               fail=0;
}
}
