new prot_table[] = {48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122};

stock GetProtVar(size){
	new ProtKey[64];
	for(new i = 0; i < size; i++){
		ProtKey[i] = prot_table[randomex(0,61)];
	}
	ProtKey[size] = '\0';
	return ProtKey;
}


stock bool:GetADMKey(){
	ADMEncryptKey = "";
	if(!fexist(ADM_CFG_FILE)) return false;
	new File:inpf = fopen(ADM_CFG_FILE,io_read), symbol[10];
	for(new i = 0, j = flength(inpf); i < j; i++){
		format(symbol,sizeof(symbol),"%d ",fgetchar(inpf,0,false));
		strcat(ADMEncryptKey,symbol);
	}
	ADMEncryptKey[strlen(ADMEncryptKey)-1] = EOS;
	printf("[DEBUG] %s",ADMEncryptKey);
	return true;
}

stock DumpErrorLog(string[]){
	static wl_date[3],wl_time[3],wl_str[1024];
	if(!IsDumpFileOpen(ErrorDump)){
		if(!fexist(DUMP_FILE_ERROR)){
			ErrorDump = DumpFileCreate(DUMP_FILE_ERROR,ADMEncryptKey,KEY_TYPE_ADMx256);
			DumpFileWrite(ErrorDump,"\r\n\r\n");
		} else {
			ErrorDump = DumpFileOpen(DUMP_FILE_ERROR,ADMEncryptKey,KEY_TYPE_ADMx256);
		}
	}
	getdate(wl_date[0],wl_date[1],wl_date[2]);
   	gettime(wl_time[0],wl_time[1],wl_time[2]);
   	format(wl_str,sizeof wl_str,"[%02d.%02d.%02d %02d:%02d:%02d] %s\r\n",wl_date[0],wl_date[1],wl_date[2],wl_time[0],wl_time[1],wl_time[2],string);
	DumpFileWrite(ErrorDump,wl_str);
}

stock ChangeRconPassword(){
	new rconPass[128];
	format(rconPass,sizeof(rconPass),"rcon_password %s",GetProtVar(16));
	SendRconCommand(rconPass);
	rconPass = "";
}

//Hook: ShowPlayerDialog
stock AC_ShowPlayerDialog(playerid,dialogid,style,caption[],info[],button1[],button2[]){
	PlayerData[playerid][DialogIsUse] = true;
	return ShowPlayerDialog(playerid,dialogid,style,caption,info,button1,button2);
}

#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog AC_ShowPlayerDialog

public OnServerMessage(const msg[]){
	printf("[SERVER MSG] %s",msg);
	return 1;
}

public OnRemoteRCONPacket(const ipaddr[], port, const password[], success, const command[]){
	printf("[RCON PACKET] %s:%d (%d) Pass: '%s' CMD: '%s'",ipaddr,port,success,password,command);
	return 1;
}
