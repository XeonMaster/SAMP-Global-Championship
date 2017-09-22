#include <samp/a_samp>
#include <samp/a_http>

#include <main/meta/version>
#include <main/config>

#include <plugin/sscanf2>
#include <plugin/streamer>
#include <plugin/audio>
#include <plugin/regex>
#include <plugin/a_mysql>
#include <plugin/colandreas>
#include <plugin/mapandreas>
#include <plugin/crashdetect>
#include <plugin/FCNPC>
#include <plugin/YSF>

#include <izcmd>
#include <general/geolocation>
#include <general/progress2>
#include <general/foreach>
#include <general/colors>
#include <general/y_timers>
#include <general/y_hooks>

#include <SAM/StreamerFunction>
#include <SAM/BitFunctions>
#include <SAM/RGB>
#include <SAM/3DTryg>
#include <SAM/LY>
#include <SAM/ADM>
#include <SAM/DataConvert>
#include <SAM/EVF>
#include <SAM/Logs>
//#include <SAM/ATM>

#include <other/Interiors>

#include <engine/EngineV6>
#include <engine/Knife>
#include <engine/Magic>
#include <engine/VehPara>
#include <engine/Mines>
#include <engine/Missile>
#include <engine/VehicleMissileCol>

//#include <event/Lottery>

//Championship Includes
#include <main/meta/definitions>
#include <main/meta/enums>
#include <main/areas/meta>
#include <main/meta/variables>
#include <main/meta/spawns>

#include <main/security/io>
#include <main/security/MySQL>
#include <main/security/ClientCheck>
#include <main/security/anti-mh>

#include <main/engine/regexp>
#include <main/engine/admin>
#include <main/engine/gm_functions>
#include <main/engine/constructors>
#include <main/engine/timers>
#include <main/engine/CA_Buildings>
#include <main/engine/Vehicles>

#include <main/areas/engine>

#include <main/dialogs>
#include <main/main>

#include <main/commands/player>
#include <main/commands/gm>
#include <main/commands/admin>
#include <main/commands/rcon>

main(){
	printf("SA:MP Global Championship Init");
}

#pragma unused _RenderBar //why i need ?

#pragma dynamic (256*1024)
