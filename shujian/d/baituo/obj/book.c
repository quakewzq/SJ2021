// book.c ŷ�����ּ�

#include <ansi.h>

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
        add_action("do_du", "read");
}

void create()
{
        set_name("��װ��", ({ "xianzhuang shu", "shu", "book", "xianzhuang"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ����������װ�顣������д�С�����ŷ���桱�����֡�\n");
                set("value", 1);
                set("material", "paper");
                set("no_drop", "�������������뿪�㡣\n");
                set("no_get", "�������������뿪�Ƕ���\n");
        }
}

int do_du(string arg)
{
        object me = this_player();

        int level; 

       	if (me->is_busy()) {
                write("��������æ���ء�\n");
                return 1;  }
        if( me->is_fighting() ) {
                write("���޷���ս����ר���������飡\n");
                return 1;  }
        if( !me->query_skill("literate", 1) ){
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;  }
       if (arg=="xianzhuang shu" || arg=="shu"){
          write("������Ҫ������ҩ(zhiyao)������(liangong)��ͼ��(tujie) �� ����(gongfu)��\n");
          me->set_temp("baituo_book", 1);           
                return 1;
        }
         
       if (arg=="zhiyao" && me->query_temp("baituo_book")){
          tell_object(me, "\n
��ҩ��
  �������ҩ��֮���ҵ�������ҩ���߼���ҩ��
  ��Ҫ�Ƴɾ���֮ҩ���ǵ�����ԭ�ϡ�

  �׺쵤���Զ������ɿ��Ұ��ӹ���֮�涾��������ˣ�Ҳ������������Ԫ��
          ԭ�ϣ����ʺ׶���һ�������ߵ�������ϳ������ꡣ
          �Ʒ�������������������
\n
    ����ɽׯׯ�� ŷ������\n\n" NOR);  
                return 1;
        }
       if (arg=="tujie" && me->query_temp("baituo_book")){ 
           tell_object(me, "\n
����ƿ���Ժ���ţ���Ժ���ҵ������졢������ʯ�顣��֮˳��
����(push)֮��������һԺ�ڵȴ�һ�̱��������ص����ص���
ֱ��ɽ����ʯ�ѡ��ص���֮�����ɺ����������������ǹز�
��ȡ���춥���мǣ�     
\n
    ����ɽׯׯ�� ŷ������\n\n" NOR); 
                 return 1;
        }   
       if (arg=="liangong" && me->query_temp("baituo_book")){ 
           tell_object(me, "\n
��������ɵ��ղ�׽�������ʱ�ɴ���������ϰ�á����ҽ���
����ܷ���ں�Ժ��ʯ���ÿ�ս�ȥ����֮ʱһ��Ҫ��ʯ����
��һ���󡹦(yungong hamagong)�Ը�֪������ܡ���ðȻ���뽫��
����֮�ǣ��мǣ�
\n
    ����ɽׯׯ�� ŷ������\n\n" NOR);      
                  return 1;
        }    

       if (arg=="gongfu" && me->query_temp("baituo_book")){ 
           tell_object(me, "\n
���ӹ�����������֣��ڹ����Ǹ�󡹦�����ÿ��ȥ��Ժ��ʯ��
��ϰ(strike stone)���⹦�����Ҽ����꾭��۲�������������
�б仯�����ġ��������ȡ������ȹ���Ҫ�������顢�ݡ������֡�
��ɴӴ�����ѧ��(read book)��

\n
    ����ɽׯׯ�� ŷ������\n\n" NOR);          
        me->set_temp("baituo_book", 2);         
                  return 1;
        }   
  	if (arg=="xianzhuang" || arg=="book" && 
      		me->query_temp("baituo_book") == 2){
          
        	if( (int)me->query("jing") < 25 ) {
                	write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                	return 1;
        	}        

        if( (int)me->query("neili") < 50) {
               write("�������������޷��������С�\n");
                return 1;
        }

        level = me->query_skill("lingshe-zhangfa", 1);
        if( (int)me->query("combat_exp") < (int)level*level*level/10 ) {
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }        
       
        if( me->query_skill("lingshe-zhangfa", 1) > 50){
                write("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
                return 1;
        }

	if( !me->query_skill("hamagong", 1) || !me->query("oyf_son")){
                write("���ж���һ��������Ƿ���������д�Ķ�����֣�û��ѧ���κζ�����\n");
                return 1;
        }
        
       	//me->receive_damage("jing", 25);
       	//me->receive_damage("neili", 3);
        
        //me->improve_skill("lingshe-zhangfa", (int)me->query_skill("literate", 1)/3+1);
        write("ֻ��ŷ�����ҵ��˲ſ��Զ��������ȼ�����\n");
        return 1;
  }
}