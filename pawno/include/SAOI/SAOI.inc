/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                           )(   San Andreas Object Image Loader   )(                                            *
 *                                                                                                                                *
 * Copyright © 2017 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SAOI/tree/master/include                                                              *
 * Publication: http://forum.sa-mp.com/showthread.php?t=618429                                                                    *
 *                                                                                                                                *
 * Plugins: Streamer, SScanf                                                                                                      *
 * Modules: None                                                                                                                  *
 *                                                                                                                                *
 * File Version: 2.0.0                                                                                                            *
 * SA:MP Version: 0.3.7                                                                                                           *
 * Streamer Version: 2.8.2                                                                                                        *
 * SScanf Version: 2.8.2                                                                                                          *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * SAOI::CreateFile(const name[],author[],version[],description[] = "");                                                          *
 * SAOI::GetFileHeader(const name[],author[],version[],description[]);                                                            *
 * SAOI::LoadObjectImage(const name[],bool:save_logs,bool:fast_boot); //save_logs = true, fast_boot = false                       *
 * SAOI::UnloadObjectImage(index);                                                                                                *
 * SAOI::IsFileLoaded(const name[],&index=INVALID_SAOI_FILE);                                                                     *
 * SAOI::CopyHeader(const input[],const output[]);                                                                                *
 * SAOI::SaveDynamicObject(objectid,const name[]);                                                                                *
 * SAOI::SaveDynamic3DTextLabel(Text3D:textid,const name[]);                                                                      *
 * SAOI::SaveDynamicPickup(pickupid,const name[]);                                                                                *
 * SAOI::SaveDynamicMapIcon(iconid,const name[]);                                                                                 *
 * SAOI::SaveDynamicArea(areaid,const name[]);                                                                                    *
 * SAOI::SaveDynamicActor(actorid,const name[]);                                                                                  *
 * SAOI::SetBumperIP(const name[],server_ip[]);                                                                                   *
 * SAOI::SetBumperPort(const name[],server_port);                                                                                 *
 * SAOI::GetPositionFlag(index,&Float:x,&Float:y,&Float:z,&Float:angle,&virtualworld,&interior);                                  *
 * SAOI::SetPositionFlag(const name[],Float:x,Float:y,Float:z,Float:angle,virtualworld,interior);                                 *
 * SAOI::SaveRemoveBuilding(const name[],modelid,Float:x,Float:y,Float:z,Float:radius);                                           *
 * SAOI::SaveVehicle(const name[],vehicletype,Float:x,Float:y,Float:z,Float:rotation,color1,color2,respawn_delay,addsiren=0,      *
 *                       worldid=0,interiorid=0);                                                                                 *
 * SAOI::GetFileCreationDate(index,output[],max_dest = sizeof(output));                                                           *
 * SAOI::CountDynamicObject(index);                                                                                               *
 * SAOI::CountDynamic3DTextLabel(index);                                                                                          *
 * SAOI::CountDynamicPickup(index);                                                                                               *
 * SAOI::CountDynamicMapIcon(index);                                                                                              *
 * SAOI::CountDynamicArea(index);                                                                                                 *
 * SAOI::CountDynamicActor(index);                                                                                                *
 * SAOI::CountVehicle(index);                                                                                                     *
 * SAOI::CountMaterial(index);                                                                                                    *
 * SAOI::CountMaterialText(index);                                                                                                *
 * SAOI::CountRemoveBuilding(index);                                                                                              *
 * SAOI::CountColAndreasObject(index);                                                                                            *
 * SAOI::GetFileName(index);                                                                                                      *
 * SAOI::GetLoadTime(index);                                                                                                      *
 * SAOI::GetActiveTime(index);                                                                                                    *
 * SAOI::GetFileSize(index);                                                                                                      *
 * SAOI::CountFileLoaded();                                                                                                       *
 * SAOI::CountAllElementsByIndex(index);                                                                                          *
 * SAOI::CountAllElements();                                                                                                      *
 * SAOI::SetEOF(const name[]);                                                                                                    *
 * SAOI::IsPositionFlagSet(index);                                                                                                *
 * SAOI::ToggleVisibleItems(const name[],playerid,type,toggle);                                                                   *
 *                                                                                                                                *
 * Extended Functions:                                                                                                            *
 * SAOI::GetFreeID();                                                                                                             *
 * SAOI::IsLoaded(index);                                                                                                         *
 * SAOI::IsStatic(index);                                                                                                         *
 * SAOI::IsReadOnly(index);                                                                                                       *
 * SAOI::GetFreeRemoveBuildingID();                                                                                               *
 * SAOI::RemoveBuilding(index,modelid,Float:x,Float:y,Float:z,Float:radius);                                                      *
 * SAOI::GetRemoveBuilding(remove_id,&index,&modelid,&Float:x,&Float:y,&Float:z,&Float:radius);                                   *
 * SAOI::DropRemoveBuildings(index);                                                                                              *
 * SAOI::CleanupElements(index);                                                                                                  *
 * SAOI::RemoveBuildingsForPlayer(playerid);                                                                                      *
 * SAOI::UpdateBuildingsForPlayer(playerid,index);                                                                                *
 * SAOI::CountRemovedBuildings();                                                                                                 *
 * SAOI::GetMemoryLoaded();                                                                                                       *
 * SAOI::GetErrorName(index,error_name[],maxdest = sizeof(error_name));                                                           *
 *                                                                                                                                *
 * Callbacks:                                                                                                                     *
 * SAOI::OnRemovedBuildings(playerid,buildings);                                                                                  *
 * SAOI::OnVehicleDestroyed(vehicleid);                                                                                           *
 * SAOI::OnVehicleCreated(vehicleid);                                                                                             *
 *                                                                                                                                *
 **********************************************************************************************************************************/

/*
//Check Version SAOI.inc
#if !defined _SAOI_LOADER
	#error You need SAOI.inc v2.0.0
#elseif !defined SAOI_LOADER_VERSION
	#error Update you SAOI.inc to v2.0.0
#elseif (SAOI_LOADER_VERSION < 20000)
	#error Update you SAOI.inc to v2.0.0
#endif
*/

#if (!defined GetPlayerPoolSize || !defined GetSVarInt)
	#error [ADM] This include requires SA:MP version 0.3.7 (github.com/AbyssMorgan/SA-MP/blob/master/samp/include)
#endif

#if ((!defined Streamer_AppendArrayData) || (!defined INVALID_STREAMER_ID) || (!defined STREAMER_TYPE_ACTOR))
	#error [ADM] You need Streamer v2.9.1 (github.com/samp-incognito/samp-streamer-plugin/releases)
#endif

#if !defined sscanf
	#error [ADM] You need SScanf v2.8.2 (github.com/AbyssMorgan/SA-MP/tree/master/plugins)
#endif

#if defined _streamer_spec
	#if !defined DISABLE_STREAMER_SPEC_FIXES
		#error [ADM] Invalid mechanism StreamerFunction.inc:DestroyFix (Use #define DISABLE_STREAMER_SPEC_FIXES before StreamerFunction.inc)
	#endif
#endif

#if defined _SAOI_LOADER
	#endinput
#endif
#define _SAOI_LOADER

#define SAOI_LOADER_VERSION 				(20000)			//a.b[c] 10000*a+100*b+c

#define SAOI_HEADER_KEY						"SAOI 1.1 ADM"	//You can never change !!!

#define INVALID_SAOI_FILE					(0)				//You can never change !!!
#define SAOI_EXTRA_ID_OFFSET				(1000000)		//You can never change !!!

#define MAX_SAOI_FILE_SIZE					(0x4000000)		//64 MB
#define MAX_SAOI_NAME_SIZE					(64)
#define MAX_SAOI_ERROR_NAME					(80)

#define MAX_SAOI_AUTHOR_SIZE 				(32)			//Max Value: 255 (auto resize header, compatible with all version) 
#define MAX_SAOI_VERSION_SIZE 				(32)			//Max Value: 255 (auto resize header, compatible with all version)
#define MAX_SAOI_DESCRIPTION_SIZE 			(128)			//Max Value: 255 (auto resize header, compatible with all version)

#define MAX_FONT_NAME 						(32)			//Max Value: 255 (These limits can be changed according to the San Andreas)
#define MAX_TXD_NAME						(32)			//Max Value: 255 (These limits can be changed according to the San Andreas)
#define MAX_TEXTURE_NAME					(32)			//Max Value: 255 (These limits can be changed according to the San Andreas)
#define MAX_TEXT_NAME						(2048)			//Max Value: 65535 (These limits can be changed according to the San Andreas)

#if !defined MAX_SAOI_FILE
	#define MAX_SAOI_FILE					(2001)			//more ? why not
#endif

#define SAOI_ERROR_UNEXEC					(0)				//function unexecutable
#define SAOI_ERROR_SUCCESS					(-1)			//success
#define SAOI_ERROR_INPUT_NOT_EXIST			(-2)			//input file not exist
#define SAOI_ERROR_OUTPUT_NOT_EXIST			(-3)			//output file not exist
#define SAOI_ERROR_INPUT_EXIST				(-4)			//input file exist
#define SAOI_ERROR_OUTPUT_EXIST				(-5)			//output file exist
#define SAOI_ERROR_INPUT_NOT_OPEN			(-6)			//error open input file
#define SAOI_ERROR_OUTPUT_NOT_OPEN			(-7)			//error open output file
#define SAOI_ERROR_FILE_SIZE				(-8)			//invalid file size
#define SAOI_ERROR_INVALID_OBJECTID			(-9)			//invalid objectid
#define SAOI_ERROR_AUTHOR_SIZE				(-10)			//invalid author size
#define SAOI_ERROR_VERSION_SIZE				(-11)			//invalid version size
#define SAOI_ERROR_DESCRIPTION_SIZE			(-12)			//invalid description size
#define SAOI_ERROR_INVALID_HEADER			(-13)			//invalid header
#define SAOI_ERROR_INPUT_EXTENSION			(-14)			//invalid input extension
#define SAOI_ERROR_OUTPUT_EXTENSION			(-15)			//invalid output extension
#define SAOI_ERROR_NOT_ENOUGH_CAPACITY		(-16)			//not enough capacity, to load new file
#define SAOI_ERROR_INVALID_ARG_COUNT		(-17)			//number of arguments exceeds the specified arguments (error structure version)
#define SAOI_ERROR_INVALID_SERVER_IP		(-18)			//bumper: invalid server ip
#define SAOI_ERROR_INVALID_SERVER_PORT		(-19)			//bumper: invalid server port
#define SAOI_ERROR_MEMORY_BLOCKED			(-20)			//memory blocked
#define SAOI_ERROR_IS_LOADED				(-21)			//file is already loaded

#define ELEMENT_FLAG_ANTI_AREA				(0)
#define ELEMENT_FLAG_NO_CAMERA_COL			(1)
#define ELEMENT_FLAG_COLANDREAS				(2)
#define ELEMENT_FLAG_COLSTATIC				(3)

#define INVALID_REMOVE_BUILDING_ID			(-1)

#define SAOI_BUMPER_ACTOR					(99)
#define SAOI_BUMPER_3D_TEXT_LABEL			(100)
#define SAOI_BUMPER_PICKUP					(101)
#define SAOI_BUMPER_MAPICON					(104)
#define SAOI_BUMPER_VEHICLE					(109)
#define SAOI_BUMPER_AREA_CIRCLE				(110)
#define SAOI_BUMPER_AREA_CYLINDER			(111)
#define SAOI_BUMPER_AREA_SPHERE				(112)
#define SAOI_BUMPER_AREA_RECTANGLE			(113)
#define SAOI_BUMPER_AREA_CUBOID				(114)
#define SAOI_BUMPER_AREA_POLYGON			(115)

#define SAOI_BUMPER_IP						(201)
#define SAOI_BUMPER_PORT					(202)
#define SAOI_BUMPER_POS						(203)
#define SAOI_BUMPER_CREATED					(204)
#define SAOI_BUMPER_REMOVEBUILDING			(205)
#define SAOI_BUMPER_EOF						(255)

#define SAOI::								SAOI_

//BitFunctions.inc
#define SAOI_GetValueBit(%0,%1)				((%0) >>> (%1) & 0x01)
#define SAOI_SetValueBit(%0,%1,%2)			((%0) = (((%0) & ~(0x01 << (%1))) | ((0x01 << (%1))*(%2))))

#define SAOI_ExtractValue(%0,%1,%2,%3,%4)	((%1) = (((%0) & 0xFF000000) >>> 24),(%2) = (((%0) & 0x00FF0000) >>> 16),(%3) = (((%0) & 0x0000FF00) >>> 8),(%4) = ((%0) & 0x000000FF))
#define SAOI_ExtractFloat(%0,%1,%2,%3,%4)	((%1) = (((_:%0) & 0xFF000000) >>> 24),(%2) = (((_:%0) & 0x00FF0000) >>> 16),(%3) = (((_:%0) & 0x0000FF00) >>> 8),(%4) = ((_:%0) & 0x000000FF))

#define SAOI_MergeValue(%0,%1,%2,%3,%4)		((%0) = (((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))
#define SAOI_MergeFloat(%0,%1,%2,%3,%4)		((%0) = Float:(((%1) << 24) | ((%2) << 16) | ((%3) << 8) | (%4)))

#define SAOI_IntMod(%0)						(0xFF & (%0)+128)
#define SAOI_Comp(%0,%1)					(SAOI_IntMod(%0) != (%1))
#define SAOI_Foreach(%0)					for(new %0 = 1; %0 < MAX_SAOI_FILE; %0++)
#define SAOI_GetByteFloat(%0,%1)			SAOI_MergeFloat((%1),fgetchar((%0),0,false),fgetchar((%0),0,false),fgetchar((%0),0,false),fgetchar((%0),0,false))
#define SAOI_GetByteInteger(%0,%1)			SAOI_MergeValue((%1),fgetchar((%0),0,false),fgetchar((%0),0,false),fgetchar((%0),0,false),fgetchar((%0),0,false))

#define SAOI_Function::						stock
#define SAOI_Public::%0(%1)					forward %0(%1); public %0(%1)

#if !defined isnull
	#define isnull(%1) 						((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#if !defined MAX_POLYGON_POINTS
	#define MAX_POLYGON_POINTS 				(256)
#endif

#if (defined COLANDREAS)
	#define SAOI_ColAndreas
#endif

enum e_remove_building {
	SAOI::index,
	SAOI::modelid,
	Float:SAOI::X,
	Float:SAOI::Y,
	Float:SAOI::Z,
	Float:SAOI::R
};

enum e_saoi {
	bool:SAOI::status,
	SAOI::name[MAX_SAOI_NAME_SIZE],
	bool:SAOI::is_static,
	
	SAOI::cnt_object,
	SAOI::cnt_pickup,
	SAOI::cnt_3dtext,
	SAOI::cnt_mapicon,
	SAOI::cnt_area,
	SAOI::cnt_actor,
	SAOI::cnt_vehicle,
	
	SAOI::cnt_material,
	SAOI::cnt_materialtext,
	SAOI::cnt_removebuilding,
	
	SAOI::offset_object,
	SAOI::offset_pickup,
	SAOI::offset_3dtext,
	SAOI::offset_mapicon,
	SAOI::offset_area,
	SAOI::offset_actor,
	SAOI::offset_vehicle,
	
	#if defined SAOI_ColAndreas
		SAOI::cnt_caobject,
		SAOI::offset_caobject,
	#endif
	
	SAOI::load_time,
	SAOI::active_tick,
	SAOI::file_size,
	bool:SAOI::write_lock,
	
	Float:SAOI::X,
	Float:SAOI::Y,
	Float:SAOI::Z,
	Float:SAOI::A,
	SAOI::VW,
	SAOI::INT,
	
	SAOI::created[32]
};

new SAOIFile[MAX_SAOI_FILE][e_saoi],
	SAOI::Vehicles[MAX_VEHICLES],
	SAOIRemoveBuildings[MAX_OBJECTS][e_remove_building],
	SAOIRemoveUpperbound = INVALID_REMOVE_BUILDING_ID,
	bool:SAOIPlayerFirstSpawn[MAX_PLAYERS],
	bool:CRC_SAOIAccess = false;
	
forward SAOI_OnRemovedBuildings(playerid,buildings);
forward SAOI_OnVehicleDestroyed(vehicleid);
forward SAOI_OnVehicleCreated(vehicleid);

#define SAOI_IsStatic(%0) 					(SAOIFile[(%0)][SAOI::is_static])
#define SAOI_IsLoaded(%0) 					(SAOIFile[(%0)][SAOI::status])
#define SAOI_GetFileSize(%0)				(SAOIFile[(%0)][SAOI::file_size])
#define SAOI_GetActiveTime(%0)				(GetTickCount()-SAOIFile[(%0)][SAOI::active_tick])
#define SAOI_GetFileName(%0)				(SAOIFile[(%0)][SAOI::name])
#define SAOI_GetLoadTime(%0)				(SAOIFile[(%0)][SAOI::load_time])
#define SAOI_IsReadOnly(%0)					(SAOIFile[(%0)][SAOI::write_lock])
#define SAOI_CountDynamicObject(%0)			(SAOIFile[(%0)][SAOI::cnt_object])
#define SAOI_CountDynamicPickup(%0)			(SAOIFile[(%0)][SAOI::cnt_pickup])
#define SAOI_CountDynamic3DTextLabel(%0)	(SAOIFile[(%0)][SAOI::cnt_3dtext])
#define SAOI_CountDynamicActor(%0)			(SAOIFile[(%0)][SAOI::cnt_actor])
#define SAOI_CountDynamicMapIcon(%0)		(SAOIFile[(%0)][SAOI::cnt_mapicon])
#define SAOI_CountDynamicArea(%0)			(SAOIFile[(%0)][SAOI::cnt_area])
#define SAOI_CountVehicle(%0)				(SAOIFile[(%0)][SAOI::cnt_vehicle])
#define SAOI_CountMaterial(%0)				(SAOIFile[(%0)][SAOI::cnt_material])
#define SAOI_CountMaterialText(%0)			(SAOIFile[(%0)][SAOI::cnt_materialtext])
#define SAOI_CountRemoveBuilding(%0)		(SAOIFile[(%0)][SAOI::cnt_removebuilding])

#if defined SAOI_ColAndreas
	#define SAOI_CountColAndreasObject(%0)	(SAOIFile[(%0)][SAOI::cnt_caobject])
#endif

SAOI::Function:: SAOI::GetErrorName(index,error_name[],maxdest = sizeof(error_name)){
	switch(index){
		case SAOI_ERROR_UNEXEC: 				format(error_name,maxdest,"Error function unexecutable");
		case SAOI_ERROR_SUCCESS:				format(error_name,maxdest,"Success");
		case SAOI_ERROR_INPUT_NOT_EXIST: 		format(error_name,maxdest,"Error input file not exist");
		case SAOI_ERROR_OUTPUT_NOT_EXIST: 		format(error_name,maxdest,"Error output file not exist");
		case SAOI_ERROR_INPUT_EXIST: 			format(error_name,maxdest,"Error input file exist");
		case SAOI_ERROR_OUTPUT_EXIST:		 	format(error_name,maxdest,"Error output file exist");
		case SAOI_ERROR_INPUT_NOT_OPEN: 		format(error_name,maxdest,"Error open input file");
		case SAOI_ERROR_OUTPUT_NOT_OPEN: 		format(error_name,maxdest,"Error open output file");
		case SAOI_ERROR_FILE_SIZE: 				format(error_name,maxdest,"Error invalid file size");
		case SAOI_ERROR_INVALID_OBJECTID:	 	format(error_name,maxdest,"Error invalid objectid");
		case SAOI_ERROR_AUTHOR_SIZE: 			format(error_name,maxdest,"Error invalid author size");
		case SAOI_ERROR_VERSION_SIZE: 			format(error_name,maxdest,"Error invalid version size");
		case SAOI_ERROR_DESCRIPTION_SIZE:	 	format(error_name,maxdest,"Error invalid description size");
		case SAOI_ERROR_INVALID_HEADER: 		format(error_name,maxdest,"Error invalid header");
		case SAOI_ERROR_INPUT_EXTENSION: 		format(error_name,maxdest,"Error invalid input extension");
		case SAOI_ERROR_OUTPUT_EXTENSION: 		format(error_name,maxdest,"Error invalid output extension");
		case SAOI_ERROR_NOT_ENOUGH_CAPACITY: 	format(error_name,maxdest,"Error not enough capacity, to load new file");
		case SAOI_ERROR_INVALID_ARG_COUNT: 		format(error_name,maxdest,"Error number of arguments exceeds the specified arguments");
		case SAOI_ERROR_INVALID_SERVER_IP:		format(error_name,maxdest,"Error invalid server ip");
		case SAOI_ERROR_INVALID_SERVER_PORT:	format(error_name,maxdest,"Error invalid server port");
		case SAOI_ERROR_MEMORY_BLOCKED:			format(error_name,maxdest,"Error memory blocked");
		case SAOI_ERROR_IS_LOADED:				format(error_name,maxdest,"Error file is already loaded");
	}
}

SAOI::Function:: SAOI::Construct(){
	new SAOI::data[e_saoi];
	#if defined SAOI_ColAndreas
		SAOI::data[SAOI::offset_caobject] = -1;
	#endif
	return SAOI::data;
}

SAOI::Function:: SAOI::CountAllElementsByIndex(index){
	new items = 0;
	items += SAOI::CountDynamicObject(index);
	items += SAOI::CountDynamicPickup(index);
	items += SAOI::CountDynamic3DTextLabel(index);
	items += SAOI::CountDynamicMapIcon(index);
	items += SAOI::CountDynamicArea(index);
	items += SAOI::CountDynamicActor(index);
	items += SAOI::CountVehicle(index);
	items += SAOI::CountMaterial(index);
	items += SAOI::CountMaterialText(index);
	items += SAOI::CountRemoveBuilding(index);
	#if defined SAOI_ColAndreas
		items += SAOI::CountColAndreasObject(index);
	#endif
	return items;
}

SAOI::Function:: SAOI::CountAllElements(){
	new items = 0;
	SAOI::Foreach(i){
		if(SAOI::IsLoaded(i)){
			items += SAOI::CountAllElementsByIndex(i);
		}
	}
	return items;
}

SAOI::Function:: SAOI::CountRemovedBuildings(){
	if(!CRC_SAOIAccess) return 0;
	new cnt = 0;
	for(new i = SAOIRemoveUpperbound; i >= 0; i--){
		if(SAOIRemoveBuildings[i][SAOI::modelid] != 0){
			cnt++;
		}
	}
	return cnt;
}

SAOI::Function:: SAOI::GetFreeRemoveBuildingID(){
	if(!CRC_SAOIAccess) return INVALID_REMOVE_BUILDING_ID;
	for(new i = 0; i < MAX_OBJECTS; i++){
		if(SAOIRemoveBuildings[i][SAOI::modelid] == 0){
			if(i > SAOIRemoveUpperbound) SAOIRemoveUpperbound = i;
			return i;
		}
	}
	return INVALID_REMOVE_BUILDING_ID;
}

SAOI::Function:: SAOI::GetRemoveBuilding(remove_id,&index,&modelid,&Float:x,&Float:y,&Float:z,&Float:radius){
	if(!CRC_SAOIAccess) return 0;
	if(SAOIRemoveBuildings[remove_id][SAOI::modelid] == 0) return 0;
	modelid = SAOIRemoveBuildings[remove_id][SAOI::modelid];
	x = SAOIRemoveBuildings[remove_id][SAOI::X];
	y = SAOIRemoveBuildings[remove_id][SAOI::Y];
	z = SAOIRemoveBuildings[remove_id][SAOI::Z];
	radius = SAOIRemoveBuildings[remove_id][SAOI::R];
	index = SAOIRemoveBuildings[remove_id][SAOI::index];
	return 1;
}

SAOI::Function:: SAOI::RemoveBuilding(index,modelid,Float:x,Float:y,Float:z,Float:radius){
	if(!CRC_SAOIAccess) return INVALID_REMOVE_BUILDING_ID;
	if(!SAOI::IsLoaded(index)) return INVALID_REMOVE_BUILDING_ID;
	new remove_id = SAOI::GetFreeRemoveBuildingID();
	if(remove_id == INVALID_REMOVE_BUILDING_ID) return INVALID_REMOVE_BUILDING_ID;
	SAOIRemoveBuildings[remove_id][SAOI::modelid] = modelid;
	SAOIRemoveBuildings[remove_id][SAOI::X] = x;
	SAOIRemoveBuildings[remove_id][SAOI::Y] = y;
	SAOIRemoveBuildings[remove_id][SAOI::Z] = z;
	SAOIRemoveBuildings[remove_id][SAOI::R] = radius;
	SAOIRemoveBuildings[remove_id][SAOI::index] = index;
	return remove_id;
}

SAOI::Function:: SAOI::DropRemoveBuildings(index){
	if(!CRC_SAOIAccess) return 0;
	if(!SAOI::IsLoaded(index)) return 0;
	new cnt = 0;
	for(new i = SAOIRemoveUpperbound; i >= 0; i--){
		if(SAOIRemoveBuildings[i][SAOI::index] == index){
			SAOIRemoveBuildings[i][SAOI::modelid] = 0;
			SAOIRemoveBuildings[i][SAOI::X] = 0.0;
			SAOIRemoveBuildings[i][SAOI::Y] = 0.0;
			SAOIRemoveBuildings[i][SAOI::Z] = 0.0;
			SAOIRemoveBuildings[i][SAOI::R] = 0.0;
			SAOIRemoveBuildings[i][SAOI::index] = INVALID_SAOI_FILE;
			if(i == SAOIRemoveUpperbound) SAOIRemoveUpperbound--;
			cnt++;
		}
	}
	return cnt;
}

SAOI::Function:: SAOI::RemoveBuildingsForPlayer(playerid){
	if(!CRC_SAOIAccess) return 0;
	new cnt = 0;
	for(new i = SAOIRemoveUpperbound; i >= 0; i--){
		if(SAOIRemoveBuildings[i][SAOI::modelid] != 0){
			RemoveBuildingForPlayer(playerid,SAOIRemoveBuildings[i][SAOI::modelid],SAOIRemoveBuildings[i][SAOI::X],SAOIRemoveBuildings[i][SAOI::Y],SAOIRemoveBuildings[i][SAOI::Z],SAOIRemoveBuildings[i][SAOI::R]);
			cnt++;
		}
	}
	return cnt;
}

SAOI::Function:: SAOI::UpdateBuildingsForPlayer(playerid,index){
	if(!CRC_SAOIAccess) return 0;
	if(!SAOI::IsLoaded(index)) return 0;
	new cnt = 0;
	for(new i = SAOIRemoveUpperbound; i >= 0; i--){
		if(SAOIRemoveBuildings[i][SAOI::modelid] != 0 && SAOIRemoveBuildings[i][SAOI::index] == index){
			RemoveBuildingForPlayer(playerid,SAOIRemoveBuildings[i][SAOI::modelid],SAOIRemoveBuildings[i][SAOI::X],SAOIRemoveBuildings[i][SAOI::Y],SAOIRemoveBuildings[i][SAOI::Z],SAOIRemoveBuildings[i][SAOI::R]);
			cnt++;
		}
	}
	return cnt;
}

SAOI::Function:: SAOI::GetFreeID(){
	if(!CRC_SAOIAccess) return INVALID_SAOI_FILE;
	SAOI::Foreach(i){
		if(!SAOI::IsLoaded(i)) return i;
	}
	return INVALID_SAOI_FILE;
}

SAOI::Function:: SAOI::CountFileLoaded(){
	if(!CRC_SAOIAccess) return 0;
	new cnt = 0;
	SAOI::Foreach(i){
		if(SAOI::IsLoaded(i)) cnt++;
	}
	return cnt;
}

SAOI::Function:: SAOI::GetMemoryLoaded(){
	if(!CRC_SAOIAccess) return 0;
	new cnt = 0;
	SAOI::Foreach(i){
		if(SAOI::IsLoaded(i)) cnt += SAOIFile[i][SAOI::file_size];
	}
	return cnt;
}

SAOI::Function:: SAOI::SetEOF(const name[]){
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	fputchar(outf,SAOI_BUMPER_EOF,false);
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::GetFileCreationDate(index,output[],max_dest = sizeof(output)){
	if(!CRC_SAOIAccess) return false;
	if(!SAOI::IsLoaded(index)) return false;
	format(output,max_dest,"%s",SAOIFile[index][SAOI::created]);
	return true;
}

SAOI::Function:: SAOI::GetPositionFlag(index,&Float:x,&Float:y,&Float:z,&Float:angle,&virtualworld,&interior){
	if(!CRC_SAOIAccess) return false;
	if(!SAOI::IsLoaded(index)) return false;
	x = SAOIFile[index][SAOI::X];
	y = SAOIFile[index][SAOI::Y];
	z = SAOIFile[index][SAOI::Z];
	angle = SAOIFile[index][SAOI::A];
	virtualworld = SAOIFile[index][SAOI::VW];
	interior = SAOIFile[index][SAOI::INT];
	return true;
}

SAOI::Function:: SAOI::IsPositionFlagSet(index){
	if(!CRC_SAOIAccess) return false;
	if(!SAOI::IsLoaded(index)) return false;
	if(SAOIFile[index][SAOI::X] == 0.0 && SAOIFile[index][SAOI::Y] == 0.0 && SAOIFile[index][SAOI::Z] == 0.0 && SAOIFile[index][SAOI::A] == 0.0) return false;
	return true;
}

SAOI::Function:: SAOI::SetPositionFlag(const name[],Float:x,Float:y,Float:z,Float:angle,virtualworld,interior){
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append), int1, int2, int3, int4;
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	fputchar(outf,SAOI_BUMPER_POS,false);
	
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(angle,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractValue(virtualworld,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);

	SAOI::ExtractValue(interior,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveRemoveBuilding(const name[],modelid,Float:x,Float:y,Float:z,Float:radius){
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append), int1, int2, int3, int4;
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	fputchar(outf,SAOI_BUMPER_REMOVEBUILDING,false);
	
	SAOI::ExtractValue(modelid,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);

	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(radius,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::IsFileLoaded(const name[],&index=INVALID_SAOI_FILE){
	if(!CRC_SAOIAccess) return false;
	new tmp_saoi_name[MAX_SAOI_NAME_SIZE];
	format(tmp_saoi_name,MAX_SAOI_NAME_SIZE,"%s",name);
	for(new i = strlen(tmp_saoi_name)-1; i >= 0; i--){
		if(tmp_saoi_name[i] == '.'){
			tmp_saoi_name[i] = EOS;
			break;
		}
	}
	SAOI::Foreach(i){
		if(SAOI::IsLoaded(i)){
			if(!strcmp(tmp_saoi_name,SAOIFile[i][SAOI::name],true)){
				index = i;
				return true;
			}
		}
	}
	return false;
}

SAOI::Function:: SAOI::CreateFile(const name[],author[],version[],description[] = ""){
	if(fexist(name)) return SAOI_ERROR_OUTPUT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_readwrite);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new year,month,day,hour,minute,second;
	getdate(year,month,day);
	gettime(hour,minute,second);
	
	fwrite(outf,SAOI_HEADER_KEY);
	//Create Header
	new author_size = strlen(author),
		version_size = strlen(version),
		description_size = strlen(description);
	
	if(author_size > MAX_SAOI_AUTHOR_SIZE){
		fclose(outf);
		return SAOI_ERROR_AUTHOR_SIZE;
	}
	if(version_size > MAX_SAOI_VERSION_SIZE ){
		fclose(outf);
		return SAOI_ERROR_VERSION_SIZE;
	}
	if(description_size > MAX_SAOI_DESCRIPTION_SIZE){
		fclose(outf);
		return SAOI_ERROR_DESCRIPTION_SIZE;
	}
	
	new key[32];
	for(new i = 0; i < 32; i++){
		key[i] = random(255)+1;
	}
	
	new step;
	
	step = 0;
	for(new i = 0; i < author_size; i++){
		author[i] = ((author[i]+key[step]) & 0xFF);
		step++;
		if(step >= 32) step = 0;
	}
	fputchar(outf,author_size,false);
	for(new i = 0; i < author_size; i++){
		fputchar(outf,author[i],false);
	}
	
	step = 0;
	for(new i = 0; i < version_size; i++){
		version[i] = ((version[i]+key[step]) & 0xFF);
		step++;
		if(step >= 32) step = 0;
	}
	fputchar(outf,version_size,false);
	for(new i = 0; i < version_size; i++){
		fputchar(outf,version[i],false);
	}
	
	step = 0;
	for(new i = 0; i < description_size; i++){
		description[i] = ((description[i]+key[step]) & 0xFF);
		step++;
		if(step >= 32) step = 0;
	}
	fputchar(outf,description_size,false);
	for(new i = 0; i < description_size; i++){
		fputchar(outf,description[i],false);
	}
	
	for(new i = 0; i < 32; i++){
		fputchar(outf,((256-key[i]) & 0xFF),false);
	}

	fputchar(outf,SAOI_BUMPER_CREATED,false);
	
	new int1, int2, int3, int4;
	SAOI::ExtractValue(year,int1,int2,int3,int4);
	fputchar(outf,SAOI::IntMod(int3),false);
	fputchar(outf,SAOI::IntMod(int4),false);
	
	fputchar(outf,SAOI::IntMod(month),false);
	fputchar(outf,SAOI::IntMod(day),false);
	fputchar(outf,SAOI::IntMod(hour),false);
	fputchar(outf,SAOI::IntMod(minute),false);
	fputchar(outf,SAOI::IntMod(second),false);
	
	#pragma unused int1,int2
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveDynamicObject(objectid,const name[]){
	if(!IsValidDynamicObject(objectid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid, Float:streamdistance, Float:drawdistance, areaid, priority,
		arg_count = 14, material_used = 0, material_text_used = 0, element_flag;
	
	//Get Object Info
	modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MODEL_ID);
	GetDynamicObjectPos(objectid,x,y,z);
	GetDynamicObjectRot(objectid,rx,ry,rz);
	worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_WORLD_ID);
	interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_INTERIOR_ID);
	
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_STREAM_DISTANCE,streamdistance);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_DRAW_DISTANCE,drawdistance);
	
	areaid = Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_AREA_ID);
	priority = Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_PRIORITY);
	
	if(Streamer_IsToggleItemInvAreas(STREAMER_TYPE_OBJECT,objectid)){
		SAOI::SetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA,1);
	}
	if(GetDynamicObjectNoCameraCol(objectid)){
		SAOI::SetValueBit(element_flag,ELEMENT_FLAG_NO_CAMERA_COL,1);
	}
	
	element_flag |= (Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID) & 0xFF);
	
	//Count Arg
	for(new i = arg_count; i > 7; i--){
		switch(i){
			case 14: {
				if(element_flag == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 13: {
				if(priority == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 12: {
				if(areaid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 11: {
				if(drawdistance == STREAMER_OBJECT_DD){
					arg_count--;
				} else {
					break;
				}
			}
			case 10: {
				if(streamdistance == STREAMER_OBJECT_SD){
					arg_count--;
				} else {
					break;
				}
			}
			case 9: {
				if(interiorid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 8: {
				if(worldid == -1){
					arg_count--;
				} else {
					break;
				}
			}
		}
	}
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,arg_count,false);
	
	//Save Object Info
	SAOI::ExtractValue(modelid,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(rx,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(ry,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(rz,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	if(arg_count >= 8){
		SAOI::ExtractValue(worldid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 9){
		SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 10){
		SAOI::ExtractFloat(streamdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 11){
		SAOI::ExtractFloat(drawdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 12){
		SAOI::ExtractValue(areaid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 13){
		SAOI::ExtractValue(priority,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	if(arg_count >= 14){
		SAOI::ExtractValue(element_flag,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	
	
	//Get and Save Object Material
	for(new i = 0; i < 16; i++){
		if(IsDynamicObjectMaterialUsed(objectid,i)){
			SAOI::SetValueBit(material_used,i,1);
		}
	}
	
	SAOI::ExtractValue(material_used,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	new mid, txdname[MAX_TXD_NAME], texturename[MAX_TEXTURE_NAME], materialcolor;
	for(new i = 0; i < 16; i++){
		if(SAOI::GetValueBit(material_used,i) == 1){
			GetDynamicObjectMaterial(objectid,i,mid,txdname,texturename,materialcolor);
			
			SAOI::ExtractValue(mid,int1,int2,int3,int4);
			fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			fputchar(outf,strlen(txdname),false);
			for(new k = 0, l = strlen(txdname); k < l; k++){
				fputchar(outf,SAOI::IntMod(txdname[k]),false);
			}
			
			fputchar(outf,strlen(texturename),false);
			for(new k = 0, l = strlen(texturename); k < l; k++){
				fputchar(outf,SAOI::IntMod(texturename[k]),false);
			}
			
			SAOI::ExtractValue(materialcolor,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
		}
	}
	
	//Get and Save Object Material Text
	for(new i = 0; i < 16; i++){
		if(IsDynamicObjectMaterialTextUsed(objectid,i)){
			SAOI::SetValueBit(material_text_used,i,1);
		}
	}
	
	SAOI::ExtractValue(material_text_used,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	new text[MAX_TEXT_NAME], materialsize, fontface[MAX_FONT_NAME], fontsize, bold, fontcolor, backcolor, textalignment;
	for(new i = 0; i < 16; i++){
		if(SAOI::GetValueBit(material_text_used,i) == 1){
			GetDynamicObjectMaterialText(objectid,i,text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
			
			new len = strlen(text);
			SAOI::ExtractValue(len,int1,int2,int3,int4);
			fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			for(new k = 0, l = strlen(text); k < l; k++){
				fputchar(outf,SAOI::IntMod(text[k]),false);
			}
			
			fputchar(outf,materialsize,false);
			
			fputchar(outf,strlen(fontface),false);
			for(new k = 0, l = strlen(fontface); k < l; k++){
				fputchar(outf,SAOI::IntMod(fontface[k]),false);
			}
			
			fputchar(outf,fontsize,false);
			
			fputchar(outf,bold,false);
			
			SAOI::ExtractValue(fontcolor,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractValue(backcolor,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			fputchar(outf,textalignment,false);
			
		}
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveDynamicPickup(pickupid,const name[]){
	if(!IsValidDynamicPickup(pickupid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new modelid, Float:x, Float:y, Float:z, type, worldid, interiorid, Float:streamdistance, areaid, priority,
		arg_count = 11, element_flag;
	
	//Get Pickup Info
	modelid = Streamer_GetIntData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_MODEL_ID);
	
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_Z,z);
	
	worldid = Streamer_GetIntData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_WORLD_ID);
	interiorid = Streamer_GetIntData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_INTERIOR_ID);
	
	Streamer_GetFloatData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_STREAM_DISTANCE,streamdistance);
	type = Streamer_GetIntData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_TYPE);
	
	areaid = Streamer_GetIntData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_AREA_ID);
	priority = Streamer_GetIntData(STREAMER_TYPE_PICKUP,pickupid,E_STREAMER_PRIORITY);
	
	if(Streamer_IsToggleItemInvAreas(STREAMER_TYPE_PICKUP,pickupid)){
		SAOI::SetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA,1);
	}
	
	//Count Arg
	for(new i = arg_count; i > 5; i--){
		switch(i){
			case 11: {
				if(element_flag == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 10: {
				if(priority == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 9: {
				if(areaid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 8: {
				if(streamdistance == STREAMER_OBJECT_SD){
					arg_count--;
				} else {
					break;
				}
			}
			case 7: {
				if(interiorid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 6: {
				if(worldid == -1){
					arg_count--;
				} else {
					break;
				}
			}
		}
	}
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,SAOI_BUMPER_PICKUP,false);
	fputchar(outf,arg_count,false);
	
	//Save Pickup Info
	SAOI::ExtractValue(modelid,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractValue(type,int1,int2,int3,int4);
	fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	if(arg_count >= 6){
		SAOI::ExtractValue(worldid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 7){
		SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 8){
		SAOI::ExtractFloat(streamdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 9){
		SAOI::ExtractValue(areaid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 10){
		SAOI::ExtractValue(priority,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	if(arg_count >= 11){
		SAOI::ExtractValue(element_flag,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveDynamic3DTextLabel(Text3D:textid,const name[]){
	if(!IsValidDynamic3DTextLabel(textid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new Float:x, Float:y, Float:z, testlos, worldid, interiorid, Float:streamdistance, areaid, priority,
		arg_count = 14, element_flag, textsize, text[2048], color, Float:drawdistance;
	
	//Get 3DTextLabel Info
	GetDynamic3DTextLabelText(textid,text,sizeof(text));
	textsize = strlen(text);
	
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_Z,z);
	
	worldid = Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_WORLD_ID);
	interiorid = Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_INTERIOR_ID);
	
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_STREAM_DISTANCE,streamdistance);
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_DRAW_DISTANCE,drawdistance);
	testlos = Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_TEST_LOS);
	color = Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_COLOR);
	
	areaid = Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_AREA_ID);
	priority = Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,textid,E_STREAMER_PRIORITY);
	
	if(Streamer_IsToggleItemInvAreas(STREAMER_TYPE_3D_TEXT_LABEL,textid)){
		SAOI::SetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA,1);
	}
	
	//Count Arg
	for(new i = arg_count; i > 7; i--){
		switch(i){
			case 14: {
				if(element_flag == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 13: {
				if(priority == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 12: {
				if(areaid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 11: {
				if(streamdistance == STREAMER_OBJECT_SD){
					arg_count--;
				} else {
					break;
				}
			}
			case 10: {
				if(interiorid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 9: {
				if(worldid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 8: {
				if(testlos == 0){
					arg_count--;
				} else {
					break;
				}
			}
		}
	}
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,SAOI_BUMPER_3D_TEXT_LABEL,false);
	fputchar(outf,arg_count,false);
	
	//Save 3DTextLabel Info
	SAOI::ExtractValue(textsize,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	for(new k = 0; k < textsize; k++){
		fputchar(outf,SAOI::IntMod(text[k]),false);
	}
	
	SAOI::ExtractValue(color,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(drawdistance,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);

	if(arg_count >= 8){
		SAOI::ExtractValue(testlos,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	if(arg_count >= 9){
		SAOI::ExtractValue(worldid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 10){
		SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 11){
		SAOI::ExtractFloat(streamdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 12){
		SAOI::ExtractValue(areaid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 13){
		SAOI::ExtractValue(priority,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	if(arg_count >= 14){
		SAOI::ExtractValue(element_flag,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveDynamicMapIcon(iconid,const name[]){
	if(!IsValidDynamicMapIcon(iconid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new Float:x, Float:y, Float:z, type, worldid, interiorid, Float:streamdistance, areaid, priority,
		arg_count = 12, element_flag, color, style;
	
	//Get MapIcon Info
	Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_X,x);
	Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_Y,y);
	Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_Z,z);
	
	worldid = Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_WORLD_ID);
	interiorid = Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_INTERIOR_ID);
	
	Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_STREAM_DISTANCE,streamdistance);
	type = Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_TYPE);
	color = Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_COLOR);
	style = Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_STYLE);
	
	areaid = Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_AREA_ID);
	priority = Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,iconid,E_STREAMER_PRIORITY);
	
	if(Streamer_IsToggleItemInvAreas(STREAMER_TYPE_MAP_ICON,iconid)){
		SAOI::SetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA,1);
	}
	
	//Count Arg
	for(new i = arg_count; i > 5; i--){
		switch(i){
			case 12: {
				if(element_flag == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 11: {
				if(priority == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 10: {
				if(areaid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 9: {
				if(style == MAPICON_LOCAL){
					arg_count--;
				} else {
					break;
				}
			}
			case 8: {
				if(streamdistance == STREAMER_OBJECT_SD){
					arg_count--;
				} else {
					break;
				}
			}
			case 7: {
				if(interiorid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 6: {
				if(worldid == -1){
					arg_count--;
				} else {
					break;
				}
			}
		}
	}
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,SAOI_BUMPER_MAPICON,false);
	fputchar(outf,arg_count,false);
	
	//Save MapIcon Info
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractValue(type,int1,int2,int3,int4);
	fputchar(outf,int4,false);
	
	SAOI::ExtractValue(color,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	if(arg_count >= 6){
		SAOI::ExtractValue(worldid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 7){
		SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 8){
		SAOI::ExtractFloat(streamdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 9){
		SAOI::ExtractValue(style,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	if(arg_count >= 10){
		SAOI::ExtractValue(areaid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 11){
		SAOI::ExtractValue(priority,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	if(arg_count >= 12){
		SAOI::ExtractValue(element_flag,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveDynamicActor(actorid,const name[]){
	if(!IsValidDynamicActor(actorid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new Float:x, Float:y, Float:z, Float:z_angle, modelid, worldid, interiorid, Float:streamdistance, areaid, priority,
		arg_count = 13, element_flag, invulnerable = 0, Float:health;
	
	//Get Actor Info
	GetDynamicActorPos(actorid,x,y,z);
	GetDynamicActorFacingAngle(actorid,z_angle);
	
	modelid = Streamer_GetIntData(STREAMER_TYPE_ACTOR,actorid,E_STREAMER_MODEL_ID);
	worldid = GetDynamicActorVirtualWorld(actorid);
	interiorid = Streamer_GetIntData(STREAMER_TYPE_ACTOR,actorid,E_STREAMER_INTERIOR_ID);
	
	if(IsDynamicActorInvulnerable(actorid)) invulnerable = 1;
	
	Streamer_GetFloatData(STREAMER_TYPE_ACTOR,actorid,E_STREAMER_STREAM_DISTANCE,streamdistance);
	GetDynamicActorHealth(actorid,health);
	
	areaid = Streamer_GetIntData(STREAMER_TYPE_ACTOR,actorid,E_STREAMER_AREA_ID);
	priority = Streamer_GetIntData(STREAMER_TYPE_ACTOR,actorid,E_STREAMER_PRIORITY);
	
	if(Streamer_IsToggleItemInvAreas(STREAMER_TYPE_ACTOR,actorid)){
		SAOI::SetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA,1);
	}
	
	//Count Arg
	for(new i = arg_count; i > 5; i--){
		switch(i){
			case 13: {
				if(element_flag == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 12: {
				if(priority == 0){
					arg_count--;
				} else {
					break;
				}
			}
			case 11: {
				if(areaid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 10: {
				if(streamdistance == STREAMER_OBJECT_SD){
					arg_count--;
				} else {
					break;
				}
			}
			case 9: {
				if(interiorid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 8: {
				if(worldid == -1){
					arg_count--;
				} else {
					break;
				}
			}
			case 7: {
				if(health == 100.0){
					arg_count--;
				} else {
					break;
				}
			}
			case 6: {
				if(invulnerable == 1){
					arg_count--;
				} else {
					break;
				}
			}
		}
	}
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,SAOI_BUMPER_ACTOR,false);
	fputchar(outf,arg_count,false);
	
	//Save Actor Info
	SAOI::ExtractValue(modelid,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z_angle,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	if(arg_count >= 6){
		SAOI::ExtractValue(invulnerable,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	if(arg_count >= 7){
		SAOI::ExtractFloat(health,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 8){
		SAOI::ExtractValue(worldid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 9){
		SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 10){
		SAOI::ExtractFloat(streamdistance,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 11){
		SAOI::ExtractValue(areaid,int1,int2,int3,int4);
		fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	}
	if(arg_count >= 12){
		SAOI::ExtractValue(priority,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	if(arg_count >= 13){
		SAOI::ExtractValue(element_flag,int1,int2,int3,int4);
		fputchar(outf,int4,false);
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveDynamicArea(areaid,const name[]){
	if(!IsValidDynamicArea(areaid)) return SAOI_ERROR_INVALID_OBJECTID;
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	switch(Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_TYPE)){
		case STREAMER_AREA_TYPE_CIRCLE: {
			//Get Area Data
			new arg_count = 6, Float:x, Float:y, Float:size, worldid = -1, interiorid = -1;
			
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_SIZE,size);
	
			worldid = Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_WORLD_ID);
			interiorid = Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_INTERIOR_ID);
			
			//Count Arg
			for(new i = arg_count; i > 4; i--){
				switch(i){
					case 6: {
						if(interiorid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 5: {
						if(worldid == -1){
							arg_count--;
						} else {
							break;
						}
					}
				}
			}
			
			//Save Arg Count
			fputchar(outf,SAOI_BUMPER_AREA_CIRCLE,false);
			fputchar(outf,arg_count,false);
			
			//Save Area Info
			SAOI::ExtractValue(areaid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(x,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(y,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(size,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			if(arg_count >= 5){
				SAOI::ExtractValue(worldid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			if(arg_count >= 6){
				SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
		}
		case STREAMER_AREA_TYPE_CYLINDER: {
			//Get Area Data
			new arg_count = 8, Float:x, Float:y, Float:minz, Float:maxz, Float:size, worldid = -1, interiorid = -1;
			
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
			
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
			
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_SIZE,size);
	
			worldid = Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_WORLD_ID);
			interiorid = Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_INTERIOR_ID);
			
			//Count Arg
			for(new i = arg_count; i > 6; i--){
				switch(i){
					case 8: {
						if(interiorid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 7: {
						if(worldid == -1){
							arg_count--;
						} else {
							break;
						}
					}
				}
			}
			
			//Save Arg Count
			fputchar(outf,SAOI_BUMPER_AREA_CYLINDER,false);
			fputchar(outf,arg_count,false);
			
			//Save Area Info
			SAOI::ExtractValue(areaid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(x,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(y,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(minz,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(maxz,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(size,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			if(arg_count >= 7){
				SAOI::ExtractValue(worldid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			if(arg_count >= 8){
				SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
		}
		case STREAMER_AREA_TYPE_SPHERE: {
			//Get Area Data
			new arg_count = 7, Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1;
			
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_X,x);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Y,y);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_Z,z);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_SIZE,size);
	
			worldid = Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_WORLD_ID);
			interiorid = Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_INTERIOR_ID);
			
			//Count Arg
			for(new i = arg_count; i > 5; i--){
				switch(i){
					case 7: {
						if(interiorid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 6: {
						if(worldid == -1){
							arg_count--;
						} else {
							break;
						}
					}
				}
			}
			
			//Save Arg Count
			fputchar(outf,SAOI_BUMPER_AREA_SPHERE,false);
			fputchar(outf,arg_count,false);
			
			//Save Area Info
			SAOI::ExtractValue(areaid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(x,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(y,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(z,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(size,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			if(arg_count >= 6){
				SAOI::ExtractValue(worldid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			if(arg_count >= 7){
				SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
		}
		case STREAMER_AREA_TYPE_RECTANGLE: {
			//Get Area Data
			new arg_count = 7, Float:minx, Float:miny, Float:maxx, Float:maxy, worldid = -1, interiorid = -1;
			
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
	
			worldid = Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_WORLD_ID);
			interiorid = Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_INTERIOR_ID);
			
			//Count Arg
			for(new i = arg_count; i > 5; i--){
				switch(i){
					case 7: {
						if(interiorid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 6: {
						if(worldid == -1){
							arg_count--;
						} else {
							break;
						}
					}
				}
			}
			
			//Save Arg Count
			fputchar(outf,SAOI_BUMPER_AREA_RECTANGLE,false);
			fputchar(outf,arg_count,false);
			
			//Save Area Info
			SAOI::ExtractValue(areaid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(minx,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(miny,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(maxx,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(maxy,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			if(arg_count >= 6){
				SAOI::ExtractValue(worldid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			if(arg_count >= 7){
				SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
		}
		case STREAMER_AREA_TYPE_CUBOID: {
			//Get Area Data
			new arg_count = 9, Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worldid = -1, interiorid = -1;
			
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_X,minx);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Y,miny);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_X,maxx);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Y,maxy);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
	
			worldid = Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_WORLD_ID);
			interiorid = Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_INTERIOR_ID);
			
			//Count Arg
			for(new i = arg_count; i > 7; i--){
				switch(i){
					case 9: {
						if(interiorid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 8: {
						if(worldid == -1){
							arg_count--;
						} else {
							break;
						}
					}
				}
			}
			
			//Save Arg Count
			fputchar(outf,SAOI_BUMPER_AREA_CUBOID,false);
			fputchar(outf,arg_count,false);
			
			//Save Area Info
			SAOI::ExtractValue(areaid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(minx,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(miny,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(minz,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(maxx,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(maxy,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractFloat(maxz,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			if(arg_count >= 8){
				SAOI::ExtractValue(worldid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			if(arg_count >= 9){
				SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
		}
		case STREAMER_AREA_TYPE_POLYGON: {
			//Get Area Data
			new arg_count = 7, Float:minz = -FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY, worldid = -1, interiorid = -1, Float:Polygon_Points[MAX_POLYGON_POINTS*2], max_points;
			
			GetDynamicPolygonPoints(areaid,Polygon_Points,sizeof(Polygon_Points));
			max_points = GetDynamicPolygonNumberPoints(areaid) * 2;
			
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MIN_Z,minz);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,areaid,E_STREAMER_MAX_Z,maxz);
			
			worldid = Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_WORLD_ID);
			interiorid = Streamer_GetIntData(STREAMER_TYPE_AREA,areaid,E_STREAMER_INTERIOR_ID);
			
			//Count Arg
			for(new i = arg_count; i > 3; i--){
				switch(i){
					case 7: {
						if(interiorid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 6: {
						if(worldid == -1){
							arg_count--;
						} else {
							break;
						}
					}
					case 5: {
						if(maxz == FLOAT_INFINITY){
							arg_count--;
						} else {
							break;
						}
					}
					case 4: {
						if(minz == -FLOAT_INFINITY){
							arg_count--;
						} else {
							break;
						}
					}
				}
			}
			
			//Save Arg Count
			fputchar(outf,SAOI_BUMPER_AREA_POLYGON,false);
			fputchar(outf,arg_count,false);
			
			//Save Area Info
			SAOI::ExtractValue(areaid,int1,int2,int3,int4);
			fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			SAOI::ExtractValue(max_points,int1,int2,int3,int4);
			fputchar(outf,int3,false), fputchar(outf,int4,false);
			
			for(new k = 0; k < max_points; k++){
				SAOI::ExtractFloat(Polygon_Points[k],int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			
			if(arg_count >= 4){
				SAOI::ExtractFloat(minz,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			
			if(arg_count >= 5){
				SAOI::ExtractFloat(maxz,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			
			if(arg_count >= 6){
				SAOI::ExtractValue(worldid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
			if(arg_count >= 7){
				SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
				fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
			}
		}
	}
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SaveVehicle(const name[],vehicletype,Float:x,Float:y,Float:z,Float:rotation,color1,color2,respawn_delay,addsiren=0,worldid=0,interiorid=0){
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	if(color1 == -1) color1 = 0xFFFF;
	if(color2 == -1) color2 = 0xFFFF;
	
	//RAW Generator
	new int1, int2, int3, int4;
	
	//Save Arg Count
	fputchar(outf,SAOI_BUMPER_VEHICLE,false);

	//Save Vehicle Info
	SAOI::ExtractValue(vehicletype,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(x,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(y,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(z,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractFloat(rotation,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractValue(color1,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	SAOI::ExtractValue(color2,int1,int2,int3,int4);
	fputchar(outf,int3,false), fputchar(outf,int4,false);

	SAOI::ExtractValue(respawn_delay,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);	
	
	SAOI::ExtractValue(addsiren,int1,int2,int3,int4);
	fputchar(outf,int4,false);

	SAOI::ExtractValue(worldid,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);

	SAOI::ExtractValue(interiorid,int1,int2,int3,int4);
	fputchar(outf,int1,false), fputchar(outf,int2,false), fputchar(outf,int3,false), fputchar(outf,int4,false);
	
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SetBumperIP(const name[],server_ip[]){
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new serv_ipsum[4], saoi_ipsum[4];
	sscanf(server_ip,"p<.>dddd",serv_ipsum[0],serv_ipsum[1],serv_ipsum[2],serv_ipsum[3]);
	
	saoi_ipsum[0] = SAOI::IntMod(serv_ipsum[3]);
	saoi_ipsum[1] = SAOI::IntMod(serv_ipsum[2]);
	saoi_ipsum[2] = SAOI::IntMod(serv_ipsum[1]);
	saoi_ipsum[3] = SAOI::IntMod(serv_ipsum[0]);
	
	fputchar(outf,SAOI_BUMPER_IP,false);
	for(new i = 0; i < 4; i++){
		fputchar(outf,saoi_ipsum[i],false);
	}

	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::SetBumperPort(const name[],server_port){
	if(!fexist(name)) return SAOI_ERROR_OUTPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_OUTPUT_EXTENSION;
	new File:outf = fopen(name,io_append);
	if(!outf) return SAOI_ERROR_OUTPUT_NOT_OPEN;
	
	new serv_portsum[4], saoi_portsum[4];
	SAOI::ExtractValue(server_port,serv_portsum[0],serv_portsum[1],serv_portsum[2],serv_portsum[3]);
	
	saoi_portsum[0] = SAOI::IntMod(serv_portsum[3]);
	saoi_portsum[1] = SAOI::IntMod(serv_portsum[2]);
	saoi_portsum[2] = SAOI::IntMod(serv_portsum[1]);
	saoi_portsum[3] = SAOI::IntMod(serv_portsum[0]);
	
	fputchar(outf,SAOI_BUMPER_PORT,false);
	for(new i = 0; i < 4; i++){
		fputchar(outf,saoi_portsum[i],false);
	}

	fclose(outf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::GetFileHeader(const name[],author[],version[],description[]){
	if(!fexist(name)) return SAOI_ERROR_INPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_INPUT_EXTENSION;
	new File:inpf = fopen(name,io_read);
	if(!inpf) return SAOI_ERROR_INPUT_NOT_OPEN;
	new asize = flength(inpf);
	if(asize > MAX_SAOI_FILE_SIZE || asize < 0){
		fclose(inpf);
		return SAOI_ERROR_FILE_SIZE;
	}
	new h_len = strlen(SAOI_HEADER_KEY), h_key[32];
	for(new i = 0; i < h_len; i++){
		h_key[i] = fgetchar(inpf,0,false);
	}
	h_key[h_len] = EOS;

	if(!strcmp(h_key,SAOI_HEADER_KEY,true)){
		new author_size, version_size, description_size, key[32];
		
		author_size = fgetchar(inpf,0,false);
		for(new i = 0; i < author_size; i++){
			author[i] = fgetchar(inpf,0,false);
		}
		
		version_size = fgetchar(inpf,0,false);
		for(new i = 0; i < version_size; i++){
			version[i] = fgetchar(inpf,0,false);
		}
		
		description_size = fgetchar(inpf,0,false);
		for(new i = 0; i < description_size; i++){
			description[i] = fgetchar(inpf,0,false);
		}
		
		for(new i = 0; i < 32; i++){
			key[i] = fgetchar(inpf,0,false);
		}
		
		new step;
		
		step = 0;
		for(new i = 0; i < author_size; i++){
			author[i] = ((author[i]+key[step]) & 0xFF);
			step++;
			if(step >= 32) step = 0;
		}
		
		step = 0;
		for(new i = 0; i < version_size; i++){
			version[i] = ((version[i]+key[step]) & 0xFF);
			step++;
			if(step >= 32) step = 0;
		}
		
		step = 0;
		for(new i = 0; i < description_size; i++){
			description[i] = ((description[i]+key[step]) & 0xFF);
			step++;
			if(step >= 32) step = 0;
		}
		
	} else {
		fclose(inpf);
		return SAOI_ERROR_INVALID_HEADER;
	}
	
	fclose(inpf);
	return SAOI_ERROR_SUCCESS;
}

SAOI::Function:: SAOI::CopyHeader(const input[],const output[]){
	if(!fexist(input)) return SAOI_ERROR_INPUT_NOT_EXIST;
	if(fexist(output)) return SAOI_ERROR_OUTPUT_EXIST;
	new File:inpf = fopen(input,io_read);
	if(!inpf) return SAOI_ERROR_INPUT_NOT_OPEN;
	new File:outf = fopen(output,io_append);
	if(!outf){
		fclose(inpf);
		return SAOI_ERROR_OUTPUT_NOT_OPEN;
	}
	new h_len = strlen(SAOI_HEADER_KEY), h_key[32];
	for(new i = 0; i < h_len; i++){
		h_key[i] = fgetchar(inpf,0,false);
	}
	h_key[h_len] = EOS;
	if(!strcmp(h_key,SAOI_HEADER_KEY,true)){
		new key[32],
			author[MAX_SAOI_AUTHOR_SIZE],
			version[MAX_SAOI_VERSION_SIZE],
			description[MAX_SAOI_DESCRIPTION_SIZE],
			author_size,
			version_size,
			description_size;
		
		//load
		author_size = fgetchar(inpf,0,false);
		for(new i = 0; i < author_size; i++){
			author[i] = fgetchar(inpf,0,false);
		}
		
		version_size = fgetchar(inpf,0,false);
		for(new i = 0; i < version_size; i++){
			version[i] = fgetchar(inpf,0,false);
		}
		
		description_size = fgetchar(inpf,0,false);
		for(new i = 0; i < description_size; i++){
			description[i] = fgetchar(inpf,0,false);
		}
		
		for(new i = 0; i < 32; i++){
			key[i] = fgetchar(inpf,0,false);
		}
		
		
		//save
		fwrite(outf,SAOI_HEADER_KEY);
		
		fputchar(outf,author_size,false);
		for(new i = 0; i < author_size; i++){
			fputchar(outf,author[i],false);
		}
		
		fputchar(outf,version_size,false);
		for(new i = 0; i < version_size; i++){
			fputchar(outf,version[i],false);
		}
		
		fputchar(outf,description_size,false);
		for(new i = 0; i < description_size; i++){
			fputchar(outf,description[i],false);
		}
		
		for(new i = 0; i < 32; i++){
			fputchar(outf,key[i],false);
		}
		
	} else {
		fclose(inpf);
		fclose(outf);
		fremove(output);
		return SAOI_ERROR_INVALID_HEADER;
	}
	fclose(inpf);
	fclose(outf);
	return SAOI_ERROR_SUCCESS;
	
}

SAOI::Function:: SAOI::CleanupElements(index){
	if(!SAOI::IsLoaded(index)) return false;
	
	new extraid = (SAOI_EXTRA_ID_OFFSET+index);
	
	//Remove Buildings
	SAOI::DropRemoveBuildings(index);
	
	//Objects
	if(SAOIFile[index][SAOI::cnt_object] > 0){
		new max_idx = SAOIFile[index][SAOI::cnt_object], i = SAOIFile[index][SAOI::offset_object], j = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicObject(i)){
				if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					DestroyDynamicObject(i);
				}
			}
			i++;
		}
	}

	//CA_CreateObject
	#if defined SAOI_ColAndreas
		if(SAOIFile[index][SAOI::cnt_caobject] > 0){
			new max_idx = SAOIFile[index][SAOI::cnt_caobject], i = SAOIFile[index][SAOI::offset_caobject];
			while(i < MAX_CA_OBJECTS && max_idx > 0){
				if(CA_GetObjectExtraID(i,CA_EXTRA_1) == extraid){
					max_idx--;
					CA_DestroyObject_DC(i);
				}
				i++;
			}
		}
	#endif
	
	//3DTextLabels
	if(SAOIFile[index][SAOI::cnt_3dtext] > 0){
		new max_idx = SAOIFile[index][SAOI::cnt_3dtext], i = SAOIFile[index][SAOI::offset_3dtext], j = Streamer_GetUpperBound(STREAMER_TYPE_3D_TEXT_LABEL);
		while(i <= j && max_idx > 0){
			if(IsValidDynamic3DTextLabel(Text3D:i)){
				if(Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					DestroyDynamic3DTextLabel(Text3D:i);
				}
			}
			i++;
		}
	}
	
	//Pickups
	if(SAOIFile[index][SAOI::cnt_pickup] > 0){
		new max_idx = SAOIFile[index][SAOI::cnt_pickup], i = SAOIFile[index][SAOI::offset_pickup], j = Streamer_GetUpperBound(STREAMER_TYPE_PICKUP);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicPickup(i)){
				if(Streamer_GetIntData(STREAMER_TYPE_PICKUP,i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					DestroyDynamicPickup(i);
				}
			}
			i++;
		}
	}
	
	//MapIcons
	if(SAOIFile[index][SAOI::cnt_mapicon] > 0){
		new max_idx = SAOIFile[index][SAOI::cnt_mapicon], i = SAOIFile[index][SAOI::offset_mapicon], j = Streamer_GetUpperBound(STREAMER_TYPE_MAP_ICON);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicMapIcon(i)){
				if(Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					DestroyDynamicMapIcon(i);
				}
			}
			i++;
		}
	}
	
	//Actors
	if(SAOIFile[index][SAOI::cnt_actor] > 0){
		new max_idx = SAOIFile[index][SAOI::cnt_actor], i = SAOIFile[index][SAOI::offset_actor], j = Streamer_GetUpperBound(STREAMER_TYPE_ACTOR);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicActor(i)){
				if(Streamer_GetIntData(STREAMER_TYPE_ACTOR,i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					DestroyDynamicActor(i);
				}
			}
			i++;
		}
	}
	
	//Areas
	if(SAOIFile[index][SAOI::cnt_area] > 0){
		new max_idx = SAOIFile[index][SAOI::cnt_area], i = SAOIFile[index][SAOI::offset_area], j = Streamer_GetUpperBound(STREAMER_TYPE_AREA);
		while(i <= j && max_idx > 0){
			if(IsValidDynamicArea(i)){
				if(Streamer_GetIntData(STREAMER_TYPE_AREA,i,E_STREAMER_EXTRA_ID) == extraid){
					max_idx--;
					DestroyDynamicArea(i);
				}
			}
			i++;
		}
	}
	
	//Vehicles
	new prot_i = 0;
	if(SAOIFile[index][SAOI::cnt_vehicle] > 0){
		new max_idx = SAOIFile[index][SAOI::cnt_vehicle], i = SAOIFile[index][SAOI::offset_vehicle], j = GetVehiclePoolSize();
		while(i <= j && max_idx > 0){
			prot_i = i;
			if(IsValidVehicle(i)){
				if(SAOI::Vehicles[i] == index){
					max_idx--;
					DestroyVehicle(prot_i);
					CallRemoteFunction("SAOI_OnVehicleDestroyed","d",i);
					CallRemoteFunction("EVF_RemoveVehicle","d",i);
					SAOI::Vehicles[i] = INVALID_SAOI_FILE;
				}
			}
			i++;
		}
	}
	
	return true;
}

SAOI::Public:: SAOI::LoadObjectImage(const name[],bool:save_logs,bool:fast_boot){
	if(!CRC_SAOIAccess) return SAOI_ERROR_MEMORY_BLOCKED;
	new index = SAOI::GetFreeID();
	if(index == INVALID_SAOI_FILE) return SAOI_ERROR_NOT_ENOUGH_CAPACITY;
	if(!fast_boot && SAOI::IsFileLoaded(name)) return SAOI_ERROR_IS_LOADED;
	
	new NTTime = GetTickCount();
	if(!fexist(name)) return SAOI_ERROR_INPUT_NOT_EXIST;
	if(strfind(name,".saoi",true) == -1) return SAOI_ERROR_INPUT_EXTENSION;
	new File:inpf = fopen(name,io_read);
	if(!inpf) return SAOI_ERROR_INPUT_NOT_OPEN;
	new asize = flength(inpf), idx = 0;
	if(asize > MAX_SAOI_FILE_SIZE || asize < 0){
		fclose(inpf);
		return SAOI_ERROR_FILE_SIZE;
	}
	new author[MAX_SAOI_AUTHOR_SIZE], version[MAX_SAOI_VERSION_SIZE], description[MAX_SAOI_DESCRIPTION_SIZE];
	
	SAOIFile[index] = SAOI::Construct();
	SAOIFile[index][SAOI::status] = true;
	format(SAOIFile[index][SAOI::name],MAX_SAOI_NAME_SIZE,"%s",name);
	for(new i = strlen(SAOIFile[index][SAOI::name])-1; i >= 0; i--){
		if(SAOIFile[index][SAOI::name][i] == '.'){
			SAOIFile[index][SAOI::name][i] = EOS;
			break;
		}
	}
	
	new extraid = (SAOI_EXTRA_ID_OFFSET+index);
	
	new modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid,
		Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance, areaid, priority,
		arg_count, material_used, material_text_used, elementid, element_flag,
		txdname[MAX_TXD_NAME], texturename[MAX_TEXTURE_NAME], materialcolor, txdsize, texturenamesize,
		text[MAX_TEXT_NAME], fontface[MAX_FONT_NAME], textsize, materialsize, fontfacesize, bold, fontcolor, backcolor,
		textalignment, fontsize, load_time, type, style, color,
		color1, color2, respawn_delay, addsiren, Float:size, invulnerable, Float:health,
		Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz,
		Float:Polygon_Points[MAX_POLYGON_POINTS*2], max_points, DynamicAreas[512], testlos;
	
	#if defined SAOI_ColAndreas
		new col_elementid;
	#endif
	
	//Get Header
	new h_len = strlen(SAOI_HEADER_KEY), h_key[32];
	for(new i = 0; i < h_len; i++){
		h_key[i] = fgetchar(inpf,0,false), idx++;
	}
	h_key[h_len] = EOS;
	if(!strcmp(h_key,SAOI_HEADER_KEY,true)){
		new author_size, version_size, description_size, key[32];
		
		author_size = fgetchar(inpf,0,false), idx++;
		for(new i = 0; i < author_size; i++){
			author[i] = fgetchar(inpf,0,false), idx++;
		}
		
		version_size = fgetchar(inpf,0,false), idx++;
		for(new i = 0; i < version_size; i++){
			version[i] = fgetchar(inpf,0,false), idx++;
		}
		
		description_size = fgetchar(inpf,0,false), idx++;
		for(new i = 0; i < description_size; i++){
			description[i] = fgetchar(inpf,0,false), idx++;
		}
		
		for(new i = 0; i < 32; i++){
			key[i] = fgetchar(inpf,0,false), idx++;
		}
		
		new step;
		
		step = 0;
		for(new i = 0; i < author_size; i++){
			author[i] = ((author[i]+key[step]) & 0xFF);
			step++;
			if(step >= 32) step = 0;
		}
		
		step = 0;
		for(new i = 0; i < version_size; i++){
			version[i] = ((version[i]+key[step]) & 0xFF);
			step++;
			if(step >= 32) step = 0;
		}
		
		step = 0;
		for(new i = 0; i < description_size; i++){
			description[i] = ((description[i]+key[step]) & 0xFF);
			step++;
			if(step >= 32) step = 0;
		}
	} else {
		SAOIFile[index][SAOI::status] = false;
		fclose(inpf);
		return SAOI_ERROR_INVALID_HEADER;
	}
	
	while(idx < asize){
		//Get Arg Count
		arg_count = fgetchar(inpf,0,false), idx++;
		switch(arg_count){
			case 7..14: {
				//Reset Data
				elementid = INVALID_STREAMER_ID;
				material_used = 0;
				material_text_used = 0;
				worldid = -1;
				interiorid = -1;
				streamdistance = STREAMER_OBJECT_SD;
				drawdistance = STREAMER_OBJECT_DD;
				areaid = -1;
				priority = 0;
				element_flag = 0;
		
				SAOI::MergeValue(modelid,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SAOI::GetByteFloat(inpf,x);
				SAOI::GetByteFloat(inpf,y);
				SAOI::GetByteFloat(inpf,z);
				SAOI::GetByteFloat(inpf,rx);
				SAOI::GetByteFloat(inpf,ry);
				SAOI::GetByteFloat(inpf,rz);
				idx += 26;
				
				if(arg_count >= 8){
					SAOI::GetByteInteger(inpf,worldid);
					idx += 4;
				}
				if(arg_count >= 9){
					SAOI::GetByteInteger(inpf,interiorid);
					idx += 4;
				}
				if(arg_count >= 10){
					SAOI::GetByteFloat(inpf,streamdistance);
					idx += 4;
				}
				if(arg_count >= 11){
					SAOI::GetByteFloat(inpf,drawdistance);
					idx += 4;
				}
				if(arg_count >= 12){
					SAOI::GetByteInteger(inpf,areaid);
					idx += 4;
				}
				if(arg_count >= 13){
					SAOI::MergeValue(priority,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(arg_count >= 14){
					SAOI::MergeValue(element_flag,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(areaid == -1){
					elementid = CreateDynamicObject(modelid,x,y,z,rx,ry,rz,worldid,interiorid,-1,streamdistance,drawdistance,areaid,priority);
				} else {
					elementid = CreateDynamicObject(modelid,x,y,z,rx,ry,rz,worldid,interiorid,-1,streamdistance,drawdistance,DynamicAreas[areaid],priority);
				}
				//Get Materials
				SAOI::MergeValue(material_used,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				idx += 2;
				
				for(new mat = 0; mat < 16; mat++){
					if(SAOI::GetValueBit(material_used,mat) == 1){
						SAOI::MergeValue(modelid,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 2;
						
						txdsize = fgetchar(inpf,0,false), idx++;
						for(new i = 0; i < txdsize; i++){
							txdname[i] = SAOI::IntMod(fgetchar(inpf,0,false)), idx++;
						}
						txdname[txdsize] = EOS;
						
						texturenamesize = fgetchar(inpf,0,false), idx++;
						
						for(new i = 0; i < texturenamesize; i++){
							texturename[i] = SAOI::IntMod(fgetchar(inpf,0,false)), idx++;
						}
						texturename[texturenamesize] = EOS;

						SAOI::GetByteInteger(inpf,materialcolor);
						idx += 4;
						
						SetDynamicObjectMaterial(elementid,mat,modelid,txdname,texturename,materialcolor);
						SAOIFile[index][SAOI::cnt_material]++;
					}
				}
				
				//Get Materials Text
				SAOI::MergeValue(material_text_used,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				idx += 2;
				
				for(new mat = 0; mat < 16; mat++){
					if(SAOI::GetValueBit(material_text_used,mat) == 1){
						SAOI::MergeValue(textsize,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
						idx += 2;
						
						for(new i = 0; i < textsize; i++){
							text[i] = SAOI::IntMod(fgetchar(inpf,0,false)), idx++;
						}
						text[textsize] = EOS;

						materialsize = fgetchar(inpf,0,false), idx++;
						
						fontfacesize = fgetchar(inpf,0,false), idx++;
						
						for(new i = 0; i < fontfacesize; i++){
							fontface[i] = SAOI::IntMod(fgetchar(inpf,0,false)), idx++;
						}
						fontface[fontfacesize] = EOS;

						fontsize = fgetchar(inpf,0,false), idx++;
						
						bold = fgetchar(inpf,0,false), idx++;
						
						SAOI::GetByteInteger(inpf,fontcolor);
						idx += 4;
						
						SAOI::GetByteInteger(inpf,backcolor);
						idx += 4;
						
						textalignment = fgetchar(inpf,0,false), idx++;
						
						SetDynamicObjectMaterialText(elementid,mat,text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
						SAOIFile[index][SAOI::cnt_materialtext]++;
					}
				}
				if(SAOIFile[index][SAOI::offset_object] == INVALID_STREAMER_ID){
					SAOIFile[index][SAOI::offset_object] = elementid;
				}
				Streamer_SetIntData(STREAMER_TYPE_OBJECT,elementid,E_STREAMER_EXTRA_ID,extraid);
				if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA) == 1){
					Streamer_ToggleItemInvAreas(STREAMER_TYPE_OBJECT,elementid,1);
				}
				if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_NO_CAMERA_COL) == 1){
					SetDynamicObjectNoCameraCol(elementid);
				}
				SAOIFile[index][SAOI::cnt_object]++;
				#if defined SAOI_ColAndreas
					if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_COLANDREAS) == 1){
						col_elementid = CA_CreateObject(modelid,x,y,z,rx,ry,rz,true);
						CA_SetObjectExtraID(col_elementid,CA_EXTRA_1,extraid);
						SAOIFile[index][SAOI::cnt_caobject]++;
						if(SAOIFile[index][SAOI::offset_caobject] == -1){
							SAOIFile[index][SAOI::offset_caobject] = col_elementid;
						}
					} else if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_COLSTATIC) == 1){
						CA_CreateObject(modelid,x,y,z,rx,ry,rz,false);
						SAOIFile[index][SAOI::cnt_caobject]++;
						SAOIFile[index][SAOI::is_static] = true;
					}
				#endif
				continue;
			}
			
			case SAOI_BUMPER_ACTOR: {
				arg_count = fgetchar(inpf,0,false), idx++;
				
				//Reset Data
				elementid = INVALID_STREAMER_ID;
				invulnerable = 1;
				health = 100.0;
				worldid = -1;
				interiorid = -1;
				streamdistance = STREAMER_OBJECT_SD;
				areaid = -1;
				priority = 0;
				element_flag = 0;
				
				SAOI::MergeValue(modelid,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SAOI::GetByteFloat(inpf,x);
				SAOI::GetByteFloat(inpf,y);
				SAOI::GetByteFloat(inpf,z);
				SAOI::GetByteFloat(inpf,rz);
				idx += 18;
			
				if(arg_count >= 6){
					SAOI::MergeValue(invulnerable,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(arg_count >= 7){
					SAOI::GetByteFloat(inpf,health);
					idx += 4;
				}
				if(arg_count >= 8){
					SAOI::GetByteInteger(inpf,worldid);
					idx += 4;
				}
				if(arg_count >= 9){
					SAOI::GetByteInteger(inpf,interiorid);
					idx += 4;
				}
				if(arg_count >= 10){
					SAOI::GetByteFloat(inpf,streamdistance);
					idx += 4;
				}
				if(arg_count >= 11){
					SAOI::GetByteInteger(inpf,areaid);
					idx += 4;
				}
				if(arg_count >= 12){
					SAOI::MergeValue(priority,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(arg_count >= 13){
					SAOI::MergeValue(element_flag,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(areaid == -1){
					elementid = CreateDynamicActor(modelid,x,y,z,rz,invulnerable,health,worldid,interiorid,-1,streamdistance,areaid,priority);
				} else {
					elementid = CreateDynamicActor(modelid,x,y,z,rz,invulnerable,health,worldid,interiorid,-1,streamdistance,DynamicAreas[areaid],priority);
				}
				
				if(SAOIFile[index][SAOI::offset_actor] == INVALID_STREAMER_ID){
					SAOIFile[index][SAOI::offset_actor] = elementid;
				}
				Streamer_SetIntData(STREAMER_TYPE_ACTOR,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA) == 1){
					Streamer_ToggleItemInvAreas(STREAMER_TYPE_ACTOR,elementid,1);
				}
				SAOIFile[index][SAOI::cnt_actor]++;
				continue;
			}
			
			case SAOI_BUMPER_3D_TEXT_LABEL: {
				arg_count = fgetchar(inpf,0,false), idx++;
				
				//Reset Data
				elementid = INVALID_STREAMER_ID;
				textsize = 0;
				text = "";
				testlos = 0;
				worldid = -1;
				interiorid = -1;
				streamdistance = STREAMER_OBJECT_SD;
				areaid = -1;
				priority = 0;
				element_flag = 0;
				
				SAOI::MergeValue(textsize,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				idx += 2;
				
				for(new i = 0; i < textsize; i++){
					text[i] = SAOI::IntMod(fgetchar(inpf,0,false)), idx++;
				}
				text[textsize] = EOS;
				
				SAOI::GetByteInteger(inpf,color);
				SAOI::GetByteFloat(inpf,x);
				SAOI::GetByteFloat(inpf,y);
				SAOI::GetByteFloat(inpf,z);
				SAOI::GetByteFloat(inpf,drawdistance);
				idx += 20;
				
				if(arg_count >= 8){
					SAOI::MergeValue(testlos,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(arg_count >= 9){
					SAOI::GetByteInteger(inpf,worldid);
					idx += 4;
				}
				if(arg_count >= 10){
					SAOI::GetByteInteger(inpf,interiorid);
					idx += 4;
				}
				if(arg_count >= 11){
					SAOI::GetByteFloat(inpf,streamdistance);
					idx += 4;
				}
				if(arg_count >= 12){
					SAOI::GetByteInteger(inpf,areaid);
					idx += 4;
				}
				if(arg_count >= 13){
					SAOI::MergeValue(priority,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(arg_count >= 14){
					SAOI::MergeValue(element_flag,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(areaid == -1){
					elementid = _:CreateDynamic3DTextLabel(text,color,x,y,z,drawdistance,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,testlos,worldid,interiorid,-1,streamdistance,areaid,priority);
				} else {
					elementid = _:CreateDynamic3DTextLabel(text,color,x,y,z,drawdistance,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,testlos,worldid,interiorid,-1,streamdistance,DynamicAreas[areaid],priority);
				}
				
				if(SAOIFile[index][SAOI::offset_3dtext] == INVALID_STREAMER_ID){
					SAOIFile[index][SAOI::offset_3dtext] = elementid;
				}
				Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA) == 1){
					Streamer_ToggleItemInvAreas(STREAMER_TYPE_3D_TEXT_LABEL,elementid,1);
				}
				SAOIFile[index][SAOI::cnt_3dtext]++;
				continue;
			}
			
			case SAOI_BUMPER_PICKUP: {
				arg_count = fgetchar(inpf,0,false), idx++;
				
				//Reset Data
				elementid = INVALID_STREAMER_ID, type = 0, worldid = -1, interiorid = -1, streamdistance = STREAMER_OBJECT_SD,
				areaid = -1, priority = 0, element_flag = 0;
		
				SAOI::MergeValue(modelid,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SAOI::MergeValue(type,0,0,0,fgetchar(inpf,0,false));
				SAOI::GetByteFloat(inpf,x);
				SAOI::GetByteFloat(inpf,y);
				SAOI::GetByteFloat(inpf,z);
				idx += 15;
				
				if(arg_count >= 6){
					SAOI::GetByteInteger(inpf,worldid);
					idx += 4;
				}
				if(arg_count >= 7){
					SAOI::GetByteInteger(inpf,interiorid);
					idx += 4;
				}
				if(arg_count >= 8){
					SAOI::GetByteFloat(inpf,streamdistance);
					idx += 4;
				}
				if(arg_count >= 9){
					SAOI::GetByteInteger(inpf,areaid);
					idx += 4;
				}
				if(arg_count >= 10){
					SAOI::MergeValue(priority,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(arg_count >= 11){
					SAOI::MergeValue(element_flag,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(areaid == -1){
					elementid = CreateDynamicPickup(modelid,type,x,y,z,worldid,interiorid,-1,streamdistance,areaid,priority);
				} else {
					elementid = CreateDynamicPickup(modelid,type,x,y,z,worldid,interiorid,-1,streamdistance,DynamicAreas[areaid],priority);
				}
				
				if(SAOIFile[index][SAOI::offset_pickup] == INVALID_STREAMER_ID){
					SAOIFile[index][SAOI::offset_pickup] = elementid;
				}
				Streamer_SetIntData(STREAMER_TYPE_PICKUP,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA) == 1){
					Streamer_ToggleItemInvAreas(STREAMER_TYPE_PICKUP,elementid,1);
				}
				SAOIFile[index][SAOI::cnt_pickup]++;
				continue;
			}

			case SAOI_BUMPER_MAPICON: {
				arg_count = fgetchar(inpf,0,false), idx++;
				
				//Reset Data
				elementid = INVALID_STREAMER_ID;
				worldid = -1;
				interiorid = -1;
				streamdistance = STREAMER_OBJECT_SD;
				style = 0;
				areaid = -1;
				priority = 0;
				element_flag = 0;
				
		
				SAOI::GetByteFloat(inpf,x);
				SAOI::GetByteFloat(inpf,y);
				SAOI::GetByteFloat(inpf,z);
				SAOI::MergeValue(type,0,0,0,fgetchar(inpf,0,false));
				SAOI::GetByteInteger(inpf,color);
				idx += 17;
				
				if(arg_count >= 6){
					SAOI::GetByteInteger(inpf,worldid);
					idx += 4;
				}
				if(arg_count >= 7){
					SAOI::GetByteInteger(inpf,interiorid);
					idx += 4;
				}
				if(arg_count >= 8){
					SAOI::GetByteFloat(inpf,streamdistance);
					idx += 4;
				}
				if(arg_count >= 9){
					SAOI::MergeValue(style,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(arg_count >= 10){
					SAOI::GetByteInteger(inpf,areaid);
					idx += 4;
				}
				if(arg_count >= 11){
					SAOI::MergeValue(priority,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(arg_count >= 12){
					SAOI::MergeValue(element_flag,0,0,0,fgetchar(inpf,0,false));
					idx += 1;
				}
				if(areaid == -1){
					elementid = CreateDynamicMapIcon(x,y,z,type,color,worldid,interiorid,-1,streamdistance,style,areaid,priority);
				} else {
					elementid = CreateDynamicMapIcon(x,y,z,type,color,worldid,interiorid,-1,streamdistance,style,DynamicAreas[areaid],priority);
				}
				
				if(SAOIFile[index][SAOI::offset_mapicon] == INVALID_STREAMER_ID){
					SAOIFile[index][SAOI::offset_mapicon] = elementid;
				}
				Streamer_SetIntData(STREAMER_TYPE_MAP_ICON,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				if(SAOI::GetValueBit(element_flag,ELEMENT_FLAG_ANTI_AREA) == 1){
					Streamer_ToggleItemInvAreas(STREAMER_TYPE_MAP_ICON,elementid,1);
				}
				SAOIFile[index][SAOI::cnt_mapicon]++;
				continue;
			}

			case SAOI_BUMPER_VEHICLE: {
				SAOI::MergeValue(type,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SAOI::GetByteFloat(inpf,x);
				SAOI::GetByteFloat(inpf,y);
				SAOI::GetByteFloat(inpf,z);
				SAOI::GetByteFloat(inpf,rz);
				SAOI::MergeValue(color1,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SAOI::MergeValue(color2,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SAOI::GetByteInteger(inpf,respawn_delay);
				SAOI::MergeValue(addsiren,0,0,0,fgetchar(inpf,0,false));
				SAOI::GetByteInteger(inpf,worldid);
				SAOI::GetByteInteger(inpf,interiorid);
				idx += 35;
				
				if(color1 == 0xFFFF) color1 = -1;
				if(color2 == 0xFFFF) color2 = -1;
				
				elementid = CreateVehicle(type,x,y,z,rz,color1,color2,respawn_delay,addsiren);
				if(elementid == INVALID_VEHICLE_ID){
					printf("[SAOI DEBUG] Can't create vehicle, limit exceeded !");
				} else {
					if(interiorid != 0) LinkVehicleToInterior(elementid,interiorid);
					if(worldid != 0) SetVehicleVirtualWorld(elementid,worldid);
					SAOI::Vehicles[elementid] = index;
					
					CallRemoteFunction("SAOI_OnVehicleCreated","d",elementid);
					CallRemoteFunction("EVF_ImportVehicle","ddffffddddd",elementid,type,x,y,z,rz,color1,color2,worldid,interiorid,0);
					
					if(SAOIFile[index][SAOI::offset_vehicle] == 0){
						SAOIFile[index][SAOI::offset_mapicon] = elementid;
					}
					
					SAOIFile[index][SAOI::cnt_vehicle]++;
				}
				continue;
			}

			case SAOI_BUMPER_AREA_CIRCLE: {
				arg_count = fgetchar(inpf,0,false), idx++;
				
				//Reset Data
				elementid = INVALID_STREAMER_ID;
				worldid = -1;
				interiorid = -1;
				
				SAOI::GetByteInteger(inpf,areaid);
				SAOI::GetByteFloat(inpf,x);
				SAOI::GetByteFloat(inpf,y);
				SAOI::GetByteFloat(inpf,size);
				idx += 16;
				
				if(arg_count >= 5){
					SAOI::GetByteInteger(inpf,worldid);
					idx += 4;
				}
				if(arg_count >= 6){
					SAOI::GetByteInteger(inpf,interiorid);
					idx += 4;
				}
				elementid = CreateDynamicCircle(x,y,size,worldid,interiorid,-1);
				DynamicAreas[areaid] = elementid;
				
				if(SAOIFile[index][SAOI::offset_area] == INVALID_STREAMER_ID){
					SAOIFile[index][SAOI::offset_area] = elementid;
				}
				Streamer_SetIntData(STREAMER_TYPE_AREA,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				
				SAOIFile[index][SAOI::cnt_area]++;
				continue;
			}

			case SAOI_BUMPER_AREA_CYLINDER: {
				arg_count = fgetchar(inpf,0,false), idx++;
				
				//Reset Data
				elementid = INVALID_STREAMER_ID;
				worldid = -1;
				interiorid = -1;
				
				SAOI::GetByteInteger(inpf,areaid);
				SAOI::GetByteFloat(inpf,x);
				SAOI::GetByteFloat(inpf,y);
				SAOI::GetByteFloat(inpf,minz);
				SAOI::GetByteFloat(inpf,maxz);
				SAOI::GetByteFloat(inpf,size);
				idx += 24;
				
				if(arg_count >= 7){
					SAOI::GetByteInteger(inpf,worldid);
					idx += 4;
				}
				if(arg_count >= 8){
					SAOI::GetByteInteger(inpf,interiorid);
					idx += 4;
				}
				elementid = CreateDynamicCylinder(x,y,minz,maxz,size,worldid,interiorid,-1);
				
				DynamicAreas[areaid] = elementid;
				
				if(SAOIFile[index][SAOI::offset_area] == INVALID_STREAMER_ID){
					SAOIFile[index][SAOI::offset_area] = elementid;
				}
				Streamer_SetIntData(STREAMER_TYPE_AREA,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				
				SAOIFile[index][SAOI::cnt_area]++;
				continue;
			}

			case SAOI_BUMPER_AREA_SPHERE: {
				arg_count = fgetchar(inpf,0,false), idx++;
				
				//Reset Data
				elementid = INVALID_STREAMER_ID;
				worldid = -1;
				interiorid = -1;
				
				SAOI::GetByteInteger(inpf,areaid);
				SAOI::GetByteFloat(inpf,x);
				SAOI::GetByteFloat(inpf,y);
				SAOI::GetByteFloat(inpf,z);
				SAOI::GetByteFloat(inpf,size);
				idx += 20;
				
				if(arg_count >= 6){
					SAOI::GetByteInteger(inpf,worldid);
					idx += 4;
				}
				if(arg_count >= 7){
					SAOI::GetByteInteger(inpf,interiorid);
					idx += 4;
				}
				elementid = CreateDynamicSphere(x,y,z,size,worldid,interiorid,-1);
				DynamicAreas[areaid] = elementid;
				
				if(SAOIFile[index][SAOI::offset_area] == INVALID_STREAMER_ID){
					SAOIFile[index][SAOI::offset_area] = elementid;
				}
				Streamer_SetIntData(STREAMER_TYPE_AREA,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				
				SAOIFile[index][SAOI::cnt_area]++;
				continue;
			}

			case SAOI_BUMPER_AREA_RECTANGLE: {
				arg_count = fgetchar(inpf,0,false), idx++;
				
				//Reset Data
				elementid = INVALID_STREAMER_ID;
				worldid = -1;
				interiorid = -1;
				
				SAOI::GetByteInteger(inpf,areaid);
				SAOI::GetByteFloat(inpf,minx);
				SAOI::GetByteFloat(inpf,miny);
				SAOI::GetByteFloat(inpf,maxx);
				SAOI::GetByteFloat(inpf,maxy);
				idx += 20;
				
				if(arg_count >= 6){
					SAOI::GetByteInteger(inpf,worldid);
					idx += 4;
				}
				if(arg_count >= 7){
					SAOI::GetByteInteger(inpf,interiorid);
					idx += 4;
				}
				elementid = CreateDynamicRectangle(minx,miny,maxx,maxy,worldid,interiorid,-1);
				DynamicAreas[areaid] = elementid;
				
				if(SAOIFile[index][SAOI::offset_area] == INVALID_STREAMER_ID){
					SAOIFile[index][SAOI::offset_area] = elementid;
				}
				Streamer_SetIntData(STREAMER_TYPE_AREA,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				
				SAOIFile[index][SAOI::cnt_area]++;
				continue;
			}

			case SAOI_BUMPER_AREA_CUBOID: {
				arg_count = fgetchar(inpf,0,false), idx++;
				
				//Reset Data
				elementid = INVALID_STREAMER_ID;
				worldid = -1;
				interiorid = -1;
				
				SAOI::GetByteInteger(inpf,areaid);
				SAOI::GetByteFloat(inpf,minx);
				SAOI::GetByteFloat(inpf,miny);
				SAOI::GetByteFloat(inpf,minz);
				SAOI::GetByteFloat(inpf,maxx);
				SAOI::GetByteFloat(inpf,maxy);
				SAOI::GetByteFloat(inpf,maxz);
				idx += 28;
				
				if(arg_count >= 8){
					SAOI::GetByteInteger(inpf,worldid);
					idx += 4;
				}
				if(arg_count >= 9){
					SAOI::GetByteInteger(inpf,interiorid);
					idx += 4;
				}
				elementid = CreateDynamicCube(minx,miny,minz,maxx,maxy,maxz,worldid,interiorid,-1);
				DynamicAreas[areaid] = elementid;
				
				if(SAOIFile[index][SAOI::offset_area] == INVALID_STREAMER_ID){
					SAOIFile[index][SAOI::offset_area] = elementid;
				}
				Streamer_SetIntData(STREAMER_TYPE_AREA,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				
				SAOIFile[index][SAOI::cnt_area]++;
				continue;
			}

			case SAOI_BUMPER_AREA_POLYGON: {
				arg_count = fgetchar(inpf,0,false), idx++;
				
				//Reset Data
				elementid = INVALID_STREAMER_ID;
				minz = -FLOAT_INFINITY;
				maxz = FLOAT_INFINITY;
				worldid = -1;
				interiorid = -1;
				
				SAOI::GetByteInteger(inpf,areaid);
				SAOI::MergeValue(max_points,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				idx += 6;
				
				for(new k = 0; k < max_points; k++){
					SAOI::GetByteFloat(inpf,Polygon_Points[k]);
					idx += 4;
				}
				
				if(arg_count >= 4){
					SAOI::GetByteFloat(inpf,minz);
					idx += 4;
				}
				if(arg_count >= 5){
					SAOI::GetByteFloat(inpf,maxz);
					idx += 4;
				}
				if(arg_count >= 6){
					SAOI::GetByteInteger(inpf,worldid);
					idx += 4;
				}
				if(arg_count >= 7){
					SAOI::GetByteInteger(inpf,interiorid);
					idx += 4;
				}

				elementid = CreateDynamicPolygon(Polygon_Points,minz,maxz,max_points,worldid,interiorid,-1);
				DynamicAreas[areaid] = elementid;
				
				if(SAOIFile[index][SAOI::offset_area] == INVALID_STREAMER_ID){
					SAOIFile[index][SAOI::offset_area] = elementid;
				}
				Streamer_SetIntData(STREAMER_TYPE_AREA,elementid,E_STREAMER_EXTRA_ID,SAOI_EXTRA_ID_OFFSET+index);
				
				SAOIFile[index][SAOI::cnt_area]++;
				continue;
			}
			
			case SAOI_BUMPER_REMOVEBUILDING: {
				//RemoveBuildingForPlayer
				modelid = SAOI::MergeValue(modelid,0,0,fgetchar(inpf,0,false),fgetchar(inpf,0,false));
				SAOI::GetByteFloat(inpf,x);
				SAOI::GetByteFloat(inpf,y);
				SAOI::GetByteFloat(inpf,z);
				SAOI::GetByteFloat(inpf,streamdistance);
				idx += 18;
				SAOI::RemoveBuilding(index,modelid,x,y,z,streamdistance);
				SAOIFile[index][SAOI::cnt_removebuilding]++;
				continue;
			}
			case SAOI_BUMPER_CREATED: {
				new year,month,day,hour,minute,second;
				SAOI::MergeValue(year,0,0,SAOI::IntMod(fgetchar(inpf,0,false)),SAOI::IntMod(fgetchar(inpf,0,false)));
				month = SAOI::IntMod(fgetchar(inpf,0,false));
				day = SAOI::IntMod(fgetchar(inpf,0,false));
				hour = SAOI::IntMod(fgetchar(inpf,0,false));
				minute = SAOI::IntMod(fgetchar(inpf,0,false));
				second = SAOI::IntMod(fgetchar(inpf,0,false));
				format(SAOIFile[index][SAOI::created],32,"%04d.%02d.%02d %02d:%02d:%02d",year,month,day,hour,minute,second);
				idx += 7;
				continue;
			}
			case SAOI_BUMPER_POS: {
				SAOI::GetByteFloat(inpf,SAOIFile[index][SAOI::X]);
				SAOI::GetByteFloat(inpf,SAOIFile[index][SAOI::Y]);
				SAOI::GetByteFloat(inpf,SAOIFile[index][SAOI::Z]);
				SAOI::GetByteFloat(inpf,SAOIFile[index][SAOI::A]);
				SAOI::GetByteInteger(inpf,SAOIFile[index][SAOI::VW]);
				SAOI::GetByteInteger(inpf,SAOIFile[index][SAOI::INT]);
				idx += 24;
				continue;
			}
			case SAOI_BUMPER_IP: {
				new serv_ipsum[4], saoi_ipsum[4], serv_ip[16];
				GetServerVarAsString("bind",serv_ip,sizeof(serv_ip));
				for(new i = 0; i < 4; i++){
					saoi_ipsum[i] = fgetchar(inpf,0,false), idx++;
				}
				sscanf(serv_ip,"p<.>dddd",serv_ipsum[0],serv_ipsum[1],serv_ipsum[2],serv_ipsum[3]);
				if(SAOI::Comp(serv_ipsum[0],saoi_ipsum[3]) || SAOI::Comp(serv_ipsum[1],saoi_ipsum[2]) || SAOI::Comp(serv_ipsum[2],saoi_ipsum[1]) || SAOI::Comp(serv_ipsum[3],saoi_ipsum[0])){
					fclose(inpf);
					printf("[ADM] Error: This SAOI file is protected.");
					SendRconCommand("exit");
					return SAOI_ERROR_INVALID_SERVER_IP;
				}
				continue;
			}
			case SAOI_BUMPER_PORT: {
				new serv_port = GetServerVarAsInt("port"), serv_portsum[4], saoi_portsum[4];
				for(new i = 0; i < 4; i++){
					saoi_portsum[i] = fgetchar(inpf,0,false), idx++;
				}
				SAOI::ExtractValue(serv_port,serv_portsum[0],serv_portsum[1],serv_portsum[2],serv_portsum[3]);
				if(SAOI::Comp(serv_portsum[0],saoi_portsum[3]) || SAOI::Comp(serv_portsum[1],saoi_portsum[2]) || SAOI::Comp(serv_portsum[2],saoi_portsum[1]) || SAOI::Comp(serv_portsum[3],saoi_portsum[0])){
					fclose(inpf);
					printf("[ADM] Error: This SAOI file is protected.");
					SendRconCommand("exit");
					return SAOI_ERROR_INVALID_SERVER_PORT;
				}
				continue;
			}
			case SAOI_BUMPER_EOF: {
				SAOIFile[index][SAOI::write_lock] = true;
				break;
			}
			default: {
				SAOI::CleanupElements(index);
				SAOIFile[index][SAOI::status] = false;
				
				new d_raw[8], offset = idx-1;
				for(new i = 0; i < 8; i++){
					if(idx < asize){
						d_raw[i] = fgetchar(inpf,0,false), idx++;
					} else {
						d_raw[i] = 0;
					}
				}

				fclose(inpf);
				
				//Print Error Backtrace
				printf(" ");
				printf("[SAOI DEBUG] Parse Error '%s' Offset 0x%08x Argument: 0x%02x Buffer: %02x %02x %02x %02x %02x %02x %02x %02x",name,offset,arg_count,d_raw[0],d_raw[1],d_raw[2],d_raw[3],d_raw[4],d_raw[5],d_raw[6],d_raw[7]);
				printf("[SAOI DEBUG] File Size: 0x%08x",asize);
				if(isnull(SAOIFile[index][SAOI::created])){
					printf("[SAOI DEBUG] File Creation Date: (null)");
				} else {
					printf("[SAOI DEBUG] File Creation Date: %s",SAOIFile[index][SAOI::created]);
				}
				printf(" ");
				return SAOI_ERROR_INVALID_ARG_COUNT;
			}
		}
	}
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		if(IsPlayerConnected(i)){
			CallRemoteFunction("SAOI_OnRemovedBuildings","dd",i,SAOI::UpdateBuildingsForPlayer(i,index));
		}
	}
	
	SAOIFile[index][SAOI::file_size] = idx;
	
	fclose(inpf);
	
	load_time = GetTickCount()-NTTime;
	
	SAOIFile[index][SAOI::load_time] = load_time;
	SAOIFile[index][SAOI::active_tick] = GetTickCount();
	
	if(save_logs){
		new buffer[256];
		format(buffer,sizeof buffer,"File %s has been loaded as %s in %d ms",name,(SAOI::IsStatic(index)?("static"):("dynamic")),load_time);
		printf(buffer);
		format(buffer,sizeof buffer,"Author: %s Version: %s Items: %d",author,version,SAOI::CountAllElementsByIndex(index));
		printf(buffer);
		if(!isnull(description)){
			format(buffer,sizeof buffer,"Description: %s",description);
			printf(buffer);
		}
		printf(" ");
	}
	return index;
}

SAOI::Public:: SAOI::UnloadObjectImage(index){
	if(!CRC_SAOIAccess) return 0;
	if(!SAOI::IsLoaded(index) || SAOI::IsStatic(index)) return 0;
	SAOI::CleanupElements(index);
	SAOIFile[index] = SAOI::Construct();
	return 1;
}

SAOI::Public:: SAOI::ToggleVisibleItems(const name[],playerid,type,toggle){
	if(!CRC_SAOIAccess) return 0;
	new index;
	if(!SAOI::IsFileLoaded(name,index)) return 0;
	
	new extraid = (SAOI_EXTRA_ID_OFFSET+index), cnt = 0;
	
	switch(type){
		case STREAMER_TYPE_OBJECT: {
			//Objects
			if(SAOIFile[index][SAOI::cnt_object] > 0){
				new max_idx = SAOIFile[index][SAOI::cnt_object], i = SAOIFile[index][SAOI::offset_object], j = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT);
				while(i <= j && max_idx > 0){
					if(IsValidDynamicObject(i)){
						if(Streamer_GetIntData(STREAMER_TYPE_OBJECT,i,E_STREAMER_EXTRA_ID) == extraid){
							max_idx--;
							Streamer_ToggleItem(playerid,type,i,toggle);
							cnt++;
						}
					}
					i++;
				}
			}
		}
		case STREAMER_TYPE_PICKUP: {
			//Pickups
			if(SAOIFile[index][SAOI::cnt_pickup] > 0){
				new max_idx = SAOIFile[index][SAOI::cnt_pickup], i = SAOIFile[index][SAOI::offset_pickup], j = Streamer_GetUpperBound(STREAMER_TYPE_PICKUP);
				while(i <= j && max_idx > 0){
					if(IsValidDynamicPickup(i)){
						if(Streamer_GetIntData(STREAMER_TYPE_PICKUP,i,E_STREAMER_EXTRA_ID) == extraid){
							max_idx--;
							Streamer_ToggleItem(playerid,type,i,toggle);
							cnt++;
						}
					}
					i++;
				}
			}
		}
		case STREAMER_TYPE_MAP_ICON: {
			//MapIcons
			if(SAOIFile[index][SAOI::cnt_mapicon] > 0){
				new max_idx = SAOIFile[index][SAOI::cnt_mapicon], i = SAOIFile[index][SAOI::offset_mapicon], j = Streamer_GetUpperBound(STREAMER_TYPE_MAP_ICON);
				while(i <= j && max_idx > 0){
					if(IsValidDynamicMapIcon(i)){
						if(Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,i,E_STREAMER_EXTRA_ID) == extraid){
							max_idx--;
							Streamer_ToggleItem(playerid,type,i,toggle);
							cnt++;
						}
					}
					i++;
				}
			}
		}
		case STREAMER_TYPE_3D_TEXT_LABEL: {
			//3DTextLabels
			if(SAOIFile[index][SAOI::cnt_3dtext] > 0){
				new max_idx = SAOIFile[index][SAOI::cnt_3dtext], i = SAOIFile[index][SAOI::offset_3dtext], j = Streamer_GetUpperBound(STREAMER_TYPE_3D_TEXT_LABEL);
				while(i <= j && max_idx > 0){
					if(IsValidDynamic3DTextLabel(Text3D:i)){
						if(Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,i,E_STREAMER_EXTRA_ID) == extraid){
							max_idx--;
							Streamer_ToggleItem(playerid,type,Text3D:i,toggle);
							cnt++;
						}
					}
					i++;
				}
			}
		}
		case STREAMER_TYPE_AREA: {
			//Areas
			if(SAOIFile[index][SAOI::cnt_area] > 0){
				new max_idx = SAOIFile[index][SAOI::cnt_area], i = SAOIFile[index][SAOI::offset_area], j = Streamer_GetUpperBound(STREAMER_TYPE_AREA);
				while(i <= j && max_idx > 0){
					if(IsValidDynamicArea(i)){
						if(Streamer_GetIntData(STREAMER_TYPE_AREA,i,E_STREAMER_EXTRA_ID) == extraid){
							max_idx--;
							Streamer_ToggleItem(playerid,type,i,toggle);
							cnt++;
						}
					}
					i++;
				}
			}
		}
		case STREAMER_TYPE_ACTOR: {
			//Actors
			if(SAOIFile[index][SAOI::cnt_actor] > 0){
				new max_idx = SAOIFile[index][SAOI::cnt_actor], i = SAOIFile[index][SAOI::offset_actor], j = Streamer_GetUpperBound(STREAMER_TYPE_ACTOR);
				while(i <= j && max_idx > 0){
					if(IsValidDynamicActor(i)){
						if(Streamer_GetIntData(STREAMER_TYPE_ACTOR,i,E_STREAMER_EXTRA_ID) == extraid){
							max_idx--;
							Streamer_ToggleItem(playerid,type,i,toggle);
							cnt++;
						}
					}
					i++;
				}
			}
		}
	}
	return cnt;
}

new bool:CRC_SAOIInit = true,
	bool:CRC_SAOIExit = true;

SAOI::Public:: SAOI_RemoteCheck(){
	#if defined LOCK_SAOI_MEMORY
		if(GetSVarInt("ADM:SAOI:LOCK") == 0){
			SetSVarInt("ADM:SAOI:LOCK",1);
			SetSVarString("ADM:SAOI:FM",LOCK_SAOI_MEMORY);
			printf("[ADM] Info: SAOI has been attached to %s",LOCK_SAOI_MEMORY);
			CRC_SAOIAccess = true;
		} else {
			new saoi_fm_name[64];
			GetSVarString("ADM:SAOI:FM",saoi_fm_name,64);
			printf("[SAOI DEBUG] SAOI.inc was blocked by %s !",saoi_fm_name);
			printf("[SAOI DEBUG] You can not modify the memory remotely");
			CRC_SAOIAccess = false;
		}
	#else
		if(GetSVarInt("ADM:SAOI:LOCK") == 1){
			new saoi_fm_name[64];
			GetSVarString("ADM:SAOI:FM",saoi_fm_name,64);
			printf("[SAOI DEBUG] SAOI.inc was blocked by %s !",saoi_fm_name);
			printf("[SAOI DEBUG] You can not modify the memory remotely");
			CRC_SAOIAccess = false;
		} else {
			CRC_SAOIAccess = true;
		}
	#endif
	return 1;
}

SAOI::Function:: SAOI::Init(){
	CallRemoteFunction("SAOI_RemoteCheck","");
}

SAOI::Function:: SAOI::Exit(){
	#if defined LOCK_SAOI_MEMORY
		SetSVarInt("ADM:SAOI:LOCK",0);
		DeleteSVar("ADM:SAOI:FM");
		printf("[ADM] Info: SAOI has been detached from %s",LOCK_SAOI_MEMORY);
	#endif
	
	//Vehicles
	new prot_i = 0;
	for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++){
		prot_i = i;
		if(IsValidVehicle(i)){
			if(SAOI::Vehicles[i] != INVALID_SAOI_FILE){
				DestroyVehicle(prot_i);
				CallRemoteFunction("SAOI_OnVehicleDestroyed","d",i);
				SAOI::Vehicles[i] = INVALID_SAOI_FILE;
			}
		}
	}
}

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	SAOIPlayerFirstSpawn[playerid] = true;
	#if defined SAOI_OnPlayerConnect
		SAOI_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect SAOI_OnPlayerConnect
#if defined SAOI_OnPlayerConnect
	forward SAOI_OnPlayerConnect(playerid);
#endif

//Hook: OnPlayerSpawn
public OnPlayerSpawn(playerid){
	if(SAOIPlayerFirstSpawn[playerid]){
		SAOIPlayerFirstSpawn[playerid] = false;
		CallRemoteFunction("SAOI_OnRemovedBuildings","dd",playerid,SAOI::RemoveBuildingsForPlayer(playerid));
	}
	#if defined SAOI_OnPlayerSpawn
		SAOI_OnPlayerSpawn(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn SAOI_OnPlayerSpawn
#if defined SAOI_OnPlayerSpawn
	forward SAOI_OnPlayerSpawn(playerid);
#endif

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_SAOIInit){
		CRC_SAOIInit = false;
		SAOI::Init();
	}
	#if defined SAOI_OnFilterScriptInit
		SAOI_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit SAOI_OnFilterScriptInit
#if defined SAOI_OnFilterScriptInit
	forward SAOI_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_SAOIInit){
		CRC_SAOIInit = false;
		SAOI::Init();
	}
	#if defined SAOI_OnGameModeInit
		SAOI_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SAOI_OnGameModeInit
#if defined SAOI_OnGameModeInit
	forward SAOI_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_SAOIExit){
		CRC_SAOIExit = false;
		SAOI::Exit();
	}
	#if defined SAOI_OnFilterScriptExit
		SAOI_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit SAOI_OnFilterScriptExit
#if defined SAOI_OnFilterScriptExit
	forward SAOI_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_SAOIExit){
		CRC_SAOIExit = false;
		SAOI::Exit();
	}
	#if defined SAOI_OnGameModeExit
		SAOI_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit SAOI_OnGameModeExit
#if defined SAOI_OnGameModeExit
	forward SAOI_OnGameModeExit();
#endif

//EOF