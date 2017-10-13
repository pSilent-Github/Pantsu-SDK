#include "top.h"

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

/* cheat */
#include "esp.h"

CHook * PanelHook;
CHook * CreateMoveHook;

CESP * ESP;
CRender * Render;

PaintTraverse _PaintTraverse;
CreateMove _CreateMove;

/* ptrav hook function */
void __stdcall HookedPaintTraverse( int VGUIPanel, bool ForceRepaint, bool AllowForce )
{
	_PaintTraverse( Panel, VGUIPanel, ForceRepaint, AllowForce );

	/* right panel */
	if ( !strcmp( "FocusOverlayPanel", Panel->GetName( VGUIPanel ) ) )
	{
		if ( EngineClient->IsInGame( ) && EngineClient->IsConnected( ) )
		{
			Render->DrawF( 10, 10, CColor( 26, 188, 156, 255 ), 5, 0, "[ PantsuSDK By p$ilent & Maddie ]" );

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
	Surface	= ( ISurface* )Tools->GetInterface( "vguimatsurface.dll", "VGUI_Surface031" );
	EngineClient = ( IVEngineClient* )Tools->GetInterface( "engine.dll", "VEngineClient014" );
	ClientEntityList = ( IClientEntityList* )Tools->GetInterface( "client.dll",	"VClientEntityList003" );
	BaseClientDll = ( IBaseClientDll* ) Tools->GetInterface( "client.dll", "VClient018" );

	/* get g_pClientMode */
	void** BaseClientDllVMT = *( void*** ) BaseClientDll;
	ClientMode = *( IClientMode*** ) ( ( DWORD ) BaseClientDllVMT[ 10 ] + 5 );

	/* init cheat */
	ESP = new CESP;

	/* setup ptrav hook */
	PanelHook = new CHook( ( DWORD** ) Panel );

	_PaintTraverse = ( PaintTraverse ) PanelHook->dwHookMethod( ( DWORD ) HookedPaintTraverse, 41 );

	/* setup cmove hook */
	CreateMoveHook = new CHook( *( DWORD*** ) ClientMode );

	_CreateMove = ( CreateMove ) CreateMoveHook->dwHookMethod( ( DWORD ) HookedCreateMove, 24 );


	return;
}


int __stdcall DllMain( HMODULE Instacen, DWORD Reason, LPVOID _Reserved )
{

	if ( Reason == 1 )
	{
		CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE ) Start, 0, 0, 0 );
	}

	return 1;
}