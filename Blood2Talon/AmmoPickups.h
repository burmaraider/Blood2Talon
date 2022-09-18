#ifndef __AMMOPICKUPS_H__
#define __AMMOPICKUPS_H__


#include "PickupObject.h"

#define		AMMO_NONE			0
#define		AMMO_BULLET			1
#define		AMMO_SHELL			2
#define		AMMO_BMG			3
#define		AMMO_FLARE			4
#define		AMMO_DIEBUGDIE		5
#define		AMMO_HOWITZER		6
#define		AMMO_FUEL			7
#define		AMMO_BATTERY		8
#define		AMMO_FOCUS			9
#define		AMMO_PROXIMITYBOMB	10
#define		AMMO_REMOTEBOMB		11
#define		AMMO_TIMEBOMB		12
#define		AMMO_MAXAMMOTYPES	12

#define		AMMOCOUNT_BULLET		100
#define		AMMOCOUNT_SHELL			20
#define		AMMOCOUNT_BMG			20
#define		AMMOCOUNT_FLARE			20
#define		AMMOCOUNT_DIEBUGDIE		20
#define		AMMOCOUNT_HOWITZER		5
#define		AMMOCOUNT_FUEL			10
#define		AMMOCOUNT_BATTERY		40
#define		AMMOCOUNT_PROXIMITYBOMB	1
#define		AMMOCOUNT_REMOTEBOMB	1
#define		AMMOCOUNT_TIMEBOMB		1

class AmmoPickup : public PickupObject
{
public:

	AmmoPickup() : PickupObject()
	{
		if (m_dwNumPU == 0)
		{
			dl_TieOff(&m_PUHead);
			m_PUHead.m_pData = DNULL;
		}

		m_szPickupSound = "sounds\\powerups\\ammo1.wav";
	}

	~AmmoPickup()
	{
		if (m_Link.m_pData && m_dwNumPU > 0)
		{
			dl_Remove(&m_Link);
			m_dwNumPU--;
		}
	}

	static DLink	m_PUHead;
	static DDWORD	m_dwNumPU;
	DLink			m_Link;

protected:

	DDWORD		EngineMessageFn(DDWORD messageID, void* pData, float fData);
	void		ObjectTouch(HOBJECT hObject);
};


class BulletAmmoPU : public AmmoPickup
{
public:
	BulletAmmoPU();
};


class ShellAmmoPU : public AmmoPickup
{
public:
	ShellAmmoPU();
};


class BMGAmmoPU : public AmmoPickup
{
public:
	BMGAmmoPU();
};


class FlareAmmoPU : public AmmoPickup
{
public:
	FlareAmmoPU();
};


class DieBugDieAmmoPU : public AmmoPickup
{
public:
	DieBugDieAmmoPU();
};


class HowitzerAmmoPU : public AmmoPickup
{
public:
	HowitzerAmmoPU();
};


class FuelAmmoPU : public AmmoPickup
{
public:
	FuelAmmoPU();
};


class BatteryAmmoPU : public AmmoPickup
{
public:
	BatteryAmmoPU();
};

/*		Don't need this one, since Mana regens
class ManaAmmoPU : public AmmoPickup
{
	public :
		ManaAmmoPU();
};

*/
#endif //  __AMMOPICKUPS_H__