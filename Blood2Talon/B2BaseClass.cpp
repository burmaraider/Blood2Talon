#include "B2BaseClass.h"

B2BaseClass::B2BaseClass()
{
}

B2BaseClass::B2BaseClass(DBYTE nType)
{
}

DDWORD B2BaseClass::EngineMessageFn(DDWORD messageID, void* pData, DFLOAT lData)
{
    return DDWORD();
}

DBOOL B2BaseClass::ReadProp(ObjectCreateStruct* pStruct)
{
    return DBOOL();
}

DBOOL B2BaseClass::InitialUpdate()
{
    return DBOOL();
}
