/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                                         Script Checker                                                         *
 *                                                                                                                                *
 * Copyright © 2017 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/security                                                    *
 * Publication: None                                                                                                              *
 *                                                                                                                                *
 * Plugins: None                                                                                                                  *
 * Modules: None                                                                                                                  *
 * Attributes: None                                                                                                               *
 *                                                                                                                                *
 * File Version: 1.0.4                                                                                                            *
 * SA:MP Version: 0.3.7                                                                                                           *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * CheckAllScript(playerid = INVALID_PLAYER_ID, errorlevel = 0);                                                                  *
 * OnThisScriptCheck(playerid, errorlevel);                                                                                       *
 * CallToAllScript(playerid, chanel, errorlevel, data[]);                                                                         *
 * GetFilterScriptActiveTime();                                                                                                   *
 *                                                                                                                                *
 * Callbacks:                                                                                                                     *
 * OnScriptCheck(playerid, errorlevel);                                                                                           *
 * OnScriptCall(playerid, chanel, errorlevel, data[]);                                                                            *
 *                                                                                                                                *
 **********************************************************************************************************************************
 *                                                                                                                                *
 * Supported include:                                                                                                             *
 *                                                                                                                                *
 * Include: 'streamer' Author: 'Incognito'                                                                                        *
 * Include: 'audio' Author: 'Incognito'                                                                                           *
 * Include: 'profiler' Author: 'Zeex'                                                                                             *
 * Include: 'crashdetect' Author: 'Zeex'                                                                                          *
 * Include: 'zcmd' Author: 'Zeex'                                                                                                 *
 * Include: 'socket' Author: 'BlueG'                                                                                              *
 * Include: 'a_mysql' Author: 'BlueG'                                                                                             *
 * Include: 'pointers' Author: 'Slice'                                                                                            *
 * Include: 'weapon-config' Author: 'Slice'                                                                                       *
 * Include: 'ColAndreas' Author: 'Slice, Chris420, Pottus, uint32, Crayder, Codectile'                                            *
 * Include: 'md5' Author: 'Y_Less'                                                                                                *
 * Include: 'y_timers' Author: 'Y_Less'                                                                                           *
 * Include: 'sscanf2' Author: 'Y_Less, Emmet_'                                                                                    *
 * Include: 'geolocation' Author: 'Whitetiger, RaekwonDaChef, Y_Less, Andreas Gohr'                                               *
 * Include: 'YSF' Author: 'kurta999'                                                                                              *
 * Include: 'regex' Author: 'Fro1sha'                                                                                             *
 * Include: 'FCNPC' Author: 'OrMisicL, ziggi'                                                                                     *
 * Include: 'mapandreas' Author: 'Kalcor, Mauzen, Pamdex'                                                                         *
 * Include: 'dc_cmd' Author: 'Daniel Cortez'                                                                                      *
 * Include: 'mysql' Author: 'StrickenKid'                                                                                         *
 * Include: 'a_mysql' Author: 'G-sTyLeZzZ'                                                                                        *
 * Include: 'Dini' Author: 'DracoBlue'                                                                                            *
 * Include: 'progress' Author: 'Toribio'                                                                                          *
 * Include: 'progress2' Author: 'Southclaw, Toribio'                                                                              *
 * Include: 'CA3' Author: 'DialUp'                                                                                                *
 * Include: 'nex-ac' Author: 'Nexius'                                                                                             *
 * Include: 'ScriptChecker' Author: 'Abyss Morgan'                                                                                *
 * Include: 'StreamerFunction' Author: 'Abyss Morgan'                                                                             *
 * Include: 'BitFunctions' Author: 'Abyss Morgan'                                                                                 *
 * Include: 'RGB' Author: 'Abyss Morgan'                                                                                          *
 * Include: '3DTryg' Author: 'Abyss Morgan'                                                                                       *
 * Include: 'GangZoneEx' Author: 'Abyss Morgan'                                                                                   *
 * Include: 'ADM' Author: 'Abyss Morgan'                                                                                          *
 * Include: 'MapAndreasEx' Author: 'Abyss Morgan'                                                                                 *
 * Include: 'HTMLColor' Author: 'Abyss Morgan'                                                                                    *
 * Include: 'DataConvert' Author: 'Abyss Morgan'                                                                                  *
 * Include: 'TextDrawEx' Author: 'Abyss Morgan'                                                                                   *
 * Include: 'LY' Author: 'Abyss Morgan'                                                                                           *
 * Include: 'DoT' Author: 'Abyss Morgan'                                                                                          *
 * Include: 'BINLDR' Author: 'Abyss Morgan'                                                                                       *
 * Include: 'VehicleEx' Author: 'Abyss Morgan'                                                                                    *
 * Include: 'Logs' Author: 'Abyss Morgan'                                                                                         *
 * Include: 'ATM' Author: 'Abyss Morgan'                                                                                          *
 * Include: 'scmd' Author: 'Abyss Morgan'                                                                                         *
 * Include: 'FoxForeach' Author: 'Abyss Morgan'                                                                                   *
 * Include: 'EngineX' Author: 'Abyss Morgan'                                                                                      *
 * Include: 'MultiScriptSecure' Author: 'Abyss Morgan'                                                                            *
 * Include: 'ScriptSecure' Author: 'Abyss Morgan'                                                                                 *
 * Include: 'AntiSupremeTroll' Author: 'Abyss Morgan'                                                                             *
 * Include: 'Mines' Author: 'Abyss Morgan'                                                                                        *
 * Include: 'Missile' Author: 'Abyss Morgan'                                                                                      *
 *                                                                                                                                *
 **********************************************************************************************************************************/

/*
//Check Version ScriptChecker.inc
#if !defined _Script_Checker
	#error [ADM] You need ScriptChecker.inc v1.0.4
#elseif !defined Script_Checker_Version
	#error [ADM] Update you ScriptChecker.inc to v1.0.4
#elseif (Script_Checker_Version < 10004)
	#error [ADM] Update you ScriptChecker.inc to v1.0.4
#endif
*/

#if defined _Script_Checker
	#endinput
#endif
#define _Script_Checker

#define Script_Checker_Version 			(10004) //a.b.c 10000*a+100*b+c

#if !defined SCRIPT_NAME
	#error [ADM] Please #define SCRIPT_NAME <script name> before including ScriptChecker.inc
#endif

#if defined FILTERSCRIPT
	#define SCRIPT_TYPE					"FilterScript"
#else
	#define SCRIPT_TYPE					"GameMode"
#endif

#if !defined SCRIPT_CHECK_FILE
	#define SCRIPT_CHECK_FILE			"ScriptCheck.txt"
#endif

new FilterScriptActiveTime = 0;

#define CallToAllScript(%0,%1,%2,%3)	CallRemoteFunction("OnScriptCall","ddds",(%0),(%1),(%2),(%3))
#define GetFilterScriptActiveTime()		(GetTickCount()-FilterScriptActiveTime)
#define SC_SecToTimeDay(%0)				((%0) / 86400),(((%0) % 86400) / 3600),((((%0) % 86400) % 3600) / 60),((((%0) % 86400) % 3600) % 60)
#define SC_MSToTimeDay(%0)				SC_SecToTimeDay((%0)/1000)

stock CheckAllScript(playerid = INVALID_PLAYER_ID,errorlevel = 0){
	return CallRemoteFunction("OnThisScriptCheck","dd",playerid,errorlevel);
}

stock SC_GetSAMIncludeVersion(value,name[],maxdest = sizeof(name)){
	format(name,maxdest,"%d.%d.%d",(value / 10000),((value % 10000) / 100),((value % 10000) % 100));
}

stock SC_GetStreamerVersionName(name[], value, maxdest = sizeof name){
	new str[10];
	format(str,sizeof(str),"%06x",value);
	format(name,maxdest,"%d.%d.%dr%d",(str[0]-48),(str[1]-48),(str[2]-48),(((str[3]-48)*100) + ((str[4]-48)*10) + (str[5]-48)));
}

forward WriteCheckLog(string[],file[]);
forward OnThisScriptCheck(playerid,errorlevel);
forward OnScriptCheck(playerid,errorlevel);
forward OnScriptCall(playerid,chanel,errorlevel,data[]);

public WriteCheckLog(string[],file[]){
	static wl_date[3],wl_time[3],wl_str[512];
	getdate(wl_date[0],wl_date[1],wl_date[2]);
   	gettime(wl_time[0],wl_time[1],wl_time[2]);
   	format(wl_str,sizeof wl_str,"[%02d.%02d.%02d %02d:%02d:%02d] %s\r\n",wl_date[0],wl_date[1],wl_date[2],wl_time[0],wl_time[1],wl_time[2],string);
	if(!fexist(file)){
		new File:cfile = fopen(file,io_readwrite);
		fwrite(cfile,"********************\n* Script Check Log *\n********************\n\n");
		fclose(cfile);
	}
	new File:flog = fopen(file,io_append);
	fwrite(flog,wl_str);
	fclose(flog);
	return 1;
}

public OnThisScriptCheck(playerid,errorlevel){
	new buffer[256],
		script_version[32],
		script_version2[32],
		script_version3[32];
	
	#pragma unused script_version
	#pragma unused script_version2
	#pragma unused script_version3
	
	format(buffer,sizeof(buffer),"Script Name: '%s' Script Type: '%s' Active Time: '%02d:%02d:%02d:%02d'",SCRIPT_NAME,SCRIPT_TYPE,SC_MSToTimeDay(GetFilterScriptActiveTime()));
	WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	
	//Check ScriptChecker.inc
	#if defined _Script_Checker
		SC_GetSAMIncludeVersion(Script_Checker_Version,script_version);
		format(buffer,sizeof(buffer),"Include: 'ScriptChecker' Author: 'Abyss Morgan' Version: '%s'",script_version);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif
	
	/************************************
	 *                                  *
	 * Plugins Include                  *
	 *                                  *
	 ************************************/
	
	//Check streamer.inc
	#if defined Streamer_AppendArrayData
		#if defined _streamer_spec
			//Streamer.inc Version Detect by Streamerfunction
			GetStreamerVersionName(script_version,GetStreamerVersion());
			format(buffer,sizeof(buffer),"Include: 'streamer' Author: 'Incognito' Version: '%s'",script_version);
			WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
		#else
			//Streamer.inc Version Detect Auto
			SC_GetStreamerVersionName(script_version,Streamer_IncludeFileVersion);
			format(buffer,sizeof(buffer),"Include: 'streamer' Author: 'Incognito' Version: '%s'",script_version);
			WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
		#endif
	#endif
	
	//Check sscanf2.inc
	#if defined sscanf
		WriteCheckLog("Include: 'sscanf2' Author: 'Y_Less, Emmet_'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check YSF.inc
	#if defined _YSF_included
		WriteCheckLog("Include: 'YSF' Author: 'kurta999'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check regex.inc
	#if defined _regex_included
		WriteCheckLog("Include: 'regex' Author: 'Fro1sha'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check profiler.inc
	#if defined PROFILER_INC
		WriteCheckLog("Include: 'profiler' Author: 'Zeex'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check audio.inc
	#if defined Audio_Play
		WriteCheckLog("Include: 'audio' Author: 'Incognito'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check crashdetect.inc
	#if defined CRASHDETECT_INC
		WriteCheckLog("Include: 'crashdetect' Author: 'Zeex'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check FCNPC.inc
	#if defined _FCNPC_included
		WriteCheckLog("Include: 'FCNPC' Author: 'OrMisicL, ziggi'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check mapandreas.inc
	#if defined MapAndreas_FindZ_For2DCoord
		WriteCheckLog("Include: 'mapandreas' Author: 'Kalcor, Mauzen, Pamdex'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check ColAndreas.inc
	#if defined COLANDREAS
		WriteCheckLog("Include: 'ColAndreas' Author: 'Slice, Chris420, Pottus, uint32, Crayder, Codectile'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check socket.inc
	#if defined socket_included
		WriteCheckLog("Include: 'socket' Author: 'BlueG'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check dc_cmd.inc
	#if defined DC_CMD
		format(buffer,sizeof(buffer,"Include: 'dc_cmd' Author: 'Daniel Cortez' Version: '%d.%d'",DC_CMD_VERSION_MAJOR,DC_CMD_VERSION_MINOR);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif
	
	//Check mysql.inc
	#if defined __mysql_included
		WriteCheckLog("Include: 'mysql' Author: 'StrickenKid'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check a_mysql.inc
	#if defined mysql_included
		#if defined mysql_fetch_row
			WriteCheckLog("Include: 'a_mysql' Author: 'G-sTyLeZzZ'",SCRIPT_CHECK_FILE);
		#else
			WriteCheckLog("Include: 'a_mysql' Author: 'BlueG'",SCRIPT_CHECK_FILE);
		#endif
	#endif
	
	/************************************
	 *                                  *
	 * Other Include                    *
	 *                                  *
	 ************************************/
	
	//Check md5.inc
	#if defined MD5_Hash
		WriteCheckLog("Include: 'md5' Author: 'Y_Less'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check zcmd.inc
	#if defined _zcmd_included
		WriteCheckLog("Include: 'zcmd' Author: 'Zeex'",SCRIPT_CHECK_FILE);
	#endif

	//Check y_timers.inc
	#if defined Timer
		WriteCheckLog("Include: 'y_timers' Author: 'Y_Less'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check Dini.inc
	#if defined _dini_included
		WriteCheckLog("Include: 'Dini' Author: 'DracoBlue'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check pointers.inc
	#if defined PointerByAddress
		WriteCheckLog("Include: 'pointers' Author: 'Slice'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check progress.inc
	#if defined _progress_included
		new str[10];
		format(str,sizeof(str),"%04x",_progress_version);
		format(script_version,sizeof(script_version),"%d.%d.%d.%d",(str[0]-48),(str[1]-48),(str[2]-48),(str[3]-48));
		format(buffer,sizeof(buffer),"Include: 'progress' Author: 'Toribio' Version: '%s'",script_version);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif
	
	//Check progress2.inc
	#if defined _progress2_included
		new str[10];
		format(str,sizeof(str),"%03x0",_progress2_version);
		format(script_version,sizeof(script_version),"%d.%d.%d",(str[0]-48),(str[1]-48),(str[2]-48),(str[3]-48));
		format(buffer,sizeof(buffer),"Include: 'progress2' Author: 'Southclaw, Toribio' Version: '%s'",script_version);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif
	
	//Check geolocation.inc
	#if defined _geolocation_included
		WriteCheckLog("Include: 'geolocation' Author: 'Whitetiger, RaekwonDaChef, Y_Less, Andreas Gohr'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check CA3.inc
	#if defined CreateArt3
		WriteCheckLog("Include: 'CA3' Author: 'DialUp'",SCRIPT_CHECK_FILE);
	#endif

	//Check weapon-config.inc
	#if defined _INC_WEAPON_CONFIG
		WriteCheckLog("Include: 'weapon-config' Author: 'Slice'",SCRIPT_CHECK_FILE);
	#endif

	//Check nex-ac.inc
	#if defined _nex_ac_included
		format(buffer,sizeof(buffer),"Include: 'nex-ac' Author: 'Nexius' Version '%s' for '%s'",NEX_AC_VERSION,AC_SERVER_VERSION);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif



	
	/*
	
	//Check .inc
	#if defined 
		WriteCheckLog("Include: '' Author: ''",SCRIPT_CHECK_FILE);
	#endif
	
	
	*/
	
	/************************************
	 *                                  *
	 * SAM Include made by Abyss Morgan *
	 *                                  *
	 ************************************/
	
	//Check StreamerFunction.inc
	#if defined _streamer_spec
		SC_GetSAMIncludeVersion(Streamer_Spec_Version,script_version);
		GetStreamerVersionName(script_version2,GetStreamerVersion());
		GetStreamerVersionName(script_version3,GetValidStreamerVersion());
		format(buffer,sizeof(buffer),"Include: 'StreamerFunction' Author: 'Abyss Morgan' Version: '%s' Streamer Version: '%s' Valid Streamer Version: '%s'",script_version,script_version2,script_version3);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif
	
	//Check BitFunctions
	#if defined _bit_function
		WriteCheckLog("Include: 'BitFunctions' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check RGB.inc
	#if defined _rgb_function
		WriteCheckLog("Include: 'RGB' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check 3DTryg.inc
	#if defined _3D_Tryg
		SC_GetSAMIncludeVersion(Tryg3D_Version,script_version);
		format(buffer,sizeof(buffer),"Include: '3DTryg' Author: 'Abyss Morgan' Version: '%s'",script_version);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif
	
	//Check GangZoneEx.inc
	#if defined _Gang_Zone_Ex
		WriteCheckLog("Include: 'GangZoneEx' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check ADM.inc
	#if defined _adm_encryption
		SC_GetSAMIncludeVersion(ADM_Encryption_Version,script_version);
		format(buffer,sizeof(buffer),"Include: 'ADM' Author: 'Abyss Morgan' Version: '%s'",script_version);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif
	
	//Check MapAndreasEx.inc
	#if defined _Map_Andreas_Ex
		WriteCheckLog("Include: 'MapAndreasEx' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check HTMLColor.inc
	#if defined _HTML_Color
		WriteCheckLog("Include: 'HTMLColor' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check DataConvert.inc
	#if defined _Data_Convert
		SC_GetSAMIncludeVersion(Data_Convert_Version,script_version);
		format(buffer,sizeof(buffer),"Include: 'DataConvert' Author: 'Abyss Morgan' Version: '%s'",script_version);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif
	
	//Check TextDrawEx.inc
	#if defined _Text_Draw_Ex
		WriteCheckLog("Include: 'TextDrawEx' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check LY.inc
	#if defined _Long_Yoyo
		SC_GetSAMIncludeVersion(Long_Yoyo_Version,script_version);
		format(buffer,sizeof(buffer),"Include: 'LY' Author: 'Abyss Morgan' Version: '%s'",script_version);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif
	
	//Check DoT.inc
	#if defined _DoT_Loader
		SC_GetSAMIncludeVersion(DoT_Loader_Version,script_version);
		format(buffer,sizeof(buffer),"Include: 'DoT' Author: 'Abyss Morgan' Version: '%s'",script_version);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif
	
	//Check BINLDR.inc
	#if defined _Bin_Loader
		SC_GetSAMIncludeVersion(Bin_Loader_Version,script_version);
		format(buffer,sizeof(buffer),"Include: 'BINLDR' Author: 'Abyss Morgan' Version: '%s'",script_version);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif
	
	//Check VehicleEx.inc
	#if defined _Vehicle_Ex
		WriteCheckLog("Include: 'VehicleEx' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check Logs.inc
	#if defined _Log_File
		WriteCheckLog("Include: 'Logs' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check ATM.inc
	#if defined _ATM_Core
		SC_GetSAMIncludeVersion(ATM_Version,script_version);
		format(buffer,sizeof(buffer),"Include: 'ATM' Author: 'Abyss Morgan' Version: '%s'",script_version);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif
	
	//Check scmd.inc
	#if defined _scmd_included
		WriteCheckLog("Include: 'scmd' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check FoxForeach.inc
	#if defined _FoX_Foreach
		WriteCheckLog("Include: 'FoxForeach' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif
	
	
	//Check EngineX.inc
	#if defined _NOX_ENGINE_X
		SC_GetSAMIncludeVersion(NOX_ENGINE_X_Version,script_version);
		format(buffer,sizeof(buffer),"Include: 'EngineX' Author: 'Abyss Morgan' Version: '%s' Version Name: '%s' NT Version: '%s'",script_version,NOX_VERSION,NT_VERSION);
		WriteCheckLog(buffer,SCRIPT_CHECK_FILE);
	#endif

	
	//Check ScriptSecure.inc 
	//Check MultiScriptSecure.inc
	#if defined ScriptSecureADM
		#if defined ADMServerList
			WriteCheckLog("Include: 'MultiScriptSecure' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
		#else
			WriteCheckLog("Include: 'ScriptSecure' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
		#endif
	#endif
	
	//Check AntiSupremeTroll.inc
	#if defined _anti_supreme_troll
		WriteCheckLog("Include: 'AntiSupremeTroll' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif

	//Check Mines.inc
	#if defined _dynamic_mine_system
		WriteCheckLog("Include: 'Mines' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif
	
	//Check Missile.inc
	#if defined _missile_launcher
		WriteCheckLog("Include: 'Missile' Author: 'Abyss Morgan'",SCRIPT_CHECK_FILE);
	#endif
	
	CallLocalFunction("OnScriptCheck","dd",playerid,errorlevel);
	
	WriteCheckLog("End of Detect",SCRIPT_CHECK_FILE);
	WriteCheckLog("",SCRIPT_CHECK_FILE);
	return 1;
}

new bool:CRC_ScriptChecker = true;

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_ScriptChecker){ CRC_ScriptChecker = false; } else return 1; //Init Engine
	FilterScriptActiveTime = GetTickCount();
	#if defined SC_OnFilterScriptInit
		SC_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit SC_OnFilterScriptInit
#if defined SC_OnFilterScriptInit
	forward SC_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_ScriptChecker){ CRC_ScriptChecker = false; } else return 1; //Init Engine
	FilterScriptActiveTime = GetTickCount();
	#if defined SC_OnGameModeInit
		SC_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SC_OnGameModeInit
#if defined SC_OnGameModeInit
	forward SC_OnGameModeInit();
#endif



//EOF