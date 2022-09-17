#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <vector>

#include "ltserverobj.h"


std::vector<PropDef> g_PropDefs;


void DoThing();
//dll main
BOOL APIENTRY DllMain( HANDLE hModule, 
					   DWORD  ul_reason_for_call, 
					   LPVOID lpReserved
					 )
{
	DoThing();

	return TRUE;
}

void DoThing()
{

}

SETUP_SERVERSHELL()
DEFINE_CLASSES()
