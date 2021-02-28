//COOL@SJ,20000302
string *shaoze = ({
//少泽
HIC"忽见$N左手小指一伸，一条气流从$P少冲穴中激射而出，好一招「少泽剑法」,忽左忽右，变化无常，指向$n！"NOR,
HIC"$N左斜行三步，右手食指虚点，左手小指突然点出，内力自左向右的斜攻过去，直插$n的$l！"NOR,
HIC"$N手臂陡然一提，在手掌离$n不到一尺之处，使一招「少泽剑法」,立即翻腕向上，屈掌成拳，小指弹出！"NOR,
HIC"$N左手小指上翘，灵动异常，忽屈忽伸，连续划圈，发出无数劲风！"NOR,
HIC"$N身体一蹲，小指上伸，轻轻弹出，一股无形指风打向$n的$l！"NOR,
});
string *guanchong = ({
//关冲
MAG"$N长笑一声，俯身斜倚，无名指弹出，指尖已对准$n的$l发出了一缕强烈的劲风！"NOR,
MAG"$N无名指一挥，拙滞古朴的关冲剑气直射而出，端端正正地刺向$n！"NOR,
MAG"$N身体一转，手臂向后伸出，无名指遥遥一指，剑气破空，直向$n的$l！"NOR,
MAG"$N食指一收，无名指突然点出，「关冲剑气」一发，一条剑气直射而出，快捷无比！"NOR,
MAG"$N双掌交错，缓缓伸出无名指，突然间剑气纵横，一股剑气狂冲而上！"NOR,
});
string *shangyang = ({
//商阳
HIG"$N变招奇速，右手食指如毒蛇出洞，疾从袖底穿出，大喝一声，双手幻出无数指影！"NOR,
HIG"$N拇指一屈，食指点出，变成了「商阳剑法」，一缕剑气向$n刺出！"NOR,
HIG"$N食指连动，「商阳剑法」一剑又一剑的刺出，其轻灵迅速，快速无比！"NOR,
HIG"$N以食指运那无形剑气，却不过是手指在数寸范围内转动，对着$n一点一戳！"NOR,
HIG"$N使出「商阳剑法」，食指忽屈忽伸，每一下点出，都是一缕无形指风似剑刺出！"NOR,
});
string *zhongchong = ({
//中冲
HIR"$N身体一转，中指反手划出，犹如长风破浪，一道剑气如刀般向前攻出！"NOR,
HIR"$N身形一恭，双手前伸，一式「中冲剑法」,双手合使，两道凌厉无比的剑气破空刺出！"NOR,
HIR"$N脸色森然，中指一竖，一挑，一式「中冲剑法」,两道剑气交错而行，向前刺出！"NOR,
HIR"$N将中指向上一弹，中冲剑气汹涌而出，接着$P将手指向下一划，剑气如利刀般砍向$n！"NOR,
HIR"电光火石之间，$N一翻掌，身向右移，奋起神威，右手斗然探出，中指向$n一竖！"NOR,
});
string *shaochong = ({
//少冲
CYN"$N掌托于胸前，伸出右小指，一招「少冲剑法」,缓缓地点向$n的周身大穴，弹指无声！"NOR,
CYN"$N小指一弹，使一招‘分花拂柳’，剑势如同柳絮一般，飘而不乱！"NOR,
CYN"$N一招「少冲剑法」，剑气回转，竟从左侧绕了过来，点向$n的$l！"NOR,
CYN"$N右手小指一挥，一招「少冲剑法」,点点刺刺，宛如雕花刺画一般！"NOR,
CYN"$N一招「少冲剑法」,小指一横一竖，交替两道指风一前一后攻向$n！"NOR,
});
string *shaoshang = ({
//少商
HIB"$N大拇指一按，嗤嗤两指，劲道使得甚巧，初缓后急，剑气如怒潮般汹涌而至！"NOR,
HIB"$N大拇指连挥，「少商剑气」便如是一幅泼墨山水相似，纵横倚斜，寥寥数笔，却是剑路雄劲！"NOR,
HIB"$N的「少商剑法」大开大阖，气派宏伟，每一剑刺出，都有石破天惊、风雨大至之势！"NOR,
HIB"$N大拇指一屈一伸，使出「少商剑法」,一道剑气刺出，古朴至极，却是无法可挡！"NOR,
HIB"$N双手围圈，左手紧压右手，右手大拇指慢慢按出，只见眼前气势一紧，一股排山倒海的无形之气缓缓推出！"NOR,
});
string *target_msg = ({
//少泽
"你只觉得一股无形剑气向你激射而来，其变化精微，快绝无比\n",
"那一股无形剑气当真是忽来忽去，变化精微，让你避无可避\n",
//关冲
"你感觉到那无形剑气拙滞古朴，奇正有别，委实难以架挡\n",
"所谓“大巧不工”，那直冲而来的无形剑气竟然使你无从躲避\n",
//商阳
"那无形的剑气巧妙灵活，难以琢磨，幻化间直奔你而来\n",
"无论你变招多快，也及不上那一缕剑气，瞬间已逼到了你跟前\n",
//中冲
"你感到这一股迅疾而来的的中冲剑气大开大合，气势雄伟，根本挡无可挡\n",
"猛然间你感到周身大穴都被一股大开大合，气势雄伟的无形剑气所包围\n",
//少冲
"待那剑气到得近前，竟是劲气弥漫，破空之声甚厉\n",
"只见那刺来的无形剑气‘拙’而不缓，‘缓’而不弱，有如神剑\n",
//少商
"只见那剑路雄劲，石破天惊，逼得你左躲右闪，无法招架\n",
"你见那无形剑气颇有石破天惊、风雨大至之势，逼得你纵高伏低，东闪西避\n"NOR,
});

string *winner_msg = ({
        CYN "\n$N哈哈大笑，说道：承让了\n\n" NOR,
        CYN "\n$N双手一拱，笑着说道：承让\n\n" NOR,
        CYN "\n$n向后一纵，说道：阁下武艺果然高明，这场算是在下输了\n\n" NOR,
        CYN "\n$N胜了这招，向后跃开三尺，笑道：承让\n\n" NOR,
        CYN "\n$n脸色微变，说道：佩服，佩服\n\n" NOR,
        CYN "\n$n向后退了几步，说道：这场比试算我输了，佩服，佩服\n\n" NOR,
        CYN "\n$n向后一纵，躬身做揖说道：阁下武艺不凡，果然高明\n\n" NOR,
});

string *winner_animal_msg = ({
        CYN "\n$N退在一旁，警戒地向$n盯视\n\n" NOR,
        CYN "\n$N退守开来，但仍然毫不放松地盯着$n\n\n" NOR,
        CYN "\n$N退了几步，但随时可能再冲过来\n\n" NOR
});
