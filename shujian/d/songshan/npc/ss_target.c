//edit by rock
//2008.10.20

#include <ansi.h>
inherit NPC;
int do_copy(object ob);
string ask_leave();
string *title1 = ({"清风女剑客","青蚨神","青海之灵 食鹿神君","青天剑客","轻烟上九霄","擒龙手","秋风扫落叶","拳剑无双","人绝剑","仁义剑客","柔情手","三环套月压天下 满天花雨震乾坤 摘星射月无敌神","三手追魂","三湘大侠""雷电剑","七手神剑","七星夺魂","骑鲸客","铜拳铁掌震中州","气吞斗牛","千钧担","千里飞云，万里捉月，神行无影","冷月仙子","离弦箭","立地分金","辽东大侠","凌风公子","玲珑七窍","龙卷风神","龙女","龙神太子","陆上陶朱","梅香神剑","美玉剑客","明察秋毫","摩云剑","摩云神手","摩云手","漠外神君","南海一君","南天大侠","南阳大侠","女霸王","女孟尝","霹雳火","霹雳剑","平生无败","七妙神君","七巧书生","七巧童子","见色不乱真君子","见义勇为","江南大侠","江南第一剑","金罗汉","九天玄女","九天仙子","九州王","砍虎刀","白玉魔丐","百灵丐","东海渔夫","东岳书生","夺命更夫","夺命郎中","飞大夫","飞斧神丐","毒手书生","疯丐","杆儿赵","怪手神医","鬼捕","鬼判","黑白盗","华山医隐","火灵官","冀东人屠","酒丐","九天鬼帝","九玄神丐","救命郎中","浪里神儒","妙郎中","妙僧","妙手郎中","妙手神偷，无孔不入","妙手神医","女屠户","拼命书生","七毒书生","七海渔子","七巧书生","千手神医","人命猎户","杀手书生","杀手无常","杀手无情","生死判","圣手书生","闪电大盗","神捕","神剑使者","神剑宰相","神偷","神医武匠","神医侠隐","食竹女史","天医","铁火判官","铁军使者","偷上偷","屠手渔夫","五柳书生","小李探花","凶僧","要命神丐","要命书生","阴司秀才","玉璧使者","玉面判","白骨学究","玉面神判","诸稽神医","白水仙","芙蓉剑客","海棠仙子","黑水仙","红叶公子","葫芦","花雨","江上飞花","满地飞花","梅花公子","千里踏花","青莲公子","青松剑客","塞上奇花","天上飞花","万里踏花","一朵莲花","一枝花","一枝梅","紫兰花","八臂哪吒","八臂天王","八步赶蝉","八卦刀","八卦神掌","八卦掌","八手镖","八手神刀客","八仙剑","白衣神耳","百步飞花","百胜刀王","饱宝雪剑","宝马神鞭","宝马神枪","宝马银枪","笔上生花","鞭神","不败之剑","长虹剑","穿肠刀","穿肠剑","锤王","打虎拳","大刀子","大斧头","大海缸","大老板","大刀斧王","大力金刚","大力金刚神","大力神","大力神鹰","单剑追魂","单掌开碑","单掌追魂","点苍神剑","毒后","毒剑","毒君","毒郎君","毒手姜维","毒手搜魂","赌王","断肠针","断魂镖","断魂刀","断魂剑","多臂神剑","飞叉太保","飞刀将","飞花满天，落地无声","飞虹剑","飞环","飞骑快剑","飞剑客","飞狼刀","飞鹰神剑","分光捉影，一手七杀","风郎君","风雨双流星","斧不留痕","富贵神剑","勾魂","勾魂手","钩镰枪","怪刀神翁","关外神龙剑","鬼斧大帅","鬼流星","黑煞剑","弧形剑","护花刀","花刀","潢州卧虎刀","混元指","火雷珠","火神","火神爷","急风剑","戟霸","剑雄","剑掌出手双绝","惊魂双剑追风客","金鞭","金鞭银刀","金刀","金刀无敌","金刀无敌镇三江","金刚手","金刚掌","金弓神弹","金弓银弹铁鹰爪","金弓银丸斩虎刀，追云捉月水上飘","金剑","金翎十字枪","金枪","金枪太保","金枪银梭","金丸铁掌","金针","金针渡危","九宫剑","九宫连环剑","九花枪","九连环","九龙鞭","巨灵斧","巨灵之掌，力举千斤","开碑手","铁戟温侯","铁叫子","铁剑镇三山","铁面判官","铁琵琶手","铁枪","铁枪小霸王","铁拳","铁拳无敌","铁算盘","铁头","铁丸枪","铁掌","铁掌翻天","铁掌金镖","铁掌金刀","铁掌金剑独行客","铁掌开碑","铁掌震河朔","铁指金丸","偷脑袋大侠","弯刀","万宝箱，乾坤伞，阎王没法管","万花剑","万花拳","万剑之尊","万里神行","万胜刀","万胜金刀","万事通","温侯铁戟","温一刀","瘟煞魔君","吴钩剑","五虎断门刀","五虎神刀","五花箭神","无敌刀","无孔不入","五音能手","无影枪","无声霹雳","无影神刀","五毒娘子","潇湘神剑","小刀","小花枪","小五通","晓风五更寒心掌","仙人剑","信阳蟠龙钩","旋风刀","旋风追魂四剑","雪刀雪地飘风","雪花刀","血剑","血手黑煞","阎罗伞","一刀镇九州","一股烟","一剑霸南天","一剑乘风","一剑穿心","一剑飞花","一剑飞雪","一剑镇八荒","一剑震河朔","一剑震九城","一枪刺九龙","一枪擎天","一掌翻天","一指判生死","一指通天","一指追魂","阴风神镖","阴魂剑","阴阳斧","鹰爪王","银鞭","银钩","银花镖","银枪","银枪公子","银扇子","银箫夺魂","云龙九现","鸳鸯金环","摘星手","掌剑飞","掌中天魔","震山掌","震天铁掌","子母金梭","子母离魂手","子母双飞","子母铁胆","子午催魂","朱砂掌","追风刀","追风剑","追风铁笔震江湖","追魂夺命三环剑客","追魂铃","追魂枪","左右双刀","哀魔","爱才如命","爱魔","安乐公子","白布腰带","白马公子","白马将军","白面郎君","白煞","白蛇郎君","白秀才","白衣剑客","白衣龙女","白云仙子","半面罗刹 半人半鬼","宝马金刀","碧月剑客","遍地洒金钱","冰血魔女","病丐","剥皮 不吃人头","不男不女","布袋帮主","叉子","常败高手","常剥皮","彩翼满花间","吃心怪魔","出尘剑客","催命符","翠燕剑客","大欢喜女菩萨","大头鬼王","大眼","得意妃子","地裂","地魔","地煞","独臂神龙","独臂鹰王","独脚飞魔","独手天王","独眼丐","毒君","毒郎君","毒木郎","毒心神魔","多事和尚","多事头陀","多手真人","夺命使者","恶赌鬼","恶鬼","恶魔","飞马盗后","飞驼","风流潘安","粉侯","粉郎君","粉面苏秦","福星高照","黑心妙郎君","黑珍珠","花疯子","富贵公子","赶尽杀绝","勾漏一怪","瞽目神剑","怪脸","管杀管埋","鬼郎君","鬼王","鬼衣侯","鬼影儿","鬼影子","过不去","棍子","黑煞","黑灵官","黑驴追风","黑煞魔掌","黑铁手","黑心不悔","黑秀才","黑衣摩勒","恨地无环","红鼻子","红发天魔","红粉骷髅","鬼面娇娃","红孩儿","红袍公","红衫金刀","红颜魔女","红衣娘娘","红衣仙子","红鹰剑客","绝望夫人","快活纯阳","快活王","辣椒仙子","辣手大侠","辣手童心","辣手西施","辣手仙子","辣手追魂","蓝髯客","蓝凤剑客","老实先生","冷罗刹","冷面罗刹","冷血妃子","立地开山铁霸王","猎刀小子","烈火夫人","凌波仙子，散花天女","凌风使者","灵尸","柳大脚","六亲不认","罗刹仙女","罗刹仙子","落露仙子","绿袍灵剑客","麻大夫","满天星","冒险君子，常笑天君","没事忙","没用的阿吉","迷死人不赔命","灭心神魔 冥海招魂","魔玉爷","墨龙剑客","木郎君","南海仙子","南极毒叟","泥菩萨","宁死不吃亏","怒魔","怒目天神","排骨仙","胖灵官","霹雳火","拼命","拼命七郎","拼命占便宜","破碗","七手大圣","七手神剑","七指神偷","七指神翁","七指仙","千臂如来，鬼影子摸不着，快手大醉侠","千变万化智多星","千红剑客","千里独行","千面公子","千蛇剑客","千手观音","千手千眼","千手如来","千手神丐","钱守财","巧手兰心女诸葛","青胡子","青魔","青眼红魔","情魔","穷魂","虬面孟尝","缺目乞","人魔","如花剑客","如意老人","如意掌","杀手玉郎，粉面孟尝","三花剑客","三心神君","三无先生","三笑惊魂","三眼秀士","三只手","上天入地寻小李，一心一意杀叶开","丧门神","色魔","神眼书生","神眼鹰飞","石人","石神","实心木头人","视酒如命","司空婆婆","四目温侯、长醉小将军","素手","苏吃亏","损人不利己","太行神魔","弹筝客","天崩","天残","天废","天劫魔君","天狂居士","天魔","天巧星","天杀星","天外飞来半截山","天涯狂生","天涯飘萍客","天妖","铁镖头金刀手","铁胆剑客","铁汉","铁骑金刀","铁剑金人","铁剑先生","铁金刚","铁郎君","铁面孤行客","铁面黄衫客","铁面龙王","铁面温侯","铁面阎罗","铁面专诸","铁手无情","铁驼","铁仙姑","铜胆","托塔天王","为富不仁","万毒童子","万里独行","万相真人","乌衣神剑","无肠君","无常索命","无耳丐","无法无天","无垢道人","无孔不入","无面天魔","无目煞星","无鞘刀","无情刀","无情公子","无情小子","无缺公子","无所不偷","无为剑客","无音夺魂，辣手郎君","无影罗刹","五毒","尊者","喜魔","销魂夫人","销魂罗刹","销魂天魔","小老头","小雷神","小丧门","小山神","小丧门","笑里藏刀","笑脸小福神","笑弥陀","笑面人屠","笑面追魂","笑天叟","笑天翁","相思夫人","修罗玉女","玄玄女","雪刀浪子","雪里红","薛菩萨","血公爵","血手","血手罗刹","艳魂","殃神","妖王","要命的小方","一飞冲天","一见送终","一目了然","阴魂剑","阴魔","阴青手","银刀使者","银电仙子","银箭公子","幽冥才子","开天掌","空空神手","快马神刀","快马双鞭","快手分金","快手小呆","狂鞭","昆仑玉女","浪里神","离魂圈","立地追魂手","力劈华山","烈马金枪","菱花神剑","凌空步虚","六阳神掌","龙凤环","龙虎刀","戳天夺命双枪","落英剑","龙蛇剑","龙形八掌","戳情剑","落英剑","茅山毒指","梅花剑","没影子","没羽箭","闷雷刀","妙手神医","魔刀魔剑魔眼摄魂","南海神刀王","怒箭神弓斩鬼刀","盘龙银棍劈挂掌","泼雪双刀将","七步追魂","七巧追魂七煞手","千毒人魔","千里追风神行无影妙手","千面观音","千面人魔","千手剑客","千手弥陀","千手书生","乾坤笔","乾坤掌","潜鱼叟","巧匠赛鲁班","清风剑","青萍剑","日月双枪","如意刀","三箭定花山","三手剑","三手神抓","三手侠","三手仙妪","三星夺命，两步易形，一计绝户","三斩刀帝","玲珑玉手","闪电快剑","闪电霹雳刀","闪电神刀","闪电追风剑","摄魂刀","四弦弓","神镖继魂","神锤无敌","神刀霸王","神刀大侠","神剑无影","神力霸王","神力金刚","神力鹰王","神目如电","神拳打井","神拳小诸葛","神拳泰斗","神拳无敌","神拳无敌大镖客","神行无影铜拳铁掌","神眼神剑","视人如鸡","搜魂手","双鞭无敌","双掌翻天","踏雪无痕","太湖一剑","天罗地网","天南一剑","铁臂金刚","铁椎子铁打金刚铁胆神枪","铁胆镇八方","中州大侠","中州一剑","追风无影","追云使者","巴山剑客"});

string *t_color=({ HIR , HIG , HIY , HIB , HIM , HIC , HIW});
void create()
{
	string weapon = "null" , menpai ,title,c_title;
	mapping name;
	int i;

    i = random(4);
	
	c_title = t_color[random(6)];
	title =c_title + title1[random(sizeof(title1))];
	
	name = RNAME_D->get_random_name(i);

	set_name(name["name"], name["id"] );
		set("title", title+NOR);
	set("gender", "男性");
	set("age", 20 + random(40));
	set("long", "他就是江湖人称"+title+NOR+"的"+name["name"]+"。\n");
	set("combat_exp", 7000000);

	set("str", 20+random(5));
	set("int", 20+random(5));
	set("con", 20+random(5));
	set("dex", 20+random(5));
	set("max_qi", 20000);
	set("max_jing", 20000);
	set("max_neili", 7000);
	set("max_neili", 20000);
	set("neili", 7000);
	set("neili", 20000);
	set_temp("apply/armor", 100);
	set("eff_jing", 20000);
	set("eff_jingli", 20000);
	set("jingli", 20000);
	set("max_jingli", 20000);
	set("meitude","peaceful");
	set("no_ansuan",1);
	set("no_bark", 1);
	set("no_quest", 1);
	set("location", 1);

	set_skill("strike", 700);
	set_skill("cuff", 700);
	set_skill("hand", 700);
	set_skill("dodge", 700);
	set_skill("sword", 700);
	set_skill("force", 700);
	set_skill("parry", 700);
	set_skill("blade", 700);
	set_skill("hammer", 700);
	set_skill("stick", 700);
	set_skill("club", 700);
	set_skill("staff", 700);
	set_skill("literate", query("int") * 10);
	set_skill("whip", 700);
	set_skill("dagger", 700);
	set("location",1);
	set("inquiry", ([
		"较量" : (: ask_leave :),
		"fight" : (: ask_leave :),
	]));
	
	set("no_get", 1);
	switch( random(30) ) {
		case 0:  // wd1
		set_skill("yinyun-ziqi", 700);
		set_skill("tiyunzong", 700);
		set_skill("taiji-jian", 700);
		set_skill("taiji-quan", 700);
		map_skill("force", "yinyun-ziqi");
		map_skill("dodge", "tiyunzong");
		map_skill("sword", "taiji-jian");
		map_skill("parry", "taiji-quan");
		map_skill("cuff", "taiji-quan");
		prepare_skill("cuff", "taiji-quan");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "taiji" :),
			(: perform_action, "cuff.zhan" :),
			(: perform_action, "cuff.ji" :),
			(: perform_action, "cuff.zhen" :),
		}));
		menpai = "武当";
		break;
		case 1:  // wd2
		set_skill("yinyun-ziqi", 700);
		set_skill("tiyunzong", 700);
		set_skill("taiji-jian", 700);
		set_skill("taiji-quan", 700);
		map_skill("force", "yinyun-ziqi");
		map_skill("dodge", "tiyunzong");
		map_skill("sword", "taiji-jian");
		map_skill("parry", "taiji-jian");
		map_skill("cuff", "taiji-quan");
		prepare_skill("cuff", "taiji-quan");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: perform_action, "dodge.zong" :),
			(: perform_action, "sword.chan" :),
			(: perform_action, "sword.sanhuan" :),
		}));
		weapon = "sword";
		menpai = "武当";
		break;
		case 2:  // sl1
		set_skill("yijin-jing", 700);
		set_skill("shaolin-shenfa", 700);
		set_skill("riyue-bian", 700);
		set_skill("yizhi-chan", 700);
		map_skill("force", "yijin-jing");
		map_skill("dodge", "shaolin-shenfa");
		map_skill("whip", "riyue-bian");
		map_skill("parry", "riyue-bian");
		map_skill("finger", "yizhi-chan");
		prepare_skill("finger", "yizhi-chan");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "jingang" :),
			(: perform_action, "whip.chanrao" :),
			(: perform_action, "whip.fumoquan" :),
		}));
		weapon = "whip";
		menpai = "少林";
		break;
		case 3:  // sl2
		set_skill("yijin-jing", 700);
		set_skill("shaolin-shenfa", 700);
		set_skill("damo-jian", 700);
		set_skill("yizhi-chan", 700);
		map_skill("force", "yijin-jing");
		map_skill("dodge", "shaolin-shenfa");
		map_skill("sword", "damo-jian");
		map_skill("parry", "damo-jian");
		map_skill("finger", "yizhi-chan");
		prepare_skill("finger", "yizhi-chan");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "jingang" :),
			(: perform_action, "sword.sanjue" :),
		}));
		weapon = "sword";
		menpai = "少林";
		break;
		case 4:  // sl3
		set_skill("yijin-jing", 700);
		set_skill("shaolin-shenfa", 700);
		set_skill("yizhi-chan", 700);
		map_skill("force", "yijin-jing");
		map_skill("dodge", "shaolin-shenfa");
		map_skill("parry", "yizhi-chan");
		map_skill("finger", "yizhi-chan");
		prepare_skill("finger", "yizhi-chan");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "jingang" :),
			(: perform_action, "finger.wofo" :),
			(: perform_action, "finger.qiankun" :),
		}));
		menpai = "少林";
		break;
		case 5:  // hs1
		set_skill("zixia-gong", 700);
		set_skill("huashan-shenfa", 700);
		set_skill("huashan-jianfa", 700);
		set_skill("hunyuan-zhang", 700);
		map_skill("force", "zixia-gong");
		map_skill("dodge", "huashan-shenfa");
		map_skill("sword", "huashan-jianfa");
		map_skill("parry", "huashan-jianfa");
		map_skill("strike", "hunyuan-zhang");
		prepare_skill("strike", "hunyuan-zhang");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "zixia" :),
			(: perform_action, "sword.lianhuan" :),
			(: perform_action, "sword.feijian" :),
		}));
		weapon = "sword";
		menpai = "华山";
		break;
		case 6:  // hs2
		set_skill("zixia-gong", 700);
		set_skill("huashan-shenfa", 700);
		set_skill("fanliangyi-dao", 700);
		set_skill("poyu-quan", 700);
		map_skill("force", "zixia-gong");
		map_skill("dodge", "huashan-shenfa");
		map_skill("blade", "fanliangyi-dao");
		map_skill("parry", "fanliangyi-dao");
		map_skill("cuff", "poyu-quan");
		prepare_skill("cuff", "poyu-quan");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "zixia" :),
			(: perform_action, "blade.sanshenfeng" :),
		}));
		weapon = "blade";
		menpai = "华山";
		break;
		case 7:  // gb1
		set_skill("huntian-qigong", 700);
		set_skill("bangjue", 700);
		set_skill("xiaoyaoyou", 700);
		set_skill("dagou-bang", 700);
		set_skill("xianglong-zhang", 700);
		map_skill("force", "huntian-qigong");
		map_skill("dodge", "xiaoyaoyou");
		map_skill("stick", "dagou-bang");
		map_skill("parry", "dagou-bang");
		map_skill("strike", "xianglong-zhang");
		prepare_skill("strike", "xianglong-zhang");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "huntian" :),
			(: perform_action, "stick.chuo" :),
			(: perform_action, "stick.chan" :),
		}));
		weapon = "stick";
		menpai = "丐帮";
		break;
		case 8:  // gb2
		set_skill("huntian-qigong", 700);
		set_skill("bangjue", 700);
		set_skill("xiaoyaoyou", 700);
		set_skill("dagou-bang", 700);
		set_skill("xianglong-zhang", 700);
		map_skill("force", "huntian-qigong");
		map_skill("dodge", "xiaoyaoyou");
		map_skill("stick", "dagou-bang");
		map_skill("parry", "xianglong-zhang");
		map_skill("strike", "xianglong-zhang");
		prepare_skill("strike", "xianglong-zhang");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: perform_action, "strike.xiao" :),
			(: perform_action, "strike.paiyun" :),
		}));
		menpai = "丐帮";
		break;
		case 9:  // thd1
		set_skill("bihai-chaosheng", 700);
		set_skill("qimen-bagua", 700);
		set_skill("suibo-zhuliu", 700);
		set_skill("yuxiao-jian", 700);
		set_skill("tanzhi-shentong", 700);
		set_skill("lanhua-shou", 700);
		set_skill("luoying-zhang", 700);
		set_skill("xuanfeng-tui", 700);
		map_skill("force", "bihai-chaosheng");
		map_skill("dodge", "suibo-zhuliu");
		map_skill("sword", "yuxiao-jian");
		map_skill("parry", "yuxiao-jian");
		map_skill("finger", "tanzhi-shentong");
		prepare_skill("finger", "tanzhi-shentong");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "maze" :),
			(: perform_action, "sword.yuxiao" :),
			(: perform_action, "sword.feiying" :),
			(: perform_action, "sword.qimen" :),
		}));
		set("thd/perform",999);
		weapon = "xiao";
		menpai = "桃花岛";
		break;
		case 10: // thd2
		set_skill("bihai-chaosheng", 700);
		set_skill("qimen-bagua", 700);
		set_skill("suibo-zhuliu", 700);
		set_skill("yuxiao-jian", 700);
		set_skill("tanzhi-shentong", 700);
		map_skill("force", "bihai-chaosheng");
		map_skill("dodge", "suibo-zhuliu");
		map_skill("sword", "yuxiao-jian");
		map_skill("parry", "tanzhi-shentong");
		map_skill("finger", "tanzhi-shentong");
		prepare_skill("finger", "tanzhi-shentong");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "maze" :),
			(: perform_action, "finger.huayu" :),
			(: perform_action, "finger.shentong" :),
		}));
		set("thd/perform",999);
		menpai = "桃花岛";
		break;
		case 11: // mr1
		set_skill("shenyuan-gong", 700);
		set_skill("douzhuan-xingyi", 700);
		set_skill("yanling-shenfa", 700);
		set_skill("murong-jianfa", 700);
		set_skill("tanzhi-shentong", 700);
		map_skill("force", "shenyuan-gong");
		map_skill("dodge", "yanling-shenfa");
		map_skill("sword", "murong-jianfa");
		map_skill("parry", "douzhuan-xingyi");
		map_skill("finger", "canhe-zhi");
		prepare_skill("finger", "canhe-zhi");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "shenyuan" :),
			(: perform_action, "parry.xingyi" :),
		}));
		weapon = "sword";
		menpai = "姑苏慕容";
		break;
		case 12: // gumu1
		set_skill("yunu-xinjing", 700);
		set_skill("yunu-shenfa", 700);
		set_skill("xuantie-jianfa", 700);
		set_skill("anran-zhang", 700);
		map_skill("force", "yunu-xinjing");
		map_skill("dodge", "yunu-shenfa");
		map_skill("sword", "xuantie-jianfa");
		map_skill("parry", "xuantie-jianfa");
		map_skill("strike", "anran-zhang");
		prepare_skill("strike", "anran-zhang");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: perform_action, "sword.wujian" :),
			(: perform_action, "sword.haichao" :),
		}));
		weapon = "sword";
		menpai = "古墓";
		if (random(2)) set("env/玄铁剑法","海潮");
		else set("env/玄铁剑法","汹涌");
		break;
		case 13: // emei1
		set_skill("linji-zhuang", 700);
		set_skill("anying-fuxiang", 700);
		set_skill("huifeng-jian", 700);
		set_skill("sixiang-zhang", 700);
		map_skill("force", "linji-zhuang");
		map_skill("dodge", "anying-fuxiang");
		map_skill("sword", "huifeng-jian");
		map_skill("parry", "huifeng-jian");
		map_skill("strike", "sixiang-zhang");
		prepare_skill("strike", "sixiang-zhang");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "wuwo" :),
			(: perform_action, "sword.mie" :),
			(: perform_action, "sword.jue" :),
		}));
		weapon = "sword";
		menpai = "峨嵋";
		break;
		case 14: // emei2
		set_skill("linji-zhuang", 700);
		set_skill("anying-fuxiang", 700);
		set_skill("yanxing-daofa", 700);
		set_skill("sixiang-zhang", 700);
		map_skill("force", "linji-zhuang");
		map_skill("dodge", "anying-fuxiang");
		map_skill("blade", "yanxing-daofa");
		map_skill("parry", "yanxing-daofa");
		map_skill("strike", "sixiang-zhang");
		prepare_skill("strike", "sixiang-zhang");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "wuwo" :),
			(: perform_action, "blade.huanying" :),
		}));
		weapon = "blade";
		menpai = "峨嵋";
		break;
		case 15: // mj1
		set_skill("shenghuo-shengong", 700);
		set_skill("qiankun-danuoyi", 700);
		set_skill("piaoyi-shenfa", 700);
		set_skill("shenghuo-lingfa", 700);
		set_skill("hanbing-mianzhang", 700);
		map_skill("force", "shenghuo-shengong");
		map_skill("dodge", "piaoyi-shenfa");
		map_skill("dagger", "shenghuo-lingfa");
		map_skill("parry", "qiankun-danuoyi");
		map_skill("cuff", "shenghuo-lingfa");
		prepare_skill("cuff", "shenghuo-lingfa");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "yinfeng" :),
			(: perform_action, "dagger.ji" :),
			(: perform_action, "dagger.xinmo" :),
			(: perform_action, "dagger.tisha" :),
		}));
		weapon = "tieling";
		menpai = "明教";
		break;
		case 16: // mj2
		set_skill("shenghuo-shengong", 700);
		set_skill("qiankun-danuoyi", 700);
		set_skill("piaoyi-shenfa", 700);
		set_skill("shenghuo-lingfa", 700);
		set_skill("hanbing-mianzhang", 700);
		map_skill("force", "shenghuo-shengong");
		map_skill("dodge", "piaoyi-shenfa");
		map_skill("dagger", "shenghuo-lingfa");
		map_skill("parry", "hanbing-mianzhang");
		map_skill("strike", "hanbing-mianzhang");
		prepare_skill("strike", "hanbing-mianzhang");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "yinfeng" :),
			(: perform_action, "strike.xixue" :),
		}));
		menpai = "明教";
		case 17: // dali1
		set_skill("qiantian-yiyang", 700);
		set_skill("tianlong-xiang", 700);
		set_skill("duanjia-jianfa", 700);
		set_skill("qingyan-zhang", 700);
		map_skill("force", "qiantian-yiyang");
		map_skill("dodge", "tianlong-xiang");
		map_skill("sword", "duanjia-jianfa");
		map_skill("parry", "duanjia-jianfa");
		map_skill("strike", "qingyan-zhang");
		prepare_skill("strike", "qingyan-zhang");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "xinjing" :),
			(: perform_action, "sword.fenglei" :),
		}));
		weapon = "sword";
		menpai = "西南大理";
		break;
		case 18: // tls
		set_skill("kurong-changong", 700);
		set_skill("tianlong-xiang", 700);
		set_skill("cihang-bian", 700);
		map_skill("force", "kurong-changong");
		map_skill("dodge", "tianlong-xiang");
		map_skill("parry", "kurong-changong");
		map_skill("strike", "kurong-changong");
		prepare_skill("strike","kurong-changong");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "ku" :),
			(: exert_function, "jiuchong" :),
		}));
		menpai = "大理天龙寺";
		break;
		case 19: // gumu2
		set_skill("yinsuo-jinling", 700);
		set_skill("yunu-jianfa", 700);
		set_skill("yunu-shenfa", 700);
		set_skill("meinu-quanfa", 700);
		set_skill("yunu-xinjing", 700);
		map_skill("force", "yunu-xinjing");
		map_skill("dodge", "yunu-shenfa");
		map_skill("sword", "yunu-jianfa");
		map_skill("whip", "yinsuo-jinling");
		map_skill("parry", "yinsuo-jinling");
		map_skill("cuff", "meinu-quanfa");
		prepare_skill("cuff", "meinu-quanfa");
		set("yueyin", 1);
		set("gmsanwu", 1);
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: perform_action, "whip.yueyin" :),
			(: perform_action, "whip.sanwu" :),
		}));
		weapon = "whip";
		menpai = "古墓派";
		break;
		case 20: //gumu3
		set_skill("anran-zhang", 700);
		set_skill("yunu-xinjing", 700);
		set_skill("yunu-shenfa", 700);
		map_skill("force", "yunu-xinjing");
		map_skill("dodge", "yunu-shenfa");
		map_skill("parry", "anran-zhang");
		map_skill("strike", "anran-zhang");
		prepare_skill("strike", "anran-zhang");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: perform_action, "strike.xiaohun" :),
			(: perform_action, "strike.anran" :),
			(: perform_action, "strike.jishi" :),
		}));
		menpai = "古墓派";
		break;
		case 21: // kl1
		set_skill("xuantian-wuji", 700);
		set_skill("taxue-wuhen", 700);
		set_skill("kunlun-zhang", 700);
		map_skill("force", "xuantian-wuji");
		map_skill("dodge", "taxue-wuhen");
		map_skill("parry", "kunlun-zhang");
		map_skill("strike", "kunlun-zhang");
		prepare_skill("strike", "kunlun-zhang");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: perform_action, "strike.diezhang" :),
			(: perform_action, "strike.xuebeng" :),
		}));
		menpai = "昆仑派";
		break;
		case 22: // kl2
		set_skill("xuantian-wuji", 700);
		set_skill("taxue-wuhen", 700);
		set_skill("zhentian-quan", 700);
		map_skill("force", "xuantian-wuji");
		map_skill("dodge", "taxue-wuhen");
		map_skill("parry", "zhentian-quan");
		map_skill("cuff", "zhentian-quan");
		prepare_skill("cuff", "zhentian-quan");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "taxue" :),
			(: perform_action, "cuff.kaishan" :),
		}));
		menpai = "昆仑派";
		break;
		case 23: // kl3
		set_skill("xuantian-wuji", 700);
		set_skill("taxue-wuhen", 700);
		set_skill("chuanyun-tui", 700);
		map_skill("force", "xuantian-wuji");
		map_skill("dodge", "taxue-wuhen");
		map_skill("parry", "chuanyun-tui");
		map_skill("leg", "chuanyun-tui");
		prepare_skill("leg", "chuanyun-tui");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "taxue" :),
			(: perform_action, "leg.chuanyun" :),
		}));
		menpai = "昆仑派";
		break;
		case 24: // kl4
		set_skill("xuantian-wuji", 700);
		set_skill("taxue-wuhen", 700);
		set_skill("liangyi-jian", 700);
		map_skill("force", "xuantian-wuji");
		map_skill("dodge", "taxue-wuhen");
		map_skill("parry", "liangyi-jian");
		map_skill("sword", "liangyi-jian");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: perform_action, "sword.xunlei" :),
			(: perform_action, "sword.hundun" :),
		}));
		menpai = "昆仑派";
		weapon = "sword";
		break;
		case 25: // tls3
		set_skill("kurong-changong", 700);
		set_skill("tianlong-xiang", 700);
		set_skill("yiyang-zhi", 700);
		map_skill("force", "kurong-changong");
		map_skill("dodge", "tianlong-xiang");
		map_skill("parry", "kurong-changong");
		map_skill("finger", "yiyang-zhi");
		prepare_skill("finger", "yiyang-zhi");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: perform_action, "finger.sanmai" :),
			(: perform_action, "finger.sandie" :),
		}));
		menpai = "大理天龙寺";
		break;
		case 26: // tz1
		set_skill("guiyuan-tunafa", 700);
		set_skill("shuishangpiao", 700);
		set_skill("tiezhang-zhangfa", 700);
		map_skill("force", "guiyuan-tuanfa");
		map_skill("dodge", "shuishangpiao");
		map_skill("parry", "tiezhang-zhangfa");
		map_skill("strike", "tiezhang-zhangfa");
		prepare_skill("strike", "tiezhang-zhangfa");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "juli" :),
			(: perform_action, "dodge.piao" :),
			(: perform_action, "strike.heyi" :),
			(: perform_action, "strike.duoming" :),
			(: perform_action, "strike.heisha" :),
		}));
		menpai = "铁掌派";
		break;
		case 27: // tz2
		set_skill("guiyuan-tunafa", 700);
		set_skill("shuishangpiao", 700);
		set_skill("tiezhang-zhangfa", 700);
		map_skill("force", "guiyuan-tunafa");
		map_skill("dodge", "shuishangpiao");
		map_skill("parry", "tiezhang-zhangfa");
		map_skill("strike", "tiezhang-zhangfa");
		prepare_skill("strike", "tiezhang-zhangfa");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "juli" :),
			(: perform_action, "dodge.piao" :),
			(: perform_action, "strike.xuanfeng" :),
			(: perform_action, "strike.pushan" :),
			(: perform_action, "strike.honglei" :),
		}));
		menpai = "铁掌派";
		break;
		case 28: // sld1
		set_skill("dulong-dafa", 700);
		set_skill("youlong-shenfa", 700);
		set_skill("huagu-mianzhang", 700);
		map_skill("force", "dulong-dafa");
		map_skill("dodge", "youlong-shenfa");
		map_skill("parry", "huagu-mianzhang");
		map_skill("strike", "huagu-mianzhang");
		prepare_skill("strike", "huagu-mianzhang");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "wudi" :),
			(: perform_action, "strike.bujue" :),
		}));
		menpai = "神龙教";
		break;
		case 29: // sld2
		set_skill("dulong-dafa", 700);
		set_skill("youlong-shenfa", 700);
		set_skill("huagu-mianzhang", 700);
		set_skill("tenglong-bifa", 700);
		map_skill("dagger", "tenglong-bifa");
		map_skill("force", "dulong-dafa");
		map_skill("dodge", "youlong-shenfa");
		map_skill("parry", "tenglong-bifa");
		map_skill("strike", "huagu-mianzhang");
		prepare_skill("strike", "huagu-mianzhang");
		set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "wudi" :),
			(: perform_action, "dagger.xiaolian" :),
			(: perform_action, "dagger.guifei" :),
			(: perform_action, "dagger.diqing" :),
		}));
		menpai = "神龙教";
		weapon = "dagger";
		break;
		default: // others      BUG!!!
		set("long","武功设置错误，BUG！！！");
	}
	set("weapon" , weapon);
	set("menpai" , menpai);
	setup();
	if( weapon!="null" ) carry_object(BINGQI_D(weapon))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
	add_money("silver", random(99));


	this_object()->start_call_out( (: call_other, this_object(), "dest", this_object() :), 600);
}
int return_home()
{
	return 0;
}
void dest()
{
	command("emote 急急忙忙地离开了。");
	destruct(this_object());
}
int do_copy(object target,int mode)
{
	mapping skills;
	string *sk;
	object me,ob;
	int lv,exp,i,t;

	me = this_object();
	ob = target;
	if(mode) {
		t = 10;
		//set("long",query("long")+"最近治安不太好，这个保镖是特别从京城请来的，据说还曾经是大内高手呢！\n");
		add_money("gold", random(2));
	}
	else
		t = 12+random(5);

	lv = ob->query("max_pot") -100;
	lv = lv * t/10;
	exp = ob->query("combat_exp") *t/10;
	exp = exp * (100+random(20))/100;
	me->set("no_party_job",1);
	me->set("max_qi", mode?(int)ob->query("max_qi")*t*20/100:(int)ob->query("max_qi")*t/10 );
	me->set("eff_qi", mode?(int)ob->query("max_qi")*t*20/100:(int)ob->query("max_qi")*t/10 );
	me->set("qi", mode?(int)ob->query("max_qi")*t*20/100:(int)ob->query("max_qi")*t/10 );
	me->set("max_jing",(int)ob->query("max_jing"));
	me->set("eff_jing",(int)ob->query("max_jing"));
	me->set("jing",(int)ob->query("max_jing"));
	me->set("max_neili",(int)ob->query("max_neili") );
	me->set("neili",(int)ob->query("neili")*t/10 );
	if( me->query("neili") < me->query("max_neili") )
		me->set("neili",(int)me->query("max_neili") );
	me->set("max_jingli",(int)ob->query("max_jingli"));
	me->set("eff_jingli",(int)ob->query("eff_jingli"));
	me->set("jingli",(int)ob->query("jingli"));
	if( me->query("jingli") < me->query("eff_jingli") )
		me->set("jingli",(int)me->query("eff_jingli") );
	me->set("combat_exp",exp );

	skills = me->query_skills();
	if (mapp(skills)) {
		sk = keys(skills);
		for (i=0;i<sizeof(sk);i++)
			if ( sk[i] != "literate")
			skills[sk[i]] = lv;
	}
	me->set("jiali",(int)me->query_skill("force")/4);
}
string ask_leave()
{
	object me, ob;
	me = this_object();
	ob = this_player();

	if(environment(me)->query("no_fight")) {
		random_move();
	}
	return "就在这里，动手吧！";
}