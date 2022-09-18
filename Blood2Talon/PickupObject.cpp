#include "PickupObject.h"

PickupObject::PickupObject()
{
}

PickupObject::~PickupObject()
{
}

void PickupObject::SpawnItem(DVector* pvPos)
{
}

DDWORD PickupObject::EngineMessageFn(DDWORD messageID, void* pData, DFLOAT lData)
{
	return DDWORD();
}

DDWORD PickupObject::ObjectMessageFn(HOBJECT hSender, DDWORD messageID, HMESSAGEREAD hRead)
{
	return DDWORD();
}

DBOOL PickupObject::ReadProp(ObjectCreateStruct* pStruct)
{
	return DBOOL();
}

void PickupObject::PostPropRead(ObjectCreateStruct* pStruct)
{
}

DBOOL PickupObject::InitialUpdate(DVector* pMovement)
{
	return DBOOL();
}

DBOOL PickupObject::Update(DVector* pMovement)
{
	return DBOOL();
}

void PickupObject::PickedUp(HMESSAGEREAD hRead)
{
}

void PickupObject::SendEffectMessage()
{
}

void PickupObject::CacheFiles()
{
}

void PickupObject::Save(HMESSAGEWRITE hWrite, DDWORD dwSaveFlags)
{
}

void PickupObject::Load(HMESSAGEREAD hWrite, DDWORD dwLoadFlags)
{
}
