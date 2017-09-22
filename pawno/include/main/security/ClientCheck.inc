//todo update: Abyss Morgan
stock CheckPlayersIP(playerid,src[]){
	static buffer[200];
	new cnt = 0;
	foreach(new i : Player){
		if(strcmp(GetPlayerIP(i),src,false) == 0){
			cnt++;
		}
	}
	if(cnt > MAX_IP_CONNECTIONS){
		format(buffer,sizeof buffer,"[HACK DETECT] [%s](%d)%s used Bot",GetPlayerIP(playerid),playerid,GetPlayerNick(playerid));
		WriteLog(buffer,LOG_FILE_HACK);
		MsgToAdmins(COLOR_RED,buffer,LEVEL_ADMIN);
		BanEx(playerid,"[HD] Bots");
		foreach(new i : Player){
			if(i != playerid){
				if(strcmp(GetPlayerIP(i),src,false) == 0){
					Kick(i);
				}
			}
		}
		return 1;
	} else if(cnt == MAX_IP_CONNECTIONS){
		format(buffer,sizeof buffer,"[SECURITY] [%s](%d)%s too much connection",GetPlayerIP(playerid),playerid,GetPlayerNick(playerid));
		WriteLog(buffer,LOG_FILE_HACK);
		MsgToAdmins(COLOR_RED,buffer,LEVEL_ADMIN);
		return 0;
	}
	return 0;
}

stock Firewall_CheckPlayer(playerid,nickname[],ip[],serial[],version[]){
	static buffer[200];
	if(PlayerData[playerid][uglyRejoinHack]){
		format(buffer,sizeof buffer,"[SECURITY] [%s](%d)%s used DoubleConnect",ip,playerid,nickname);
		WriteLog(buffer,LOG_FILE_HACK);
		MsgToAdmins(COLOR_RED,buffer,LEVEL_ADMIN);
		Kick(playerid);
		return 1;
	} else if((strcmp(version,"0.3.7",true) != 0 && strcmp(version,"0.3.7-R1-2",true) != 0 && strcmp(version,"0.3.7-R2",true) != 0) || (isnull(version) && !IsPlayerNPC(playerid))){
		format(buffer,sizeof buffer,"[SECURITY] [%s](%d)%s invalid samp version",ip,playerid,nickname);
		WriteLog(buffer,LOG_FILE_HACK);
		MsgToAdmins(COLOR_RED,buffer,LEVEL_ADMIN);
		Kick(playerid);
		return 1;
	} else if(!strcmp(ip,"255.255.255.255",true) || isnull(ip)){
		format(buffer,sizeof buffer,"[SECURITY] [%s](%d)%s invalid player ip",ip,playerid,nickname);
		WriteLog(buffer,LOG_FILE_HACK);
		MsgToAdmins(COLOR_RED,buffer,LEVEL_ADMIN);
		Kick(playerid);
		return 1;
	}
	if(!IsPlayerNPC(playerid)){
		if(CheckPlayersIP(playerid,ip)) return 1;
		if(isnull(serial)){
			format(buffer,sizeof buffer,"[SECURITY] [%s](%d)%s invalid player gpci",ip,playerid,nickname);
			WriteLog(buffer,LOG_FILE_HACK);
			MsgToAdmins(COLOR_RED,buffer,LEVEL_ADMIN);
			Kick(playerid);
			return 1;
		}
	} else {
		//if((strcmp(ip,"80.72.36.202",false) == 0) || (strcmp(ip,"127.0.0.1",false) == 0)){
		
		format(buffer,sizeof buffer,"[NPC JOIN] [%s](%d)%s joined the game",ip,playerid,nickname);
		MsgToAdmins(COLOR_RED,buffer,LEVEL_ADMIN);
		
		/*
		} else {
			format(buffer,sizeof buffer,"[NPC JOIN] [%s](%d)%s joined the game (unidentified)",ip,playerid,nickname);
			WriteLog(buffer,LOG_FILE_HACK);
			MsgToAdmins(COLOR_RED,buffer,LEVEL_ADMIN);
			Kick(playerid);
			return 1;
		}
		*/
	}
	
	new plen = strlen(nickname);
	if(plen < 3 || plen > 20){
		format(buffer,sizeof buffer,"[SECURITY] [%s](%d)%s invalid player nick",ip,playerid,nickname);
		WriteLog(buffer,LOG_FILE_HACK);
		MsgToAdmins(COLOR_RED,buffer,LEVEL_ADMIN);
		Kick(playerid);
		return 1;
	}
	return 0;
}

T3D:function CheckPlayerWeaponPickup(playerid,pickupid){
	if(GetDynamicPickupType(pickupid) == 2){
		switch(GetDynamicPickupModel(pickupid)){
			/*
			//Conqueror Shield
			case 2061: {
				TogglePlayerConqueror(playerid,true);
			}
			
			//box supply of war
			case 2037: {
				switch(random(3)){
					case 0: GivePlayerWeapon(playerid,27,50);
					case 1: GivePlayerWeapon(playerid,35,12);
					case 2: GivePlayerWeapon(playerid,16,12);
				}
			}
			
			//big box supply of war
			case 2969: {
				if(!PlayerData[playerid][ConquerorStatus]){
					SetPlayerHealth(playerid,100.0);
				}
				SetPlayerArmour(playerid,100.0);
				switch(random(3)){
					case 0: GivePlayerWeapon(playerid,27,1000);
					case 1: GivePlayerWeapon(playerid,35,25);
					case 2: GivePlayerWeapon(playerid,16,25);
				}
			}
			*/
			
			case 1254: {
				new Float:x,Float:y,Float:z;
				GetPlayerPos(playerid,x,y,z);
				CreateDynamicExplosion(x-10.0,y-10.0,z,7,5.0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0);
				CreateDynamicExplosion(x-10.0,y+10.0,z,7,5.0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0);
				CreateDynamicExplosion(x+10.0,y-10.0,z,7,5.0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0);
				CreateDynamicExplosion(x+10.0,y+10.0,z,7,5.0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid),-1,200.0);
				SendClientMessage(playerid,0xCC0000FF,"Kamikaze !!!");
			}
			
			//Slot 0
			case 331: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,0,wepid,ammo);
				SetPlayerAmmo(playerid,wepid,1);
			}
			
			//Slot 1
			case 333..339, 341: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,1,wepid,ammo);
				SetPlayerAmmo(playerid,wepid,1);
			}
			
			//Slot 2
			case 346..348: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,2,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 3
			case 349..351: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,3,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 4
			case 352..353, 372: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,4,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 5
			case 355..356: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,5,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 6
			case 357..358: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,6,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 7
			case 359..362: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,7,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 8
			case 342..344, 363: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,8,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 9
			case 365..367: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,9,wepid,ammo);
				if(ammo >= 10000){
					SetPlayerAmmo(playerid,wepid,10000);
				}
			}
			
			//Slot 10
			case 321..326: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,10,wepid,ammo);
				SetPlayerAmmo(playerid,wepid,1);
			}
			
			//Slot 11
			case 368..369, 371: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,11,wepid,ammo);
				SetPlayerAmmo(playerid,wepid,1);
			}
			
			//Slot 12
			case 364: {
				new wepid, ammo;
				GetPlayerWeaponData(playerid,12,wepid,ammo);
				SetPlayerAmmo(playerid,wepid,1);
			}
		}
	}
	return 1;
}

//Hook: SetPlayerAmmo
stock CG_SetPlayerAmmo(playerid,weaponid,ammo){
	if(ammo < 0 || ammo > 10000) ammo = 10000;
	return SetPlayerAmmo(playerid,weaponid,ammo);
}

#if defined _ALS_SetPlayerAmmo
	#undef SetPlayerAmmo
#else
	#define _ALS_SetPlayerAmmo
#endif
#define SetPlayerAmmo CG_SetPlayerAmmo

//Hook: GivePlayerWeapon
stock CG_GivePlayerWeapon(playerid,weaponid,ammo){
	new wepid, ammo_a;
	GetPlayerWeaponData(playerid,weaponSlots[weaponid],wepid,ammo_a);
	if(ammo < 0){
		ammo = 0;
	} else if(ammo+ammo_a > 10000){
		SetPlayerAmmo(playerid,weaponid,10000);
	} else {
		return GivePlayerWeapon(playerid,weaponid,ammo);
	}
	return 1;
}

#if defined _ALS_GivePlayerWeapon
	#undef GivePlayerWeapon
#else
	#define _ALS_GivePlayerWeapon
#endif
#define GivePlayerWeapon CG_GivePlayerWeapon
//EOF