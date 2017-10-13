#include "top.h"

#define watermark "PantsuSDK by p$ilent & Maddie"
/* Pretty Simple And Self Explanatory SDK */
#include "client-entity-list.h"
#include "engine-client.h"
#include "base-client.h"
#include "clientmode.h"
#include "usercmd.h"
#include "panel.h"
#include "surface.h"
#include "hook.h"

CTools * Tools;
IPanel * Panel;
ISurface * Surface;
IClientMode ** ClientMode;
IVEngineClient * EngineClient;
IBaseClientDll * BaseClientDll;
IClientEntityList * ClientEntityList;
CViewSetup * ViewSetup;
INetChannel * NetChannel;
CGlobalVars * Globalvars;
/* cheat */
#include "esp.h"

CHook * PanelHook;
CHook * CreateMoveHook;
CHook * OverrideviewHook;

CESP * ESP;
CRender * Render;

PaintTraverse _PaintTraverse;
CreateMove _CreateMove;

Overrideview _OverrideView;
/* ptrav hook function */
void __stdcall HookedPaintTraverse( int VGUIPanel, bool ForceRepaint, bool AllowForce )
{
	_PaintTraverse( Panel, VGUIPanel, ForceRepaint, AllowForce );

	/* right panel */
	if ( !strcmp( "FocusOverlayPanel", Panel->GetName( VGUIPanel ) ) )
	{
		Render->DrawF(10, 10, CColor(255, 255, 255, 255), 5, 0, watermark);
		if ( EngineClient->IsInGame( ) && EngineClient->IsConnected( ) )
		{
			ESP->Think( );
		}
	}
}

/* cmove hook function */
bool __stdcall HookedCreateMove( float SampleTime, CUserCmd* UserCmd )
{
	if ( !UserCmd->CommandNumber )
		return true;




	if ( EngineClient->IsInGame( ) && EngineClient->IsConnected( ) )
	{
		CBaseEntity * Local = ( CBaseEntity* ) ClientEntityList->GetClientEntity( EngineClient->GetLocalPlayer( ) );
		
		if ( !Local )
			return true;

		/* Auto Bunnyhop */
		if ( UserCmd->Buttons & IN_JUMP )
		{
			if ( !( Local->GetFlags( ) & FL_ONGROUND ) )
			{
				UserCmd->Buttons &= ~IN_JUMP;
			}
		}

	}

	return false;
}

/* main */
void __stdcall Start( )
{
	/* maketools */
	Tools = new CTools;


	/* createinterface the objects we need */
	Panel = ( IPanel* )Tools->GetInterface( "vgui2.dll", "VGUI_Panel009" );
	Tools->PrintToConsole("VGUI_Panel009");
	Surface	= ( ISurface* )Tools->GetInterface( "vguimatsurface.dll", "VGUI_Surface031" );
	Tools->PrintToConsole("VGUI_Surface031");
	EngineClient = ( IVEngineClient* )Tools->GetInterface( "engine.dll", "VEngineClient014" );
	Tools->PrintToConsole("VEngineClient014");
	ClientEntityList = ( IClientEntityList* )Tools->GetInterface( "client.dll",	"VClientEntityList003" );
	Tools->PrintToConsole("VClientEntityList003");
	BaseClientDll = ( IBaseClientDll* ) Tools->GetInterface( "client.dll", "VClient018" );
	Tools->PrintToConsole("VClient018");

	/* get g_pClientMode */
	void** BaseClientDllVMT = *( void*** ) BaseClientDll;
	ClientMode = *( IClientMode*** ) ( ( DWORD ) BaseClientDllVMT[ 10 ] + 5 );

	/* init cheat */
	ESP = new CESP;

	/* setup ptrav hook */
	PanelHook = new CHook( ( DWORD** ) Panel );

	_PaintTraverse = ( PaintTraverse ) PanelHook->dwHookMethod( ( DWORD ) HookedPaintTraverse, 41 );

	Tools->PrintToConsole("PaintTraverse Hooked");

	/* setup cmove hook */
	CreateMoveHook = new CHook( *( DWORD*** ) ClientMode );

	_CreateMove = ( CreateMove ) CreateMoveHook->dwHookMethod( ( DWORD ) HookedCreateMove, 24 );

	Tools->PrintToConsole("Createmove Hooked");


	Tools->PrintToConsole("PantsuSDK Fully Loaded");

	return;
}


int __stdcall DllMain( HMODULE Instacen, DWORD Reason, LPVOID _Reserved )
{

	if ( Reason == 1 )
	{
		Tools->OpenNewConsole("PantsuSDK - Debug Information");
		CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE ) Start, 0, 0, 0 );
	}

	return 1;
}