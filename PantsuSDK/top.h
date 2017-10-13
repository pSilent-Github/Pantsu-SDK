#pragma once

#pragma region includes

#include <Windows.h>
#include <iostream>

#include "usercmd.h"
#include "viewsetup.h"
#include "netchannel.h"
#include "globalvars.h"

#pragma endregion

#pragma region protos

typedef void*	( *Interface )( char* _Name, int Return );

typedef void( __thiscall *PaintTraverse )( void*, unsigned int, bool, bool );

typedef bool( __thiscall *CreateMove )( void*, float, CUserCmd* );

typedef void(__thiscall *Overrideview)(void*, float, CViewSetup*);

#pragma endregion

class CTools
{
public:

	virtual void* GetInterface( char* _Module, char* _Interface )
	{
		Interface TempInterface = ( Interface ) GetProcAddress( GetModuleHandle( _Module ), "CreateInterface" );

		return ( void* ) TempInterface( _Interface, 0 );
	}

	void OpenNewConsole(std::string ConsoleTitle) // Taken From Valve SDK
	{
		AllocConsole(); freopen("CONIN$", "r", stdin);freopen("CONOUT$", "w", stdout);freopen("CONOUT$", "w", stderr);	SetConsoleTitle(ConsoleTitle.c_str());
	}

	void PrintToConsole(const char *Text, ...) // Taken From Valve SDK
	{
			if (!Text) return; if (strlen(Text) < 2) return; va_list va_alist; char logBuf[256] = { 0 }; va_start(va_alist, Text); _vsnprintf(logBuf + strlen(logBuf), sizeof(logBuf) - strlen(logBuf), Text, va_alist); va_end(va_alist); if (logBuf[0] != '\0') {	printf("%s\n", logBuf); }
	}
}; extern CTools * Tools;


template< typename Function > Function EmulateVirtual( void* _VMT, int Index )
{
	void*** _TVMT = ( void*** ) _VMT;

	void** VMT = *_TVMT;

	void* _Address = VMT[ Index ];

	return ( Function ) ( _Address );
}