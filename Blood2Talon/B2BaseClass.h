#ifndef __B2BASECLASS_H__
#define __B2BASECLASS_H__
#include "ltengineobjects.h"
#include "ltbasetypes.h"
#include "ltbasedefs.h"
#include <compat/ltcompat.h>

#include "ClientRes.h"

class B2BaseClass : public BaseClass
{
public:

	B2BaseClass();
	B2BaseClass(DBYTE nType);
	virtual ~B2BaseClass() {}
	DBYTE GetGameDifficulty()
	{
		if (!g_pServerDE) return 0;
		HCONVAR hConVar = 0;
		return hConVar ? (DBYTE)g_pServerDE->GetVarValueFloat(hConVar) : 0;
	}

	DBYTE GetGameType()
	{
		if (!g_pServerDE) return 0;
		HCONVAR hConVar = 0;
		return hConVar ? (DBYTE)g_pServerDE->GetVarValueFloat(hConVar) : 0;
	}

protected:

	virtual DDWORD EngineMessageFn(DDWORD messageID, void* pData, DFLOAT lData);

	DBOOL	ReadProp(ObjectCreateStruct* pStruct);
	DBOOL	InitialUpdate();

	DDWORD	m_dwOptFlags;
};
#endif