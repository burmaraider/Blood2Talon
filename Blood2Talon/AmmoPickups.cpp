#include "AmmoPickups.h"

DLink AmmoPickup::m_PUHead;
DDWORD AmmoPickup::m_dwNumPU = 0;

ShellAmmoPU::ShellAmmoPU()
{
	m_nType = AMMO_SHELL;
	m_fValue = AMMOCOUNT_SHELL;
	m_szFile = "ShellAmmo_pu";
	m_szObjectName = "Shells";
	m_nNameID = IDS_AMMO_SHELLS;
}

DDWORD AmmoPickup::EngineMessageFn(DDWORD messageID, void* pData, float fData)
{
	return DDWORD();
}

void AmmoPickup::ObjectTouch(HOBJECT hObject)
{
}

BulletAmmoPU::BulletAmmoPU() : AmmoPickup()
{
	m_nType = AMMO_BULLET;
	m_fValue = AMMOCOUNT_BULLET;
	m_szFile = "BulletAmmo_pu";
	m_szObjectName = "Bullets";
	m_nNameID = IDS_AMMO_BULLETS;
}

BMGAmmoPU::BMGAmmoPU()
{
	m_nType = AMMO_BMG;
	m_fValue = AMMOCOUNT_BMG;
	m_szFile = "BMGAmmo_pu";
	m_szObjectName = "BMG Rounds";
	m_nNameID = IDS_AMMO_BMG;
}

FlareAmmoPU::FlareAmmoPU()
{
	m_nType = AMMO_FLARE;
	m_fValue = AMMOCOUNT_FLARE;
	m_szFile = "FlareAmmo_pu";
	m_szObjectName = "Flares";
	m_nNameID = IDS_AMMO_FLARES;
}

DieBugDieAmmoPU::DieBugDieAmmoPU() : AmmoPickup()
{
	m_nType = AMMO_DIEBUGDIE;
	m_fValue = AMMOCOUNT_DIEBUGDIE;
	m_szFile = "DieBugDieAmmo_pu";
	m_szObjectName = "DieBugDie";
	m_nNameID = IDS_AMMO_DIEBUGDIE;
}

HowitzerAmmoPU::HowitzerAmmoPU() : AmmoPickup()
{
	m_nType = AMMO_HOWITZER;
	m_fValue = AMMOCOUNT_HOWITZER;
	m_szFile = "HowitzerAmmo_pu";
	m_szObjectName = "Howizter Shells";
}

FuelAmmoPU::FuelAmmoPU() : AmmoPickup()
{
	m_nType = AMMO_FUEL;
	m_fValue = AMMOCOUNT_FUEL;
	m_szFile = "FuelAmmo_pu";
	m_szObjectName = "FuelTank";
	m_nNameID = IDS_AMMO_FUEL;
}
BatteryAmmoPU::BatteryAmmoPU() : AmmoPickup()
{
	m_nType = AMMO_BATTERY;
	m_fValue = AMMOCOUNT_BATTERY;
	m_szFile = "BatteryAmmo_pu";
	m_szObjectName = "Chemical Batteries";
	m_nNameID = IDS_AMMO_BATTERY;
}