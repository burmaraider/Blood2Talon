#include "iservershell.h"




IServerShell* CreateServerShell(ILTServer* pServer)
{
	return nullptr;
}

void DeleteServerShell(IServerShell* pServer)
{
	free(pServer);
}