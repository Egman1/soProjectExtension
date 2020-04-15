/*
*	S.T.A.L.K.E.R. Online - network hooks for different patches
*	Developers:
*		009 (�������� �������)
*		
*	Extension:
*		DiR.X (��������� ��������)
*/

#include "multipatch.h"
// creatures
#include "Creatures/Client/CAI_Bloodsucker.h"
#include "Creatures/Client/CAI_Boar.h"
#include "Creatures/Client/CAI_Crow.h"
#include "Creatures/Client/CAI_Dog.h"
#include "Creatures/Client/CAI_Flesh.h"
#include "Creatures/Client/CAI_PseudoDog.h"
#include "Creatures/Client/CAI_Rat.h"
#include "Creatures/Client/CAI_Stalker.h"
#include "Creatures/Client/CAI_Trader.h"
#include "Creatures/Client/CBurer.h"
#include "Creatures/Client/CCat.h"
#include "Creatures/Client/CChimera.h"
#include "Creatures/Client/CController.h"
#include "Creatures/Client/CFracture.h"
#include "Creatures/Client/CPhantom.h"
#include "Creatures/Client/CPoltergeist.h"
#include "Creatures/Client/CPseudoGigant.h"
#include "Creatures/Client/CPsyDog.h"
#include "Creatures/Client/CPsyDogPhantom.h"
#include "Creatures/Client/CSnork.h"
#include "Creatures/Client/CTushkano.h"
#include "Creatures/Client/CZombie.h"
#include "Creatures/Server/CSE_ALifeCreatureCrow.h"
#include "Creatures/Server/CSE_ALifeCreaturePhantom.h"
#include "Creatures/Server/CSE_ALifeCreatureRat.h"
#include "Creatures/Server/CSE_ALifeHumanStalker.h"
#include "Creatures/Server/CSE_ALifeMonsterBase.h"
#include "Creatures/Server/CSE_ALifeSmartZone.h"
#include "Creatures/Server/CSE_ALifeTrader.h"
#include "Creatures/Server/CSE_ALifePsyDogPhantom.h"
#include "events.h"
#include "motions.h"
#include "../build_defines.h"

#include "../shared/log.h"
#define M_SOPROJECT_MESSANGE 52
#define Msg LogHandle->Write

// extern
extern CLog* LogHandle;
extern BYTE	 PatchVersion;
extern CHook* HookHandle;

// vars
DWORD (_cdecl * lua_alife__create)(DWORD _alife,char* _section,float* _position,DWORD _lvertex,WORD _gvertex,WORD _parentid);
DWORD (_cdecl * lua_alife)();
DWORD (_cdecl * F_entity_Create)(char* section);
DWORD (_cdecl * ai)();
DWORD (_cdecl * CObjectItemClientServer_CActor_CSE_ALifeCreatureActor___client_object)();
void (_cdecl * game_cl_GameState__u_EventSend)(NET_Packet &P);
DWORD (_cdecl * game_cl_GameState__GetPlayerByGameID)(unsigned short id);
void (_cdecl * game_sv_mp__Player_AddMoney)(DWORD, int);
unsigned int (_cdecl *game_sv_GameState__count_players)();
LPCSTR get_event_server();
LPCSTR get_event_client();
CSE_Abstract* (_cdecl * game_sv_GameState__get_entity_from_eid)(unsigned short);
DWORD*	(_cdecl * IPureServer__ID_to_client)		(ClientID ID, bool ScanAll);
DWORD(_cdecl * actor)();

DWORD smart_cast__CGameObject_CInventoryItem;
DWORD CGameObject__lua_game_object;
DWORD CGameObject__callback;
DWORD CGameObject__CScriptCallbackEx;

DWORD pIPureServer__SendTo;
DWORD pCKinematicsAnimated__PlayCycle;
DWORD pCKinematicsAnimated__PlayCycleEx;
DWORD pCSE_ALifeCreatureCrow__UPDATE_Write;
DWORD pCSE_ALifeCreatureCrow__UPDATE_Read;
DWORD pCSE_ALifeCreaturePhantom__UPDATE_Write;
DWORD pCSE_ALifeCreaturePhantom__UPDATE_Read;
DWORD pCSE_ALifeCreatureRat__UPDATE_Write;
DWORD pCSE_ALifeCreatureRat__UPDATE_Read;
DWORD pCSE_ALifeMonsterZombie__UPDATE_Write;
DWORD pCSE_ALifeMonsterZombie__UPDATE_Read;
DWORD pCSE_ALifeHumanStalker__UPDATE_Write;
DWORD pCSE_ALifeHumanStalker__UPDATE_Read;
DWORD pCSE_ALifeMonsterBase__UPDATE_Write;
DWORD pCSE_ALifeMonsterBase__UPDATE_Read;
DWORD pCSE_ALifeTrader__UPDATE_Write;
DWORD pCSE_ALifeTrader__UPDATE_Read;
DWORD pCSE_ALifePsyDogPhantom__UPDATE_Write;
DWORD pCSE_ALifePsyDogPhantom__UPDATE_Read;
DWORD pUPDATE_Write_call_address;
DWORD pUPDATE_Read_call_address;
DWORD pCALifeSimulator__CALifeSimulator;
DWORD pCGameGraph__CGameGraph;
DWORD pCLevel__IsServer;
DWORD pCAI_Space__reinit;
DWORD pCAI_Space__load;
DWORD pCAI_Space__patrol_path_storage;
DWORD pCActor__NeedToDestroyObject;
DWORD pCActor__TimePassedAfterDeath;
DWORD pCDestroyer__CALifeSimulator__delete;
DWORD pCScriptStorage__load_file_into_namespace;  // CScriptStorage::load_file_into_namespace(char* file_path,char* namespace)
DWORD pCScriptBinder__reload;
DWORD pCScriptBinder__reinit;
DWORD pCScriptBinder__net_spawn;
DWORD pCActor__CActor;
DWORD pCActor__net_spawn;
DWORD pCSE_ALifeCreatureActor__CSE_ALifeCreatureActor;
DWORD CSE_ALifeCreatureActor__ftable;
DWORD CSE_ActorMP__ftable;
DWORD CAI_Bloodsucker__ftable;
DWORD CAI_Boar__ftable;
DWORD CAI_Crow__ftable;
DWORD CAI_Dog__ftable;
DWORD CAI_Flesh__ftable;
DWORD CAI_PseudoDog__ftable;
DWORD CAI_Rat__ftable;
DWORD CAI_Stalker__ftable;
DWORD CAI_Trader__ftable;
DWORD CBurer__ftable;
DWORD CCat__ftable;
DWORD CChimera__ftable;
DWORD CController__ftable;
DWORD CFracture__ftable;
DWORD CPhantom__ftable;
DWORD CPoltergeist__ftable;
DWORD CPseudoGigant__ftable;
DWORD CPsyDog__ftable;
DWORD CPsyDogPhantom__ftable;
DWORD CSnork__ftable;
DWORD CTushkano__ftable;
DWORD CZombie__ftable;
DWORD CActorMP__ftable;
DWORD gGameOffset;
DWORD gServerOffset;
DWORD gActorPointer;
DWORD gActorObject;
char* LevelAlifeSpawnFile = "alife";
char* LevelScriptFile = "location_main";
char* LevelDirectory = "$level$";
char* LevelLocalPlayer = "get_local_player_id";
char* str_AddMoneyMP = "add_money_mp";
char* str_ScriptLog = "script_log";
char* SendDataToServer = "send_data_to_server";
char* GetEventServer = "get_event_server";
char* GetEventClient = "get_event_client";
char* str_IsServer = "is_server";
char* str_IsDedicated = "is_dedicated";
char* GetGActorID = "get_g_actor_id";
void* CustomSyncData_Entity[0xFFFF];	// 0xFFFF - max of Entitys in game
DWORD g_actor;

// headers
void game_sv_mp__Create_fix(DWORD pClass,DWORD a2);
void CLevel__Load_GameSpecific_Before_fix();
void add_function_to_level();
void add_function_to_level2();
void send_data_to_server_script(LPCSTR data,bool b);
void send_data_to_server_engine(NET_Packet *p);
void script_log(LPCSTR data,bool b);
unsigned int get_local_client_id();
unsigned int get_local_player();
unsigned int get_g_actor_id();
DWORD F_entity_Create_fix(DWORD pClass);
DWORD CSE_ALifeObject__alife_fix();
DWORD CActor__net_Spawn_fix(DWORD pClass,DWORD CEntity);
DWORD CActor__net_Destroy_fix(DWORD CObject);
DWORD CActor__UpdateCL(DWORD pClass);
bool bind_object_fix();
DWORD CALifeGraphRegistry__update_fix(DWORD pClass);
bool Messange_Listner(NET_Packet& p);
bool is_server();
bool is_dedicated();
void add_money_mp(unsigned short id, float money);

void Hook_onEat_callback(WORD pClass, WORD unkn);
void Hook_Open_PDA();
void Hook_open_dialog();
void Hook_CHudItem_SwitchState(DWORD pClass, DWORD State);

void Hook_CPhysicObject_Door_Disable_Interpolation();

void Hook_xrServerSendEvent_det(ClientID cl_id, NET_Packet& pack);

void Launch_Mod_Extension();

// patch 1.6.0.0

CHook_Patch_00::CHook_Patch_00()
{
	for(int i = 0;i < 0xFFFF;i++) CustomSyncData_Entity[i] = NULL;

	// wait modules load
	while((EngineOffset = GetModuleHandle(L"xrEngine.exe")) == NULL) {}
	while((CoreOffset = GetModuleHandle(L"xrCore.dll")) == NULL) {}
	while((GameOffset = GetModuleHandle(L"xrGame.dll")) == NULL) {}
	while((NetServerOffset = GetModuleHandle(L"xrNetServer.dll")) == NULL) {}
	while(true)
	{
		if((RenderOffset = GetModuleHandle(L"xrRender_R1.dll")) != NULL)
		{
			RenderVersion = 1;
			break;
		}
		if((RenderOffset = GetModuleHandle(L"xrRender_R2.dll")) != NULL)
		{
			RenderVersion = 2;
			break;
		}
		if((RenderOffset = GetModuleHandle(L"xrRender_R3.dll")) != NULL)
		{
			RenderVersion = 3;
			break;
		}
		if((RenderOffset = GetModuleHandle(L"xrRender_R4.dll")) != NULL)
		{
			RenderVersion = 4;
			break;
		}
	}
	while((LuaOffset = GetModuleHandle(L"xrPhysics.dll")) == NULL) {}


	PatchVersion = 0;
}

void CHook_Patch_00::InstallHooks()
{
	LogHandle->Write("patch 1.6.0.0 not compatible");
}

// patch 1.6.0.1

CHook_Patch_01::CHook_Patch_01()
{
	for(int i = 0;i < 0xFFFF;i++) CustomSyncData_Entity[i] = NULL;

	// wait modules load
	while((EngineOffset = GetModuleHandle(L"xrEngine.exe")) == NULL) {}
	while((CoreOffset = GetModuleHandle(L"xrCore.dll")) == NULL) {}
	while((GameOffset = GetModuleHandle(L"xrGame.dll")) == NULL) {}
	while((NetServerOffset = GetModuleHandle(L"xrNetServer.dll")) == NULL) {}
	while(true)
	{
		if((RenderOffset = GetModuleHandle(L"xrRender_R1.dll")) != NULL)
		{
			RenderVersion = 1;
			break;
		}
		if((RenderOffset = GetModuleHandle(L"xrRender_R2.dll")) != NULL)
		{
			RenderVersion = 2;
			break;
		}
		if((RenderOffset = GetModuleHandle(L"xrRender_R3.dll")) != NULL)
		{
			RenderVersion = 3;
			break;
		}
		if((RenderOffset = GetModuleHandle(L"xrRender_R4.dll")) != NULL)
		{
			RenderVersion = 4;
			break;
		}
	}
	while((PhysicsOffset = GetModuleHandle(L"xrPhysics.dll")) == NULL) {}
	PatchVersion = 1;
}

void CHook_Patch_01::InstallHooks()
{
	LogHandle->Write("patch 1.6.0.1 not compatible");
}

// patch 1.6.0.2

CHook_Patch_02::CHook_Patch_02()
{
	for(int i = 0;i < 0xFFFF;i++) CustomSyncData_Entity[i] = NULL;

	// wait modules load
	while((EngineOffset = GetModuleHandle(L"xrEngine.exe")) == NULL) {}
	while((CoreOffset = GetModuleHandle(L"xrCore.dll")) == NULL) {}
	while((GameOffset = GetModuleHandle(L"xrGame.dll")) == NULL) {}
	while((NetServerOffset = GetModuleHandle(L"xrNetServer.dll")) == NULL) {}
	while(true)
	{
		if((RenderOffset = GetModuleHandle(L"xrRender_R1.dll")) != NULL)
		{
			RenderVersion = 1;
			break;
		}
		if((RenderOffset = GetModuleHandle(L"xrRender_R2.dll")) != NULL)
		{
			RenderVersion = 2;
			break;
		}
		if((RenderOffset = GetModuleHandle(L"xrRender_R3.dll")) != NULL)
		{
			RenderVersion = 3;
			break;
		}
		if((RenderOffset = GetModuleHandle(L"xrRender_R4.dll")) != NULL)
		{
			RenderVersion = 4;
			break;
		}
	}
	while((PhysicsOffset = GetModuleHandle(L"xrPhysics.dll")) == NULL) {}
	while((LuaOffset = GetModuleHandle(L"lua.JIT.1.1.4.dll")) == NULL) {}

	PatchVersion = 2;
}

void CHook_Patch_02::InstallHooks()
{
	// link addresses and functions
	lua_alife__create = reinterpret_cast<DWORD (_cdecl *)(DWORD,char*,float*,DWORD,WORD,WORD)>((DWORD)(GameOffset) + 0x99490);
	lua_alife = reinterpret_cast<DWORD (_cdecl *)()>((DWORD)(GameOffset) + 0x97780);
	F_entity_Create = reinterpret_cast<DWORD (_cdecl *)(char*)>((DWORD)(GameOffset) + 0x3B4AB0);
	ai = reinterpret_cast<DWORD (_cdecl *)()>((DWORD)(GameOffset) + 0x39A30);
	actor = reinterpret_cast<DWORD(_cdecl *)()>((DWORD)(GameOffset)+0x26A790);

	smart_cast__CGameObject_CInventoryItem = ((DWORD)(GameOffset)+0x1C27A0);
	CGameObject__lua_game_object = ((DWORD)(GameOffset)+0x27FD40);
	CGameObject__callback = ((DWORD)(GameOffset)+0x281920);
	CGameObject__CScriptCallbackEx = ((DWORD)(GameOffset)+0x188800);
	
	game_cl_GameState__u_EventSend = reinterpret_cast<void (_cdecl *)(NET_Packet &)>((DWORD)(GameOffset) + 0x358CB0);
	game_cl_GameState__GetPlayerByGameID = reinterpret_cast<DWORD (_cdecl *)(unsigned short)>((DWORD)(GameOffset) + 0x358E90);
	game_sv_mp__Player_AddMoney = reinterpret_cast<void (_cdecl *)(DWORD, int)>((DWORD)(GameOffset) + 0x38ECB0);
	
	
	CObjectItemClientServer_CActor_CSE_ALifeCreatureActor___client_object = reinterpret_cast<unsigned long (_cdecl *)()>((DWORD)(GameOffset) + 0x33E830);
	pIPureServer__SendTo = ((DWORD)NetServerOffset + 0xAC10);
	pCSE_ALifeCreatureCrow__UPDATE_Write = (DWORD)GameOffset + 0x403570;
	pCSE_ALifeCreatureCrow__UPDATE_Read = (DWORD)GameOffset + 0x403560;
	pCSE_ALifeCreaturePhantom__UPDATE_Write = (DWORD)GameOffset + 0x403570;
	pCSE_ALifeCreaturePhantom__UPDATE_Read = (DWORD)GameOffset + 0x403560;
	pCSE_ALifeCreatureRat__UPDATE_Write = (DWORD)GameOffset + 0x4035E0;
	pCSE_ALifeCreatureRat__UPDATE_Read = (DWORD)GameOffset + 0x403580;
	pCSE_ALifeMonsterZombie__UPDATE_Read = (DWORD)GameOffset + 0x403600;
	pCSE_ALifeMonsterZombie__UPDATE_Write = (DWORD)GameOffset + 0x4031D0;
	pCSE_ALifeMonsterBase__UPDATE_Write = (DWORD)GameOffset + 0x4036F0;
	pCSE_ALifeMonsterBase__UPDATE_Read = (DWORD)GameOffset + 0x403660;;
	pCSE_ALifeHumanStalker__UPDATE_Write = (DWORD)GameOffset + 0x406720;
	pCSE_ALifeHumanStalker__UPDATE_Read = (DWORD)GameOffset + 0x406700;
	pCSE_ALifeTrader__UPDATE_Write = (DWORD)GameOffset + 0x403840;
	pCSE_ALifeTrader__UPDATE_Read = (DWORD)GameOffset + 0x403840;
	pCSE_ALifePsyDogPhantom__UPDATE_Write = (DWORD)GameOffset + 0x4036F0;
	pCSE_ALifePsyDogPhantom__UPDATE_Read = (DWORD)GameOffset + 0x4036E0;
	pUPDATE_Write_call_address = (DWORD)GameOffset + 0x34C7E8;
	pUPDATE_Read_call_address = (DWORD)GameOffset + 0x438911;
	pCALifeSimulator__CALifeSimulator = (DWORD)GameOffset + 0x96970;
	pCGameGraph__CGameGraph = (DWORD)GameOffset + 0xA8780;
	pCLevel__IsServer = (DWORD)GameOffset + 0x232E20;
	pCAI_Space__load = (DWORD)GameOffset + 0x227C60;
	pCAI_Space__reinit = (DWORD)GameOffset + 0x227A80;
	pCAI_Space__patrol_path_storage = (DWORD)GameOffset + 0x2268A0;
	pCActor__NeedToDestroyObject = (DWORD)GameOffset + 0x25F4C0;
	pCActor__TimePassedAfterDeath = (DWORD)GameOffset + 0x25F530;
	pCDestroyer__CALifeSimulator__delete = (DWORD)GameOffset + 0x387F90;
	pCScriptStorage__load_file_into_namespace = (DWORD)GameOffset + 0x225320;
	pCScriptBinder__reload = (DWORD)GameOffset + 0xC1A40;
	pCScriptBinder__reinit = (DWORD)GameOffset + 0xC1570;
	pCScriptBinder__net_spawn = (DWORD)GameOffset + 0xC15E0;
	pCActor__CActor = (DWORD)GameOffset + 0x264F60;
	pCActor__net_spawn = (DWORD)GameOffset + 0x26CB80;
	pCSE_ALifeCreatureActor__CSE_ALifeCreatureActor = (DWORD)GameOffset + 0x405FC0;
	CSE_ALifeCreatureActor__ftable = (DWORD)GameOffset + 0x597644; 
	CSE_ActorMP__ftable = (DWORD)GameOffset + 0x54C0BC;
	CAI_Bloodsucker__ftable = (DWORD)GameOffset + 0x51F194;
	CAI_Boar__ftable = (DWORD)GameOffset + 0x5207D4;
	CAI_Crow__ftable = (DWORD)GameOffset + 0x5219CC;
	CAI_Dog__ftable = (DWORD)GameOffset + 0x52E27C;
	CAI_Flesh__ftable = (DWORD)GameOffset + 0x53023C;
	CAI_PseudoDog__ftable = (DWORD)GameOffset + 0x53141C;
	CAI_Rat__ftable = (DWORD)GameOffset + 0x52FA8C;
	CAI_Stalker__ftable = (DWORD)GameOffset + 0x534774;
	CAI_Trader__ftable = (DWORD)GameOffset + 0x5334B4;
	CBurer__ftable = (DWORD)GameOffset + 0x5222D4;
	CCat__ftable = (DWORD)GameOffset + 0x52B7C4;
	CChimera__ftable = (DWORD)GameOffset + 0x52362C;
	CController__ftable = (DWORD)GameOffset + 0x52A37C;
	CFracture__ftable = (DWORD)GameOffset + 0x527FBC;
	CPhantom__ftable = (DWORD)GameOffset + 0x52DAF4;
	CPoltergeist__ftable = (DWORD)GameOffset + 0x5259FC;
	CPseudoGigant__ftable = (DWORD)GameOffset + 0x52471C;
	CPsyDog__ftable = (DWORD)GameOffset + 0x532BF4;
	CPsyDogPhantom__ftable = (DWORD)GameOffset + 0x5325F4;
	CSnork__ftable = (DWORD)GameOffset + 0x5290F4;
	CTushkano__ftable = (DWORD)GameOffset + 0x52C9B4;
	CZombie__ftable = (DWORD)GameOffset + 0x526F6C;
	CActorMP__ftable = (DWORD)GameOffset + 0x54BBBC;
	gGameOffset = (DWORD)GameOffset;
	gServerOffset = (DWORD)NetServerOffset;
	gActorPointer = (DWORD)GameOffset + 0x64E2C0;


	// setup fixs
	// fix game_sv_mp::Create (call our func)
	/*
		mov eax, [esp+4+arg4]			8B 44 24 08
		push eax						50
		push esi						56
		call game_sv_mp__Create_fix
		pop eax							58
		pop eax							58
		pop eax							58
		jmp end_func
	*/
	Byte(((DWORD)GameOffset + 0x38B1C0 + 0),1,0x8B);
	Byte(((DWORD)GameOffset + 0x38B1C0 + 1),1,0x44);
	Byte(((DWORD)GameOffset + 0x38B1C0 + 2),1,0x24);
	Byte(((DWORD)GameOffset + 0x38B1C0 + 3),1,0x08);
	Byte(((DWORD)GameOffset + 0x38B1C0 + 4),1,0x50);
	Byte(((DWORD)GameOffset + 0x38B1C0 + 5),1,0x56);
	Call(((DWORD)GameOffset + 0x38B1C0 + 6),(DWORD)game_sv_mp__Create_fix);
	Byte(((DWORD)GameOffset + 0x38B1C0 + 11),1,0x58);
	Byte(((DWORD)GameOffset + 0x38B1C0 + 12),1,0x58);
	Byte(((DWORD)GameOffset + 0x38B1C0 + 13),1,0x58);
	Jmp(((DWORD)GameOffset + 0x38B1C0 + 14),((DWORD)GameOffset + 0x38B1E8));
	// fix game_sv_mp::~game_sv_mp (destroy ALifeSimulator)
	/*
		mov esi, ecx
		lea eax, [esi+4170h]
		push eax
		call CDestroyer__CHelper2_CALifeSimulator_____delete_data_1_
		add esp, 4
		jmp game_sv_GameState___game_sv_GameState
	*/
	DWORD end_of_func = (DWORD)malloc(24);
	Byte((end_of_func + 0),1,0x8B);	// mov esi, ecx
	Byte((end_of_func + 1),1,0xF1);
	Byte((end_of_func + 2),1,0x8D); // lea eax, [esi+4170h]
	Byte((end_of_func + 3),1,0x86);
	Byte((end_of_func + 4),1,0x70);
	Byte((end_of_func + 5),1,0x41);
	Byte((end_of_func + 6),1,0x00);
	Byte((end_of_func + 7),1,0x00);
	Byte((end_of_func + 8),1,0x50); // push eax
	Call((end_of_func + 9),(DWORD)pCDestroyer__CALifeSimulator__delete); // call CDestroyer__CHelper2_CALifeSimulator_____delete_data_1_
	Byte((end_of_func + 14),1,0x83); // add esp, 4
	Byte((end_of_func + 15),1,0xC4);
	Byte((end_of_func + 16),1,0x04);
	Byte((end_of_func + 17),1,0x8B); // mov ecx, esi
	Byte((end_of_func + 18),1,0xCE);
	Jmp((end_of_func + 19),((DWORD)GameOffset + 0x379620)); // jmp game_sv_GameState___game_sv_GameState
	Jmp(((DWORD)GameOffset + 0x391FDD),end_of_func);
	Byte(((DWORD)GameOffset + 0x391FB1),1,0xEB);
	// fix CALifeSimulator::CALifeSimulator (not check cmdline and load alife.spawn with "new" param)
	Jmp(((DWORD)GameOffset + 0x96A84),((DWORD)GameOffset + 0x96BA0));
	/*
		push 1
		push 0
		push ebp
		mov ecx, ebx
		call CALifeUpdateManager::load
	*/
	Byte(((DWORD)GameOffset + 0x96C82 + 0),1,0x6A);	// push 1
	Byte(((DWORD)GameOffset + 0x96C82 + 1),1,0x01);
	Byte(((DWORD)GameOffset + 0x96C82 + 2),1,0x6A);	// push 0
	Byte(((DWORD)GameOffset + 0x96C82 + 3),1,0x00);
	Byte(((DWORD)GameOffset + 0x96C82 + 4),1,0x68); // push offset LevelAlifeSpawnFile
	Address(((DWORD)GameOffset + 0x96C82 + 5),(DWORD)LevelAlifeSpawnFile);
	Byte(((DWORD)GameOffset + 0x96C82 + 9),1,0x8B);	// mov ecx, ebx
	Byte(((DWORD)GameOffset + 0x96C82 + 10),1,0xCB);
	Call(((DWORD)GameOffset + 0x96C82 + 11),((DWORD)GameOffset + 0xABE80));	// call CALifeUpdateManager::load
	Jmp(((DWORD)GameOffset + 0x96C82 + 16),((DWORD)GameOffset + 0x96CCA));
	// fix CALifeSpawnRegistry::load_0 (load spawn file from level directory)
	Address(((DWORD)GameOffset + 0xA6A73),(DWORD)LevelDirectory);
	// fix for CLevel::Load_GameSpecific_Before (call our func)
	/*
		jmp start_func
		call CLevel__Load_GameSpecific_Before_fix
	*/
	Jmp(((DWORD)GameOffset + 0x237CB5),((DWORD)GameOffset + 0x237CC3));
	Jmp(((DWORD)GameOffset + 0x237CC9),((DWORD)GameOffset + 0x237CD6));
	Call(((DWORD)GameOffset + 0x237D0C),(DWORD)CLevel__Load_GameSpecific_Before_fix);
	Byte(((DWORD)GameOffset + 0x237D11),8,0x90);
	// fix Actor() (allow to use in MP)
	Jmp(((DWORD)GameOffset + 0x26A790),((DWORD)GameOffset + 0x26A7CA));
	// fix game_sv_Deathmatch::on_death (disable Class dynamic cast)
	Jmp(((DWORD)GameOffset + 0x383258),((DWORD)GameOffset + 0x38326F));	
	// fix game_sv_mp::RespawnPlayer (not change some var of alife)
	Byte(((DWORD)GameOffset + 0x39153B),1,0xEB);
	Byte(((DWORD)GameOffset + 0x391543),4,0x90);
	// fix game_sv_mp::OnPlayerDisconnect (not change some var of alife)
	Byte(((DWORD)GameOffset + 0x38FA29),1,0xEB);
	Byte(((DWORD)GameOffset + 0x38FA2E),4,0x90);
	// fix 103503F0 (not change some var of alife)
	Byte(((DWORD)GameOffset + 0x3503FF),1,0xEB);
	Byte(((DWORD)GameOffset + 0x35040B),4,0x90);
	// fix xrServer::Process_event_destroy (disable Class dynamic cast)
	Jmp(((DWORD)GameOffset + 0x437A37),((DWORD)GameOffset + 0x437A4E));
	// fix CSE_ALifeObject::can_switch_online (always return 1)
	Jmp(((DWORD)GameOffset + 0x3BC6A1),((DWORD)GameOffset + 0x3BC6BB));
	// fix CSE_ALifeObject::can_switch_offline (always return 0)
	Jmp(((DWORD)GameOffset + 0x3BC6D1),((DWORD)GameOffset + 0x3BC6EF));
	Byte(((DWORD)GameOffset + 0x3BC6F0),1,0x00);
	// fix CSE_ALifeObject::alife (go to our CSE_ALifeObject::alife)
	Jmp(((DWORD)GameOffset + 0x4E0330),(DWORD)&CSE_ALifeObject__alife_fix);	
	// fix F_entity_Create (call our func)
	Byte(((DWORD)GameOffset + 0x3B4B1F + 0),1,0x50);	// push eax
	Call(((DWORD)GameOffset + 0x3B4B1F + 1),(DWORD)&F_entity_Create_fix);
	end_of_func = (DWORD)malloc(8);
	Byte((end_of_func + 0),1,0x83);	// add esp, 4h
	Byte((end_of_func + 1),1,0xC4);
	Byte((end_of_func + 2),1,0x04);
	Byte((end_of_func + 3),1,0x5E);	// pop esi
	Byte((end_of_func + 4),1,0x83);	// add esp, 8h
	Byte((end_of_func + 5),1,0xC4);
	Byte((end_of_func + 6),1,0x08);
	Byte((end_of_func + 7),1,0xC3);	// retn
	Jmp(((DWORD)GameOffset + 0x3B4B1F + 6),end_of_func);
	// fix CPsyDog::Think (disable CPsyDogAura::update_schedule)
	Byte(((DWORD)GameOffset + 0x1581F2),5,0x90);	
	// fix xrServer::Process_event_destroy (crash c_dest == c_from)
	Byte(((DWORD)GameOffset + 0x437836),1,0xEB);
	// fix CPHMovementControl::AllocateCharacterObject (create mp_actor with singleplayer physics)
	Byte(((DWORD)GameOffset + 0x4FE3E7),0x10,0x90);
	Byte(((DWORD)GameOffset + 0x4FE3F7),1,0x6A);	// push 1
	Byte(((DWORD)GameOffset + 0x4FE3F8),1,0x01);
	// fix CPHMovementControl::Calculate_0 (not call callback...SCollisionHitCallback::call)
	Jmp(((DWORD)GameOffset + 0x501469),((DWORD)GameOffset + 0x5014D9));	
	// fix CSE_ALifeTraderAbstract::specific_character (not check gametype)
	Byte(((DWORD)GameOffset + 0x4074BD),1,0xEB);
	// fix CMapLocation::UpdateSpot (think what CALifeSimulator not exist)
	Byte(((DWORD)GameOffset + 0x2A42DD),1,0xEB);
	// fix bind_object (if it server - work)
	Byte(((DWORD)GameOffset + 0xC1720),7,0x90);
	Call(((DWORD)GameOffset + 0xC1727),(DWORD)&bind_object_fix);
	Byte(((DWORD)GameOffset + 0xC172C),1,0x3C);
	Byte(((DWORD)GameOffset + 0xC172D),1,0x01);
	// fix CActor::net_Spawn (jump to our func)
	Byte(((DWORD)GameOffset + 0x26CC26),1,0x57); // push edi (Entity*)
	Byte(((DWORD)GameOffset + 0x26CC27),1,0x56); // push esi (CObject*)
	Call(((DWORD)GameOffset + 0x26CC28),(DWORD)&CActor__net_Spawn_fix);
	Byte(((DWORD)GameOffset + 0x26CC2D),1,0x83); // add esp, 8h
	Byte(((DWORD)GameOffset + 0x26CC2E),1,0xC4);
	Byte(((DWORD)GameOffset + 0x26CC2F),1,0x08);
	Jmp(((DWORD)GameOffset + 0x26CC30),((DWORD)GameOffset + 0x26CC38));
	// fix CActor::net_Destroy (jump to our func)
	Byte(((DWORD)GameOffset + 0x26F22E),1,0x56); // push esi (CObject*)
	Call(((DWORD)GameOffset + 0x26F22F),(DWORD)&CActor__net_Destroy_fix);
	Byte(((DWORD)GameOffset + 0x26F234),1,0x83); // add esp, 4h
	Byte(((DWORD)GameOffset + 0x26F235),1,0xC4);
	Byte(((DWORD)GameOffset + 0x26F236),1,0x04);
	Byte(((DWORD)GameOffset + 0x26F237),5,0x90);
	// fix CSpaceRestrictionHolder::collect_garbage (not see on time)	
	Jmp(((DWORD)GameOffset + 0x759DA),((DWORD)GameOffset + 0x75A89));
	// fix game_sv_mp::Update (disable max corpses check)
	Jmp(((DWORD)GameOffset + 0x38EEF9),((DWORD)GameOffset + 0x38F1A0));
	// fix CALifeGraphRegistry::update (need not flag & 8 but our check)
	end_of_func = (DWORD)malloc(22);
	Byte((end_of_func + 0),1,0x56);	// push esi
	Call((end_of_func + 1),(DWORD)&CALifeGraphRegistry__update_fix);
	Byte((end_of_func + 6),1,0x83);	// add esp, 4h
	Byte((end_of_func + 7),1,0xC4);
	Byte((end_of_func + 8),1,0x04);
	Byte((end_of_func + 9),1,0x85);	// test eax, eax
	Byte((end_of_func + 10),1,0xC0);
	Byte((end_of_func + 11),1,0x0F); // jnz 100A52DB
	Byte((end_of_func + 12),1,0x85);
	Address((end_of_func + 13),(((DWORD)GameOffset + 0xA52DB) - (end_of_func + 13) - 4));
	Jmp((end_of_func + 17),((DWORD)GameOffset + 0xA532C)); // jmp 100A532C
	Jmp(((DWORD)GameOffset + 0xA52D5),end_of_func);
	Byte(((DWORD)GameOffset + 0xA52DA),1,0x90);


	Byte(((DWORD)GameOffset + 0x26CDF6),2,0x90);//?

	// disable singleplayer checks
	// CEntity::net_Spawn
	Byte(((DWORD)GameOffset + 0x279C3D),6,0x90);
	// CEntity::net_Destroy
	Byte(((DWORD)GameOffset + 0x279191),2,0x90);
	// CEntity::Die
	Byte(((DWORD)GameOffset + 0x279666),2,0x90);
	// CEntityAlive::Die
	Byte(((DWORD)GameOffset + 0x27BFA3),2,0x90);
	// CEntityAlive::Hit
	Byte(((DWORD)GameOffset + 0x27BEC6),6,0x90);
	// 102ACC20
	Byte(((DWORD)GameOffset + 0x2ACC27),9,0x90);
	// CLevel::OnFrame
	Byte(((DWORD)GameOffset + 0x234A42),2,0x90);
	// CMapManager::RemoveMapLocationByObjectID
	Byte(((DWORD)GameOffset + 0x2A6461),2,0x90);
	// CInventoryOwner::net_Spawn
	Byte(((DWORD)GameOffset + 0x2B227C),1,0x84);


	// disable dedicated checks
	// game_sv_GameState::Create
	Byte(((DWORD)GameOffset + 0x37A34B),6,0x90);
	// game_sv_GameState::Update
	Byte(((DWORD)GameOffset + 0x37915A),2,0x90);
	// game_sv_GameState::~game_sv_GameState
	Byte(((DWORD)GameOffset + 0x379635),2,0x90);
	// game_sv_GameState::Update
	Byte(((DWORD)GameOffset + 0x37915A),2,0x90);
	// CAI_Space::Initialize
	Byte(((DWORD)GameOffset + 0x22788C),6,0x90);
	// CAI_Space::unload
	Byte(((DWORD)GameOffset + 0x2279AB),6,0x90);
	// CAI_Space::patrol_path_storage
	Byte(((DWORD)GameOffset + 0x2268AD),2,0x90);
	// CAI_Space::patrol_path_storage_raw
	Byte(((DWORD)GameOffset + 0x22680D),6,0x90);
	// CObjectFactory::register_script_classes
	Byte(((DWORD)GameOffset + 0x3471B8),2,0x90);
	// CLevel::CLevel
	Byte(((DWORD)GameOffset + 0x236E35),2,0x90);
	Byte(((DWORD)GameOffset + 0x236F00),6,0x90);
	// CLevel::~CLevel
	Byte(((DWORD)GameOffset + 0x235515),2,0x90);
	// CLevel::g_sv_Spawn
	Byte(((DWORD)GameOffset + 0x23B8C0),2,0x90);
	Byte(((DWORD)GameOffset + 0x23B7DC),2,0x90);
	// CLevel::Load_GameSpecific_After
	Byte(((DWORD)GameOffset + 0x2388DB),6,0x90);
	Byte(((DWORD)GameOffset + 0x238B33),6,0x90);
	// CLevel::Load_GameSpecific_Before
	Byte(((DWORD)GameOffset + 0x237D22),2,0x90);
	// CLevel::remove_objects
	Byte(((DWORD)GameOffset + 0x23A745),2,0x90);
	Byte(((DWORD)GameOffset + 0x23A782),2,0x90);
	Byte(((DWORD)GameOffset + 0x23A821),2,0x90);
	// CLevel::OnFrame
	Byte(((DWORD)GameOffset + 0x234CFB),2,0x90);
	Byte(((DWORD)GameOffset + 0x234A42), 2, 0x90);
	//Byte(((DWORD)GameOffset + 0x2A6461), 2, 0x90);
	// CActor::CActor
	Byte(((DWORD)GameOffset + 0x2655C8),2,0x90);
	// CGameObject::CGameObject
	Byte(((DWORD)GameOffset + 0x281601),2,0x90);
	// CGameObject::~CGameObject (maybe it)
	Byte(((DWORD)GameOffset + 0x280243),2,0x90);
	// CGameObject::net_Spawn
	Byte(((DWORD)GameOffset + 0x280EBF),2,0x90);
	Byte(((DWORD)GameOffset + 0x280EF6),2,0x90);
	// CGameObject::net_Relcase
	Byte(((DWORD)GameOffset + 0x27F827),2,0x90);
	// CGameObject::shedule_Update
	Byte(((DWORD)GameOffset + 0x27F589),2,0x90);
	// CGameObject::reinit
	Byte(((DWORD)GameOffset + 0x280243),2,0x90);


	void* add_function_to_lvl1 = calloc(200,1);
	//������ �� ��� ��������
	//call		set_weather_register
	Call(((DWORD)add_function_to_lvl1 + 0),(DWORD)GameOffset + 0x2416C7);
	//pop		ecx
	//pop		ecx
	Byte(((DWORD)add_function_to_lvl1 + 5),2,0x59);
	//mov		eax, esp
	Byte(((DWORD)add_function_to_lvl1 + 7),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 8),1,0xC4);
	//push		offset function
	Byte(((DWORD)add_function_to_lvl1 + 9),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 10),(DWORD)&get_g_actor_id);
	//push		offset LevelLocalPlayer
	Byte(((DWORD)add_function_to_lvl1 + 14),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 15),(DWORD)LevelLocalPlayer);
	//push		eax
	Byte(((DWORD)add_function_to_lvl1 + 19),1,0x50);
	//call		get_time_minutes_register
	Call(((DWORD)add_function_to_lvl1 + 20),(DWORD)GameOffset + 0x24199F);
	
	Byte(((DWORD)add_function_to_lvl1 + 25),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 27),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 28),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 29),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 30),(DWORD)&send_data_to_server_script);
	Byte(((DWORD)add_function_to_lvl1 + 34),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 35),(DWORD)SendDataToServer);
	Byte(((DWORD)add_function_to_lvl1 + 39),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 40),(DWORD)GameOffset + 0x2416C7);
	
	
	
	Byte(((DWORD)add_function_to_lvl1 + 45),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 47),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 48),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 49),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 50),(DWORD)&get_event_server);
	Byte(((DWORD)add_function_to_lvl1 + 54),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 55),(DWORD)GetEventServer);
	Byte(((DWORD)add_function_to_lvl1 + 59),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 60),(DWORD)GameOffset + 0x24166C);

	
	Byte(((DWORD)add_function_to_lvl1 + 65),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 67),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 68),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 69),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 70),(DWORD)&is_server);
	Byte(((DWORD)add_function_to_lvl1 + 74),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 75),(DWORD)str_IsServer);
	Byte(((DWORD)add_function_to_lvl1 + 79),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 80),(DWORD)GameOffset + 0x1FF277);

	
	Byte(((DWORD)add_function_to_lvl1 + 85),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 87),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 88),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 89),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 90),(DWORD)&is_dedicated);
	Byte(((DWORD)add_function_to_lvl1 + 94),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 95),(DWORD)str_IsDedicated);
	Byte(((DWORD)add_function_to_lvl1 + 99),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 100),(DWORD)GameOffset + 0x1FF277);
	
	Byte(((DWORD)add_function_to_lvl1 + 105),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 107),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 108),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 109),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 110),(DWORD)&get_event_client);
	Byte(((DWORD)add_function_to_lvl1 + 114),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 115),(DWORD)GetEventClient);
	Byte(((DWORD)add_function_to_lvl1 + 119),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 120),(DWORD)GameOffset + 0x24166C);
	
	Byte(((DWORD)add_function_to_lvl1 + 125),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 127),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 128),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 129),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 130),(DWORD)&script_log);
	Byte(((DWORD)add_function_to_lvl1 + 134),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 135),(DWORD)str_ScriptLog);
	Byte(((DWORD)add_function_to_lvl1 + 139),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 140),(DWORD)GameOffset + 0x2416C7);
	
	Byte(((DWORD)add_function_to_lvl1 + 145),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 147),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 148),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 149),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 150),(DWORD)&add_money_mp);
	Byte(((DWORD)add_function_to_lvl1 + 154),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 155),(DWORD)str_AddMoneyMP);
	Byte(((DWORD)add_function_to_lvl1 + 159),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 160),(DWORD)GameOffset + 0x2422DD);



	//
	Jmp(((DWORD)add_function_to_lvl1 + 165),(DWORD) GameOffset + 0x24A71F + 5);
	Jmp(((DWORD)GameOffset + 0x24A71F),(DWORD) add_function_to_lvl1);




	void* add_function_to_lvl2 = malloc(100);
	Byte(((DWORD)add_function_to_lvl2 + 0),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 1),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 2),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 3),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 4),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 5),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 6),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 7),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 8),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 9),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 10),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 11),1,0xD6);
	
	//Add block for each registration!!!
	Byte(((DWORD)add_function_to_lvl2 + 12),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 13),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 14),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 15),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 16),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 17),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 18),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 19),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 20),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 21),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 22),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 23),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 24),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 25),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 26),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 27),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 28),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 29),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 30),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 31),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 32),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 33),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 34),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 35),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 36),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 37),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 38),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 39),1,0xD6);

	Jmp(((DWORD)add_function_to_lvl2 + 40),(DWORD)GameOffset + 0x24A762 + 5);

	Jmp(((DWORD)GameOffset + 0x24A762),(DWORD) add_function_to_lvl2);
	Byte(((DWORD)GameOffset + 0x24A762 + 5),3,0x90);
	
	
	// correct switch tables
	// xrServer::OnMessage
	// create EventLocServer
	void* event_loc_server = malloc(100);
	/*
		push edi
		call EventFunc
		add esp, 4h
		jmp 1034DB19
	*/
	Byte(((DWORD)event_loc_server + 0),1,0x57); // push edi
	Call(((DWORD)event_loc_server + 1),(DWORD)&CLevel__cl_Process_CustomEventServer); // call EventFunc
	Byte(((DWORD)event_loc_server + 6),1,0x83);		// add esp, 4
	Byte(((DWORD)event_loc_server + 7),1,0xC4);
	Byte(((DWORD)event_loc_server + 8),1,0x4);
	Jmp(((DWORD)event_loc_server + 9),((DWORD)GameOffset + 0x34DB19));
	// change switch



	DWORD locations_xrServer[29] =
	{
		((DWORD)(GameOffset) + 0x34D618),((DWORD)(GameOffset) + 0x34D626),((DWORD)(GameOffset) + 0x34D645),
		((DWORD)(GameOffset) + 0x34D748),((DWORD)(GameOffset) + 0x34D6B4),((DWORD)(GameOffset) + 0x34D781),
		((DWORD)(GameOffset) + 0x34D7AB),((DWORD)(GameOffset) + 0x34D7F6),((DWORD)(GameOffset) + 0x34D7C5),
		((DWORD)(GameOffset) + 0x34D7DF),((DWORD)(GameOffset) + 0x34D821),((DWORD)(GameOffset) + 0x34D794),
		((DWORD)(GameOffset) + 0x34D808),((DWORD)(GameOffset) + 0x34D653),((DWORD)(GameOffset) + 0x34D82F),
		((DWORD)(GameOffset) + 0x34D83D),((DWORD)(GameOffset) + 0x34D8B0),((DWORD)(GameOffset) + 0x34D8C5),
		((DWORD)(GameOffset) + 0x34D8F1),((DWORD)(GameOffset) + 0x34D973),((DWORD)(GameOffset) + 0x34D723),
		((DWORD)(GameOffset) + 0x34D994),((DWORD)(GameOffset) + 0x34D852),((DWORD)(GameOffset) + 0x34D86C),
		((DWORD)(GameOffset) + 0x34DB05),((DWORD)(GameOffset) + 0x34DB10),((DWORD)(GameOffset) + 0x34D8DB),
		((DWORD)(GameOffset) + 0x34DB19),(DWORD)event_loc_server
	};
	BYTE jump_table_xrServer[51] =
	{
		0x0,	0x1,	0x1B,	0x1B,
		0x1B,	0x1B,	0x1B,	0x1B,
		0x2,	0x3,	0x4,	0x1B,
		0x5,	0x6,	0x7,	0x8,
		0x9,	0x0A,	0x0B,	0x0C,
		0x0D,	0x1B,	0x1B,	0x1B,
		0x0E,	0x0F,	0x1B,	0x10,
		0x1B,	0x1B,	0x1B,	0x11,
		0x1B,	0x0C,	0x12,	0x13,
		0x1B,	0x1B,	0x14,	0x1B,
		0x15,	0x0E,	0x1B,	0x16,
		0x17,	0x0E,	0x1B,	0x18,
		0x19,	0x1A,	0x1C

	};
	CreateSwitchTable(locations_xrServer,29,jump_table_xrServer,51,((DWORD)(GameOffset) + 0x34D614),((DWORD)(GameOffset) + 0x34D60D),((DWORD)(GameOffset) + 0x34D5FF));



	
	
	// correct classes ftables
	// CAI_Bloodsucker
	// CAI_Bloodsucker::NET_Export
	JoinInClassFtable((CAI_Bloodsucker__ftable + 0x38),(DWORD)&CAI_Bloodsucker__NET_Export,0x4);
	// CAI_Bloodsucker::NET_Import
	JoinInClassFtable((CAI_Bloodsucker__ftable + 0x3C),(DWORD)&CAI_Bloodsucker__NET_Import,0x4);
	// CAI_Bloodsucker::NeedToDestroyObject
	Address((CAI_Bloodsucker__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CAI_Bloodsucker::TimePassedAfterDeath
	Address((CAI_Bloodsucker__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CAI_Boar
	// CAI_Boar::NET_Export
	JoinInClassFtable((CAI_Boar__ftable + 0x38),(DWORD)&CAI_Boar__NET_Export,0x4);
	// CAI_Boar::NET_Import
	JoinInClassFtable((CAI_Boar__ftable + 0x3C),(DWORD)&CAI_Boar__NET_Import,0x4);
	// CAI_Boar::NeedToDestroyObject
	Address((CAI_Boar__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CAI_Boar::TimePassedAfterDeath
	Address((CAI_Boar__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CAI_Dog
	// CAI_Dog::NET_Export
	JoinInClassFtable((CAI_Dog__ftable + 0x38),(DWORD)&CAI_Dog__NET_Export,0x4);
	// CAI_Dog::NET_Import
	JoinInClassFtable((CAI_Dog__ftable + 0x3C),(DWORD)&CAI_Dog__NET_Import,0x4);
	// CAI_Dog::NeedToDestroyObject
	Address((CAI_Dog__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CAI_Dog::TimePassedAfterDeath
	Address((CAI_Dog__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CAI_Flesh
	// CAI_Flesh::NET_Export
	JoinInClassFtable((CAI_Flesh__ftable + 0x38),(DWORD)&CAI_Flesh__NET_Export,0x4);
	// CAI_Flesh::NET_Import
	JoinInClassFtable((CAI_Flesh__ftable + 0x3C),(DWORD)&CAI_Flesh__NET_Import,0x4);
	// CAI_Flesh::NeedToDestroyObject
	Address((CAI_Flesh__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CAI_Flesh::TimePassedAfterDeath
	Address((CAI_Flesh__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CAI_Pseudodog
	// CAI_PseudoDog::NET_Export
	JoinInClassFtable((CAI_PseudoDog__ftable + 0x38),(DWORD)&CAI_PseudoDog__NET_Export,0x4);
	// CAI_PseudoDog::NET_Import
	JoinInClassFtable((CAI_PseudoDog__ftable + 0x3C),(DWORD)&CAI_PseudoDog__NET_Import,0x4);
	// CAI_PseudoDog::NeedToDestroyObject
	Address((CAI_PseudoDog__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CAI_PseudoDog::TimePassedAfterDeath
	Address((CAI_PseudoDog__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CAI_Stalker
	// CAI_Stalker::NET_Export
	JoinInClassFtable((CAI_Stalker__ftable + 0x38),(DWORD)&CAI_Stalker__NET_Export,0x4);
	// CAI_Stalker::NET_Import
	JoinInClassFtable((CAI_Stalker__ftable + 0x3C),(DWORD)&CAI_Stalker__NET_Import,0x4);
	// CAI_Stalker::NeedToDestroyObject
	Address((CAI_Stalker__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CAI_Stalker::TimePassedAfterDeath
	Address((CAI_Stalker__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CBurer
	// CBurer::NET_Export
	JoinInClassFtable((CBurer__ftable + 0x38),(DWORD)&CBurer__NET_Export,0x4);
	// CBurer::NET_Import
	JoinInClassFtable((CBurer__ftable + 0x3C),(DWORD)&CBurer__NET_Import,0x4);
	// CBurer::NeedToDestroyObject
	Address((CBurer__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CBurer::TimePassedAfterDeath
	Address((CBurer__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CChimera
	// CChimera::NET_Export
	JoinInClassFtable((CChimera__ftable + 0x38),(DWORD)&CChimera__NET_Export,0x4);
	// CChimera::NET_Import
	JoinInClassFtable((CChimera__ftable + 0x3C),(DWORD)&CChimera__NET_Import,0x4);
	// CChimera::NeedToDestroyObject
	Address((CChimera__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CChimera::TimePassedAfterDeath
	Address((CChimera__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CController
	// CController::NET_Export
	JoinInClassFtable((CController__ftable + 0x38),(DWORD)&CController__NET_Export,0x4);
	// CController::NET_Import
	JoinInClassFtable((CController__ftable + 0x3C),(DWORD)&CController__NET_Import,0x4);
	// CController::NeedToDestroyObject
	Address((CController__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CController::TimePassedAfterDeath
	Address((CController__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CPhantom
	// CPhantom::NET_Export
	JoinInClassFtable((CPhantom__ftable + 0x38),(DWORD)&CPhantom__NET_Export,0x4);
	// CPhantom::NET_Import
	JoinInClassFtable((CPhantom__ftable + 0x3C),(DWORD)&CPhantom__NET_Import,0x4);
	// CPhantom::NeedToDestroyObject
	Address((CPhantom__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CPhantom::TimePassedAfterDeath
	Address((CPhantom__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CPoltergeist
	// CPoltergeist::NET_Export
	JoinInClassFtable((CPoltergeist__ftable + 0x38),(DWORD)&CPoltergeist__NET_Export,0x4);
	// CPoltergeist::NET_Import
	JoinInClassFtable((CPoltergeist__ftable + 0x3C),(DWORD)&CPoltergeist__NET_Import,0x4);
	// CPoltergeist::NeedToDestroyObject
	Address((CPoltergeist__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CPoltergeist::TimePassedAfterDeath
	Address((CPoltergeist__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CPseudoGigant

	// CPseudoGigant::NET_Export
	JoinInClassFtable((CPseudoGigant__ftable + 0x38),(DWORD)&CPseudoGigant__NET_Export,0x4);
	// CPseudoGigant::NET_Import
	JoinInClassFtable((CPseudoGigant__ftable + 0x3C),(DWORD)&CPseudoGigant__NET_Import,0x4);

	// CPseudoGigant::NeedToDestroyObject
	Address((CPseudoGigant__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CPseudoGigant::TimePassedAfterDeath
	Address((CPseudoGigant__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CPsyDog
	// CPsyDog::NET_Export
	JoinInClassFtable((CPsyDog__ftable + 0x38),(DWORD)&CPsyDog__NET_Export,0x4);
	// CPsyDog::NET_Import
	JoinInClassFtable((CPsyDog__ftable + 0x3C),(DWORD)&CPsyDog__NET_Import,0x4);
	// CPsyDog::NeedToDestroyObject
	Address((CPsyDog__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CPsyDog::TimePassedAfterDeath
	Address((CPsyDog__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CPsyDogPhantom
	// CPsyDogPhantom::NET_Export
	JoinInClassFtable((CPsyDogPhantom__ftable + 0x38),(DWORD)&CPsyDogPhantom__NET_Export,0x4);
	// CPsyDogPhantom::NET_Import
	JoinInClassFtable((CPsyDogPhantom__ftable + 0x3C),(DWORD)&CPsyDogPhantom__NET_Import,0x4);
	// CPsyDogPhantom::NeedToDestroyObject
	Address((CPsyDogPhantom__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CPsyDogPhantom::TimePassedAfterDeath
	Address((CPsyDogPhantom__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CSnork
	// CSnork::NET_Export
	JoinInClassFtable((CSnork__ftable + 0x38),(DWORD)&CSnork__NET_Export,0x4);
	// CSnork::NET_Import
	JoinInClassFtable((CSnork__ftable + 0x3C),(DWORD)&CSnork__NET_Import,0x4);
	// CSnork::NeedToDestroyObject
	Address((CSnork__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CSnork::TimePassedAfterDeath
	Address((CSnork__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CTushkano
	// CTushkano::NET_Export
	JoinInClassFtable((CTushkano__ftable + 0x38),(DWORD)&CTushkano__NET_Export,0x4);
	// CTushkano::NET_Import
	JoinInClassFtable((CTushkano__ftable + 0x3C),(DWORD)&CTushkano__NET_Import,0x4);
	// CTushkano::NeedToDestroyObject
	Address((CTushkano__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CTushkano::TimePassedAfterDeath
	Address((CTushkano__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CZombie
	// CZombie::NET_Export
	JoinInClassFtable((CZombie__ftable + 0x38),(DWORD)&CZombie__NET_Export,0x4);
	// CZombie::NET_Import
	JoinInClassFtable((CZombie__ftable + 0x3C),(DWORD)&CZombie__NET_Import,0x4);
	// CZombie::NeedToDestroyObject
	Address((CZombie__ftable + 0xFC),pCActor__NeedToDestroyObject);
	// CZombie::TimePassedAfterDeath
	Address((CZombie__ftable + 0x290),pCActor__TimePassedAfterDeath);
	// CWrapper
	// CWrapperAbstractMonster<class CSE_ALifeCreaturePhantom>::UPDATE_Write
	JoinInClassFtable(((DWORD)GameOffset + 0x597A48),(DWORD)&CSE_ALifeCreaturePhantom__UPDATE_Write,0x4);
	// CWrapperAbstractMonster<class CSE_ALifeCreaturePhantom>::UPDATE_Read
	JoinInClassFtable(((DWORD)GameOffset + 0x597A4C),(DWORD)&CSE_ALifeCreaturePhantom__UPDATE_Read,0x4);
	// CWrapperAbstractMonster<class CSE_ALifeHumanStalker>::UPDATE_Write
	JoinInClassFtable(((DWORD)GameOffset + 0x5973B0),(DWORD)&CSE_ALifeHumanStalker__UPDATE_Write,0x4);
	// CWrapperAbstractMonster<class CSE_ALifeHumanStalker>::UPDATE_Read
	JoinInClassFtable(((DWORD)GameOffset + 0x5973B4),(DWORD)&CSE_ALifeHumanStalker__UPDATE_Read,0x4);

	// CWrapperAbstractMonster<class CSE_ALifeMonsterBase>::UPDATE_Write
	JoinInClassFtable(((DWORD)GameOffset + 0x5971B0),(DWORD)&CSE_ALifeMonsterBase__UPDATE_Write,0x4);
	// CWrapperAbstractMonster<class CSE_ALifeMonsterBase>::UPDATE_Read
	JoinInClassFtable(((DWORD)GameOffset + 0x5971B4),(DWORD)&CSE_ALifeMonsterBase__UPDATE_Read,0x4);

	// CWrapperAbstractMonster<class CSE_ALifePsyDogPhantom>::UPDATE_Write
	JoinInClassFtable(((DWORD)GameOffset + 0x598480),(DWORD)&CSE_ALifePsyDogPhantom__UPDATE_Write,0x4);
	// CWrapperAbstractMonster<class CSE_ALifePsyDogPhantom>::UPDATE_Read
	JoinInClassFtable(((DWORD)GameOffset + 0x598484),(DWORD)&CSE_ALifePsyDogPhantom__UPDATE_Read,0x4);
	// CWrapperAbstractMonster<class CSE_ALifeCreaturePhantom>::NeedUpdate (call CSE_ALifeCreatureAbstract::alive)
	Address(((DWORD)GameOffset + 0x597A9C),((DWORD)GameOffset + 0xB1F50));
	// CWrapperAbstractMonster<class CSE_ALifeHumanStalker>::NeedUpdate (call CSE_ALifeCreatureAbstract::alive)
	Address(((DWORD)GameOffset + 0x597404),((DWORD)GameOffset + 0xB1F50));
	// CWrapperAbstractMonster<class CSE_ALifeMonsterBase>::NeedUpdate (call CSE_ALifeCreatureAbstract::alive)
	Address(((DWORD)GameOffset + 0x597204),((DWORD)GameOffset + 0xB1F50));
	// CWrapperAbstractMonster<class CSE_ALifePsyDogPhantom>::NeedUpdate (call CSE_ALifeCreatureAbstract::alive)
	Address(((DWORD)GameOffset + 0x5984D4),((DWORD)GameOffset + 0xB1F50));
	// CWrapperAbstractMonster<class CSE_ALifeCreatureActor>::NeedUpdate (call nullsub (return 0))
	Address(((DWORD)GameOffset + 0x59767C),((DWORD)GameOffset + 0x3BB6E0));
	// other
	// CActor::shedule_Update
	Address(((DWORD)GameOffset + 0x54C818),((DWORD)GameOffset + 0x27F550));
	// CActor::UpdateCL
	JoinInClassFtable(((DWORD)GameOffset + 0x54C880),(DWORD)&CActor__UpdateCL,0x0);

	// Render hooks
	switch(RenderVersion)
	{
		case 1:
		{
			// CKinematicsAnimated::PlayCycle
			JoinInClassFtableEx(((DWORD)RenderOffset + 0x9807C + 0x74),(DWORD)&CKinematicsAnimated__PlayCycle,0x14,pCKinematicsAnimated__PlayCycle);
			break;
		}
		case 2:
		{
			// CKinematicsAnimated::PlayCycle
			JoinInClassFtableEx(((DWORD)RenderOffset + 0xBE7E4 + 0x74),(DWORD)&CKinematicsAnimated__PlayCycle,0x14,pCKinematicsAnimated__PlayCycle);
			break;
		}
		case 3:
		{
			// CKinematicsAnimated::PlayCycle
			JoinInClassFtableEx(((DWORD)RenderOffset + 0xD9C34 + 0x74),(DWORD)&CKinematicsAnimated__PlayCycle,0x14,pCKinematicsAnimated__PlayCycle);
			break;
		}
		case 4:
		{
			// CKinematicsAnimated::PlayCycle
			JoinInClassFtableEx(((DWORD)RenderOffset + 0xE6244 + 0x74),(DWORD)&CKinematicsAnimated__PlayCycle,0x14,pCKinematicsAnimated__PlayCycle);
			break;
		}
	}
	////////////BloodMark Hook
	wchar_t* CmdLine = GetCommandLine();

	//if (wcsstr(CmdLine, TEXT("-bloodmark"))) {
	switch (RenderVersion)
	{
	case 1: {
		Byte((DWORD)(RenderOffset)+0x617D, 1, 0x2D);
		//Nop((DWORD)(RenderOffset)+0x617C, 6);
		//Nop((DWORD)(RenderOffset)+0x6166, 6);
		//Nop((DWORD)(RenderOffset)+0x25B88, 1);
		//Byte((DWORD)(RenderOffset)+0x25B88+1, 1, 0xE9);
		break;
	}
	case 2: {

	}
	case 3: {

	}
	case 4: {

	}
	default:
		break;
	}

	//}
	// correct switch tables
	// CLevel::ClientReceive
	// create MotionsLoc
	void* motions_loc = malloc(14);
	/*
		push ebp
		call MotionsFunc
		add esp, 4h
		jmp 1023B669
	*/
	Byte(((DWORD)motions_loc + 0),1,0x55); // push ebp
	Call(((DWORD)motions_loc + 1),(DWORD)&CLevel__cl_Process_Motion); // call MotionsFunc
	Byte(((DWORD)motions_loc + 6),1,0x83);		// add esp, 4
	Byte(((DWORD)motions_loc + 7),1,0xC4);
	Byte(((DWORD)motions_loc + 8),1,0x4);
	Jmp(((DWORD)motions_loc + 9),((DWORD)GameOffset + 0x23B669));
	// create EventLoc
	void* event_loc = malloc(14);
	/*
		push ebp
		call EventFunc
		add esp, 4h
		jmp 1023B669
	*/
	Byte(((DWORD)event_loc + 0),1,0x55); // push ebp
	Call(((DWORD)event_loc + 1),(DWORD)&CLevel__cl_Process_CustomEvent); // call EventFunc
	Byte(((DWORD)event_loc + 6),1,0x83);		// add esp, 4
	Byte(((DWORD)event_loc + 7),1,0xC4);
	Byte(((DWORD)event_loc + 8),1,0x4);
	Jmp(((DWORD)event_loc + 9),((DWORD)GameOffset + 0x23B669));
	// change switch
	DWORD locations[33] =
	{
		((DWORD)(GameOffset) + 0x23AFCC),((DWORD)(GameOffset) + 0x23AEF7),((DWORD)(GameOffset) + 0x23B2AE),
		((DWORD)(GameOffset) + 0x23B2BB),((DWORD)(GameOffset) + 0x23B2CE),((DWORD)(GameOffset) + 0x23B300),
		((DWORD)(GameOffset) + 0x23B639),((DWORD)(GameOffset) + 0x23B276),((DWORD)(GameOffset) + 0x23B09F),
		((DWORD)(GameOffset) + 0x23AFDF),((DWORD)(GameOffset) + 0x23B325),((DWORD)(GameOffset) + 0x23B3CB),
		((DWORD)(GameOffset) + 0x23B630),((DWORD)(GameOffset) + 0x23AF44),((DWORD)(GameOffset) + 0x23B3D7),
		((DWORD)(GameOffset) + 0x23B3F7),((DWORD)(GameOffset) + 0x23B404),((DWORD)(GameOffset) + 0x23B42C),
		((DWORD)(GameOffset) + 0x23B48C),((DWORD)(GameOffset) + 0x23B3E4),((DWORD)(GameOffset) + 0x23B5F3),
		((DWORD)(GameOffset) + 0x23B622),((DWORD)(GameOffset) + 0x23B1DB),((DWORD)(GameOffset) + 0x23B5E6),
		((DWORD)(GameOffset) + 0x23B454),((DWORD)(GameOffset) + 0x23B46F),((DWORD)(GameOffset) + 0x23B480),
		((DWORD)(GameOffset) + 0x23B657),((DWORD)(GameOffset) + 0x23B661),((DWORD)(GameOffset) + 0x23B081),
		((DWORD)(GameOffset) + 0x23B669),(DWORD)motions_loc,(DWORD)event_loc		
	};
	BYTE jump_table[53] =
	{
		0,1,2,3,
		4,30,30,5,
		6,7,8,9,
		30,10,10,10,
		11,30,30,12,
		13,14,30,15,
		30,16,17,18,
		30,30,19,30,
		20,21,30,30,
		6,22,30,23,
		24,24,30,25,
		26,6,30,27,
		28,30,29,31,
		32
	};
	CreateSwitchTable(locations,33,jump_table,53,((DWORD)(GameOffset) + 0x23AEF3),((DWORD)(GameOffset) + 0x23AEEC),((DWORD)(GameOffset) + 0x23AEE2));

	Launch_Mod_Extension();	// ��������� ������ MoD

	LogHandle->Write("lua_alife__create = 0x%X",lua_alife__create);
	LogHandle->Write("lua_alife = 0x%X",lua_alife);
	LogHandle->Write("F_entity_Create = 0x%X",F_entity_Create);
	LogHandle->Write("ai = 0x%X",ai);
	LogHandle->Write("CObjectItemClientServer_CActor_CSE_ALifeCreatureActor___client_object = 0x%X",CObjectItemClientServer_CActor_CSE_ALifeCreatureActor___client_object);
	LogHandle->Write("pIPureServer__SendTo = 0x%X",pIPureServer__SendTo);
	LogHandle->Write("pCKinematicsAnimated__PlayCycle = 0x%X",pCKinematicsAnimated__PlayCycle);
	LogHandle->Write("pCKinematicsAnimated__PlayCycleEx = 0x%X",pCKinematicsAnimated__PlayCycleEx);
	LogHandle->Write("pCSE_ALifeCreatureCrow__UPDATE_Write = 0x%X",pCSE_ALifeCreatureCrow__UPDATE_Write);
	LogHandle->Write("pCSE_ALifeCreatureCrow__UPDATE_Read = 0x%X",pCSE_ALifeCreatureCrow__UPDATE_Read);
	LogHandle->Write("pCSE_ALifeCreaturePhantom__UPDATE_Write = 0x%X",pCSE_ALifeCreaturePhantom__UPDATE_Write);
	LogHandle->Write("pCSE_ALifeCreaturePhantom__UPDATE_Read = 0x%X",pCSE_ALifeCreaturePhantom__UPDATE_Read);
	LogHandle->Write("pCSE_ALifeCreatureRat__UPDATE_Write = 0x%X",pCSE_ALifeCreatureRat__UPDATE_Write);
	LogHandle->Write("pCSE_ALifeCreatureRat__UPDATE_Read = 0x%X",pCSE_ALifeCreatureRat__UPDATE_Read);
	LogHandle->Write("pCSE_ALifeHumanStalker__UPDATE_Write = 0x%X",pCSE_ALifeHumanStalker__UPDATE_Write);
	LogHandle->Write("pCSE_ALifeHumanStalker__UPDATE_Read = 0x%X",pCSE_ALifeHumanStalker__UPDATE_Read);
	LogHandle->Write("pCSE_ALifeMonsterBase__UPDATE_Write = 0x%X",pCSE_ALifeMonsterBase__UPDATE_Write);
	LogHandle->Write("pCSE_ALifeMonsterBase__UPDATE_Read = 0x%X",pCSE_ALifeMonsterBase__UPDATE_Read);
	LogHandle->Write("pCSE_ALifeTrader__UPDATE_Write = 0x%X",pCSE_ALifeTrader__UPDATE_Write);
	LogHandle->Write("pCSE_ALifeTrader__UPDATE_Read = 0x%X",pCSE_ALifeTrader__UPDATE_Read);
	LogHandle->Write("pCSE_ALifePsyDogPhantom__UPDATE_Write = 0x%X",pCSE_ALifePsyDogPhantom__UPDATE_Write);
	LogHandle->Write("pCSE_ALifePsyDogPhantom__UPDATE_Read = 0x%X",pCSE_ALifePsyDogPhantom__UPDATE_Read);
	LogHandle->Write("pUPDATE_Write_call_address = 0x%X",pUPDATE_Write_call_address);
	LogHandle->Write("pUPDATE_Read_call_address = 0x%X",pUPDATE_Read_call_address);
	LogHandle->Write("pCALifeSimulator__CALifeSimulator = 0x%X",pCALifeSimulator__CALifeSimulator);
	LogHandle->Write("pCGameGraph__CGameGraph = 0x%X",pCGameGraph__CGameGraph);
	LogHandle->Write("pCLevel__IsServer = 0x%X",pCLevel__IsServer);
	LogHandle->Write("pCAI_Space__load = 0x%X",pCAI_Space__load);
	LogHandle->Write("pCAI_Space__reinit = 0x%X",pCAI_Space__reinit);
	LogHandle->Write("pCAI_Space__patrol_path_storage = 0x%X",pCAI_Space__patrol_path_storage);
	LogHandle->Write("pCActor__NeedToDestroyObject = 0x%X",pCActor__NeedToDestroyObject);
	LogHandle->Write("pCActor__TimePassedAfterDeath = 0x%X",pCActor__TimePassedAfterDeath);
	LogHandle->Write("pCDestroyer__CALifeSimulator__delete = 0x%X",pCDestroyer__CALifeSimulator__delete);
	LogHandle->Write("pCScriptStorage__load_file_into_namespace = 0x%X",pCScriptStorage__load_file_into_namespace);
	LogHandle->Write("pCScriptBinder__reload = 0x%X",pCScriptBinder__reload);
	LogHandle->Write("pCScriptBinder__reinit = 0x%X",pCScriptBinder__reinit);
	LogHandle->Write("pCScriptBinder__net_spawn = 0x%X",pCScriptBinder__net_spawn);
	LogHandle->Write("pCActor__CActor = 0x%X",pCActor__CActor);
	LogHandle->Write("pCSE_ALifeCreatureActor__CSE_ALifeCreatureActor = 0x%X",pCSE_ALifeCreatureActor__CSE_ALifeCreatureActor);
	LogHandle->Write("CSE_ALifeCreatureActor__ftable = 0x%X",CSE_ALifeCreatureActor__ftable);
	LogHandle->Write("CSE_ActorMP__ftable = 0x%X",CSE_ActorMP__ftable);
	LogHandle->Write("CAI_Bloodsucker__ftable = 0x%X",CAI_Bloodsucker__ftable);
	LogHandle->Write("CAI_Boar__ftable = 0x%X",CAI_Boar__ftable);
	LogHandle->Write("CAI_Crow__ftable = 0x%X",CAI_Crow__ftable);
	LogHandle->Write("CAI_Dog__ftable = 0x%X",CAI_Dog__ftable);
	LogHandle->Write("CAI_Flesh__ftable = 0x%X",CAI_Flesh__ftable);
	LogHandle->Write("CAI_PseudoDog__ftable = 0x%X",CAI_PseudoDog__ftable);
	LogHandle->Write("CAI_Rat__ftable = 0x%X",CAI_Rat__ftable);
	LogHandle->Write("CAI_Stalker__ftable = 0x%X",CAI_Stalker__ftable);
	LogHandle->Write("CAI_Trader__ftable = 0x%X",CAI_Trader__ftable);
	LogHandle->Write("CBurer__ftable = 0x%X",CBurer__ftable);
	LogHandle->Write("CCat__ftable = 0x%X",CCat__ftable);
	LogHandle->Write("CChimera__ftable = 0x%X",CChimera__ftable);
	LogHandle->Write("CController__ftable = 0x%X",CController__ftable);
	LogHandle->Write("CFracture__ftable = 0x%X",CFracture__ftable);
	LogHandle->Write("CPhantom__ftable = 0x%X",CPhantom__ftable);
	LogHandle->Write("CPoltergeist__ftable = 0x%X",CPoltergeist__ftable);
	LogHandle->Write("CPseudoGigant__ftable = 0x%X",CPseudoGigant__ftable);
	LogHandle->Write("CPsyDog__ftable = 0x%X",CPsyDog__ftable);
	LogHandle->Write("CPsyDogPhantom__ftable = 0x%X",CPsyDogPhantom__ftable);
	LogHandle->Write("CSnork__ftable = 0x%X",CSnork__ftable);
	LogHandle->Write("CTushkano__ftable = 0x%X",CTushkano__ftable);
	LogHandle->Write("CZombie__ftable = 0x%X",CZombie__ftable);
	LogHandle->Write("gGameOffset = 0x%X",gGameOffset);
	LogHandle->Write("gActorPointer = 0x%X",gActorPointer);
	LogHandle->Write("Actor = 0x%X", actor);
}
/*
void CHook_Patch_02::MessangeRecieved(string msg) {
	DWORD CLevel = (DWORD)g_pGameLevel;
	DWORD game_cl_GameState = (DWORD)((DWORD*)CLevel + 0x486F8);
	unsigned int ClientID = (unsigned int)*((DWORD*)game_cl_GameState + 0xBC);
	
	CHook_Patch_02* hook = static_cast<CHook_Patch_02*>(HookHandle);

	hook->messanges[ClientID]->push_back(msg);

	Msg("MessangeRecieved %d %s",ClientID,msg.c_str());
	
}*/



bool is_server() {
	return HookHandle->IsServer();
}
bool is_dedicated() {
	return HookHandle->IsDedicated();
}

bool CHook_Patch_02::IsDedicated() {

	DWORD g_pAI_Space = ai();
	DWORD alife = (DWORD) ((DWORD*)g_pAI_Space + 0x14);

	return *((bool*) (GetProcAddress(GetModuleHandle(L"xrEngine.exe"),"?g_dedicated_server@@3_NA")));
}

//good way to create C function without prolog and epilog
__declspec(naked) void messange_listner_asm(){ 
	_asm {
	}
}

LPCSTR get_event_client() {
	if (HookHandle->IsServer() && HookHandle->IsDedicated()) {
		Msg("ERROR: get_event_client called at server dedicated side!");
	}
	if (HookHandle->messanges_cl.size()) {
		string* result = new string;
		result->assign(HookHandle->messanges_cl.front().c_str());
		HookHandle->messanges_cl.pop_front();

		return result->c_str();
	}
	return "";
}

LPCSTR get_event_server() {
	if (!HookHandle->IsServer()) {
		Msg("ERROR: get_event_server called at client side!");
	}
	if (HookHandle->messanges_sv.size()) {
		string* result = new string;
		result->assign(HookHandle->messanges_sv.front().c_str());
		HookHandle->messanges_sv.pop_front();

		return result->c_str();
	}
	return "";
	 


	//WORKED BUT NOT NEED
	/*game_sv_GameState__count_players = reinterpret_cast<unsigned int (_cdecl *)()>(GetProcAddress(GetModuleHandle(L"xrNetServer.dll"),"?GetClientsCount@IPureServer@@QAEIXZ"));
	IPureServer* pPureServer = (IPureServer*)*(DWORD*)((DWORD)g_pGameLevel + 0x48730);
	
	unsigned int count = unsigned int(-1);

	_asm {
		mov ecx, pPureServer
		call game_sv_GameState__count_players
		mov count, eax
	}

	LogHandle->Write("client_id_by_obj_id count %d id %d",count,id);

	DWORD CLevel = (DWORD)g_pGameLevel;
	LogHandle->Write("2");
	DWORD xrServerHandle = *(DWORD*)(CLevel + 0x48730);
	LogHandle->Write("3");
	DWORD game_cl_GameState = *(DWORD*)(xrServerHandle + 0x98E14);			//????
	LogHandle->Write("4");
	LogHandle->Write("3.5 %d",(unsigned int)(*((DWORD*)(game_sv_GameState + 0x10))));
	LogHandle->Write("4");
	game_sv_GameState__get_entity_from_eid = reinterpret_cast<CSE_Abstract* (_cdecl *)(unsigned short)>(GetProcAddress(GetModuleHandle(L"xrNetServer.dll"),"?ID_to_client@IPureServer@@IAEPAVIClient@@VClientID@@_N@Z"));
	*/

	
	/*
	//WORKED BUT NOT NEED
	DWORD result = 0x0;

	_asm {
		push id
		mov ecx, pPureServer
		call game_sv_GameState__get_entity_from_eid
		mov result, eax
	}
	CSE_Abstract* entry = (CSE_Abstract*)result;
	if (entry) {
		xrClientData* entry_owner = entry->owner;				//xrClientDataPointer
		if (entry_owner) {
			Ga* 
				8178h
			if (entry) {
			} else {
				LogHandle->Write("entry is null");
			}
		} else {
			LogHandle->Write("entry_owner is null");
		}
	} else {
		LogHandle->Write("entry is null");
	}
	*/


}


unsigned int get_local_player() {
	return g_pGameLevel->pCurrentEntity->ID();
}


unsigned int get_local_client_id() {
	DWORD CLevel = (DWORD)g_pGameLevel;
	DWORD game_cl_GameState = *(DWORD*)(CLevel+0x486F8);

	DWORD cl_id = *(DWORD*)(game_cl_GameState+0xBC);

	Msg("client_id %x",cl_id);
	return cl_id;
}

void add_money_mp(unsigned short ident, float money_f) {
	int money = (int)money_f;
	Msg("1 %d %d",ident,money);

	if (HookHandle->IsServer()) {
		ClientID cl_id;
		cl_id.set(get_local_client_id());
		HookHandle->Add_money_mp(cl_id);
	} else {
		NET_Packet pack;
		pack.write_start();
		pack.w_begin(0x32);		
		pack.w_u8(e_so_engine_packet);
		pack.w_u8(e_add_money);

		ClientID cl_id;
		cl_id.set(get_local_client_id());
		pack.w_clientID(cl_id);

		send_data_to_server_engine(&pack);
	}

	
	return;
}

void send_data_to_server_script(LPCSTR data,bool b) {
	if (HookHandle->IsServer()) {
		Msg("send_data_to_server_script '%s' from server to client",data);
		NET_Packet pack;
		pack.write_start();
		pack.w_begin(0x34);		
		pack.w_u8(e_so_script_packet);
		pack.w_stringZ(data);
	
		HookHandle->SendPacketToAll(pack);
	} else {
		Msg("send_data_to_server_script '%s' from client to server",data);
		
		DWORD CLevel = (DWORD)g_pGameLevel;
		DWORD game_cl_GameState = (DWORD)(*(DWORD*)CLevel + 0x486F8);
		NET_Packet P;
		P.write_start();
		P.w_begin(0x32);
		P.w_u8(e_so_script_packet);
		P.w_stringZ(data);
		DWORD pointer = (DWORD)&P;
		_asm {
			push pointer
			mov ecx, game_cl_GameState
			call game_cl_GameState__u_EventSend
		}
	}
}

void send_data_to_server_engine(NET_Packet *P) {
	if (HookHandle->IsServer()) {
		Msg("send_data_to_server_engine from server to client");
	
		HookHandle->SendPacketToAll(*P);
	} else {
		Msg("send_data_to_server_engine from client to server");
		
		DWORD CLevel = (DWORD)g_pGameLevel;
		DWORD game_cl_GameState = (DWORD)(*(DWORD*)CLevel + 0x486F8);
		_asm {
			push P
			mov ecx, game_cl_GameState
			call game_cl_GameState__u_EventSend
		}
	}
}

void script_log(LPCSTR data,bool b) {
	LogHandle->Write(data);
}

WORD CHook_Patch_02::CreateObject(char* section,char* name,float pos_x,float pos_y,float pos_z,WORD parentid)
{
	float position[3];
	position[0] = pos_x;
	position[1] = pos_y;
	position[2] = pos_z;

	unsigned long result = lua_alife__create(lua_alife(),section,position,0,0,parentid);

	unsigned short objectid = *(unsigned short*)(result + 0x32);

	// null custom sync
	CustomSyncData_Entity[objectid] = NULL;

	// return objectid
	return objectid;
}

void CHook_Patch_02::PlayCycle(DWORD pClass,DWORD MotionID)
{
	// base data
	DWORD pIRender_Visual = (DWORD)((CObject*)pClass)->Visual();
	DWORD pCKinematicsAnimated = pIRender_Visual + 0xB0;
	DWORD pObject = pClass;
	
	// anticrash
	for(DWORD mid = 0;mid < 4;mid++)
	{
		DWORD array_addr = pIRender_Visual + 0x44D8 + 0x104 * mid;
		for(DWORD i = 0;i < *(DWORD*)(array_addr + 0x100);i++)
		{
			DWORD item = *(DWORD*)(array_addr + 4*i);
			if(!item) return;
		}
	}

	_asm
	{
		push 0				// HZ = 0
		push pObject		
		push 0				// IBlend
		push 1				// HZ = 1
		push MotionID
		mov ecx, pCKinematicsAnimated
		call pCKinematicsAnimated__PlayCycle
	};
}

void CHook_Patch_02::PlayCycleEx(DWORD pClass,DWORD unk,DWORD MotionID)
{
	// base data
	DWORD pIRender_Visual = (DWORD)((CObject*)pClass)->Visual();
	DWORD pCKinematicsAnimated = pIRender_Visual + 0xB0;
	DWORD pObject = pClass;

	// anticrash
	for(DWORD mid = 0;mid < 4;mid++)
	{
		DWORD array_addr = pIRender_Visual + 0x44D8 + 0x104 * mid;
		for(DWORD i = 0;i < *(DWORD*)(array_addr + 0x100);i++)
		{
			DWORD item = *(DWORD*)(array_addr + 4*i);
			if(!item) return;
		}
	}

	_asm
	{
		push 0				// HZ = 0
		push pObject		
		push 0				// IBlend
		push 1				// HZ = 1
		push MotionID
		push unk
		mov ecx, pCKinematicsAnimated
		call pCKinematicsAnimated__PlayCycleEx
	};
}

void CHook_Patch_02::Add_money_mp(ClientID cl_id) {
	IPureServer* pPureServer = (IPureServer*)*(DWORD*)((DWORD)g_pGameLevel + 0x48730);
	IPureServer__ID_to_client = reinterpret_cast<DWORD* (_cdecl *)(ClientID,bool)>(GetProcAddress(GetModuleHandle(L"xrNetServer.dll"),"?ID_to_client@IPureServer@@IAEPAVIClient@@VClientID@@_N@Z"));


	DWORD pIClient = 0x0;
	_asm {
		mov ecx, pPureServer
		push 0
		push cl_id
		call IPureServer__ID_to_client
		mov pIClient, eax
	}

	Msg("pIClient %p",pIClient);
	DWORD player_state = *(DWORD*)(pIClient + 0x8178);
	Msg("%p Name %s",player_state,*(DWORD*)(player_state+0x72) + 0x10);

	//DWORD xrServerHandle = *(DWORD*)((DWORD)g_pGameLevel + 0x48730);
	//DWORD game_sv_GameState = *(DWORD*)(xrServerHandle + 0x98E14);
	DWORD game_sv_mp__Player_AddMoney = ((DWORD)GameOffset + 0x38ECB0);
	
	_asm {
		mov ecx, g_pGameLevel
		mov edx, [ecx]
		mov eax, [edx+48730h]
		mov ecx, [eax+98E14h]

		push 100
		push player_state
		call game_sv_mp__Player_AddMoney
	}

}

void CHook_Patch_02::SendPacketToAll(NET_Packet& pack)
{
	IPureServer* pPureServer = (IPureServer*)*(DWORD*)((DWORD)g_pGameLevel + 0x48730);
	DWORD ClientList = ((DWORD)pPureServer + 0x34);
	DWORD CurrentClient = *(DWORD*)(ClientList + 0x4);
	DWORD LastClient = *(DWORD*)(ClientList + 0x8);

	while(CurrentClient != LastClient)
	{
		DWORD Client_id = *(DWORD*)(*(DWORD*)CurrentClient + 0x80C0);

		if(*(DWORD*)(*(DWORD*)CurrentClient + 0x8170))
		{
			_asm
			{
				push 0
				push 8
				push pack
				push Client_id
				mov ecx, pPureServer
				call pIPureServer__SendTo
			};
		}

		CurrentClient += 0x4;
	}
}

bool CHook_Patch_02::IsServer()
{
	DWORD CLevel = (DWORD)g_pGameLevel;
	bool result = false;

	_asm
	{
		mov ecx, CLevel
		call pCLevel__IsServer
		mov result, al
	};

	return result;
}

void CHook_Patch_02::LoadAImap()
{
	char path[520];
	IReader* chunk;
	DWORD g_pAI_Space = ai();
	if(xr_FS->exist(path,LevelDirectory,LevelAlifeSpawnFile,".spawn"))
	{
		IReader* spawn_file = xr_FS->r_open(path);
		if(spawn_file)
		{
			chunk = spawn_file->open_chunk(3);
			if(chunk)
			{
				// path storage
				_asm
				{
					push chunk
					mov ecx, g_pAI_Space
					call pCAI_Space__patrol_path_storage
				}
				// close
				chunk->close();
			}
			chunk = spawn_file->open_chunk(4);
			if(chunk)
			{
				// GameGraph load
				void* CGameGraph = Memory->mem_alloc(0x54);
				_asm
				{
					push chunk
					mov ecx, CGameGraph
					call pCGameGraph__CGameGraph
				}
				// reinit
				_asm
				{
					push CGameGraph
					mov ecx, g_pAI_Space
					call pCAI_Space__reinit
				}
			}
		}
	}
	// get game map name
	IPureClient* client = (IPureClient*)((DWORD)g_pGameLevel + 0x40110);
	const char* gamemap = client->net_SessionName();
	// load ai map
	_asm
	{
		push gamemap
		mov ecx, g_pAI_Space
		call pCAI_Space__load
	}
}

void CHook_Patch_02::LoadMapScript()
{
	char path[520];
	char* _path = path;
	DWORD pCScriptStorage = *(DWORD*)(ai() + 0x1C);

	if(xr_FS->exist(path,LevelDirectory,LevelScriptFile,".script"))
	{
		_asm
		{
			mov ecx, pCScriptStorage
			push LevelScriptFile
			push _path
			call pCScriptStorage__load_file_into_namespace
		}
		LogHandle->Write("level script exist");
		
	}
	else LogHandle->Write("level script (%s) not exist",_path);
}

// Other functions

void game_sv_mp__Create_fix(DWORD pClass,DWORD a2)
{
	PUSH_REG(ecx)

	// vars
	void* pCALifeSimulator = NULL;
	DWORD param_1 = 0;	

	// relink addresses
	HookHandle->LinkAddresses();

	// ALifeSimulator
	pCALifeSimulator = HookHandle->Memory->mem_alloc(0x2FC);
	if(pCALifeSimulator) 
	{
		param_1 = *(DWORD*)(pClass + 0x98);
		_asm
		{
			push 1
			push a2
			push param_1
			mov ecx, pCALifeSimulator
			call pCALifeSimulator__CALifeSimulator
		}
		*(DWORD*)(pClass + 0x4170) = (DWORD)pCALifeSimulator;
	}
	
	POP_REG(ecx)
}

void Hook_onEat_callback(WORD pClass, WORD ID) 
{
	PUSH_REG(ecx)
	CObject* Obj = g_pGameLevel->ObjectList.objects[ID]; //Find obj by id
	DWORD CurActor = (DWORD)gGameOffset + 0x64E2C0; // actor
	_asm {
		mov cx, ID
		mov ecx, Obj
		call CGameObject__lua_game_object //Obj->lua_game_object()
		push eax						  //(eax = lua_game_object())
		push 0Fh						  // Callback id = eUseObject(15, 0xf)
		mov  ecx, CurActor				  // (Actor obj)
		mov  ecx, [ecx]
		call CGameObject__callback		  // Callback create
		mov ecx, eax
		call CGameObject__CScriptCallbackEx // Callback call
		mov cx, ID 
	}
	POP_REG(ecx)
}

void Hook_Open_PDA() //��� �� ������� ������ ���
{
	DWORD game_cl_Deathmatch__OnKeyboardPress_ShowScore = gGameOffset + 0x35515E; //Show score
	DWORD game_cl_Deathmatch__OnKeyboardPress_Next = gGameOffset + 0x35517D; //Next code
	DWORD CUIGameCustom__ShowPdaMenu = gGameOffset + 0x4B61DF; //Show PDA

	__asm {
		cmp edi, 33h //if key PDA
		jz Pda
		cmp edi, 29h //if key Score
		jnz Score
		jmp game_cl_Deathmatch__OnKeyboardPress_ShowScore

		Score:
			jmp game_cl_Deathmatch__OnKeyboardPress_Next

		Pda:
			jmp CUIGameCustom__ShowPdaMenu
	}
}

void Hook_open_dialog()
{
	DWORD UIGameSP__TryTALK = gGameOffset + 0x4B5A50;//0x4B5A50
	DWORD UIGameSP__GETUI = gGameOffset + 0x164960;//0x2783AA test 2B1458
	DWORD CUIGameCustom__CurentGameUI = gGameOffset + 0x4AFD90;

	_asm {
		//push dword ptr[esp + 0Ch]
		//call CUIGameCustom__CurentGameUI
		////movzx   ecx, byte ptr[edi + 20h]
		//push eax
		movzx ecx, byte ptr[edi + 20h]
		push ecx
		//call UIGameSP__GETUI
		//add esp, 4
		//mov eax, esp
		//push dword ptr[eax+0Ch]
		//mov eax, [ecx+6Ch]
		//mov eax, [eax+8]
		//mov eax, [eax+6Ch]
		//push dword ptr[eax+6Ch+8]
		mov ecx, eax
		//push 1
		call UIGameSP__TryTALK
	}
}

void Hook_CPhysicObject_Door_Disable_Interpolation()
{
	PUSH_REG(ecx)
	DWORD obj;
	_asm {
		mov obj, esi
	}
	CObject* PhObj = (CObject*)obj;
	if (!strcmp(PhObj->cNameSect_str(), "physic_door")) {
		return;
	}
	else
	{
		_asm {
			mov edx, [obj]
			mov eax, [edx + 1E8h]
			mov ecx, obj
			call eax
		}
	}
	POP_REG(ecx)
}

void Hook_CHudItem_SwitchState(DWORD pClass, DWORD State)
{
	PUSH_REG(ecx)
	DWORD CCustomDetector__OnStateSwitch = gGameOffset + 0x2EC8C0;
	DWORD CCustomDetector__STATE = gGameOffset + 0x2EC8C0;
	DWORD CCustomDetector__OnStateSwitch_exit = gGameOffset + 0x2F95FD;

	LogHandle->Write("det_test12: %u, %u", pClass, State);
	CObject* Obj = (CObject*)pClass;
	if (Obj->getDestroy()) {
		return;
	}
	LogHandle->Write("det_test14: %u, %u", pClass, State);
	if (!strcmp(Obj->cNameSect_str(), "detector_simple") && !HookHandle->IsServer()) {
		LogHandle->Write("det_test2: %s, %u",Obj->cNameSect_str(), State);
		_asm {
			push State
			call CCustomDetector__OnStateSwitch
		}
		LogHandle->Write("det_test3: %u, %u", pClass, State);
		return;
	}
	LogHandle->Write("det_test16: %u, %u", pClass, State);
	POP_REG(ecx)
}

void Hook_xrServerSendEvent_det(ClientID cl_id, NET_Packet& pack)
{
	//PUSH_REG(ecx)
	LogHandle->Write("test: %u", cl_id.value());
	//HookHandle->SendPacketToAll(pack);
	DWORD CLID = cl_id.value();
	IPureServer* pPureServer = (IPureServer*)*(DWORD*)((DWORD)g_pGameLevel + 0x48730);
	LogHandle->Write("test1: %u", cl_id.value());
	//LogHandle->Write("test: %u", pClass2);
	if (cl_id.value() < 65535)
	{
		_asm
		{
			push 0
			push 8
			push pack
			push cl_id
			mov ecx, pPureServer
			call pIPureServer__SendTo
		};
	}
	LogHandle->Write("test2: %u", cl_id.value());
	//return;
	//POP_REG(ecx)
}

void Launch_Mod_Extension() //���������� �� MoD Team(DiR.X)
{
	wchar_t* CmdLine = GetCommandLine();

	//������ Fov
	long double  fov = 55.0f; //��� �� ���������


	if (wcsstr(CmdLine, TEXT("-fov")))
	{
		wchar_t* fovT = wcsstr(CmdLine, TEXT("-fov "));
		fovT = wcsstr(fovT, TEXT(" "));
		fov = wcstold(fovT, NULL);
		if (fov > 100.0f) {
			fov = 100.0f;
		}
		if (fov < 50.0f) {
			fov = 50.0f;
		}
	}
	HookHandle->FloatToHex((DWORD)(gGameOffset)+0x635C44, (float)fov);

	//������ �������.
	if (wcsstr(CmdLine, TEXT("-circle_crosshair")))
	{
		HookHandle->Nop((DWORD)(gGameOffset)+0x4D9439, 6);
	}

	///////////���������� ������? ����?
	unsigned char SkinCount = SKIN_COUNTS; //6 ������

	HookHandle->Byte((DWORD)(gGameOffset)+0x4D05AD, 1, SkinCount);
	HookHandle->Byte((DWORD)(gGameOffset)+0x4D0471, 1, SkinCount);
	HookHandle->Byte((DWORD)(gGameOffset)+0x4D0BF5, 1, SkinCount);
	HookHandle->Byte((DWORD)(gGameOffset)+0x4D0CF8, 1, SkinCount);
	HookHandle->Byte((DWORD)(gGameOffset)+0x4CFEE2, 1, SkinCount);
	HookHandle->Byte((DWORD)(gGameOffset)+0x4CFF46, 1, SkinCount);
	HookHandle->Byte((DWORD)(gGameOffset)+0x4CFFD8, 1, SkinCount - 0x01);
	HookHandle->Byte((DWORD)(gGameOffset)+0x4CFFFB, 1, 0x100 - SkinCount);
	HookHandle->Byte((DWORD)(gGameOffset)+0x4D001E, 1, 0x100 - SkinCount);
	///////////////////////////////////////////////////////
	// ���� ���� �� ���������� �������
	unsigned char PlayerCount = MAX_PLAYER_SLOTS; //64 ������
	HookHandle->Byte((DWORD)(gGameOffset)+0x45F244, 1, PlayerCount);
	HookHandle->Byte((DWORD)(gGameOffset)+0x45F258, 1, PlayerCount);
	HookHandle->Byte((DWORD)(gGameOffset)+0x439308, 1, PlayerCount);
	HookHandle->Byte((DWORD)(gServerOffset)+0xA2FC, 1, PlayerCount);
	HookHandle->Byte((DWORD)(gServerOffset)+0xA310, 1, PlayerCount);
	//////////////////////////////////////////////////////

#ifdef FIX_SPACE_RESTRICTORS_FOR_DEDICATED
	// ���� ����� ������������ �� �������� �������.
	HookHandle->Nop((DWORD)(gGameOffset)+0x346C7D, 1);
	HookHandle->Byte((DWORD)(gGameOffset)+0x346C7D + 1, 1, 0xE9);
#endif

	
#ifdef NO_MONEY_LIMIT
	// ������� ����������� � 1000000��
	HookHandle->Byte((DWORD)(gGameOffset)+0x38ECF8, 1, 0x15);
	HookHandle->Nop((DWORD)(gGameOffset)+0x38ED01, 13);
#endif


	// ������� ��� � �������� �� �� ����� ������ ������ ������
	HookHandle->Byte((DWORD)(gGameOffset)+0x2A9AF0, 1, 0x74);
	HookHandle->Byte((DWORD)(gGameOffset)+0x2A9AFD, 1, 0xEB);
	HookHandle->Call((DWORD)(gGameOffset)+0x25D207, (DWORD)&Hook_onEat_callback);

	// Mp_rank fix?? ��� ���������� ������ ����������� ������ � mp_rank ���� �� ��������� �� ������� ���� 0
	HookHandle->Byte((DWORD)(gGameOffset)+0x4CCC32, 1, 0x00);
	HookHandle->Byte((DWORD)(gGameOffset)+0x4CCC32 + 1, 1, 0x00);
	HookHandle->Byte((DWORD)(gGameOffset)+0x4CCC32 + 2, 1, 0x00);
	HookHandle->Byte((DWORD)(gGameOffset)+0x4CCC32 + 3, 1, 0x00);

	
#ifdef FIX_SOC_SLOPES
	// ������� ��� � ��?
	HookHandle->Nop((DWORD)(gGameOffset)+0x262161, 2);				// �� ������� ������
	HookHandle->Nop((DWORD)(gGameOffset)+0x25F485, 2);				// �� ������� ������
	HookHandle->Byte((DWORD)(gGameOffset)+0x278453, 1, 0xEB);		// ��������� ��������
	HookHandle->Byte((DWORD)(gGameOffset)+0x278477, 1, 0xEB);		// ��������� �������� �� ���� ����� ���������� ������. � ����� ������?
	HookHandle->Byte((DWORD)(gGameOffset)+0x25CEAF, 1, 0x75);		// ������ �������
#endif


#ifdef FIX_BOLT_AND_PDA_SPAWN
	// ����� ������ / ��� (���� ��������� ��� �������-������� ����� �������, ����� ����, ����� ������)
	HookHandle->Nop((DWORD)(gGameOffset)+0x2B1828, 4);
	HookHandle->Nop((DWORD)(gGameOffset)+0x2B185D, 10);
	HookHandle->Nop((DWORD)(gGameOffset)+0x2B186F, 13);
#endif


#ifdef ACTIVE_BOLT_KEY
	// ���������� ������ �����
	HookHandle->Byte((DWORD)(gGameOffset)+0x2A99B2, 1, 0xEB);
#endif


#ifdef HIDE_WEAPON_ON_PRESS_ACTIVE_BUT
	// ������ ������ �� ������� �� ������ �������� �����.
	HookHandle->Byte((DWORD)(gGameOffset)+0x2A82A0, 1, 0x84);
#endif

	// ��������� �����. ��� ������ �� �������((
	//HookHandle->Nop((DWORD)(gGameOffset)+0x46CB46, 13);

#ifdef VODKA_EFFECT
	// ������ �����
	HookHandle->Nop((DWORD)(gGameOffset)+0x27729F, 8);
	HookHandle->Nop((DWORD)(gGameOffset)+0x27736A, 6);
	HookHandle->Nop((DWORD)(gGameOffset)+0x277376, 6);
#endif


#ifdef NEED_SATIETY
	// �����    
	HookHandle->Byte((DWORD)(gGameOffset)+0x2751A2, 1, 0x75);
#endif


#ifdef WEAPON_AMMO_INFO
	// �������� �����
	HookHandle->Byte((DWORD)(gGameOffset + 0x4530AA), 1, 0x84);
	HookHandle->Byte((DWORD)(gGameOffset + 0x453D18), 1, 0x84);
#endif

#ifdef NPC_INFO_ON_CROSHAIR
	//��������� ��� �� �����������.
	HookHandle->Byte((DWORD)(gGameOffset + 0x2B227C), 1, 0x84);
	HookHandle->Byte((DWORD)(gGameOffset + 0x4D8EAD), 1, 0x84);
#endif

#ifdef INV_BOX_FIX
	// Inv Box 
	HookHandle->Jmp(((DWORD)gGameOffset + 0x27813C), ((DWORD)gGameOffset + 0x278153)); // disable smart cast?
	HookHandle->Byte((DWORD)(gGameOffset + 0x3897C3), 1, 0xEB);		// OnTouch fix TDM?
	HookHandle->Byte((DWORD)(gGameOffset + 0x437C06), 1, 0xEB);		// ownership fix
	HookHandle->Byte((DWORD)(gGameOffset + 0x437C11), 1, 0xEB);		// ownership fix
	HookHandle->Byte((DWORD)(gGameOffset + 0x437BF1), 1, 0xEB);		// ownership fix
#endif

#ifdef TALK_FIX
	// TALK
	HookHandle->Byte((DWORD)(gGameOffset + 0x2781D7), 1, 0x74);		//talk?
	HookHandle->Jmp(((DWORD)gGameOffset + 0x265C94), ((DWORD)gGameOffset + 0x265CA8)); // Talk disable smart cast 0x265CAF?
	HookHandle->Nop((DWORD)(gGameOffset)+0x265CAC, 3);
#endif


#ifdef DEADBODY_INV_FIX
	// Deadbody INV
	HookHandle->Nop((DWORD)(gGameOffset)+0x164966, 2);				// deadbody? Disable smart cast?
	HookHandle->Byte((DWORD)(gGameOffset + 0x262A1B), 1, 0x84);
#endif


#ifdef OVERWEIGHT_FIX
	// ����������� ����
	HookHandle->Nop((DWORD)(gGameOffset)+0x27535B, 7);
#endif

#ifdef RELOAD_CAMERA
	// ������ ������ ��� �����������
	HookHandle->Nop((DWORD)(gGameOffset)+0x2FEBE3, 13);
	HookHandle->Nop((DWORD)(gGameOffset)+0x2FB55D, 7);
#endif

#ifdef ACTIVE_PDA_AND_DETECTOR_KEY
	//���� ������ ��������� � ���
	HookHandle->Byte((DWORD)(gGameOffset)+0x6346FC, 1, 0x01);		//��������� ������ ��������� � ��� � ��
	HookHandle->Byte((DWORD)(gGameOffset)+0x634864, 1, 0x01);		//
#endif



	// ���� ��������� �� ��������(���� ��������� �������)
	//HookHandle->Nop((DWORD)(gGameOffset)+0x2F959B, 2);//HUDItem  uncheck isclient()
	/*HookHandle->Byte((DWORD)(gGameOffset)+0x436DF7+1, 1, 0xC8); //mov ecx, eax
	HookHandle->Call(((DWORD)(gGameOffset)+0x436DF2), ((DWORD)(gGameOffset)+0x436CF2)); //xrServer:event �������� ��� ���
	HookHandle->Byte((DWORD)(gGameOffset)+0x436CF2, 1, 0x8B); //mov eax, [esp+4140h+arg_4] ;senderid
	HookHandle->Byte((DWORD)(gGameOffset)+0x436CF2 +1, 1, 0x84);
	HookHandle->Byte((DWORD)(gGameOffset)+0x436CF2 +2, 1, 0x24);
	HookHandle->Byte((DWORD)(gGameOffset)+0x436CF2 +3, 1, 0x48);
	HookHandle->Byte((DWORD)(gGameOffset)+0x436CF2 +4, 1, 0x41);
	HookHandle->Byte((DWORD)(gGameOffset)+0x436CF2 +5, 1, 0x00);
	HookHandle->Byte((DWORD)(gGameOffset)+0x436CF2 +6, 1, 0x00);
	HookHandle->Byte((DWORD)(gGameOffset)+0x436CF2 +7, 1, 0xC3); *///return
	/*HookHandle->Byte((DWORD)(gGameOffset)+0x436DF2, 1, 0x8B); //mov eax, [esp+4140h+arg_4] ;senderid
	HookHandle->Byte((DWORD)(gGameOffset)+0x436DF2 + 1, 1, 0x84);
	HookHandle->Byte((DWORD)(gGameOffset)+0x436DF2 + 2, 1, 0x24);
	HookHandle->Byte((DWORD)(gGameOffset)+0x436DF2 + 3, 1, 0x48);
	HookHandle->Byte((DWORD)(gGameOffset)+0x436DF2 + 4, 1, 0x41);
	HookHandle->Byte((DWORD)(gGameOffset)+0x436DF2 + 5, 1, 0x00);
	HookHandle->Byte((DWORD)(gGameOffset)+0x436DF2 + 6, 1, 0x00);
	HookHandle->Byte((DWORD)(gGameOffset)+0x436DF2 + 7, 1, 0x50); //push eax
	HookHandle->Byte((DWORD)(gGameOffset)+0x436DF2 + 8, 1, 0x57); //push edi
	HookHandle->Call(((DWORD)(gGameOffset)+0x436DF2+9), ((DWORD)Hook_xrServerSendEvent_det));
	HookHandle->Nop((DWORD)(gGameOffset)+0x436E00, 6);*/
	//HookHandle->Jmp((DWORD)(gGameOffset)+0x436DF2, (DWORD)(gGameOffset)+0x436E45);
	/*HookHandle->Nop((DWORD)(gGameOffset)+0x2F95B1, 14);
	HookHandle->Nop((DWORD)(gGameOffset)+0x2A8081, 6);
	HookHandle->Nop((DWORD)(gGameOffset)+0x2F95B1, 7);*///�����-�� ����, ����� �������, �� ��� ���� ������ ������.
	//HookHandle->Nop((DWORD)(gGameOffset)+0x2F95BF, 62);
	//���� ��������
	//HookHandle->Byte((DWORD)(gGameOffset)+0x2A9775, 1, 0x15);

	// ����! ������� ����������� �������� � ��� --- Not work?
	HookHandle->Byte((DWORD)(gGameOffset)+0x2BD161, 1, 0x74);		

#ifdef PDA_FIX
	//���
	HookHandle->Nop((DWORD)(gGameOffset)+0x44263E, 6);				//���� ������� ���, ���������� ������� ���
	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61DF, 1, 0x8B);		// ���� PDA! mov ecx, [esi+0FC0h]
	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61DF + 1, 1, 0x8E);	// ���� PDA!
	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61DF + 2, 1, 0xC0);	// ���� PDA!
	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61DF + 3, 1, 0x0F);	// ���� PDA!
	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61DF + 4, 1, 0x00);	// ���� PDA!
	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61DF + 5, 1, 0x00);	// ���� PDA!

	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61EA, 1, 0x5F);		// ���� PDA! pop edi
	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61EA + 1, 1, 0xB0);	// ���� PDA! mov al, 1
	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61EA + 2, 1, 0x01);	// ���� PDA!
	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61EA + 3, 1, 0x5E);	// ���� PDA! pop esi
	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61EA + 4, 1, 0xC2);	// ���� PDA! retn 4
	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61EA + 5, 1, 0x04);	// ���� PDA!
	HookHandle->Byte((DWORD)(gGameOffset)+0x4B61EA + 6, 1, 0x00);	// ���� PDA!
	HookHandle->Nop((DWORD)(gGameOffset)+0x355182, 31);				// ���� PDA! ���� ���������� �����

	HookHandle->Jmp(((DWORD)(gGameOffset)+0x355159), (DWORD)Hook_Open_PDA); //jmp Hook_open_pda ��������� ������� �� ������� ���
#endif

#ifdef FIX_AF_PARTICLE
	//������� �������� �� ����� � �����(�� ��������)
	HookHandle->Byte((DWORD)(gGameOffset + 0x2E43F2), 1, 0x74);

	//Dissable continue for CArtefact item(destroyAllItems)
	HookHandle->Byte((DWORD)(gGameOffset + 0x390D5D), 1, 0xEB);
	HookHandle->Nop((DWORD)(gGameOffset + 0x390D5F), 6);
	HookHandle->Nop((DWORD)(gGameOffset + 0x390D65), 20);
#endif // FIX_AF_PARTICLE

#ifdef ACTOR_SINGLE_MINI_MAP_ICO
	//26D03B ���� ������ �� �����. �� ����� ��� ���������� ������ ��� � ������(�� ������)
	HookHandle->Byte((DWORD)(gGameOffset + 0x26D03B), 1, 0x84);
#endif

	//NPC Reaction FIX
	HookHandle->Byte((DWORD)(gGameOffset + 0x4B8BA), 1, 0xEB);
	//Monster Stay and play animation FIX!
	HookHandle->Nop((DWORD)(gGameOffset + 0x4E671), 10);

	//Boy NEXT Door!
	HookHandle->Call((DWORD)(gGameOffset)+0x2913DC, (DWORD)&Hook_CPhysicObject_Door_Disable_Interpolation);
	HookHandle->Nop((DWORD)(gGameOffset + 0x2913DC+5), 7);
}

void CLevel__Load_GameSpecific_Before_fix()
{
	PUSH_REG(ecx)
	
	// load aimap for client
	if(!HookHandle->IsServer()) // client
	{
		HookHandle->LoadAImap();
		//��������� �� �������
		/*HookHandle->Byte((DWORD)(gGameOffset)+0x2F95B1, 1, 0x57);
		HookHandle->Byte((DWORD)(gGameOffset)+0x2F95B1 + 1, 1, 0x51); //51
		HookHandle->Call(((DWORD)(gGameOffset)+0x2F95B1 + 2), ((DWORD)Hook_CHudItem_SwitchState));
		HookHandle->Byte((DWORD)(gGameOffset)+0x2F95B1 + 7, 1, 0x83); // add esp, 4
		HookHandle->Byte((DWORD)(gGameOffset)+0x2F95B1 + 8, 1, 0xC4);
		HookHandle->Byte((DWORD)(gGameOffset)+0x2F95B1 + 9, 1, 0x08);
		HookHandle->Nop((DWORD)(gGameOffset)+0x2F95B1 + 0xA, 2);
		HookHandle->Nop((DWORD)(gGameOffset)+0x2F95A8, 9);
		HookHandle->Byte((DWORD)(gGameOffset+0x2F95B1 + 0xC), 1, 0xEB);*/
		//HookHandle->Byte((DWORD)(gGameOffset + 0x2F95B6), 1, 0x75);
		//NPC UPDATE Animation remove on client
		HookHandle->Nop((DWORD)(gGameOffset + 0x15E4DE), 2);
	}

	HookHandle->LoadMapScript();

	POP_REG(ecx)
}

DWORD F_entity_Create_fix(DWORD pClass)
{
	return pClass;
}

DWORD CSE_ALifeObject__alife_fix()
{
	return *(DWORD*)(ai() + 0x14);
}

DWORD CActor__net_Spawn_fix(DWORD pClass,DWORD CEntity)
{
	PUSH_REG(ecx)
	
	WORD flags = *(WORD*)(CEntity + 0x43);
	bool is_mp_actor = (*(DWORD*)(pClass) == CActorMP__ftable);
	
	if(is_mp_actor)
	{
		if(flags & 1)
		{
			if (flags & 8) 
			{ 
				*(DWORD*)(gActorPointer) = pClass;
			}
		}
	}
	else
	{
		*(DWORD*)(gActorPointer) = pClass;
		g_actor = pClass;
		*(WORD*)(CEntity + 0x43) = 0x21;
	}

	POP_REG(ecx)
	return 1;
}

unsigned int get_g_actor_id()
{
	if (!actor()) {
		return -1;
	}
	CObject* Obj = (CObject*)actor();
	if (!Obj) {
		return -1;
	}
	return Obj->ID();
}

DWORD CActor__net_Destroy_fix(DWORD CObject)
{
	PUSH_REG(ecx)

	if(*(DWORD*)(gActorPointer) == CObject)
	{
		*(DWORD*)(gActorPointer) = g_actor;
	}

	POP_REG(ecx)
	return 1;
}

DWORD CActor__UpdateCL(DWORD pClass)
{
	PUSH_REG(ecx)

	((CObject*)pClass)->setVisible(0);

	POP_REG(ecx)
}

bool bind_object_fix()
{
	PUSH_REG(ecx)

	bool result;

	if(HookHandle->IsServer()) result = true;
	else result = false;

	POP_REG(ecx)
#ifndef NEED_CLIENT_BIND
	return result;
#else
	return true;
#endif
}

DWORD CALifeGraphRegistry__update_fix(DWORD pClass)
{
	if(*(DWORD*)(pClass) == CSE_ALifeCreatureActor__ftable) return 1;
	return 0;
}

CHook_Patch_02_Client::CHook_Patch_02_Client()
{
	for(int i = 0;i < 0xFFFF;i++) CustomSyncData_Entity[i] = NULL;

	// wait modules load
	while((EngineOffset = GetModuleHandle(L"xrEngine.exe")) == NULL) {}
	while((CoreOffset = GetModuleHandle(L"xrCore.dll")) == NULL) {}
	while((GameOffset = GetModuleHandle(L"xrGame.dll")) == NULL) {}
	while((NetServerOffset = GetModuleHandle(L"xrNetServer.dll")) == NULL) {}
	while(true)
	{
		if((RenderOffset = GetModuleHandle(L"xrRender_R1.dll")) != NULL)
		{
			RenderVersion = 1;
			break;
		}
		if((RenderOffset = GetModuleHandle(L"xrRender_R2.dll")) != NULL)
		{
			RenderVersion = 2;
			break;
		}
		if((RenderOffset = GetModuleHandle(L"xrRender_R3.dll")) != NULL)
		{
			RenderVersion = 3;
			break;
		}
		if((RenderOffset = GetModuleHandle(L"xrRender_R4.dll")) != NULL)
		{
			RenderVersion = 4;
			break;
		}
	}
	while((PhysicsOffset = GetModuleHandle(L"xrPhysics.dll")) == NULL) {}
	while((LuaOffset = GetModuleHandle(L"lua.JIT.1.1.4.dll")) == NULL) {}

	PatchVersion = 2;
}

void CHook_Patch_02_Client::InstallHooks() {
	LogHandle->Write("InstallHooks client");
	void* add_function_to_lvl1 = calloc(200,1);
	//������ �� ��� ��������
	//call		set_weather_register
	Call(((DWORD)add_function_to_lvl1 + 0),(DWORD)GameOffset + 0x2416C7);
	//pop		ecx
	//pop		ecx
	Byte(((DWORD)add_function_to_lvl1 + 5),2,0x59);
	//mov		eax, esp
	Byte(((DWORD)add_function_to_lvl1 + 7),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 8),1,0xC4);
	//push		offset function
	Byte(((DWORD)add_function_to_lvl1 + 9),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 10),(DWORD)&get_g_actor_id);
	//push		offset LevelLocalPlayer
	Byte(((DWORD)add_function_to_lvl1 + 14),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 15),(DWORD)LevelLocalPlayer);
	//push		eax
	Byte(((DWORD)add_function_to_lvl1 + 19),1,0x50);
	//call		get_time_minutes_register
	Call(((DWORD)add_function_to_lvl1 + 20),(DWORD)GameOffset + 0x24199F);
	
	Byte(((DWORD)add_function_to_lvl1 + 25),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 27),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 28),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 29),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 30),(DWORD)&send_data_to_server_script);
	Byte(((DWORD)add_function_to_lvl1 + 34),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 35),(DWORD)SendDataToServer);
	Byte(((DWORD)add_function_to_lvl1 + 39),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 40),(DWORD)GameOffset + 0x2416C7);
	
	
	
	Byte(((DWORD)add_function_to_lvl1 + 45),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 47),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 48),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 49),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 50),(DWORD)&get_event_server);
	Byte(((DWORD)add_function_to_lvl1 + 54),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 55),(DWORD)GetEventServer);
	Byte(((DWORD)add_function_to_lvl1 + 59),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 60),(DWORD)GameOffset + 0x24166C);

	
	Byte(((DWORD)add_function_to_lvl1 + 65),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 67),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 68),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 69),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 70),(DWORD)&is_server);
	Byte(((DWORD)add_function_to_lvl1 + 74),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 75),(DWORD)str_IsServer);
	Byte(((DWORD)add_function_to_lvl1 + 79),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 80),(DWORD)GameOffset + 0x1FF277);

	
	Byte(((DWORD)add_function_to_lvl1 + 85),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 87),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 88),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 89),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 90),(DWORD)&is_dedicated);
	Byte(((DWORD)add_function_to_lvl1 + 94),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 95),(DWORD)str_IsDedicated);
	Byte(((DWORD)add_function_to_lvl1 + 99),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 100),(DWORD)GameOffset + 0x1FF277);
	
	Byte(((DWORD)add_function_to_lvl1 + 105),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 107),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 108),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 109),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 110),(DWORD)&get_event_client);
	Byte(((DWORD)add_function_to_lvl1 + 114),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 115),(DWORD)GetEventClient);
	Byte(((DWORD)add_function_to_lvl1 + 119),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 120),(DWORD)GameOffset + 0x24166C);
	
	Byte(((DWORD)add_function_to_lvl1 + 125),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 127),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 128),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 129),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 130),(DWORD)&script_log);
	Byte(((DWORD)add_function_to_lvl1 + 134),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 135),(DWORD)str_ScriptLog);
	Byte(((DWORD)add_function_to_lvl1 + 139),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 140),(DWORD)GameOffset + 0x2416C7);

	//
	Byte(((DWORD)add_function_to_lvl1 + 145),2,0x59);
	Byte(((DWORD)add_function_to_lvl1 + 147),1,0x8B);
	Byte(((DWORD)add_function_to_lvl1 + 148),1,0xC4);
	Byte(((DWORD)add_function_to_lvl1 + 149),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 150),(DWORD)&add_money_mp);
	Byte(((DWORD)add_function_to_lvl1 + 154),1,0x68);
	Address(((DWORD)add_function_to_lvl1 + 155),(DWORD)str_AddMoneyMP);
	Byte(((DWORD)add_function_to_lvl1 + 159),1,0x50);
	Call(((DWORD)add_function_to_lvl1 + 160),(DWORD)GameOffset + 0x2422DD);


	//
	Jmp(((DWORD)add_function_to_lvl1 + 165),(DWORD) GameOffset + 0x24A71F + 5);


	Jmp(((DWORD)GameOffset + 0x24A71F),(DWORD) add_function_to_lvl1);

	void* add_function_to_lvl2 = malloc(100);
	Byte(((DWORD)add_function_to_lvl2 + 0),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 1),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 2),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 3),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 4),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 5),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 6),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 7),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 8),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 9),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 10),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 11),1,0xD6);
	
	//Add block for each registration!!!
	Byte(((DWORD)add_function_to_lvl2 + 12),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 13),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 14),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 15),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 16),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 17),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 18),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 19),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 20),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 21),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 22),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 23),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 24),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 25),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 26),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 27),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 28),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 29),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 30),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 31),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 32),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 33),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 34),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 35),1,0xD6);
	
	Byte(((DWORD)add_function_to_lvl2 + 36),1,0x8B);
	Byte(((DWORD)add_function_to_lvl2 + 37),1,0xC8);
	Byte(((DWORD)add_function_to_lvl2 + 38),1,0xFF);
	Byte(((DWORD)add_function_to_lvl2 + 39),1,0xD6);

	Jmp(((DWORD)add_function_to_lvl2 + 40),(DWORD)GameOffset + 0x24A762 + 5);

	Jmp(((DWORD)GameOffset + 0x24A762),(DWORD) add_function_to_lvl2);
	Byte(((DWORD)GameOffset + 0x24A762 + 5),3,0x90);



	// correct switch tables
	// CLevel::ClientReceive
	// create MotionsLoc
	void* motions_loc = malloc(14);
	/*
		push ebp
		call MotionsFunc
		add esp, 4h
		jmp 1023B669
	*/
	Jmp(((DWORD)motions_loc + 0),((DWORD)GameOffset + 0x23B669));
	// create EventLoc
	void* event_loc = malloc(14);
	/*
		push ebp
		call EventFunc
		add esp, 4h
		jmp 1023B669
	*/
	Byte(((DWORD)event_loc + 0),1,0x55); // push ebp
	Call(((DWORD)event_loc + 1),(DWORD)&CLevel__cl_Process_CustomEvent); // call EventFunc
	Byte(((DWORD)event_loc + 6),1,0x83);		// add esp, 4
	Byte(((DWORD)event_loc + 7),1,0xC4);
	Byte(((DWORD)event_loc + 8),1,0x4);
	Jmp(((DWORD)event_loc + 9),((DWORD)GameOffset + 0x23B669));
	// change switch
	DWORD locations[33] =
	{
		((DWORD)(GameOffset) + 0x23AFCC),((DWORD)(GameOffset) + 0x23AEF7),((DWORD)(GameOffset) + 0x23B2AE),
		((DWORD)(GameOffset) + 0x23B2BB),((DWORD)(GameOffset) + 0x23B2CE),((DWORD)(GameOffset) + 0x23B300),
		((DWORD)(GameOffset) + 0x23B639),((DWORD)(GameOffset) + 0x23B276),((DWORD)(GameOffset) + 0x23B09F),
		((DWORD)(GameOffset) + 0x23AFDF),((DWORD)(GameOffset) + 0x23B325),((DWORD)(GameOffset) + 0x23B3CB),
		((DWORD)(GameOffset) + 0x23B630),((DWORD)(GameOffset) + 0x23AF44),((DWORD)(GameOffset) + 0x23B3D7),
		((DWORD)(GameOffset) + 0x23B3F7),((DWORD)(GameOffset) + 0x23B404),((DWORD)(GameOffset) + 0x23B42C),
		((DWORD)(GameOffset) + 0x23B48C),((DWORD)(GameOffset) + 0x23B3E4),((DWORD)(GameOffset) + 0x23B5F3),
		((DWORD)(GameOffset) + 0x23B622),((DWORD)(GameOffset) + 0x23B1DB),((DWORD)(GameOffset) + 0x23B5E6),
		((DWORD)(GameOffset) + 0x23B454),((DWORD)(GameOffset) + 0x23B46F),((DWORD)(GameOffset) + 0x23B480),
		((DWORD)(GameOffset) + 0x23B657),((DWORD)(GameOffset) + 0x23B661),((DWORD)(GameOffset) + 0x23B081),
		((DWORD)(GameOffset) + 0x23B669),(DWORD)motions_loc,(DWORD)event_loc		
	};
	BYTE jump_table[53] =
	{
		0,1,2,3,
		4,30,30,5,
		6,7,8,9,
		30,10,10,10,
		11,30,30,12,
		13,14,30,15,
		30,16,17,18,
		30,30,19,30,
		20,21,30,30,
		6,22,30,23,
		24,24,30,25,
		26,6,30,27,
		28,30,29,31,
		32
	};
	CreateSwitchTable(locations,33,jump_table,53,((DWORD)(GameOffset) + 0x23AEF3),((DWORD)(GameOffset) + 0x23AEEC),((DWORD)(GameOffset) + 0x23AEE2));
}