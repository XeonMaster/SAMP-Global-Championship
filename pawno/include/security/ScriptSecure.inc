/****************************************************************************************************
 *                                                                                                  *
 *                                          Script Secure                                           *
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

//#define DONT_ALLOW_LOCALHOST	//additional option
//#define CHECK_MAX_PLAYERS		//additional option
//#define CHECK_RCON_PASSWORD	//additional option
//#define CHECK_SERVER_LANGUAGE	//additional option

//Web ACK System
//#define ENABLE_WEB_ACK		//additional option (definitions below apply to this option)
//#define SCRIPT_ACK_KEY		"{BOBO_HAHA,ACCESSCONTROL,TRUE}"
//#define SCRIPT_ACK_URL		"example.com/secure_adm/index.php"
//#define SCRIPT_ANTI_FLOOD		(123) //change this number
//#define SCRIPT_ACK_TIME		(10000) //10 second


#define FILE_SERVERIP			"127.0.0.1"
#define FILE_SERVERPORT			(7777)			
#define FILE_LICENSEID			(20160201)		//<--- YYYYMMDD 01.02.2016 (DD.MM.YYYY)
#define FILE_MAX_PLAYERS		(500)			//max players in server.cfg
#define FILE_RCONPASS			"123"			//rcon password
#define FILE_LANGUAGE			"English"		//server language

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
			printf("[ADM] Error: The script did not get permission to activation.");
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

#if !defined FILE_SERVERIP
	#error [ADM] Please #define FILE_SERVERIP "server ip"
#endif

#if !defined FILE_SERVERPORT
	#error [ADM] Please #define FILE_SERVERPORT <port>
#endif

#if !defined FILE_LICENSEID
	#error [ADM] Please #define FILE_LICENSEID <license id>
#endif

#if defined CHECK_MAX_PLAYERS
	#if !defined FILE_MAX_PLAYERS
		#error [ADM] Please #define FILE_MAX_PLAYERS <players>
	#endif
#endif

#if defined CHECK_RCON_PASSWORD
	#if !defined FILE_RCONPASS
		#error [ADM] Please #define FILE_RCONPASS "rcon pass"
	#endif
#endif

#if defined CHECK_SERVER_LANGUAGE
	#if !defined FILE_LANGUAGE
		#error [ADM] Please #define FILE_LANGUAGE "language"
	#endif
#endif

AntiDeAMX(){
	new UAX[][] = { "Unarmed (Fist)", "Brass K" };
	#pragma unused UAX
}

ScriptSecureADM(){
	//IP and PORT check
	new ADMserverIP[16];
	GetServerVarAsString("bind",ADMserverIP,sizeof(ADMserverIP));
	
	if(!strcmp(ADMserverIP,FILE_SERVERIP,true) && !isnull(ADMserverIP)){
		//Server IP OK
	} else {
		if(!strcmp(ADMserverIP,"127.0.0.1",true) || !strcmp(ADMserverIP,"localhost",true)){
			//localhost
			#if defined DONT_ALLOW_LOCALHOST
				if(GetSVarInt("ADM:Logging:Disable") == 0){
					print("[ADM] Error: This script is stolen.");
				}
				SendRconCommand("exit");
				return 0;
			#else
				if(GetSVarInt("ADM:Logging:Disable") == 0){
					print("[ADM] Info: Local server detect.");
				}
			#endif
		} else {
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: This script is stolen.");
			}
			SendRconCommand("exit");
			return 0;
		}
	}
	if(!strcmp(ADMserverIP,"127.0.0.1",true) || !strcmp(ADMserverIP,"localhost",true)){
		//localhost
		#if defined DONT_ALLOW_LOCALHOST
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: This script is stolen.");
			}
			SendRconCommand("exit");
			return 0;
		#endif
	} else if(GetServerVarAsInt("port") != FILE_SERVERPORT){
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
	if(tmpdate > FILE_LICENSEID){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			print("[ADM] Error: Script license has expired.");
		}
		SendRconCommand("exit");
		return 0;
	}

	//Check server.cfg
	#if defined CHECK_MAX_PLAYERS
		if(GetMaxPlayers() != FILE_MAX_PLAYERS){
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
		if(strcmp(rtemp,FILE_RCONPASS,false) != 0){
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
		if(strcmp(rtemp,FILE_LANGUAGE,false) != 0 || isnull(rtemp)){
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
		format(buffer,sizeof(buffer),"%s?code=%d&bind=%s&port=%d",SCRIPT_ACK_URL,SCRIPT_ANTI_FLOOD,ADMserverIP,GetServerVarAsInt("port"));
		HTTP(790,HTTP_POST,buffer," ","ScriptSecureADMWeb");
		SetTimerEx("ADMWebACKCheck",SCRIPT_ACK_TIME, false, "d", 1);
	#endif
	
	return 1;
}

#undef FILE_SERVERIP
#undef FILE_SERVERPORT
#undef FILE_LICENSEID

#if defined FILE_MAX_PLAYERS
	#undef FILE_MAX_PLAYERS
#endif

#if defined FILE_RCONPASS
	#undef FILE_RCONPASS
#endif

#if defined FILE_LANGUAGE
	#undef FILE_LANGUAGE
#endif

//EOF