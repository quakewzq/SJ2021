int main(object me, string str)
{
        object ob, where, *ob_list;
        int i,level;
		string *heavy_level_desc= ({"极轻","很轻","不重","不轻","很重","极重",});
        if (!str)
                return notify_fail("指令格式错误\n"); 
        //ob = find_object(str);
        //if( !ob ) ob = find_living(str);
		ob_list = children(str);
		//if (sizeof(ob_list)<1)	ob_list = objects(str);
        //write("\n共有"+chinese_number(sizeof(ob_list))+"个复制件\n");
        if( sizeof(ob_list)>0 ) 
		{
                //str = resolve_path(me->query("cwd"), str);
        
                for(i=0; i<sizeof(ob_list); i++) {
                	
                	write((string)ob_list[i]+"\n");
                }
                return 1;
        }
        
	

	
	level = to_int(str);
	if( level >= sizeof(heavy_level_desc) ) level = sizeof(heavy_level_desc)-1;
	write("sizeof(heavy_level_desc)"+(string)sizeof(heavy_level_desc)+"\n");
	write((string)level+"\n");
	write((string)heavy_level_desc[level]+"\n");
        return 1;
}  

