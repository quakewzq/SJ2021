// Balanced.c

#include <localtime.h>

inherit F_SAVE;

// Functions:
private void t_check();
private void Get_tmpdUser();
private void Get_dUser();

// Var:
mapping dUser;
/*
([
  "gumu":([
  		"max": 最高在线人数
  		"min": 最低在线人数
  		"now": 目前在线人数
  		"normal": 平均在线人数
  	])
])
*/
nosave mapping dUser_temp;
/*
记录每一个时段在线人数
([
 "gumu":({10,20,.....}) /每小时记录一次
])
*/
mapping dPerform;
/*
([
 "anran-zhang":
 	([
 	   "anran":10,
 	   ..
 	])
 ...
])
*/
mapping dExert;//类似dPerform
mapping dSkilltoParty;
/*
将skill与party建立对应关系
([
  "gumu":({anran-zhang})  
  ...
])
*/

string query_save_file()
{
	return DATA_DIR+"balance";
}

void create()
{
	restore();
	
	//INIT
	if(!dUser) dUser = ([]);
	if(!dUser_temp) dUser_temp = ([]);
	if(!dPerform) dPerform = ([]);
	if(!dExert) dExert = ([]);
	if(!dSkilltoParty) dSkilltoParty = ([]);
		
	t_check();
}

void remove()
{
	save();
}

void t_check()
{
	mixed * tm;
		
	remove_call_out("t_check");
	call_out("t_check",1);

	tm = localtime(time());
		
	if(tm[LT_SEC]) return;
	//每一分钟执行一次 记录在线人数
	Get_dUser();
	
	if(tm[LT_MIN]) return;
	
	Get_tmpdUser();
	save();	
}

private string checkparty(object obj)
{
	if(!obj) return 0;
		
	return obj->query("family/family_name");				
	//return ob1->query("family/family_name")==ob2->query("family/family_name");
}

private void Get_tmpdUser()
{
	mixed ret;
	int i,j;
	string party;
	object* us = filter_array(children(USER_OB),(:clonep:));
			
	ret = unique_array(us,(:checkparty:));
	
	i = sizeof(ret);
	while(i--)
	{
		us = (object*)ret[i];
		if(!us || !sizeof(us)) continue;
								
		j = sizeof(us);
		party = us[0]->query("family/family_name");
		if(!party) continue;
		//dUser_temp
		if(undefinedp(dUser_temp[party]))
		{
			dUser_temp[party] = ({});			
		}
		dUser_temp[party] += ({j});		
	}
}

private void Get_dUser()
{
	mixed ret;
	object* us = filter_array(children(USER_OB),(:clonep:));
	int i,j;
	string party;
				
	ret = unique_array(us,(:checkparty:));
	
	i = sizeof(ret);
	while(i--)
	{
		us = (object*)ret[i];
		if(!us || !sizeof(us)) continue;
		
		j = sizeof(us);				
		party = us[0]->query("family/family_name");
		if(!party) continue;
		//dUser
		if(undefinedp(dUser[party]))
		{
			dUser[party]=allocate_mapping(4);
			dUser[party]["max"]=j;
			dUser[party]["min"]=j;
			dUser[party]["now"]=j;
			dUser[party]["normal"]=j;
		}
		if(j>dUser[party]["max"]) dUser[party]["max"]=j;
		if(j<dUser[party]["min"]) dUser[party]["min"]=j;
		
		dUser[party]["now"]=j;
		
		if(!undefinedp(dUser_temp[party]))
		{
			int* manlist = dUser_temp[party];
			int var = 0;
			if(!manlist) continue;			
			j=sizeof(manlist);
			if(!j) continue;
			while(j--) var += manlist[j];
			dUser[party]["normal"]=(int)(var/sizeof(manlist));
		}
	}
}

private int get_all_duse(string type)
{
	string* partys = keys(dUser);
	int ret,i;
	
	if(undefinedp(dUser[partys[0]][type])) return 0;
			
	ret = 0;
	i = sizeof(partys);
	while(i--)
	{
		ret += dUser[partys[i]][type];		
	}
	
	return ret;
}

///Open

public void t(string x)
{
	call_out(x,1);
}

public void add_perform(string skill,string name,int use)
{
	//dPerform
	if(undefinedp(dPerform[skill]))
	{
		dPerform[skill] = ([]);
	}
	
	if(undefinedp(dPerform[skill][name]))
	{
		dPerform[skill][name] = 0;
	}
	
	dPerform[skill][name] += use;
}

public void add_exert(string skill,string name,int use)
{
	//dExert
	if(undefinedp(dExert[skill]))
	{
		dExert[skill] = ([]);
	}
	
	if(undefinedp(dExert[skill][name]))
	{
		dExert[skill][name] = 0;
	}
		
	dExert[skill][name] += use;
}

public void set_party(string skill,string party)
{
	//party forbit...
	//dSkilltoParty[skill] = party;
	if(undefinedp(dSkilltoParty[party])) dSkilltoParty[party] = ({});
	
	dSkilltoParty[party] += ({skill});	
}

public void remove_party(string skill,string party)
{
	if(undefinedp(dSkilltoParty[party])) return;
	
	dSkilltoParty[party] -= ({skill});
}

//////////////For Use///////////////////////////

public int query_power(string party)
{
	if(undefinedp(dUser[party])) return 0;

	return dUser[party]["normal"]*10000/get_all_duse("normal");
}

public string query_skill(string skill)
{
	string* use;
	string ret = "";
	int j;

	ret += capitalize(skill)+"：\n";
		
	//Exert
	if(!undefinedp(dExert[skill]))
	{
		ret += "内功使用情况：\n";
		use = keys(dExert[skill]);
		if(use && j = sizeof(use))
		{
			while(j--)
			{
				ret += "    "+capitalize(use[j])+"："+sprintf("%d；\n",dExert[skill][use[j]]);
			}
		}
	}
	
	//Perform
	if(!undefinedp(dPerform[skill]))
	{
		ret += "外功使用情况：\n";
		use = keys(dPerform[skill]);
		if(use && j = sizeof(use))
		{
			while(j--)
			{
				ret += "    "+capitalize(use[j])+"："+sprintf("%d；\n",dPerform[skill][use[j]]);
			}
		}
	}
	return ret;
}

public string query_party(string party)
{
	//object me = this_player();
	string* skills;	
	int i;
	string ret;
				
	if(undefinedp(dSkilltoParty[party])) return 0;
	skills = dSkilltoParty[party];
	
	ret = "关于"+party+"系统提供的有关咨询是：\n";
	if(query_power(party)) ret += sprintf("门派实力为：%d。\n",query_power(party));
	
	if(!skills)
	{		
		return ret;
	}
	i = sizeof(skills);
	if(!i)
	{		
		return ret;
	}
	
	ret += "该门派各项Skills的使用情况如下：\n";
	while(i--)
	{
		ret += query_skill(skills[i]);
	}
	//write(ret);	
	return ret;	
}
