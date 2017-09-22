/*

IsAdmin(playerid,level);
MsgToAdmins(color,string[],level);


*/

#define IsAdmin(%0,%1)		(PlayerData[(%0)][adminLevel] >= (%1))

T3D:function LoginAdmin(playerid){
	switch(PlayerData[playerid][allowedLevel]){
		case LEVEL_GM: {
			gmlogin(playerid);
		}
		case LEVEL_ADMIN: {
			alogin(playerid);
		}
		case LEVEL_HEADADMIN: {
			SetPlayerAdmin(playerid,true);
			OnRconLoginAttempt(GetPlayerIP(playerid),"$auto_login",1);
		}
	}
}

T3D:function MsgToAdmins(color,string[],level){
	foreach(new i : Player){
		if(IsAdmin(i,LEVEL_ADMIN)){
			SendClientMessage(i,color,string);
		}
	}
}

T3D:function gmlogin(playerid){
	if(IsAdmin(playerid,LEVEL_GM)) return 0;
	if(PlayerData[playerid][allowedLevel] < LEVEL_GM){
		SendClientMessage(playerid,0xFF0000FF,"Access denied...");
		BanEx(playerid,"[HD] gmlogin");
	}
	PlayerData[playerid][adminLevel] = PlayerData[playerid][allowedLevel];

	new szPlayerName[24],buffer[128];
	GetPlayerName(playerid,szPlayerName,sizeof(szPlayerName));
	format(buffer,sizeof(buffer),"{00FFFF}%s {FF6600}logged on as moderator.",GetPlayerNick(playerid));
	foreach(new i : Player){
		SendClientMessage(i,COLOR_INFO,buffer);
		PlaySound(i,1133);
	}
	return 1;
}

T3D:function alogin(playerid){
	if(IsAdmin(playerid,LEVEL_ADMIN)) return 0;
	if(PlayerData[playerid][allowedLevel] < LEVEL_ADMIN){
		SendClientMessage(playerid,0xFF0000FF,"Access denied...");
		BanEx(playerid,"[HD] alogin");
	}
	if(PlayerData[playerid][allowedLevel] >= LEVEL_HEADADMIN) return 0;
	PlayerData[playerid][adminLevel] = PlayerData[playerid][allowedLevel];

	new szPlayerName[24],buffer[128];
	GetPlayerName(playerid,szPlayerName,sizeof(szPlayerName));
	format(buffer,sizeof(buffer),"{CC0000}%s {FF6600}logged on as admin.",GetPlayerNick(playerid));
	foreach(new i : Player){
		SendClientMessage(i,COLOR_INFO,buffer);
		PlaySound(i,1133);
	}
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success){
	if(success){
		SetTimer( # "SearchForNewAdmin", 50, false);
	} else {
		foreach(new hackerid : Player){
			if(!strcmp(ip,GetPlayerIP(hackerid),true)){
				BanEx(hackerid,"Login to RCON without authorization");
			}
		}
	}

	new buffer[128];
	format(buffer,sizeof(buffer),"[RCON LOGIN] IP: %s - password: %s - login: %s",ip,password,success?("YES"):("NO"));
	WriteLog(buffer,LOG_FILE_SYSTEM);
	return 1;
}

T3D:function SearchForNewAdmin(){
	foreach(new playerid : Player){
		if(!PlayerData[playerid][isRcon] && IsPlayerAdmin(playerid) && PlayerData[playerid][allowedLevel] >= LEVEL_HEADADMIN){
			PlayerData[playerid][isRcon] = true;
			OnPlayerRCONLogin(playerid);
			break;
		} else if(!PlayerData[playerid][isRcon] && IsPlayerAdmin(playerid) && PlayerData[playerid][allowedLevel] < LEVEL_HEADADMIN){
			new buffer[255];
			format(buffer,sizeof buffer,"Unauthorized login to the admin RCON %d by %s (%d)! level %d/%d.", PlayerData[playerid][isRcon],GetPlayerNick(playerid),playerid,PlayerData[playerid][adminLevel],PlayerData[playerid][allowedLevel]);
			Kick(playerid);
			MsgToAdmins(COLOR_RED,buffer,LEVEL_ADMIN);
			WriteLog(buffer,LOG_FILE_SYSTEM);
		}
	}
}

T3D:function OnPlayerRCONLogin(playerid){
	new buffer[128];
	if(PlayerData[playerid][allowedLevel] < LEVEL_HEADADMIN){
		format(buffer,sizeof buffer,"Player %s [ID %d] with allowedLevel=%d tried to log on as RCON (adminLevel=%d) and has been kicked!", GetPlayerNick(playerid), playerid, PlayerData[playerid][adminLevel], PlayerData[playerid][allowedLevel]);
		MsgToAdmins(COLOR_RED,buffer,LEVEL_ADMIN);
		WriteLog(buffer,LOG_FILE_SYSTEM);
		Kick(playerid);
	} else {
		PlayerData[playerid][adminLevel] = PlayerData[playerid][allowedLevel];
		format(buffer,sizeof(buffer),"{FF0000}%s {FF6600}logged on as Head Admin.",GetPlayerNick(playerid));
		foreach(new i : Player){
			SendClientMessage(i,COLOR_INFO,buffer);
			PlaySound(i,1133);
		}
	}
}
