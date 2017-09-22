//A little security magic XD
stock bool:ConnectDataBase(){
	new RAW[200], MySQL_Config[200], buffer[200],
		hostname[32],username[32],password[34],database[32];
		
	//Create new config file
	if(!fexist(MYSQL_CFG_FILE)){
		fcreate(MYSQL_CFG_FILE);
		new File:outf = fopen(MYSQL_CFG_FILE,io_append);
		format(password,sizeof(password),"%s",GetProtVar(32));
		
		//for humans: "hostname;login;password;database"
		format(buffer,sizeof(buffer),"localhost;root;null;helios");
		
		if(ADMx512String(buffer,MySQL_Config,password,false) != ERROR_CODE_ADM_OK) return false;
		for(new i = 0; i < 32; i++){
			fputchar(outf,((password[i]+128) & 0xFF),false);
		}
		for(new i = 0, j = strlen(buffer); i < j; i++){
			fputchar(outf,MySQL_Config[i],false);
		}
		fclose(outf);
	}
	MySQL_Config = "";
	buffer = "";
	
	new File:inpf = fopen(MYSQL_CFG_FILE,io_read);
		
	if(!inpf) return false;
	new asize = flength(inpf);
	for(new i = 0; i < asize; i++){
		if(i < 32){
			password[i] = (fgetchar(inpf,0,false)+128) & 0xFF;
		} else {
			RAW[i-32] = fgetchar(inpf,0,false);
		}
	}
	fclose(inpf);
	password[32] = EOS;
	RAW[asize] = EOS;
	if(ADMx512String(RAW,MySQL_Config,password,true) != ERROR_CODE_ADM_OK) return false;
	sscanf(MySQL_Config,"p<;>s[32]s[32]s[32]s[32]",hostname,username,password,database);
	if(StringEqual(password,"null",true)) password = "";
	MySQLConn = mysql_connect(hostname,username,password,database);
	if(mysql_errno(MySQLConn)){
		printf("Failed to connect database");
		return false;
	}
	hostname = "", username = "", password = "", database = "", MySQL_Config = "", RAW = "";
	return true;
}