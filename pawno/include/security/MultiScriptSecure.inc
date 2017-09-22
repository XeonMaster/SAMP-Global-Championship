/****************************************************************************************************
 *                                                                                                  *
 *                                       Multi Script Secure                                        *
 *                                                                                                  *
 * Copyright © 2017 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/security                      *
 * Publication: http://forum.sa-mp.com/showthread.php?t=600408                                      *
 *                                                                                                  *
 * Plugins: None                                                                                    *
 * Modules: None                                                                                    *
 * Attributes: None                                                                                 *
 *                                                                                                  *
 * File Version: 4.0.1                                                                              *
 * SA:MP Version: 0.3.7                                                                             *
 *                                                                                                  *
 * Functions:                                                                                       *
 * AntiDeAMX();                                                                                     *
 * ScriptSecureADM();                                                                               *
 *                                                                                                  *
 ****************************************************************************************************/

/*
//Install

//#define CHECK_MAX_PLAYERS		//additional option
//#define CHECK_RCON_PASSWORD	//additional option
//#define CHECK_SERVER_LANGUAGE	//additional option

//Web ACK System
//#define ENABLE_WEB_ACK		//additional option (definitions below apply to this option)
//#define SCRIPT_ACK_KEY		"{BOBO_HAHA,ACCESSCONTROL,TRUE}"
//#define SCRIPT_ACK_URL		"example.com/secure_adm/index.php"
//#define SCRIPT_ANTI_FLOOD		(123) //change this number
//#define SCRIPT_ACK_TIME		(10000) //10 second

Add server information to ADMServerList

public OnGameModeInit(){

	AntiDeAMX();
	ScriptSecureADM();
	
	return 1;
}

public OnFilterScriptInit(){

	AntiDeAMX();
	ScriptSecureADM();
	
	return 1;
}
*/

enum e_server_config {
	ADM_ADMserverIP[16],
	ADM_ServerPort,
	ADM_LicenseID,
	ADM_MaxPlayers,
	ADM_RconPassword[32],
	ADM_Language[32]
}

/*
IP - string
PORT - integer value
LicenseID - integer value //YYYYMMDD
MaxPlayers - integer value
RconPassword - string
Language - string
*/

//IP Port LicenseID MaxPlayers RconPassword Language
new ADMServerList[][e_server_config] = {
	{ "127.0.0.1", 7777, 20160201, 500, "123", "Polish" },
	{ "127.0.0.1", 7778, 20170201, 500, "123", "English" }
};


#define INVALID_SERVERID		(-1)

#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

//Web ACK System
#if defined ENABLE_WEB_ACK
	#if !defined SCRIPT_ACK_KEY
		#error [ADM] Please #define SCRIPT_ACK_KEY "key"
	#endif
	
	#if !defined SCRIPT_ACK_URL
		#error [ADM] Please #define SCRIPT_ACK_URL "ack_url"
	#endif
	
	#if !defined SCRIPT_ANTI_FLOOD
		#error [ADM] Please #define SCRIPT_ANTI_FLOOD <random number>
	#endif
#else
	#if !defined SCRIPT_ACK_KEY
		#define SCRIPT_ACK_KEY		"none"
	#endif
	
	#if !defined SCRIPT_ACK_URL
		#define SCRIPT_ACK_URL		"none"
	#endif
	
	#if !defined SCRIPT_ANTI_FLOOD
		#define SCRIPT_ANTI_FLOOD	(0)
	#endif
#endif

new bool:ADMWebCheck = false;

forward ScriptSecureADMWeb(index, response_code, data[]);
forward ADMWebACKCheck(important);

public ScriptSecureADMWeb(index, response_code, data[]){
	if(strfind(data,SCRIPT_ACK_KEY,false) != -1){
		ADMWebCheck = true;
		//ok
	} else {
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Error: The script did not get permission to activation.");
		}
		SendRconCommand("exit");
		return 0;
	}
	return 1;
}

public ADMWebACKCheck(important){
	if(!ADMWebCheck){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Error: The script did not get permission to activation.");
		}
		SendRconCommand("exit");
		return 0;
	}
	return 1;
}

FindServerID(){
	new ADMserverIP[16], serverPort = GetServerVarAsInt("port");
	GetServerVarAsString("bind",ADMserverIP,sizeof(ADMserverIP));
	for(new i = 0, j = sizeof(ADMServerList); i < j; i++){
		if(!strcmp(ADMserverIP,ADMServerList[i][ADM_ADMserverIP],true) && !isnull(ADMserverIP)){
			if(serverPort == ADMServerList[i][ADM_ServerPort]){
				return i;
			}
		}
	}
	return INVALID_SERVERID;
}

AntiDeAMX(){
	new UAX[][] = { "Unarmed (Fist)", "Brass K" };
	#pragma unused UAX
}


ScriptSecureADM(){

	//IP and PORT check
	new sid = FindServerID();
	if(sid == INVALID_SERVERID){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Error: This script is stolen.");
		}
		SendRconCommand("exit");
		return 0;
	}

	//Date Check
	new tmpdate, tmpyear, tmpmonth, tmpday;
	getdate(tmpyear,tmpmonth,tmpday);
	tmpdate = (10000*tmpyear)+(100*tmpmonth)+tmpday;
	if(tmpdate > ADMServerList[sid][ADM_LicenseID]){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Error: Script license has expired.");
		}
		SendRconCommand("exit");
		return 0;
	}

	//Check server.cfg
	#if defined CHECK_MAX_PLAYERS
		if(GetMaxPlayers() != ADMServerList[sid][ADM_MaxPlayers]){
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: Invalid server config, check your max players.");
			}
			SendRconCommand("exit");
			return 0;
		}
	#endif
	
	new rtemp[32];
	
	#if defined CHECK_RCON_PASSWORD
		GetServerVarAsString("rcon_password",rtemp,sizeof(rtemp));
		if(strcmp(rtemp,ADMServerList[sid][ADM_RconPassword],false) != 0){
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: Invalid server config, check your rcon password.");
			}
			SendRconCommand("exit");
			return 0;
		}
		rtemp = "";
	#endif
	
	#if defined CHECK_SERVER_LANGUAGE
		GetServerVarAsString("language",rtemp,sizeof(rtemp));
		if(strcmp(rtemp,ADMServerList[sid][ADM_Language],false) != 0 || isnull(rtemp)){
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: Invalid server config, check your language.");
			}
			SendRconCommand("exit");
			return 0;
		}
		rtemp = "";
	#endif
	
	#pragma unused rtemp
	
	//Web ACK System
	#if defined ENABLE_WEB_ACK
		new buffer[256];
		format(buffer,sizeof(buffer),"%s?code=%d&bind=%s&port=%d",SCRIPT_ACK_URL,SCRIPT_ANTI_FLOOD,ADMServerList[sid][ADM_ADMserverIP],ADMServerList[sid][ADM_ServerPort]);
		HTTP(790,HTTP_POST,buffer," ","ScriptSecureADMWeb");
		SetTimerEx("ADMWebACKCheck",SCRIPT_ACK_TIME, false, "d", 1);
	#endif
	
	return 1;
}

//EOF