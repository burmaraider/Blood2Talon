#ifndef __PICKUPOBJECT_H__
#define __PICKUPOBJECT_H__
#include <compat/ltcompat.h>
#include <ltbasedefs.h>
#include "B2BaseClass.h"

class PickupObject : public B2BaseClass
{
public:

	PickupObject();
	~PickupObject();

	void			SetBounce(DBOOL bBounce) { m_bBounce = bBounce; }
	void			SpawnItem(DVector* pvPos);
	HSTRING			GetObjectName() { return m_hstrObjectName; }
	HSTRING			GetDisplayName() { return m_hstrDisplayName; }
	void			SetValue(DFLOAT fValue) { m_fValue = fValue; }

protected:

	DDWORD			EngineMessageFn(DDWORD messageID, void* pData, DFLOAT lData);
	DDWORD			ObjectMessageFn(HOBJECT hSender, DDWORD messageID, HMESSAGEREAD hRead);

	DBOOL			ReadProp(ObjectCreateStruct* pStruct);
	void			PostPropRead(ObjectCreateStruct* pStruct);
	DBOOL			InitialUpdate(DVector* pMovement);
	DBOOL			Update(DVector* pMovement);
	virtual void	PickedUp(HMESSAGEREAD hRead);
	//		virtual void	HandleTrigger( HOBJECT hSender, HMESSAGEREAD hRead );

			// base classes will override this function	to send a specific
			// message to the object that touched us

	virtual void	ObjectTouch(HOBJECT hObject) {}
	void			SendEffectMessage();

private:

	void	CacheFiles();
	void	Save(HMESSAGEWRITE hWrite, DDWORD dwSaveFlags);
	void	Load(HMESSAGEREAD hWrite, DDWORD dwLoadFlags);

protected:

	DFLOAT	m_fRespawnTime;		// How quickly we respawn
	DBOOL	m_bRotate;			// Do we rotate
	DBOOL	m_bBounce;			// Do we bounce when spawned.
	float	m_fYaw;				// Angular position around Y axis
	float	m_fLastTime;		// Last update time
	DDWORD	m_dwFlags;			// Copy of flags
	float	m_fBounce;			// Bounce acceleration
	DBOOL	m_bBouncing;		// Bounce indicator
	DVector m_vRestPos;			// Position when not bouncing
	DBOOL	m_bFirstUpdate;		// Is this the first update?

	HSTRING m_hstrPickupTriggerTarget;	// Object we trigger
	HSTRING m_hstrPickupTriggerMessage;	// Trigger message
	HSTRING m_hstrObjectName;
	HSTRING m_hstrDisplayName;	// Name of object to use as display
	char* m_szFile;
	char* m_szObjectName;
	int		m_nNameID;
	DBYTE	m_nType;			// Powerup type: This value is dependent on the class
	DFLOAT	m_fValue;			// Powerup value: This value is dependent on the class
	DFLOAT	m_fValueMult;		// Multiplier of the value set by server.

	char* m_szPickupSound;
	char* m_szRespawnSound;
};
#endif