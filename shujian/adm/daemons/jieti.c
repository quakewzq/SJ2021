//by spiderii@ty 参照NT重新编译转生系统，特别说明，此系统并不完善
#include <ansi.h>

string *jieti_msg = ({
        HIM "你盘膝坐在地上，平心净气，试着将内息在体内循环十二周天，发现\n" NOR
        HIM "完全畅通无阻，便运起无上心法\n\n" NOR            
        HIR "            天     魔       解      体     大     法\n\n" NOR,
        
        HIW "顿时只听得一阵阵巨雷滚滚而起，天空乌云密布，道道紫色闪电划破\n" NOR 
        HIW "长空！你丝毫不感分心，按照天魔解体大法所述将自身内力分成两部\n" NOR 
        HIW "分，分别归入丹田与百汇中，只感觉丹田和百汇好像绝了堤的水坝一\n" NOR 
        HIW "般，内力如滚滚洪水似的向前冲去，而内力所经过的经脉瞬间被摧毁。\n" NOR,
        HIC "经脉瞬间被毁的巨痛险些使你昏过去，身体传来撕心裂肺的痛苦，更\n" NOR 
        HIC "是让你的脸完全扭曲了。半秒锺的时间都不到，但在你感觉好像经过\n" NOR 
        HIC "半个世纪那麽长一般。\n" NOR ,
        HIM "两穴里冲出来的内力遍会集到龙回穴所处的地方，两股内力互相融合，\n" NOR 
        HIM "慢慢形成太极形状，各分阴阳的流淌著，当所有内力集中在太极上後，\n" NOR 
        HIM "整个太极图案突然一跳，而你的神经也跟著猛地跳动一下，你知道这\n" NOR 
        HIM "是龙回穴成功产生出来後的效果。\n" NOR,
        HIY "就在这时，四周的灵气仿佛被什么牵引着疯狂的开始向你体内涌入，\n" NOR 
        HIY "以惊人的速度飞快的从龙回穴往回开始修复损坏的经脉，瞬间在精神\n" NOR 
        HIY "恍惚间你仿佛感觉回到了母亲的怀里般，终忍不住袭来的倦意，缓缓\n" NOR 
        HIY "的睡过了去。。。。\n" NOR,
        HIG "清晨醒来，乌云四散，清空万里，唯有大地一片寂静。。。。。\n" NOR,
        HIR "你发现体内的情况让你震惊，虽然内力已经减了近三成，但是却是生\n" NOR
        HIR "生不息，取之不尽，用之不完，经脉也被拓宽了几倍。而在眉心已留\n" NOR 
        HIR "下一小道红色胎记，仔细观察的话，会发现这块胎记如同一把倒立的\n" NOR 
        HIR "宝剑一般，散发著阵阵煞灵之气，你摸了摸身子，发现身体外层好像\n" NOR 
        HIR "脱皮一般，稀里哗啦的掉下不少老化的皮肤，而那些脱落旧皮後的新\n" NOR 
        HIR "肌肤比以前更加的白嫩。\n\n" NOR,
});

string get_jieti_place()
{
        string file;
        
        file = domain_file(base_name(this_object()));
        
        return file;
}

int do_jieti();
int do_decide(object); 
void jieti_player(object me);

int do_jieti()
{
        object me;
        string msg;
        
        me = this_player();

        if (me->query("combat_exp") < 20000000)
                return notify_fail("你的经验还不够，贸然天魔解体，会走火入魔的。\n");
/*
        if((int)me->query("combat_exp",1) - (int)me->query("relife/failed_exp",1) < 500000)
                return notify_fail("你还需要再多积累点实战经验方能有转世重修机会！\n");

        if(time() - (int)me->query("relife/failed_time",1) < 86400)
                return notify_fail("你刚尝试过转世重修，还是先休息会吧！\n");

        if (random((int)me->query("kar")+((int)me->query("combat_exp")/1000000)) < 20){
                me->add("relife/failed",1);
                me->set("relife/failed_time",time());
                me->set("relife/failed_exp",(int)me->query("combat_exp"));
                log_file("quest/zhuanshi_fail", sprintf(HIR"%s(%s) 在泰山之颠转世重修失败。此生总计失败%d次!\n"NOR, me->name(1),me->query("id"), me->query("relife/failed")) );
                return notify_fail("你想了想，觉得自己似乎尚未准备好，还是下次再说吧。。。。\n");
        }
*/
        msg = HIY "天魔解体是一种耗费大量的经验、武技来体悟中华武学精髓的方式，通过天魔\n" +
                  "解体，可以大大的提升你的体质，无论是先天资质、精力上限、内力上限、还\n" +
                  "是你的自身潜力都会得到很大的提高，你战斗中的杀伤力也会大大的加强，你\n" +
                  "是否确定(decide)自己将进行天魔解体？\n" NOR;

        me->set_temp("attempt_jieti",1);
        tell_object(me, msg);
        add_action("do_decide","decide");
        return 1;
}

int do_decide(string arg)
{
        object me = this_player();
        
        if (!me->query_temp("attempt_jieti"))
                return notify_fail("你想决定什么？\n");
       if (arg != "jieti")
               return notify_fail("你想做什么？？\n");
        tell_object(me, HIW "你闭目沉思，良久，终于下定决心，进行天魔解体！！\n\n" NOR);
        me->delete_temp("attempt_jieti");
        call_out("jieti_msg", 0, me, 0);
        return 1;
}

void jieti_player(object me)
{
        string *skl;
        mapping skill;
        int i, j;
                
        if (me->query("gender") == "无性")
                me->set("gender", "男性");   
                             
        me->delete("relife/failed");
        me->delete("relife/failed_time");
        me->delete("relife/failed_exp");

        me->set("shen", 0);
        me->set("mud_age", 0);
        me->set("age", 16); 
        me->set("relife/time", time());
        me->add("relife/times", 1);
        me->set("balance",5000000);
        me->set("SJ_Credit",500);       
        me->set("relife/combat_exp",(int)me->query("combat_exp",1));
        me->set("combat_exp", 1000000);
        me->set("potential", 10000);
        me->set("max_neili", 5000);
        me->set("max_qi", 2500);
        me->set("max_jing", 1500);
        me->set("max_jingli", 3000);
        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("eff_qi"));
        me->set("eff_jing", me->query("max_jing"));
        me->set("jing", me->query("eff_jing"));
        me->set("eff_jingli", me->query("max_jingli"));
        
        me->delete("MKS");                   //杀NPC记录
        me->delete("PKS");                    //杀PLAYER记录
        me->delete("FKS");                    //正当防卫记录
        me->delete("SJ_YuanBao");          //试剑元宝
        me->delete("last_death");            //上次遇害记录      
        me->delete("family");                // 门派记录
        me->set("title", "普通百姓");        // 个人称号
        me->delete("user_weapon_imbued");    //打造次数
        me->delete("no_pk");                 //洗手标记
        me->delete("betrayer");              //叛师记录
        me->delete("rules");                 //犯规记录
        me->delete("death_count");           //死亡次数记录
        me->delete("death_times");           //死亡有效记录
        me->delete("nickname");              //外号记录
        me->delete("quest");                 //quest记录
        me->delete("double_attack");         //左右互搏
        me->delete("job_time");              //任务次数
        me->delete("luohan_winner",1);          //罗汉阵记录
        me->delete("forging");                //工匠技能记录
        me->delete("worker");                 //自造物品记录
        me->delete("xlz");                 //降龙掌亢龙有悔
        me->delete("spec");                  //删除通宝物品使用记录
        me->delete("class");                  //出家标记删除
        me->delete("divorce");                //删除离婚次数
        me->delete("marry");                  //删除离婚对象
        me->delete("jiuyang");
        me->delete("job_last_gift");
//by spiderii@ty 为sl特别增加
        me->delete("pass_xin");
        me->delete("passdu");

        me->delete("job_name");
        me->set("job_time/送信",100);         //以免score不通过出bug
       //by spdierii@ty 先天隐藏属性也全部打乱
        me->set("pur", 15 + random(15));
        me->set("per", 15 + random(15));
	 me->set("kar", 15 + random(15));

        skill = me->query_skills();
        skl = keys(skill);
        i = sizeof(skl);
           while (i--) 
              {
                   me->delete_skill(skl[i]);              
                 }
        
        if (me->is_ghost()) me->reincarnate();
        me->reset_action(); 
        
     //by spiderii@ty 我希望的是随机给予天赋技能点数，不希望人人都一样。
     //Update by lsxk@hsbbs 修改为：20M获得4-6点天赋，30M获得7-10点天赋，40M获得12-15点天赋，50M获得17-20点天赋
     //Update by lsxk@hsbbs 感觉天赋点有点少，适当多给点。   2008/3/18
      if((int)me->query("relife/combat_exp",1)> 50000000){
          me->set("relife/exp_ext",20);
          j = 30;
      }
      else if((int)me->query("relife/combat_exp",1)> 40000000){
          me->set("relife/exp_ext",15);
          j = 20 + random(6);
      }
      else if((int)me->query("relife/combat_exp",1)> 30000000){
          me->set("relife/exp_ext",10);
          j = 12 + random(6);
      }
      else{
          me->set("relife/exp_ext",5);
          j = 6 + random(5);
      }
      me->add("relife/gift/now",j);
      me->add("relife/gift/total",j);
      tell_object(me, CYN"你在转世重修的同时，获得"+ HIR + chinese_number(j) + CYN +"点「"+HIG+"天赋技能"+CYN+"」！\n"NOR);

}

void jieti_msg(object me, int stage, string place)
{
        string msg;

        if (stage == 5) me->revive();

        msg = HIR + jieti_msg[stage] + NOR;
        tell_object(me, HIY + msg + NOR);
        if (stage < sizeof(jieti_msg) - 1)
        {
                if (stage == 4) me->unconcious();

                stage++;
                call_out("jieti_msg", 1, me, stage, place);
        } else
        {
                jieti_player(me);
                CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) +
                                     "在泰山之颠成功天魔解体,转世重修了！\n"NOR);
                me->set("relife/zhuanshi",1);//要skills的标记
                log_file("quest/zhuanshi", sprintf(HIG"%s(%s) 在东岳泰山之颠成功转世重修。获得天赋技能点数：%d。\n"NOR, me->name(1),me->query("id"), me->query("relife/gift/now")) );

        }      
        return;
}
