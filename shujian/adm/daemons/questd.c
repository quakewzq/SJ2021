//Create by lsxk@hsbbs 2007/8/20
//方便Quest调用判断,留个后门。grin
//Update by lsxk 增加天赋影响效果：  2008/4/16
/*
使用方法介绍：
1、主程序调用。符合条件则返回1，否则返回0.
QUEST_D->questing(人物,难度系数,vip难度调整系数,计算源)
计算源：让程序用哪个数值去进行计算。有4种选择：
"KAR"-----只选择当前人物的福缘去计算。
"PUR"-----只选择当前人物的淳扑去计算。
"BOTH"----选择当前任务的福缘与淳朴的和去计算。
  1  -----选择直接用参数中的“难度系数”去计算。
如果选择"KAR","PUR","BOTH",计算公式为：
random(计算源)>难度系数?:1:0
特殊玩家，则:random(计算源)>(难度系数-vip难度调整系数)?:1:0
如果计算源传递的是数值1，则计算公式为：
特殊玩家，则!random(难度系数-vip难度调整系数)?:1:0
2、特殊玩家设定:
总共两种特殊玩家：
deny_quest_player----只要在这个组里的id,返回的值就是0,不进行任
何判断。
vip_quest_player-----在这个组里的人，才会用“vip难度调整系数”
去做难度调节。
两种方式设定：
A:在/adm/daemons/questd.c里，的vip_quest_player数组里加上player
的id, 或者deny_quest_player数组里加上id. update更新即可永久生效.
B:用函数调用添加：
QUEST_D->add_quest_player(人物，"DENY")--将人物临时添加到deny组里
QUEST_D->add_quest_player(人物，"VIP")---将人物临时添加到vip组里
QUEST_D->delete_quest_player(人物，"DENY")--将人物临时从deny组里删除
QUEST_D->delete_quest_player(人物，"VIP")--将人物临时从vip组里删除
*/

private int calc_quest(object, int, int, int);

//拒绝解quest玩家列表，惩罚恶意捣乱的人。grin
string *deny_quest_player = ({ });

//string *deny_quest_player = ({"zmud",});

//以下列表中的player将提高一定解quest成功率，几率由传递的参数决定。
string *vip_quest_player = ({"zmud", });

//添加该player到相应的数组中。由arg控制到deny还是vip.
void add_quest_player(object ob, string arg)
{
    int i;
    if(arg=="DENY"){
        for(i=0;i<sizeof(deny_quest_player);i++)
            if(ob->query("id")==deny_quest_player[i])
                return;

        deny_quest_player += ({ob->query("id")});
    }
    else{
        for(i=0;i<sizeof(vip_quest_player);i++)
            if(ob->query("id")==vip_quest_player[i])
                return;

        vip_quest_player += ({ob->query("id")});
    }
    return;
}

//从数组中删除该player。由arg控制到deny还是vip.
void delete_quest_player(object ob, string arg)
{
    if(arg=="DENY"){
        deny_quest_player -= ({ob->query("id")});
    }
    else{
        vip_quest_player -= ({ob->query("id")});
    }
    return;
}

//外部调用接口
int questing(object me, int level, int rlvl, string arg)
{
    int i, mboth;

        for(i=0;i<sizeof(deny_quest_player);i++)
            if(me->query("id")==deny_quest_player[i])
                return 0;

  /*其中level是难度调节,rlvl是针对vip的难度微调,level为0则返回假值,为
    1则返回真值,其他数字则返回“1/数字”的概率为真值,若非数字,则返回假.*/
    if(level<=0) return 0;
    if(level==1) return 1;
//    if(typeof(level)!=2) return 0;
    if(!objectp(me)) return 0;

       //tag为用哪种参数进行计算的标志。
        if(arg=="KAR")
            return calc_quest(me,me->query("kar"),level,rlvl);
        else if (arg=="PUR")
            return calc_quest(me,me->query("pur"),level,rlvl);
        else if (arg=="BOTH"){
            mboth = (int)me->query("kar")+(int)me->query("pur");
            return calc_quest(me,mboth,level,rlvl);
        }
        else
            return calc_quest(me,0,level,rlvl);

    return 0;
}

private int calc_quest(object me, int i, int level, int rlvl)
{
    int j;

  //如果i是0，则只对level进行判断。
    if(!i){
        //天赋“探险奇人”影响效果：  by lsxk@hsbbs 2008/3/16
        if(me->query("relife/quest/txqr"))
            level -= level * (int)me->query("relife/quest/txqr",1) / 100;
        
        if(level <= rlvl)  level = rlvl + 1;

        for(j=0;j<sizeof(vip_quest_player);j++)
            if(me->query("id")==vip_quest_player[j])
            {
                //天赋“探险专家”影响效果：  by lsxk@hsbbs 2008/3/16
                if(me->query("relife/quest/txzj") && (random(100) < (int)me->query("relife/quest/txzj",1) * 2)){
                    if(!(!random(level-rlvl)?1:0))
                        return !random(level-rlvl)?1:0;
                    else return 1;
                    }
                return !random(level-rlvl)?1:0;
            }
        //天赋“探险专家”影响效果：  by lsxk@hsbbs 2008/3/16
        if(me->query("relife/quest/txzj") && (random(100) < (int)me->query("relife/quest/txzj",1) * 2)){
            if(!(!random(level)?1:0))
                return !random(level)?1:0;
            else return 1;
            }
        return !random(level)?1:0;
    }
  //如果i不为0,则判断random(i)>level，才返回1
    else{
        //天赋“探险奇人”影响效果：  by lsxk@hsbbs 2008/3/16
        if(me->query("relife/quest/txqr"))
            level -= i * (int)me->query("relife/quest/txqr",1) / 100;

        if(level <= rlvl)  level = rlvl + 1;

        for(j=0;j<sizeof(vip_quest_player);j++)
            if(me->query("id")==vip_quest_player[j])
            {
                //天赋“探险专家”影响效果：  by lsxk@hsbbs 2008/3/16
                if(me->query("relife/quest/txzj") && (random(100) < (int)me->query("relife/quest/txzj",1) * 2)){
                if(!((random(i)>(level-rlvl))?1:0))
                    return (random(i)>(level-rlvl))?1:0;
                else return 1;
                }
                return (random(i)>(level-rlvl))?1:0;
            }
            //天赋“探险专家”影响效果：  by lsxk@hsbbs 2008/3/16
            if(me->query("relife/quest/txzj") && (random(100) < (int)me->query("relife/quest/txzj",1) * 2)){
                if(!((random(i)>level)?1:0))
                    return (random(i)>level)?1:0;
                else return 1;
                }
        return (random(i)>level)?1:0;
    }
}
