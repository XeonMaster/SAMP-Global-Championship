/****************************************************************************************************
 *                                                                                                  *
 *                                    )(   ADM Guard System   )(                                    *
 *                                                                                                  *
 * Copyright © 2017 Abyss Morgan. All rights reserved.                                              *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                           *
 * Publication: ---                                                                                 *
 * Website: http://8.ct8.pl                                                                         *
 *                                                                                                  *
 * Plugins: None                                                                                    *
 * Modules: None                                                                                    *
 *                                                                                                  *
 * File Version: 1.0.0                                                                              *
 * SA:MP Version: 0.3.7                                                                             *
 *                                                                                                  *
 * Modules:                                                                                         *
 * - Anti God Mode                                                                                  *
 * - Anti Money Hack                                                                                *
 * - Anti Score Hack                                                                                *
 * - Anti AFK Kill (YSF)                                                                            *
 * - Anti Driver Kill                                                                               *
 * - Anti Weapon Hack                                                                               *
 * - Custom Health/Armour Bars                                                                      *
 *                                                                                                  *
 * Functions:                                                                                       *
 * SetPlayerMoney(playerid,money);                                                                  *
 * ADMG::ResetPlayerWeapons(playerid);                                                              *
 *                                                                                                  *
 ****************************************************************************************************/
 
#if defined _ADM_GUARD_SYSTEM
	#endinput
#endif
#define _ADM_GUARD_SYSTEM

#if !defined _progress2_included
	#error [ADM] You need progress2.inc (github.com/AbyssMorgan/SA-MP/blob/master/include/samp/progress2.inc)
#endif

#if !defined MAX_PLAYER_HEALTH
	#define MAX_PLAYER_HEALTH				(100.0)
#endif

#if !defined MAX_PLAYER_ARMOUR
	#define MAX_PLAYER_ARMOUR				(100.0)
#endif

#if !defined BAR_COLOR_HEALTH
	#define BAR_COLOR_HEALTH				(0x990000FF)
#endif

#if !defined BAR_COLOR_ARMOUR
	#define BAR_COLOR_ARMOUR				(0xFFFFFFFF)
#endif

#define ADMG::								ADMG_

#define ADMG_GetWeaponSlot(%0)				ADMG::WeaponSlot[(%0)]
#define ADMG_NMTVF(%0,%1)					(((%0) > (%1))?(%1):(%0))

new Float:		ADMG::health[MAX_PLAYERS],
	Float:		ADMG::armour[MAX_PLAYERS],
				ADMG::money[MAX_PLAYERS],
				ADMG::score[MAX_PLAYERS],
				ADMG::WeaponID[MAX_PLAYERS][12],
				ADMG::WeaponAmmo[MAX_PLAYERS][12],
	PlayerBar:	ADMG::ProgressBar[MAX_PLAYERS][2];
	
new ADMG::WeaponSlot[] = {0,0,1,1,1,1,1,1,1,1,10,10,10,10,10,10,8,8,8,-1,-1,-1,2,2,2,3,3,3,4,4,5,5,4,6,6,7,7,7,7,8,12,9,9,9,11,11,11};


stock ADMG::GetPlayerNick(playerid){
	new ADMG::nick[MAX_PLAYER_NAME];
	GetPlayerName(playerid,ADMG::nick,sizeof(ADMG::nick));
	return ADMG::nick;
}

stock ADMG::GetPlayerIP(playerid){
	new ADMG::ip[MAX_PLAYER_NAME];
	GetPlayerIp(playerid,ADMG::ip,sizeof(ADMG::ip));
	return ADMG::ip;
}

//Hook: GetPlayerHealth
stock Float:ADMG::GetPlayerHealth(playerid){
	return ADMG::health[playerid];
}

#if defined _ALS_GetPlayerHealth
	#undef GetPlayerHealth
#else
	#define _ALS_GetPlayerHealth
#endif
#define GetPlayerHealth ADMG::GetPlayerHealth

//Hook: SetPlayerHealth
stock ADMG::SetPlayerHealth(playerid,Float:health){
	ADMG::health[playerid] = health;
	SetPlayerProgressBarValue(playerid,ADMG::ProgressBar[playerid][0],ADMG::NMTVF(health,MAX_PLAYER_HEALTH));
	return SetPlayerHealth(playerid,health+256);
}

#if defined _ALS_SetPlayerHealth
	#undef SetPlayerHealth
#else
	#define _ALS_SetPlayerHealth
#endif
#define SetPlayerHealth ADMG::SetPlayerHealth

//Hook: GetPlayerArmour
stock Float:ADMG::GetPlayerArmour(playerid){
	return ADMG::armour[playerid];
}

#if defined _ALS_GetPlayerArmour
	#undef GetPlayerArmour
#else
	#define _ALS_GetPlayerArmour
#endif
#define GetPlayerArmour ADMG::GetPlayerArmour

//Hook: SetPlayerArmour
stock ADMG::SetPlayerArmour(playerid,Float:armour){
	ADMG::armour[playerid] = armour;
	SetPlayerProgressBarValue(playerid,ADMG::ProgressBar[playerid][1],ADMG::NMTVF(armour,MAX_PLAYER_ARMOUR));
	if(armour <= 0.0){
		HidePlayerProgressBar(playerid,ADMG::ProgressBar[playerid][1]);
	} else {
		ShowPlayerProgressBar(playerid,ADMG::ProgressBar[playerid][1]);
	}
	return SetPlayerArmour(playerid,armour);
}

#if defined _ALS_SetPlayerArmour
	#undef SetPlayerArmour
#else
	#define _ALS_SetPlayerArmour
#endif
#define SetPlayerArmour ADMG::SetPlayerArmour

stock SetPlayerMoney(playerid,money){
	ADMG::money[playerid] = money;
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid,money);
}

//Hook: GetPlayerMoney
stock ADMG::GetPlayerMoney(playerid){
	return ADMG::money[playerid];
}

#if defined _ALS_GetPlayerMoney
	#undef GetPlayerMoney
#else
	#define _ALS_GetPlayerMoney
#endif
#define GetPlayerMoney ADMG::GetPlayerMoney

//Hook: GivePlayerMoney
stock ADMG::GivePlayerMoney(playerid,money){
	ADMG::money[playerid] += money;
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid,ADMG::money[playerid]);
}

#if defined _ALS_GivePlayerMoney
	#undef GivePlayerMoney
#else
	#define _ALS_GivePlayerMoney
#endif
#define GivePlayerMoney ADMG::GivePlayerMoney

//Hook: GetPlayerScore
stock ADMG::GetPlayerScore(playerid){
	return ADMG::score[playerid];
}

#if defined _ALS_GetPlayerScore
	#undef GetPlayerScore
#else
	#define _ALS_GetPlayerScore
#endif
#define GetPlayerScore ADMG::GetPlayerScore

//Hook: SetPlayerScore
stock ADMG::SetPlayerScore(playerid,score){
	ADMG::score[playerid] = score;
	SetPlayerScore(playerid,ADMG::score[playerid]);
}

#if defined _ALS_SetPlayerScore
	#undef SetPlayerScore
#else
	#define _ALS_SetPlayerScore
#endif
#define SetPlayerScore ADMG::SetPlayerScore

//Hook: GetPlayerWeaponData
stock ADMG::GetPlayerWeaponData(playerid,slot,&weapons,&ammo){
	switch(slotid){
		case 0..1, 7..12: {
			GetPlayerWeaponData(playerid,slot,weapons,ammo);
			weapons = ADMG::WeaponID[playerid][slotid];
		}
		default: {
			weapons = ADMG::WeaponID[playerid][slotid];
			ammo = ADMG::WeaponAmmo[playerid][slotid];
		}
	}
}

#if defined _ALS_GetPlayerWeaponData
	#undef GetPlayerWeaponData
#else
	#define _ALS_GetPlayerWeaponData
#endif
#define GetPlayerWeaponData ADMG::GetPlayerWeaponData

//Hook: GetPlayerAmmo
stock ADMG::GetPlayerAmmo(playerid){
	new slotid = ADMG::GetWeaponSlot(GetPlayerWeapon(playerid));
	switch(slotid){
		case 0..1, 7..12: return GetPlayerAmmo(playerid);
		default: return ADMG::WeaponAmmo[playerid][slotid];
	}
	return 0;
}

#if defined _ALS_GetPlayerAmmo
	#undef GetPlayerAmmo
#else
	#define _ALS_GetPlayerAmmo
#endif
#define GetPlayerAmmo ADMG::GetPlayerAmmo

//Hook: SetPlayerAmmo
stock ADMG::SetPlayerAmmo(playerid,weaponslot,ammo){
	ADMG::WeaponAmmo[playerid][weaponslot] = ammo;
	return SetPlayerAmmo(playerid,weaponslot,ammo);
}

#if defined _ALS_SetPlayerAmmo
	#undef SetPlayerAmmo
#else
	#define _ALS_SetPlayerAmmo
#endif
#define SetPlayerAmmo ADMG::SetPlayerAmmo

//Hook: GivePlayerWeapon
stock ADMG::GivePlayerWeapon(playerid,weaponid,ammo){
	new slotid = ADMG::GetWeaponSlot(weaponid);
	if(ADMG::WeaponID[playerid][slotid] == weaponid){
		ADMG::WeaponAmmo[playerid][slotid] += ammo;
		GivePlayerWeapon(playerid,weaponid,ammo);
	} else {
		ADMG::WeaponID[playerid][slotid] = weaponid;
		ADMG::WeaponAmmo[playerid][slotid] = ammo;
		GivePlayerWeapon(playerid,weaponid,ammo);
		SetPlayerAmmo(playerid,slotid,ammo);
	}
}

#if defined _ALS_GivePlayerWeapon
	#undef GivePlayerWeapon
#else
	#define _ALS_GivePlayerWeapon
#endif
#define GivePlayerWeapon ADMG::GivePlayerWeapon

//Hook: ResetPlayerWeapons
stock ADMG::ResetPlayerWeapons(playerid){
	for(new slot = 0; slot < 12; slot++){
		ADMG::WeaponID[playerid][slot] = 0;
		ADMG::WeaponAmmo[playerid][slot] = 0;
	}
	return ResetPlayerWeapons(playerid);
}

#if defined _ALS_ResetPlayerWeapons
	#undef ResetPlayerWeapons
#else
	#define _ALS_ResetPlayerWeapons
#endif
#define ResetPlayerWeapons ADMG::ResetPlayerWeapons

stock RemovePlayerWeapon(playerid,weaponid){
	new plyWeapons[12], plyAmmo[12];
	for(new slot = 0; slot < 12; slot++){
	new wep, ammo;
	GetPlayerWeaponData(playerid,slot,wep,ammo);
	if(wep != weaponid)
		GetPlayerWeaponData(playerid,slot,plyWeapons[slot],plyAmmo[slot]);
	}
	ResetPlayerWeapons(playerid);
	for(new slot = 0; slot < 12; slot++){
		GivePlayerWeapon(playerid,plyWeapons[slot],plyAmmo[slot]);
	}
}

stock ADMG::GivePlayerDamage(targetid,Float:amount,playerid,weaponid){
	if(ADMG::armour[targetid] >= amount){
		SetPlayerArmour(targetid,ADMG::armour[targetid]-amount);
	} else if(ADMG::armour[targetid] < amount){
		amount -= ADMG::armour[targetid];
		SetPlayerArmour(targetid,0.0);
		if(ADMG::health[targetid]-amount <= 0.0){
			CallRemoteFunction("OnPlayerDeath","ddd",targetid,playerid,weaponid);
			SpawnPlayer(targetid);
		} else {
			SetPlayerHealth(targetid,ADMG::health[targetid]-amount);
		}
	} else {
		if(ADMG::health[targetid]-amount <= 0.0){
			CallRemoteFunction("OnPlayerDeath","ddd",targetid,playerid,weaponid);
			SpawnPlayer(targetid);
		} else {
			SetPlayerHealth(targetid,ADMG::health[targetid]-amount);
		}
	}
	return 1;
} 

//Hook: OnPlayerTakeDamage
public OnPlayerTakeDamage(playerid,issuerid,Float:amount,weaponid,bodypart){
	if(issuerid == INVALID_PLAYER_ID){
		ADMG::GivePlayerDamage(playerid,amount,issuerid,weaponid);
	}
	#if defined ADMG_OnPlayerTakeDamage
		ADMG::OnPlayerTakeDamage(playerid,issuerid,amount,weaponid,bodypart);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerTakeDamage
	#undef OnPlayerTakeDamage
#else
	#define _ALS_OnPlayerTakeDamage
#endif
#define OnPlayerTakeDamage ADMG::OnPlayerTakeDamage
#if defined ADMG_OnPlayerTakeDamage
	forward ADMG::OnPlayerTakeDamage(playerid,issuerid,Float:amount,weaponid,bodypart);
#endif

//Hook: OnPlayerGiveDamage
public OnPlayerGiveDamage(playerid,damagedid,Float:amount,weaponid,bodypart){
	ADMG::GivePlayerDamage(damagedid,amount,playerid,weaponid);
	#if defined ADMG_OnPlayerGiveDamage
		ADMG::OnPlayerGiveDamage(playerid,damagedid,amount,weaponid,bodypart);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerGiveDamage
	#undef OnPlayerGiveDamage
#else
	#define _ALS_OnPlayerGiveDamage
#endif
#define OnPlayerGiveDamage ADMG::OnPlayerGiveDamage
#if defined ADMG_OnPlayerGiveDamage
	forward ADMG::OnPlayerGiveDamage(playerid,damagedid,Float:amount,weaponid,bodypart);
#endif

//Hook: OnPlayerWeaponShot
public OnPlayerWeaponShot(playerid,weaponid,hittype,hitid,Float:fX,Float:fY,Float:fZ){
	switch(hittype){
		case BULLET_HIT_TYPE_PLAYER: {
			#if defined _YSF_included
				if(IsPlayerPaused(hitid)) return 0;
			#endif
			if(IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleID(playerid) == GetPlayerVehicleID(hitid)) return 0;
		}
		case BULLET_HIT_TYPE_VEHICLE: {
			if(IsPlayerInVehicle(playerid,hitid)) return 0;
		}
	}
	new slotid = ADMG::GetWeaponSlot(weaponid);
	if(ADMG::WeaponID[playerid][slotid] != weaponid || ADMG::WeaponAmmo[playerid][slotid] == 0){
		printf("[ADM GUARD] [%s](%d)%s has been kicked: Weapon Hack",ADMG::GetPlayerIP(playerid),playerid,ADMG::GetPlayerNick(playerid));
		Kick(playerid);
		return 1;
	}
	ADMG::WeaponAmmo[playerid][slotid]--;
	
	#if defined ADMG_OnPlayerWeaponShot
		ADMG::OnPlayerWeaponShot(playerid,weaponid,hittype,hitid,fX,fY,fZ);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerWeaponShot
	#undef OnPlayerWeaponShot
#else
	#define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot ADMG::OnPlayerWeaponShot
#if defined ADMG_OnPlayerWeaponShot
	forward ADMG::OnPlayerWeaponShot(playerid,weaponid,hittype,hitid,Float:fX,Float:fY,Float:fZ);
#endif

//Hook: OnPlayerDeath
public OnPlayerDeath(playerid,killerid,reason){
	if(killerid == INVALID_PLAYER_ID){
		switch(reason){
			case 0..34: {
				printf("[ADM GUARD] [%s](%d)%s has been kicked: Fake Kill",ADMG::GetPlayerIP(playerid),playerid,ADMG::GetPlayerNick(playerid));
				Kick(playerid);
				return 1;
			}
		}
	}
	ResetPlayerWeapons(playerid);
	#if defined ADMG_OnPlayerDeath
		ADMG::OnPlayerDeath(playerid,killerid,reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath ADMG::OnPlayerDeath
#if defined ADMG_OnPlayerDeath
	forward ADMG::OnPlayerDeath(playerid,killerid,reason);
#endif


//Hook: OnPlayerSpawn
public OnPlayerSpawn(playerid){
	SetPlayerHealth(playerid,100.0);
	SetPlayerArmour(playerid,0.0);
	ShowPlayerProgressBar(playerid,ADMG::ProgressBar[playerid][0]);
	#if defined ADMG_OnPlayerSpawn
		ADMG::OnPlayerSpawn(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn ADMG::OnPlayerSpawn
#if defined ADMG_OnPlayerSpawn
	forward ADMG::OnPlayerSpawn(playerid);
#endif

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	SetPlayerHealth(playerid,100.0);
	SetPlayerArmour(playerid,0.0);
	SetPlayerMoney(playerid,0);
	SetPlayerScore(playerid,0);
	ResetPlayerWeapons(playerid);
	
	ADMG::ProgressBar[playerid][0] = CreatePlayerProgressBar(playerid,548.5,57.5+10.5,61.0,5.0,BAR_COLOR_HEALTH,MAX_PLAYER_HEALTH);
	ADMG::ProgressBar[playerid][1] = CreatePlayerProgressBar(playerid,548.5,57.5-10.7,61.0,5.0,BAR_COLOR_ARMOUR,MAX_PLAYER_ARMOUR);
	HidePlayerProgressBar(playerid,ADMG::ProgressBar[playerid][0]);
	HidePlayerProgressBar(playerid,ADMG::ProgressBar[playerid][1]);
	
	#if defined ADMG_OnPlayerConnect
		ADMG::OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect ADMG::OnPlayerConnect
#if defined ADMG_OnPlayerConnect
	forward ADMG::OnPlayerConnect(playerid);
#endif

//Hook: OnPlayerDisconnect
public OnPlayerDisconnect(playerid,reason){
	ADMG::health[playerid] = 0.0;
	ADMG::armour[playerid] = 0.0;
	ADMG::score[playerid] = 0;
	ADMG::money[playerid] = 0;
	for(new slot = 0; slot < 12; slot++){
		ADMG::WeaponID[playerid][slot] = 0;
		ADMG::WeaponAmmo[playerid][slot] = 0;
	}
	DestroyPlayerProgressBar(playerid,ADMG::ProgressBar[playerid][0]);
	DestroyPlayerProgressBar(playerid,ADMG::ProgressBar[playerid][1]);
	#if defined ADMG_OnPlayerDisconnect
		ADMG::OnPlayerDisconnect(playerid,reason);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect ADMG::OnPlayerDisconnect
#if defined ADMG_OnPlayerDisconnect
	forward ADMG::OnPlayerDisconnect(playerid,reason);
#endif

//EOF