#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <vector>

#include "ltserverobj.h"
#include "B2BaseClass.h"


//dllmain
BOOL APIENTRY DllMain( HANDLE hModule, 
					   DWORD  ul_reason_for_call, 
					   LPVOID lpReserved
					 )
{
	return TRUE;
}


SETUP_SERVERSHELL()


BEGIN_CLASS(BaseClass)
ADD_STRINGPROP(Name, "noname")
ADD_VECTORPROP(Pos)
ADD_ROTATIONPROP(Rotation)
ADD_BOOLPROP_FLAG(TrueBaseObj, LTTRUE, PF_HIDDEN)
END_CLASS_DEFAULT_NOPARENT(BaseClass, BaseClass::EngineMessageFn, BaseClass::ObjectMessageFn);


// ------------------------------------------------------------------------ //
// Container.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(Container)
ADD_LONGINTPROP(Flags, FLAG_VISIBLE)
ADD_LONGINTPROP(ContainerCode, 0)
END_CLASS_DEFAULT_FLAGS(Container, BaseClass, NULL, NULL, CF_ALWAYSLOAD)

uint32 Container::EngineMessageFn(uint32 messageID, void* pData, float fData)
{
	ObjectCreateStruct* pStruct;
	long code;

	if (messageID == MID_PRECREATE)
	{
		pStruct = (ObjectCreateStruct*)pData;
		pStruct->m_ObjectType = OT_CONTAINER;
		pStruct->m_Flags |= FLAG_CONTAINER;

		if (fData == PRECREATE_WORLDFILE)
		{
			code = 0;
			g_pLTServer->GetPropLongInt("ContainerCode", &code);
			pStruct->m_ContainerCode = (uint16)code;
			g_pLTServer->GetPropString("Name", pStruct->m_Filename, MAX_CS_FILENAME_LEN);
		}
	}

	// Pass the message down to the base class.
	return BaseClass::EngineMessageFn(messageID, pData, fData);
}



// ------------------------------------------------------------------------ //
// Sound.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(Sound)
ADD_STRINGPROP(Filename, "")
ADD_LONGINTPROP(Priority, 0.0f)
ADD_REALPROP_FLAG(OuterRadius, 100.0f, PF_RADIUS)
ADD_REALPROP_FLAG(InnerRadius, 10.0f, PF_RADIUS)
ADD_LONGINTPROP(Volume, 100.0f)
ADD_BOOLPROP(Ambient, 1)
ADD_BOOLPROP(FileStream, 0)
END_CLASS_DEFAULT_FLAGS(Sound, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_ALWAYSLOAD)

unsigned long Sound::EngineMessageFn(unsigned long a, void* b, float c)
{
	return 0;
}

// ------------------------------------------------------------------------ //
// InsideDef.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(InsideDef)
END_CLASS_DEFAULT_FLAGS(InsideDef, BaseClass, NULL, NULL, CF_NORUNTIME | CF_HIDDEN)



// ------------------------------------------------------------------------ //
// OutsideDef.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(OutsideDef)
END_CLASS_DEFAULT_FLAGS(OutsideDef, BaseClass, NULL, NULL, CF_NORUNTIME)



// ------------------------------------------------------------------------ //
// FastApproxArea.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(FastApproxArea)
END_CLASS_DEFAULT_FLAGS(FastApproxArea, BaseClass, NULL, NULL, CF_NORUNTIME)



// ------------------------------------------------------------------------ //
// Light.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(Light)
ADD_BOOLPROP(ClipLight, 1)
ADD_BOOLPROP(LightObjects, 1)
ADD_REALPROP_FLAG(LightRadius, 300.0f, PF_RADIUS)
ADD_COLORPROP(LightColor, 255.0f, 255.0f, 255.0f)
ADD_COLORPROP(OuterColor, 0.0f, 0.0f, 0.0f)
ADD_REALPROP(BrightScale, 1.0f)
ADD_REALPROP(Time, 0.0f)
END_CLASS_DEFAULT_FLAGS(Light, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_NORUNTIME)


// ------------------------------------------------------------------------ //
// ObjectLight.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(ObjectLight)
ADD_REALPROP_FLAG(LightRadius, 300.0f, PF_RADIUS)
ADD_COLORPROP(LightColor, 255.0f, 255.0f, 255.0f)
ADD_COLORPROP(OuterColor, 0.0f, 0.0f, 0.0f)
ADD_REALPROP(BrightScale, 1.0f)
END_CLASS_DEFAULT_FLAGS(ObjectLight, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_NORUNTIME)



// ------------------------------------------------------------------------ //
// DirLight.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(DirLight)
ADD_BOOLPROP(LightObjects, 1)
ADD_BOOLPROP(ClipLight, 1)
ADD_REALPROP_FLAG(LightRadius, 300.0f, PF_RADIUS)
ADD_COLORPROP(InnerColor, 255.0f, 255.0f, 255.0f)
ADD_COLORPROP(OuterColor, 0.0f, 0.0f, 0.0f)
ADD_REALPROP_FLAG(FOV, 90.0f, PF_FIELDOFVIEW)
ADD_REALPROP(BrightScale, 1.0f)
ADD_REALPROP(Time, 0.0f)
END_CLASS_DEFAULT_FLAGS(DirLight, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_NORUNTIME)



// ------------------------------------------------------------------------ //
// Brush.
// ------------------------------------------------------------------------ //
BEGIN_CLASS(Brush)
ADD_BOOLPROP(Solid, 1)
ADD_BOOLPROP(Nonexistant, 0)
ADD_BOOLPROP(Invisible, 0)
ADD_BOOLPROP(Translucent, 0)
ADD_BOOLPROP(SkyPortal, 0)
ADD_BOOLPROP(FullyBright, 0)
ADD_BOOLPROP(FlatShade, 0)
ADD_BOOLPROP(GouraudShade, 1)
ADD_BOOLPROP(LightMap, 1)
ADD_BOOLPROP(Subdivide, 1)
ADD_BOOLPROP(HullMaker, 0)
ADD_BOOLPROP(AlwaysLightMap, 0)
ADD_BOOLPROP(DirectionalLight, 0)
ADD_BOOLPROP(Portal, 0)
ADD_BOOLPROP(NoSnap, 0)
ADD_BOOLPROP(SkyPan, 0)

ADD_LONGINTPROP(DetailLevel, 0)
ADD_STRINGPROP(Effect, "")
ADD_STRINGPROP(EffectParam, "")
ADD_REALPROP(FrictionCoefficient, 1)
END_CLASS_DEFAULT_FLAGS(Brush, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_ALWAYSLOAD)
	

// The model class..
typedef struct
{
	BaseClass m_BaseClass;
} Model;

BEGIN_CLASS(Model)
ADD_STRINGPROP(Filename, "")
ADD_STRINGPROP(Skin, "")
ADD_LONGINTPROP(Flags, FLAG_VISIBLE)
END_CLASS_DEFAULT_FLAGS(Model, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_ALWAYSLOAD)

// The WorldModel class.
typedef struct
{
	BaseClass m_BaseClass;
} WorldModel;


BEGIN_CLASS(WorldModel)
ADD_LONGINTPROP(Flags, FLAG_VISIBLE)
END_CLASS_DEFAULT_FLAGS(WorldModel, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_ALWAYSLOAD)

// The sprite class.
typedef struct
{
	BaseClass	m_BaseClass;
	DWORD		m_Color[4]; // RGBA
} Sprite;

BEGIN_CLASS(Sprite)
	ADD_STRINGPROP(Filename, "")
	ADD_LONGINTPROP(Flags, FLAG_VISIBLE)
	ADD_VECTORPROP_VAL(Scale, 1, 1, 1)
	ADD_COLORPROP(Color, 255, 255, 255)
	ADD_REALPROP(Alpha, 1)
END_CLASS_DEFAULT_FLAGS(Sprite, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_ALWAYSLOAD)

typedef struct
{
	BaseClass m_BaseClass;
} StartPoint;

BEGIN_CLASS(StartPoint)
END_CLASS_DEFAULT_FLAGS(StartPoint, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_ALWAYSLOAD)

// LightAnimator class.
typedef struct LightAnimator_t
{
	BaseClass m_BaseClass;
} LightAnimator;

BEGIN_CLASS(LightAnimator)
ADD_STRINGPROP(BaseLightName, "light")
END_CLASS_DEFAULT_FLAGS(LightAnimator, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_NORUNTIME)

// ProjectorSprite.
typedef struct ProjectorSprite_t
{
	BaseClass m_BaseClass;
} ProjectorSprite;

BEGIN_CLASS(ProjectorSprite)
ADD_STRINGPROP(Filename, "sprite.spr")
END_CLASS_DEFAULT_FLAGS(ProjectorSprite, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_NORUNTIME)

// GlobalDirLight class (just uses the Light code).
typedef struct GlobalDirLight_t
{
	BaseClass m_BaseClass;
} GlobalDirLight;

BEGIN_CLASS(GlobalDirLight)
ADD_VECTORPROP_VAL_FLAG(BigDims, 90.0f, 90.0f, 90.0f, PF_DIMS | PF_HIDDEN)
ADD_COLORPROP(InnerColor, 255.0f, 255.0f, 255.0f)
ADD_COLORPROP(OuterColor, 0.0f, 0.0f, 0.0f)
ADD_REALPROP(BrightScale, 1.0f)
END_CLASS_DEFAULT_FLAGS(GlobalDirLight, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_NORUNTIME)

// World class..
typedef struct
{
	BaseClass m_BaseClass;
} World;

BEGIN_CLASS(World)
END_CLASS_DEFAULT_FLAGS(World, BaseClass, DNULL, DNULL, CF_ALWAYSLOAD)

BEGIN_CLASS(DemoSkyWorldModel)
ADD_VECTORPROP_VAL_FLAG(SkyDims, 0.0f, 0.0f, 0.0f, PF_DIMS)
ADD_LONGINTPROP(Flags, 1)
ADD_LONGINTPROP(Index, 0)
ADD_REALPROP(InnerPercentX, 0.1f)
ADD_REALPROP(InnerPercentY, 0.1f)
ADD_REALPROP(InnerPercentZ, 0.1f)
END_CLASS_DEFAULT_FLAGS(DemoSkyWorldModel, BaseClass, DemoSky_EngineMessageFn, bc_ObjectMessageFn, CF_ALWAYSLOAD)

unsigned long DemoSkyWorldModel::EngineMessageFn(unsigned long a, void* b, float c)
{
	return 0;
}

BEGIN_CLASS(SkyPointer)
ADD_STRINGPROP(SkyObjectName, "")
ADD_VECTORPROP_VAL_FLAG(SkyDims, 0.0f, 0.0f, 0.0f, PF_DIMS)
ADD_LONGINTPROP(Flags, 1)
ADD_LONGINTPROP(Index, 0)
ADD_REALPROP(InnerPercentX, 0.1f)
ADD_REALPROP(InnerPercentY, 0.1f)
ADD_REALPROP(InnerPercentZ, 0.1f)
END_CLASS_DEFAULT_FLAGS(SkyPointer, BaseClass, SkyPointer_EngineMessageFn, bc_ObjectMessageFn, CF_ALWAYSLOAD)

unsigned long SkyPointer::EngineMessageFn(unsigned long a, void* b, float c)
{
	return 0;
}

// These generate areas of fog.
typedef struct FogSphere_t
{
	BaseClass m_BaseClass;
	float m_Radius;
} FogSphere;

BEGIN_CLASS(FogSphere)
ADD_REALPROP_FLAG(LightRadius, 300.0f, PF_RADIUS)
END_CLASS_DEFAULT_FLAGS(FogSphere, BaseClass, FogSphere_EngineMessageFn, bc_ObjectMessageFn, CF_ALWAYSLOAD)


BEGIN_CLASS(RaySelecter)
END_CLASS_DEFAULT_FLAGS(RaySelecter, BaseClass, bc_EngineMessageFn, bc_ObjectMessageFn, CF_NORUNTIME)


BEGIN_CLASS(B2BaseClass)
PROP_DEFINEGROUP(GameSettings, PF_GROUP6)
ADD_BOOLPROP_FLAG(DifficultyEasy, LTTRUE, PF_GROUP6)
ADD_BOOLPROP_FLAG(DifficultyMed, LTTRUE, PF_GROUP6)
ADD_BOOLPROP_FLAG(DifficultyHard, LTTRUE, PF_GROUP6)
ADD_BOOLPROP_FLAG(TypeCustom, LTTRUE, PF_GROUP6)
ADD_BOOLPROP_FLAG(TypeSingle, LTTRUE, PF_GROUP6)
ADD_BOOLPROP_FLAG(TypeActionMode, LTTRUE, PF_GROUP6)
ADD_BOOLPROP_FLAG(TypeBloodBath, LTTRUE, PF_GROUP6)
ADD_BOOLPROP_FLAG(TypeCTF, LTTRUE, PF_GROUP6)
ADD_BOOLPROP_FLAG(TypeCoop, LTTRUE, PF_GROUP6)
END_CLASS_DEFAULT_FLAGS(B2BaseClass, BaseClass, NULL, NULL, CF_HIDDEN)

typedef struct CBaseCharacter_t
{
	BaseClass m_BaseClass;
} CBaseCharacter;

BEGIN_CLASS(CBaseCharacter)
	PROP_DEFINEGROUP(DamageProperties, PF_GROUP1) \
	ADD_REALPROP_FLAG(Mass, 30.0f, PF_GROUP1) \
	ADD_REALPROP_FLAG(HitPoints, 100.0f, PF_GROUP1) \
	ADD_REALPROP_FLAG(MaxHitPoints, 100.0f, PF_GROUP1) \
	ADD_REALPROP_FLAG(Armor, 100.0f, PF_GROUP1) \
	ADD_REALPROP_FLAG(MaxArmor, 100.0f, PF_GROUP1) \
	ADD_LONGINTPROP_FLAG(DamageTriggerCounter, 0, PF_GROUP1) \
	ADD_STRINGPROP_FLAG(DamageTriggerTarget, "", PF_GROUP1) \
	ADD_STRINGPROP_FLAG(DamageTriggerMessage, "", PF_GROUP1) \
	ADD_LONGINTPROP_FLAG(DamageTriggerNumSends, 1, PF_GROUP1) \
	ADD_STRINGPROP_FLAG(DamagerMessage, "", PF_GROUP1) \
	ADD_STRINGPROP_FLAG(DeathTriggerTarget, "", PF_GROUP1) \
	ADD_STRINGPROP_FLAG(DeathTriggerMessage, "", PF_GROUP1) \
	ADD_STRINGPROP_FLAG(PlayerDeathTriggerTarget, "", PF_GROUP1) \
	ADD_STRINGPROP_FLAG(PlayerDeathTriggerMessage, "", PF_GROUP1) \
	ADD_STRINGPROP_FLAG(KillerMessage, "", PF_GROUP1) \
	ADD_BOOLPROP_FLAG(CanHeal, LTTRUE, PF_GROUP1) \
	ADD_BOOLPROP_FLAG(CanRepair, LTTRUE, PF_GROUP1) \
	ADD_BOOLPROP_FLAG(CanDamage, LTTRUE, PF_GROUP1) \
	ADD_BOOLPROP_FLAG(NeverDestroy, LTTRUE, PF_GROUP1)
END_CLASS_DEFAULT(CBaseCharacter, B2BaseClass, NULL, NULL)

#pragma region AI
typedef struct AI_Mgr_t
{
	BaseClass m_BaseClass;
} AI_Mgr;

BEGIN_CLASS(AI_Mgr)
	ADD_STRINGPROP(SpotTriggerTarget, "") \
	ADD_STRINGPROP(SpotTriggerMessage, "") \
	ADD_STRINGPROP(TriggerRelayTarget, "") \
END_CLASS_DEFAULT_FLAGS(AI_Mgr, CBaseCharacter, NULL, NULL, CF_HIDDEN)

typedef struct AncientOne_t
{
	BaseClass m_BaseClass;
} AncientOne;

BEGIN_CLASS(AncientOne)
	ADD_REALPROP(RandomHitPoints, 00.0f) \
	ADD_STRINGPROP(AIState, "IDLE")     \
END_CLASS_DEFAULT(AncientOne, AI_Mgr, NULL, NULL)

typedef struct AncientOneTentacle_t
{
	BaseClass m_BaseClass;
} AncientOneTentacle;

BEGIN_CLASS(AncientOneTentacle)
	ADD_STRINGPROP(SpotTriggerTarget, "")
	ADD_STRINGPROP(SpotTriggerMessage, "")
	ADD_STRINGPROP(TriggerRelayTarget, "")
	ADD_STRINGPROP(AIState, "IDLE")
END_CLASS_DEFAULT(AncientOneTentacle, AI_Mgr, NULL, NULL)

typedef struct Behemoth_t
{
	BaseClass m_BaseClass;
} Behemoth;

BEGIN_CLASS(Behemoth)
	ADD_REALPROP(RandomHitPoints, 0.0f)
	ADD_STRINGPROP(AIState, "IDLE")
	ADD_VECTORPROP_VAL_FLAG(Dims, 37.0f, 52.0f, 31.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(Behemoth, AI_Mgr, NULL, NULL)

typedef struct BirdAI_t
{
	BaseClass m_BaseClass;
} BirdAI;

BEGIN_CLASS(BirdAI)
ADD_STRINGPROP(SpotTriggerTarget, "")
ADD_STRINGPROP(SpotTriggerMessage, "")
ADD_STRINGPROP(TriggerRelayTarget, "")
ADD_REALPROP(SightDistance, 1000.0f)
ADD_REALPROP(SenseDistance, 400.0f)
ADD_REALPROP(SmellDistance, 300.0f)
ADD_REALPROP(ListenDistance, 0.0f)
ADD_REALPROP(Mass, 2.0f)
ADD_REALPROP(HitPoints, 5.0f)
ADD_REALPROP(RandomHitPoints, 5.0f)
ADD_REALPROP(ArmorPoints, 0.0f)
ADD_STRINGPROP(AIState, "IDLE")
ADD_STRINGPROP(AIBrain, "WEAK")
ADD_STRINGPROP(AIWeapon1, "MELEE")
END_CLASS_DEFAULT(BirdAI, AI_Mgr, NULL, NULL)

typedef struct BoneLeech_t
{
	BaseClass m_BaseClass;
} BoneLeech;

BEGIN_CLASS(BoneLeech)
	ADD_REALPROP(RandomHitPoints, 0.0f)
	ADD_STRINGPROP(AIState, "IDLE")
	ADD_VECTORPROP_VAL_FLAG(Dims, 2.0f, 1.5f, 11.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(BoneLeech, AI_Mgr, NULL, NULL)

typedef struct BugAI_t
{
	BaseClass m_BaseClass;
} BugAI;

BEGIN_CLASS(BugAI)
	ADD_STRINGPROP(SpotTriggerTarget, "")
	ADD_STRINGPROP(SpotTriggerMessage, "")
	ADD_STRINGPROP(TriggerRelayTarget, "")
	ADD_REALPROP(SightDistance, 500.0f)
	ADD_REALPROP(SenseDistance, 500.0f)
	ADD_REALPROP(SmellDistance, 500.0f)
	ADD_REALPROP(Mass, 1.0f)
	ADD_REALPROP(HitPoints, 1.0f)
	ADD_REALPROP(RandomHitPoints, 0.0f)
END_CLASS_DEFAULT(BugAI, AI_Mgr, NULL, NULL)

typedef struct CalebAI_t
{
	BaseClass m_BaseClass;
} CalebAI;

BEGIN_CLASS(CalebAI)
	ADD_STRINGPROP(SpotTriggerTarget, "")
	ADD_STRINGPROP(SpotTriggerMessage, "")
	ADD_STRINGPROP(TriggerRelayTarget, "")
	ADD_REALPROP(HitPoints, 30.0f)
	ADD_REALPROP(RandomHitPoints, 0.0f)
	ADD_REALPROP(ArmorPoints, 0.0f)
	ADD_STRINGPROP(AIState, "IDLE")
	ADD_STRINGPROP(AIWeapon, "NONE")
END_CLASS_DEFAULT(CalebAI, AI_Mgr, NULL, NULL)

typedef struct CivilianAI_t
{
	BaseClass m_BaseClass;
} CivilianAI;

BEGIN_CLASS(CivilianAI)
ADD_REALPROP(RandomHitPoints, 0.0f) \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_STRINGPROP(AIWeapon1, "NONE")   \
ADD_BOOLPROP(Male, DTRUE) \
ADD_BOOLPROP(LabTech, DFALSE) \
ADD_BOOLPROP(Scared, DFALSE) \
ADD_VECTORPROP_VAL_FLAG(Dims, 21.0f, 37.0f, 21.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN) \
ADD_BOOLPROP(SororitySkin, DFALSE)
END_CLASS_DEFAULT(CivilianAI, AI_Mgr, NULL, NULL)

typedef struct CultistAI_t
{
	BaseClass m_BaseClass;
} CultistAI;

BEGIN_CLASS(CultistAI)
ADD_REALPROP(RandomHitPoints, 0.0f)
ADD_STRINGPROP(AIState, "IDLE")
ADD_STRINGPROP(AIWeapon1, "BERETTA")
ADD_REALPROP(Bullets, 150.0f)
ADD_REALPROP(Flares, 20.0f)
ADD_BOOLPROP(Male, DTRUE)
ADD_VECTORPROP_VAL_FLAG(Dims, 19.0f, 41.0f, 14.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN) \
ADD_BOOLPROP(ClownSkin, DFALSE)
ADD_BOOLPROP(RobeSkin, DFALSE)
END_CLASS_DEFAULT(CultistAI, AI_Mgr, NULL, NULL)

typedef struct DeathShroud_t
{
	BaseClass m_BaseClass;
} DeathShroud;

BEGIN_CLASS(DeathShroud)
	ADD_REALPROP(RandomHitPoints, 0.0f)
	ADD_STRINGPROP(AIState, "IDLE")
	ADD_VECTORPROP_VAL_FLAG(Dims, 20.0f, 48.0f, 20.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(DeathShroud, AI_Mgr, NULL, NULL)


typedef struct DefenseGlobeAI_t
{
	BaseClass m_BaseClass;
} DefenseGlobeAI;

BEGIN_CLASS(DefenseGlobeAI)
ADD_STRINGPROP(SpotTriggerTarget, "")
ADD_STRINGPROP(SpotTriggerMessage, "")
ADD_STRINGPROP(TriggerRelayTarget, "")
ADD_REALPROP(SightDistance, 400.0f)
ADD_REALPROP(SenseDistance, 250.0f)
ADD_REALPROP(SmellDistance, 0.0f)
ADD_REALPROP(ListenDistance, 0.0f)
ADD_REALPROP(Mass, 17.0f)
ADD_REALPROP(HitPoints, 100.0f)
ADD_REALPROP(RandomHitPoints, 50.0f)
ADD_REALPROP(ArmorPoints, 0.0f)
ADD_STRINGPROP(AIState, "IDLE")
ADD_STRINGPROP(AIBrain, "STRONG")
ADD_STRINGPROP(AIWeapon, "PULSE")
END_CLASS_DEFAULT(DefenseGlobeAI, CBaseCharacter, NULL, NULL)

typedef struct DefenseGlobeLegs_t
{
	BaseClass m_BaseClass;
} DefenseGlobeLegs;

BEGIN_CLASS(DefenseGlobeLegs)
END_CLASS_DEFAULT_FLAGS(DefenseGlobeLegs, CBaseCharacter, NULL, NULL, CF_HIDDEN)

typedef struct DrudgeLord_t
{
	BaseClass m_BaseClass;
} DrudgeLord;

BEGIN_CLASS(DrudgeLord)
	ADD_REALPROP(RandomHitPoints, 0.0f)
	ADD_STRINGPROP(AIState, "IDLE")
	ADD_VECTORPROP_VAL_FLAG(Dims, 31.0f, 51.0f, 25.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(DrudgeLord, AI_Mgr, NULL, NULL)

typedef struct DrudgePriest_t
{
	BaseClass m_BaseClass;
} DrudgePriest;

BEGIN_CLASS(DrudgePriest)
	ADD_REALPROP(RandomHitPoints, 0.0f)
	ADD_STRINGPROP(AIState, "IDLE")
	ADD_VECTORPROP_VAL_FLAG(Dims, 40.0f, 30.0f, 37.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(DrudgePriest, AI_Mgr, NULL, NULL)

typedef struct EnhancedGideon_t
{
	BaseClass m_BaseClass;
} EnhancedGideon;

BEGIN_CLASS(EnhancedGideon)
	ADD_REALPROP(RandomHitPoints, 0.0f)
	ADD_STRINGPROP(AIState, "IDLE")
	ADD_BOOLPROP(Enhanced, DFALSE)
END_CLASS_DEFAULT(EnhancedGideon, AI_Mgr, NULL, NULL)

typedef struct Fanatic_t
{
	BaseClass m_BaseClass;
} Fanatic;

BEGIN_CLASS(Fanatic)
ADD_REALPROP(RandomHitPoints, 0.0f) \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_STRINGPROP(AIWeapon1, "BERETTA")   \
ADD_STRINGPROP(AIWeapon2, "COMBAT")   \
ADD_STRINGPROP(AIWeapon3, "ASSAULTRIFLE")   \
ADD_REALPROP(Bullets, 300.0f)     \
ADD_REALPROP(BMG, 150.0f)     \
ADD_REALPROP(Shells, 50.0f)     \
ADD_REALPROP(Grenades, 50.0f)	\
ADD_REALPROP(Rockets, 25.0f)     \
ADD_REALPROP(Flares, 40.0f)     \
ADD_REALPROP(Cells, 200.0f)     \
ADD_REALPROP(Charges, 120.0f)     \
ADD_REALPROP(Fuel, 100.0f)     \
ADD_REALPROP(Proximity_Bombs, 25.0f)	\
ADD_VECTORPROP_VAL_FLAG(Dims, 21.0f, 38.0f, 19.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(Fanatic, AI_Mgr, NULL, NULL)

typedef struct GabriellaAI_t
{
	BaseClass m_BaseClass;
} GabriellaAI;

BEGIN_CLASS(GabriellaAI)
ADD_STRINGPROP(AIState, "PASSIVE")     \
ADD_STRINGPROP(AIWeapon1, "MINIGUN")   \
ADD_STRINGPROP(AIWeapon2, "NAPALM")   \
ADD_VECTORPROP_VAL_FLAG(Dims, 12.0f, 46.0f, 12.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(GabriellaAI, AI_Mgr, NULL, NULL)

typedef struct GabriellaREV_t
{
	BaseClass m_BaseClass;
} GabriellaREV;

BEGIN_CLASS(GabriellaREV)
ADD_STRINGPROP(AIState, "PASSIVE")     \
ADD_STRINGPROP(AIWeapon1, "MINIGUN")   \
ADD_STRINGPROP(AIWeapon2, "NAPALM")   \
ADD_VECTORPROP_VAL_FLAG(Dims, 12.0f, 46.0f, 12.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(GabriellaREV, AI_Mgr, NULL, NULL)

typedef struct Gideon_t
{
	BaseClass m_BaseClass;
} Gideon;

BEGIN_CLASS(Gideon)
	ADD_REALPROP(RandomHitPoints, 0.0f)
	ADD_STRINGPROP(AIState, "IDLE")
	ADD_BOOLPROP(Enhanced, DFALSE)
END_CLASS_DEFAULT(Gideon, AI_Mgr, NULL, NULL)

typedef struct GremlinAI_t
{
	BaseClass m_BaseClass;
} GremlinAI;

BEGIN_CLASS(GremlinAI)
ADD_REALPROP(RandomHitPoints, 10.0f) \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_VECTORPROP_VAL_FLAG(Dims, 19.0f, 30.0f, 24.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(GremlinAI, AI_Mgr, NULL, NULL)

typedef struct IshmaelAI_t
{
	BaseClass m_BaseClass;
} IshmaelAI;

BEGIN_CLASS(IshmaelAI)
ADD_STRINGPROP(AIState, "PASSIVE")
ADD_STRINGPROP(AIWeapon1, "ORB")   \
ADD_STRINGPROP(AIWeapon2, "HEAL")   \
ADD_STRINGPROP(AIWeapon3, "SHOCKWAVE")   \
ADD_VECTORPROP_VAL_FLAG(Dims, 12.0f, 39.0f, 12.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(IshmaelAI, AI_Mgr, NULL, NULL)

typedef struct IshmaelREV_t
{
	BaseClass m_BaseClass;
} IshmaelREV;


BEGIN_CLASS(IshmaelREV)
ADD_STRINGPROP(AIState, "PASSIVE")
ADD_STRINGPROP(AIWeapon1, "ORB")   \
ADD_STRINGPROP(AIWeapon2, "HEAL")   \
ADD_STRINGPROP(AIWeapon3, "SHOCKWAVE")   \
ADD_VECTORPROP_VAL_FLAG(Dims, 12.0f, 39.0f, 12.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(IshmaelREV, AI_Mgr, NULL, NULL)

typedef struct MadScientistAI_t
{
	BaseClass m_BaseClass;
} MadScientistAI;

BEGIN_CLASS(MadScientistAI)
ADD_REALPROP(HitPoints, 30.0f)     \
ADD_REALPROP(RandomHitPoints, 0.0f) \
ADD_REALPROP(ArmorPoints, 0.0f)     \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_STRINGPROP(AIWeapon, "NONE")   \
END_CLASS_DEFAULT(MadScientistAI, AI_Mgr, NULL, NULL)


typedef struct Naga_t
{
	BaseClass m_BaseClass;
} Naga;

BEGIN_CLASS(Naga)
ADD_REALPROP(RandomHitPoints, 0.0f) \
ADD_STRINGPROP(AIState, "IDLE")     \
END_CLASS_DEFAULT(Naga, AI_Mgr, NULL, NULL)

typedef struct Nightmare_t
{
	BaseClass m_BaseClass;
} Nightmare;

BEGIN_CLASS(Nightmare)
ADD_STRINGPROP(SpotTriggerTarget, "")
ADD_STRINGPROP(SpotTriggerMessage, "")
ADD_STRINGPROP(TriggerRelayTarget, "")
ADD_REALPROP(HitPoints, 200000.0f)     \
ADD_REALPROP(RandomHitPoints, 400.0f) \
ADD_REALPROP(ArmorPoints, 0.0f)     \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_STRINGPROP(AIBrain, "STRONG")   \
ADD_STRINGPROP(AIWeapon1, "NIGHTMARE_BITE")   \
ADD_STRINGPROP(AIWeapon2, "NIGHTMARE_FIREBALLS")   \
ADD_STRINGPROP(AIWeapon3, "BEHEMOTH_SHOCKWAVE")   \
END_CLASS_DEFAULT(Nightmare, AI_Mgr, NULL, NULL)

typedef struct OpheliaAI_t
{
	BaseClass m_BaseClass;
} OpheliaAI;

BEGIN_CLASS(OpheliaAI)
ADD_STRINGPROP(AIState, "PASSIVE")
ADD_STRINGPROP(AIWeapon1, "TESLA")   \
ADD_STRINGPROP(AIWeapon2, "SNIPER")   \
ADD_VECTORPROP_VAL_FLAG(Dims, 12.0f, 38.0f, 12.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(OpheliaAI, AI_Mgr, NULL, NULL)

typedef struct OpheliaREV_t
{
	BaseClass m_BaseClass;
} OpheliaREV;

BEGIN_CLASS(OpheliaREV)
ADD_STRINGPROP(AIState, "PASSIVE")
ADD_STRINGPROP(AIWeapon1, "TESLA")   \
ADD_STRINGPROP(AIWeapon2, "SNIPER")   \
ADD_VECTORPROP_VAL_FLAG(Dims, 12.0f, 38.0f, 12.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(OpheliaREV, AI_Mgr, NULL, NULL)

typedef struct Prophet_t
{
	BaseClass m_BaseClass;
} Prophet;

BEGIN_CLASS(Prophet)
ADD_REALPROP(RandomHitPoints, 0.0f) \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_STRINGPROP(AIWeapon1, "BERETTA")   \
ADD_STRINGPROP(AIWeapon2, "COMBAT")   \
ADD_STRINGPROP(AIWeapon3, "ASSAULTRIFLE")   \
ADD_STRINGPROP(AIWeapon4, "COMBAT")   \
ADD_STRINGPROP(AIWeapon5, "ASSAULTRIFLE")   \
ADD_REALPROP(Bullets, 750.0f)     \
ADD_REALPROP(BMG, 150.0f)     \
ADD_REALPROP(Shells, 150.0f)     \
ADD_REALPROP(Grenades, 50.0f)	\
ADD_REALPROP(Rockets, 100.0f)     \
ADD_REALPROP(Flares, 100.0f)     \
ADD_REALPROP(Cells, 600.0f)     \
ADD_REALPROP(Charges, 400.0f)     \
ADD_REALPROP(Fuel, 200.0f)     \
ADD_VECTORPROP_VAL_FLAG(Dims, 19.0f, 43.0f, 15.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(Prophet, AI_Mgr, NULL, NULL)

typedef struct RatAI_t
{
	BaseClass m_BaseClass;
} RatAI;

BEGIN_CLASS(RatAI)
ADD_STRINGPROP(SpotTriggerTarget, "")
ADD_STRINGPROP(SpotTriggerMessage, "")
ADD_STRINGPROP(TriggerRelayTarget, "")
ADD_REALPROP(HitPoints, 1.0f)     \
ADD_REALPROP(RandomHitPoints, 0.0f) \
END_CLASS_DEFAULT(RatAI, AI_Mgr, NULL, NULL)

typedef struct ShikariAI_t
{
	BaseClass m_BaseClass;
} ShikariAI;

BEGIN_CLASS(ShikariAI)
ADD_REALPROP(RandomHitPoints, 50.0f) \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_VECTORPROP_VAL_FLAG(Dims, 19.0f, 30.0f, 24.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(ShikariAI, AI_Mgr, NULL, NULL)

typedef struct SoulDrudge_t
{
	BaseClass m_BaseClass;
} SoulDrudge;

BEGIN_CLASS(SoulDrudge)
ADD_REALPROP(RandomHitPoints, 50.0f) \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_VECTORPROP_VAL_FLAG(Dims, 21.0f, 36.0f, 18.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(SoulDrudge, AI_Mgr, NULL, NULL)

typedef struct TheHandAI_t
{
	BaseClass m_BaseClass;
} TheHandAI;

BEGIN_CLASS(TheHandAI)
ADD_REALPROP(RandomHitPoints, 0.0f) \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_VECTORPROP_VAL_FLAG(Dims, 4.0f, 4.0f, 5.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(TheHandAI, AI_Mgr, NULL, NULL)

typedef struct Thief_t
{
	BaseClass m_BaseClass;
} Thief;

BEGIN_CLASS(Thief)
ADD_REALPROP(RandomHitPoints, 0.0f) \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_VECTORPROP_VAL_FLAG(Dims, 9.0f, 9.0f, 8.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(Thief, AI_Mgr, NULL, NULL)

typedef struct UndeadGideon_t
{
	BaseClass m_BaseClass;
} UndeadGideon;

BEGIN_CLASS(UndeadGideon)
ADD_REALPROP(RandomHitPoints, 50.0f) \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_VECTORPROP_VAL_FLAG(Dims, 70.0f, 88.0f, 70.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(UndeadGideon, AI_Mgr, NULL, NULL)

typedef struct WurmAI_t
{
	BaseClass m_BaseClass;
} WurmAI;

BEGIN_CLASS(WurmAI)
ADD_STRINGPROP(SpotTriggerTarget, "")
ADD_STRINGPROP(SpotTriggerMessage, "")
ADD_STRINGPROP(TriggerRelayTarget, "")
ADD_REALPROP(HitPoints, 30.0f)     \
ADD_REALPROP(RandomHitPoints, 50.0f) \
ADD_REALPROP(ArmorPoints, 0.0f)     \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_STRINGPROP(AIBrain, "STRONG")   \
END_CLASS_DEFAULT(WurmAI, AI_Mgr, NULL, NULL)

typedef struct ZealotAI_t
{
	BaseClass m_BaseClass;
} ZealotAI;

BEGIN_CLASS(ZealotAI)
ADD_REALPROP(RandomHitPoints, 50.0f) \
ADD_STRINGPROP(AIState, "IDLE")     \
ADD_BOOLPROP(Divine, DFALSE)
ADD_VECTORPROP_VAL_FLAG(Dims, 12.0f, 44.0f, 12.0f, PF_DIMS | PF_LOCALDIMS | PF_HIDDEN)
END_CLASS_DEFAULT(ZealotAI, AI_Mgr, NULL, NULL)
#pragma endregion

#pragma region PICKUPS
//pickups
typedef struct PickupObject_t
{
	BaseClass m_BaseClass;
} PickupObject;

BEGIN_CLASS(PickupObject)
ADD_STRINGPROP(PickupTriggerTarget, "")
ADD_STRINGPROP(PickupTriggerMessage, "")
END_CLASS_DEFAULT(PickupObject, B2BaseClass, NULL, NULL)

#pragma region ITEMS
typedef struct ItemPickup_t
{
	PickupObject m_PickupObject;
} ItemPickup;

BEGIN_CLASS(ItemPickup)
END_CLASS_DEFAULT(ItemPickup, PickupObject, NULL, NULL)

typedef struct ItemPickupCharged_t
{
	ItemPickup m_ItemPickup;
} ItemPickupCharged;
BEGIN_CLASS(ItemPickupCharged)
END_CLASS_DEFAULT_FLAGS(ItemPickupCharged, ItemPickup, NULL, NULL, CF_HIDDEN)

typedef struct BinocularsPU_t
{
	ItemPickup m_ItemPickup;
} BinocularsPU;
BEGIN_CLASS(BinocularsPU)
END_CLASS_DEFAULT(BinocularsPU, ItemPickupCharged, NULL, NULL)

typedef struct TheEyePU_t
{
	ItemPickup m_ItemPickup;
} TheEyePU;
BEGIN_CLASS(TheEyePU)
END_CLASS_DEFAULT(TheEyePU, ItemPickupCharged, NULL, NULL)

typedef struct FlashlightPU_t
{
	ItemPickup m_ItemPickup;
} FlashlightPU;
BEGIN_CLASS(FlashlightPU)
END_CLASS_DEFAULT(FlashlightPU, ItemPickupCharged, NULL, NULL)

typedef struct MedKitPU_t
{
	ItemPickup m_ItemPickup;
} MedKitPU;
BEGIN_CLASS(MedKitPU)
END_CLASS_DEFAULT(MedKitPU, ItemPickupCharged, NULL, NULL)

typedef struct NightGogglesPU_t
{
	ItemPickup m_ItemPickup;
} NightGogglesPU;
BEGIN_CLASS(NightGogglesPU)
END_CLASS_DEFAULT(NightGogglesPU, ItemPickupCharged, NULL, NULL)

typedef struct ItemPickupWeapon_t
{
	ItemPickup m_ItemPickup;
} ItemPickupWeapon;
BEGIN_CLASS(ItemPickupWeapon)
END_CLASS_DEFAULT_FLAGS(ItemPickupWeapon, ItemPickup, NULL, NULL, CF_HIDDEN)

typedef struct ProximitiesPU_t
{
	ItemPickupWeapon m_ItemPickupWeapon;
} ProximitiesPU;
BEGIN_CLASS(ProximitiesPU)
END_CLASS_DEFAULT(ProximitiesPU, ItemPickupWeapon, NULL, NULL)

typedef struct RemotesPU_t
{
	ItemPickupWeapon m_ItemPickupWeapon;
} RemotesPU;
BEGIN_CLASS(RemotesPU)
END_CLASS_DEFAULT(RemotesPU, ItemPickupWeapon, NULL, NULL)

typedef struct TimeBombPU_t
{
	ItemPickupWeapon m_ItemPickupWeapon;
} TimeBombPU;

BEGIN_CLASS(TimeBombPU)
END_CLASS_DEFAULT(TimeBombPU, ItemPickupWeapon, NULL, NULL)

typedef struct KeyPickup_t
{
	PickupObject m_PickupObject;
} KeyPickup;
BEGIN_CLASS(KeyPickup)
ADD_STRINGPROP(ObjectName, "SuperKey")		// item name
ADD_LONGINTPROP(ResourceNum, 0)
ADD_STRINGPROP(IconFile, "key.pcx")			// File to use for the status bar icon
ADD_STRINGPROP(HiIconFile, "key_h.pcx")		// File to use for the status bar hilighted icon
ADD_STRINGPROP(ModelFile, "models\\powerups\\key.abc")	// Model filename for this item
ADD_STRINGPROP(ModelSkin, "skins\\powerups\\key.dtx")	// Model skin to use
ADD_LONGINTPROP(UseCount, 1)				// number of times it can be used before removal
END_CLASS_DEFAULT(KeyPickup, PickupObject, NULL, NULL)
#pragma endregion

#pragma region POWERUPS

typedef struct PowerupPickup_t
{
	PickupObject m_PickupObject;
} PowerupPickup;
BEGIN_CLASS(PowerupPickup)
END_CLASS_DEFAULT(PowerupPickup, PickupObject, NULL, NULL)

typedef struct HealthBase_t
{
	PowerupPickup m_PowerupPickup;
} HealthBase;

BEGIN_CLASS(HealthBase)
END_CLASS_DEFAULT_FLAGS(HealthBase, PowerupPickup, NULL, NULL, CF_HIDDEN)

typedef struct HealthPU_t
{
	HealthBase m_HealthBase;
} HealthPU;

BEGIN_CLASS(HealthPU)
END_CLASS_DEFAULT(HealthPU, HealthBase, NULL, NULL)

typedef struct MegaHealthPU_t
{
	HealthBase m_HealthBase;
} MegaHealthPU;

BEGIN_CLASS(MegaHealthPU)
END_CLASS_DEFAULT(MegaHealthPU, HealthBase, NULL, NULL)

typedef struct ArmorBase_t
{
	PowerupPickup m_PowerupPickup;
} ArmorBase;
BEGIN_CLASS(ArmorBase)
END_CLASS_DEFAULT_FLAGS(ArmorBase, PowerupPickup, NULL, NULL, CF_HIDDEN)

typedef struct WardPU_t
{
	ArmorBase m_ArmorBase;
} WardPU;

BEGIN_CLASS(WardPU)
END_CLASS_DEFAULT(WardPU, ArmorBase, NULL, NULL)

typedef struct NecroWardPU_t
{
	ArmorBase m_ArmorBase;
} NecroWardPU;

BEGIN_CLASS(NecroWardPU)
END_CLASS_DEFAULT(NecroWardPU, ArmorBase, NULL, NULL)

typedef struct EnhancementBase_t
{
	PowerupPickup m_PowerupPickup;
} EnhancementBase;

BEGIN_CLASS(EnhancementBase)
END_CLASS_DEFAULT_FLAGS(EnhancementBase, PowerupPickup, NULL, NULL, CF_HIDDEN)

typedef struct InvulnerabilityPU_t
{
	EnhancementBase m_EnhancementBase;
} InvulnerabilityPU;

BEGIN_CLASS(InvulnerabilityPU)
END_CLASS_DEFAULT(InvulnerabilityPU, EnhancementBase, NULL, NULL)

typedef struct StealthPU_t
{
	EnhancementBase m_EnhancementBase;
} StealthPU;
BEGIN_CLASS(StealthPU)
END_CLASS_DEFAULT(StealthPU, EnhancementBase, NULL, NULL)

typedef struct AngerPU_t
{
	EnhancementBase m_EnhancementBase;
} AngerPU;

BEGIN_CLASS(AngerPU)
END_CLASS_DEFAULT(AngerPU, EnhancementBase, NULL, NULL)

typedef struct RevenantPU_t
{
	EnhancementBase m_EnhancementBase;
} RevenantPU;
BEGIN_CLASS(RevenantPU)
END_CLASS_DEFAULT(RevenantPU, EnhancementBase, NULL, NULL)


#pragma endregion

#pragma region AMMO
	typedef struct AmmoPickup_t
	{
		PickupObject m_PickupObject;
	} AmmoPickup;
	BEGIN_CLASS(AmmoPickup)
	END_CLASS_DEFAULT(AmmoPickup, PickupObject, NULL, NULL)

	typedef struct BulletAmmoPU_t
	{
		AmmoPickup m_AmmoPickup;
	} BulletAmmoPU;
	BEGIN_CLASS(BulletAmmoPU)
	END_CLASS_DEFAULT(BulletAmmoPU, AmmoPickup, NULL, NULL)

	typedef struct ShellAmmoPU_t
	{
		AmmoPickup m_AmmoPickup;
	} ShellAmmoPU;
	BEGIN_CLASS(ShellAmmoPU)
	END_CLASS_DEFAULT(ShellAmmoPU, AmmoPickup, NULL, NULL)

	typedef struct BMGAmmoPU_t
	{
		AmmoPickup m_AmmoPickup;
	} BMGAmmoPU;
	BEGIN_CLASS(BMGAmmoPU)
	END_CLASS_DEFAULT(BMGAmmoPU, AmmoPickup, NULL, NULL)

	typedef struct FlareAmmoPU_t
	{
		AmmoPickup m_AmmoPickup;
	} FlareAmmoPU;
	BEGIN_CLASS(FlareAmmoPU)
	END_CLASS_DEFAULT(FlareAmmoPU, AmmoPickup, NULL, NULL)

		typedef struct DieBugDieAmmoPU_t
	{
		AmmoPickup m_AmmoPickup;
	} DieBugDieAmmoPU;
	BEGIN_CLASS(DieBugDieAmmoPU)
	END_CLASS_DEFAULT(DieBugDieAmmoPU, AmmoPickup, NULL, NULL)

	typedef struct HowitzerAmmoPU_t
	{
		AmmoPickup m_AmmoPickup;
	} HowitzerAmmoPU;
	BEGIN_CLASS(HowitzerAmmoPU)
	END_CLASS_DEFAULT(HowitzerAmmoPU, AmmoPickup, NULL, NULL)

	typedef struct FuelAmmoPU_t
	{
		AmmoPickup m_AmmoPickup;
	} FuelAmmoPU;
	BEGIN_CLASS(FuelAmmoPU)
	END_CLASS_DEFAULT(FuelAmmoPU, AmmoPickup, NULL, NULL)

		typedef struct BatteryAmmoPU_t
	{
		AmmoPickup m_AmmoPickup;
	} BatteryAmmoPU;
	BEGIN_CLASS(BatteryAmmoPU)
	END_CLASS_DEFAULT(BatteryAmmoPU, AmmoPickup, NULL, NULL)
	#pragma endregion
	
#pragma region WEAPONS
		typedef struct WeaponPickup_t
		{
			PickupObject m_PickupObject;
		} WeaponPickup;
		BEGIN_CLASS(WeaponPickup)
		END_CLASS_DEFAULT(WeaponPickup, PickupObject, NULL, NULL)
		
		typedef struct BerettaPU_t
		{
			WeaponPickup m_WeaponPickup;
		} BerettaPU;
		BEGIN_CLASS(BerettaPU)
		END_CLASS_DEFAULT(BerettaPU, WeaponPickup, NULL, NULL)

		typedef struct ShotgunPU_t	
		{
			WeaponPickup m_WeaponPickup;
		} ShotgunPU;
		BEGIN_CLASS(ShotgunPU)
		END_CLASS_DEFAULT(ShotgunPU, WeaponPickup, NULL, NULL)
			
		typedef struct CombatShotgunPU_t
		{
			ShotgunPU m_ShotgunPU;
		} CombatShotgunPU;
		
		BEGIN_CLASS(CombatShotgunPU)
		END_CLASS_DEFAULT(CombatShotgunPU, WeaponPickup, NULL, NULL)

		typedef struct SniperRiflePU_t
		{
			WeaponPickup m_WeaponPickup;
		} SniperRiflePU;
		BEGIN_CLASS(SniperRiflePU)
		END_CLASS_DEFAULT(SniperRiflePU, WeaponPickup, NULL, NULL)

		typedef struct AssaultRiflePU_t
		{
			WeaponPickup m_WeaponPickup;
		} AssaultRiflePU;
		BEGIN_CLASS(AssaultRiflePU)
		END_CLASS_DEFAULT(AssaultRiflePU, WeaponPickup, NULL, NULL)

		typedef struct SubMachineGunPU_t
		{
			WeaponPickup m_WeaponPickup;
		} SubMachineGunPU;
		BEGIN_CLASS(SubMachineGunPU)
		END_CLASS_DEFAULT(SubMachineGunPU, WeaponPickup, NULL, NULL)

		typedef struct FlareGunPU_t
		{
			WeaponPickup m_WeaponPickup;
		} FlareGunPU;
		BEGIN_CLASS(FlareGunPU)
		END_CLASS_DEFAULT(FlareGunPU, WeaponPickup, NULL, NULL)

		typedef struct HowitzerPU_t
		{
			WeaponPickup m_WeaponPickup;
		} HowitzerPU;
		BEGIN_CLASS(HowitzerPU)
		END_CLASS_DEFAULT(HowitzerPU, WeaponPickup, NULL, NULL)

		typedef struct BugSprayPU_t
		{
			WeaponPickup m_WeaponPickup;
		} BugSprayPU;
		BEGIN_CLASS(BugSprayPU)
		END_CLASS_DEFAULT(BugSprayPU, WeaponPickup, NULL, NULL)

		typedef struct NapalmCannonPU_t
		{
			WeaponPickup m_WeaponPickup;
		} NapalmCannonPU;
		BEGIN_CLASS(NapalmCannonPU)
		END_CLASS_DEFAULT(NapalmCannonPU, WeaponPickup, NULL, NULL)

		typedef struct MiniGunPU_t
		{
			WeaponPickup m_WeaponPickup;
		} MiniGunPU;
		BEGIN_CLASS(MiniGunPU)
		END_CLASS_DEFAULT(MiniGunPU, WeaponPickup, NULL, NULL)

		typedef struct VoodooDollPU_t
		{
			WeaponPickup m_WeaponPickup;
		} VoodooDollPU;
		BEGIN_CLASS(VoodooDollPU)
		END_CLASS_DEFAULT(VoodooDollPU, WeaponPickup, NULL, NULL)

		typedef struct OrbPU_t
		{
			WeaponPickup m_WeaponPickup;
		} OrbPU;
		BEGIN_CLASS(OrbPU)
		END_CLASS_DEFAULT(OrbPU, WeaponPickup, NULL, NULL)

		typedef struct DeathRayPU_t
		{
			WeaponPickup m_WeaponPickup;
		} DeathRayPU;
		BEGIN_CLASS(DeathRayPU)
		END_CLASS_DEFAULT(DeathRayPU, WeaponPickup, NULL, NULL)

		typedef struct LifeLeechPU_t
		{
			WeaponPickup m_WeaponPickup;
		} LifeLeechPU;
		BEGIN_CLASS(LifeLeechPU)
		END_CLASS_DEFAULT(LifeLeechPU, WeaponPickup, NULL, NULL)

		typedef struct FlayerPU_t
		{
			WeaponPickup m_WeaponPickup;
		} FlayerPU;
		BEGIN_CLASS(FlayerPU)
		END_CLASS_DEFAULT(FlayerPU, WeaponPickup, NULL, NULL)
			
		typedef struct TeslaCannonPU_t
		{
			WeaponPickup m_WeaponPickup;
		} TeslaCannonPU;
		BEGIN_CLASS(TeslaCannonPU)
		END_CLASS_DEFAULT(TeslaCannonPU, WeaponPickup, NULL, NULL)

		typedef struct SingularityPU_t
		{
			WeaponPickup m_WeaponPickup;
		} SingularityPU;
		BEGIN_CLASS(SingularityPU)
		END_CLASS_DEFAULT(SingularityPU, WeaponPickup, NULL, NULL)
			
#pragma endregion
#pragma endregion

#pragma region CLIENT
	typedef struct CClientSFX_t
	{
		BaseClass m_BaseClass;
	} CClientSFX;

	BEGIN_CLASS(CClientSFX)
	END_CLASS_DEFAULT_FLAGS(CClientSFX, B2BaseClass, NULL, NULL, CF_HIDDEN)

	typedef struct CBulletImpactSFX_t
	{
		CClientSFX m_BaseClass;
	} CBulletImpactSFX;
	BEGIN_CLASS(CBulletImpactSFX)
	END_CLASS_DEFAULT_FLAGS(CBulletImpactSFX, CClientSFX, NULL, NULL, CF_HIDDEN)
	
	typedef struct CClientCastLineSFX_t
	{
		CClientSFX m_BaseClass;
	} CClientCastLineSFX;
	BEGIN_CLASS(CClientCastLineSFX)
	END_CLASS_DEFAULT_FLAGS(CClientCastLineSFX, CClientSFX, NULL, NULL, CF_HIDDEN)
		
	typedef struct CClientExplosionSFX_t
	{
		CClientSFX m_BaseClass;
	} CClientExplosionSFX;
	BEGIN_CLASS(CClientExplosionSFX)
	ADD_LONGINTPROP(ExplosionType, 0)
	ADD_REALPROP(Damage, 50.0f)
	ADD_REALPROP_FLAG(DamageRadius, 200.0f, PF_RADIUS)
	ADD_VECTORPROP_VAL(Direction, 0.0f, 1.0f, 0.0f)
	ADD_STRINGPROP(WaveFile, "Sounds\\exp_tnt.wav")
	END_CLASS_DEFAULT(CClientExplosionSFX, CClientSFX, NULL, NULL)

	typedef struct CClientLaserBeamSFX_t
	{
		CClientSFX m_BaseClass;
	} CClientLaserBeamSFX;
	
	BEGIN_CLASS(CClientLaserBeamSFX)
	ADD_LONGINTPROP(BeamType, 0)
	ADD_REALPROP(Damage, 100.0f)
	ADD_REALPROP(DamageRadius, 100.0f)
	ADD_STRINGPROP(Sound, "Sounds\\Thunder.wav")
	ADD_REALPROP_FLAG(SoundRadius, 500.0f, PF_RADIUS)
	END_CLASS_DEFAULT(CClientLaserBeamSFX, CClientSFX, NULL, NULL)

	typedef struct ClientLightFX_t
	{
		CClientSFX m_BaseClass;
	} ClientLightFX;
	
	BEGIN_CLASS(ClientLightFX)
		ADD_STRINGPROP(DamageTriggerTarget, "") \
		ADD_STRINGPROP(DamageTriggerMessage, "") \
		ADD_STRINGPROP(DeathTriggerTarget, "") \
		ADD_STRINGPROP(DeathTriggerMessage, "") \
		ADD_BOOLPROP(TriggerDestroyOnly, DFALSE) \
		ADD_STRINGPROP(SpawnObject, "") \
		ADD_VECTORPROP(SpawnObjectVel) \
		ADD_BOOLPROP(CanDamage, DTRUE)
	ADD_REALPROP(HitPoints, 1.0f)
	ADD_BOOLPROP(LightSwitch, DTRUE)
	ADD_REALPROP(LifeTime, 0.0f)
	ADD_COLORPROP(Color, 255.0f, 255.0f, 255.0f)
	ADD_REALPROP(IntensityMin, 0.5f)
	ADD_REALPROP(IntensityMax, 1.0f)
	ADD_LONGINTPROP(IntensityWaveform, 0)
	ADD_REALPROP(IntensityFreq, 4.0f)
	ADD_REALPROP(IntensityPhase, 0.0f)

	ADD_REALPROP_FLAG(RadiusMin, 200.0f, PF_RADIUS)
	ADD_REALPROP_FLAG(RadiusMax, 500.0f, PF_RADIUS)
	ADD_LONGINTPROP(RadiusWaveform, 0)
	ADD_REALPROP(RadiusFreq, 4.0f)
	ADD_REALPROP(RadiusPhase, 0.0f)

	ADD_STRINGPROP(RampUpSound, "")
	ADD_STRINGPROP(RampDownSound, "")
	ADD_BOOLPROP(CastShadowsFlag, DFALSE)
	ADD_BOOLPROP(SolidLightFlag, DFALSE)
	ADD_BOOLPROP(OnlyLightWorldFlag, DFALSE)
	ADD_BOOLPROP(DontLightBackfacingFlag, DFALSE)
	ADD_BOOLPROP(FogLightFlag, DFALSE)
	END_CLASS_DEFAULT(ClientLightFX, CClientSFX, NULL, NULL)

	typedef struct CClientLightningSFX_t
	{
		CClientSFX m_BaseClass;
	} CClientLightningSFX;
		
	BEGIN_CLASS(CClientLightningSFX)
	ADD_LONGINTPROP(LightningShape, 2)
	ADD_LONGINTPROP(LightningForm, 1)
	ADD_LONGINTPROP(LightningType, 2)
	ADD_REALPROP(Damage, 500.0f)
	ADD_REALPROP(DamageRadius, 300.0f)
	ADD_STRINGPROP(Sound, "Sounds\\Thunder.wav")
	ADD_REALPROP_FLAG(SoundRadius, 1000.0f, PF_RADIUS)
	END_CLASS_DEFAULT(CClientLightningSFX, CClientSFX, NULL, NULL)
			
	typedef struct CClientMarkSFX_t
	{
		CClientSFX m_BaseClass;
	} CClientMarkSFX;
	BEGIN_CLASS(CClientMarkSFX)
	END_CLASS_DEFAULT_FLAGS(CClientMarkSFX, CClientSFX, NULL, NULL, CF_HIDDEN)
			
	typedef struct CClientParticleStreamSFX_t
	{
		CClientSFX m_BaseClass;
	} CClientParticleStreamSFX;
		
	BEGIN_CLASS(CClientParticleStreamSFX)
	ADD_REALPROP(SystemRadius, 1000.0f)
	ADD_REALPROP_FLAG(PositionRadius, 1.0f, PF_RADIUS)
	ADD_REALPROP(MinVelocity, 0.0f)
	ADD_REALPROP(MaxVelocity, 25.0f)
	ADD_LONGINTPROP(NumParticles, 1)
	ADD_REALPROP(VelSpread, 0.0f)
	ADD_COLORPROP(MinColor, 255.0f, 255.0f, 255.0f)
	ADD_COLORPROP(MaxColor, 255.0f, 255.0f, 255.0f)
	ADD_REALPROP(SystemAlpha, 1.0f)
	ADD_REALPROP(MinLifetime, 1.0f)
	ADD_REALPROP(MaxLifetime, 2.0f)
	ADD_REALPROP(RampTime, 0.0f)
	ADD_REALPROP(AddDelay, 0.1f)
	ADD_REALPROP(Gravity, 15.0f)
	ADD_BOOLPROP(RampAmount, DFALSE)
	ADD_BOOLPROP(RampOffset, DFALSE)
	ADD_BOOLPROP(RampVelocity, DFALSE)
	ADD_BOOLPROP(RampLifetime, DFALSE)
	ADD_BOOLPROP(InitiallyOn, DFALSE)
	ADD_STRINGPROP(ParticleFile, "SpriteTextures\\drop32_1.dtx")
	ADD_REALPROP(SoundRadius, 200.0f)
	ADD_STRINGPROP(RampUpSound, "")
	ADD_STRINGPROP(LoopSound, "")
	ADD_STRINGPROP(RampDownSound, "")
	END_CLASS_DEFAULT(CClientParticleStreamSFX, CClientSFX, NULL, NULL)
				
	typedef struct CClientSmokeTrail_t
	{
		CClientSFX m_BaseClass;
	} CClientSmokeTrail;
			
	BEGIN_CLASS(CClientSmokeTrail)
	END_CLASS_DEFAULT_FLAGS(CClientSmokeTrail, CClientSFX, NULL, NULL, CF_HIDDEN)
				
	typedef struct CClientSparksSFX_t
	{
		CClientSFX m_BaseClass;
	} CClientSparksSFX;
	BEGIN_CLASS(CClientSparksSFX)
	END_CLASS_DEFAULT_FLAGS(CClientSparksSFX, CClientSFX, NULL, NULL, CF_HIDDEN)
				
	typedef struct CClientSplashSFX_t
	{
		CClientSFX m_BaseClass;
	} CClientSplashSFX;
	BEGIN_CLASS(CClientSplashSFX)
	END_CLASS_DEFAULT_FLAGS(CClientSplashSFX, CClientSFX, NULL, NULL, CF_HIDDEN)
					
	typedef struct CClientSplatFX_t
	{
		BaseClass m_BaseClass;
	} CClientSplatFX;
	BEGIN_CLASS(CClientSplatFX)
	END_CLASS_DEFAULT_FLAGS(CClientSplatFX, CClientSFX, NULL, NULL, CF_HIDDEN)

	typedef struct CClientTracer_t
	{
		BaseClass m_BaseClass;
	} CClientTracer;
	BEGIN_CLASS(CClientTracer)
	END_CLASS_DEFAULT_FLAGS(CClientTracer, CClientSFX, NULL, NULL, CF_HIDDEN)

	typedef struct CClientWarpGateSFX_t
	{
		BaseClass m_BaseClass;
	} CClientWarpGateSFX;
			
	BEGIN_CLASS(CClientWarpGateSFX)
	ADD_REALPROP(RampUpTime, 5.0f)
	ADD_REALPROP(RampDownTime, 5.0f)
	ADD_BOOLPROP(InitiallyOn, DFALSE)

	PROP_DEFINEGROUP(SpriteData, PF_GROUP1)
	ADD_REALPROP_FLAG(SpriteMinScale, 0.1f, PF_GROUP1)
	ADD_REALPROP_FLAG(SpriteMaxScale, 1.0f, PF_GROUP1)
	ADD_REALPROP_FLAG(SpriteAlpha, 0.75f, PF_GROUP1)
	ADD_LONGINTPROP_FLAG(SpriteRampUpType, 1, PF_GROUP1)
	ADD_LONGINTPROP_FLAG(SpriteRampDownType, 2, PF_GROUP1)
	ADD_BOOLPROP_FLAG(SpriteAlign, DFALSE, PF_GROUP1)
	ADD_STRINGPROP_FLAG(SpriteFile, "Sprites\\rift.spr", PF_GROUP1)

	PROP_DEFINEGROUP(ParticleSystem1Data, PF_GROUP2)
	ADD_REALPROP_FLAG(PS1SystemRadius, 5000.0f, PF_GROUP2)
	ADD_REALPROP_FLAG(PS1PositionRadius, 100.0f, PF_RADIUS | PF_GROUP2)
	ADD_VECTORPROP_FLAG(PS1Offset, PF_GROUP2)
	ADD_VECTORPROP_FLAG(PS1Rotations, PF_GROUP2)
	ADD_REALPROP_FLAG(PS1MinVelocity, 10.0f, PF_GROUP2)
	ADD_REALPROP_FLAG(PS1MaxVelocity, 25.0f, PF_GROUP2)
	ADD_LONGINTPROP_FLAG(PS1NumParticles, 10, PF_GROUP2)
	ADD_LONGINTPROP_FLAG(PS1EmitType, 1, PF_GROUP2)
	ADD_COLORPROP_FLAG(PS1MinColor, 50.0f, 50.0f, 50.0f, PF_GROUP2)
	ADD_COLORPROP_FLAG(PS1MaxColor, 255.0f, 255.0f, 255.0f, PF_GROUP2)
	ADD_REALPROP_FLAG(PS1SystemAlpha, 0.5f, PF_GROUP2)
	ADD_REALPROP_FLAG(PS1MinLifetime, 4.0f, PF_GROUP2)
	ADD_REALPROP_FLAG(PS1MaxLifetime, 5.0f, PF_GROUP2)
	ADD_REALPROP_FLAG(PS1AddDelay, 0.25f, PF_GROUP2)
	ADD_REALPROP_FLAG(PS1Gravity, 15.0f, PF_GROUP2)
	ADD_LONGINTPROP_FLAG(PS1RampUpType, 1, PF_GROUP2)
	ADD_LONGINTPROP_FLAG(PS1RampDownType, 1, PF_GROUP2)
	ADD_BOOLPROP_FLAG(PS1Align, DFALSE, PF_GROUP2)
	ADD_STRINGPROP_FLAG(PS1ParticleFile, "SpriteTextures\\smoke64_3.dtx", PF_GROUP2)

	PROP_DEFINEGROUP(ParticleSystem2Data, PF_GROUP3)
	ADD_REALPROP_FLAG(PS2SystemRadius, 5000.0f, PF_GROUP3)
	ADD_REALPROP_FLAG(PS2PositionRadius, 100.0f, PF_RADIUS | PF_GROUP3)
	ADD_VECTORPROP_FLAG(PS2Offset, PF_GROUP3)
	ADD_VECTORPROP_FLAG(PS2Rotations, PF_GROUP3)
	ADD_REALPROP_FLAG(PS2MinVelocity, 10.0f, PF_GROUP3)
	ADD_REALPROP_FLAG(PS2MaxVelocity, 25.0f, PF_GROUP3)
	ADD_LONGINTPROP_FLAG(PS2NumParticles, 10, PF_GROUP3)
	ADD_LONGINTPROP_FLAG(PS2EmitType, 1, PF_GROUP3)
	ADD_COLORPROP_FLAG(PS2MinColor, 50.0f, 50.0f, 50.0f, PF_GROUP3)
	ADD_COLORPROP_FLAG(PS2MaxColor, 255.0f, 255.0f, 255.0f, PF_GROUP3)
	ADD_REALPROP_FLAG(PS2SystemAlpha, 0.5f, PF_GROUP3)
	ADD_REALPROP_FLAG(PS2MinLifetime, 4.0f, PF_GROUP3)
	ADD_REALPROP_FLAG(PS2MaxLifetime, 5.0f, PF_GROUP3)
	ADD_REALPROP_FLAG(PS2AddDelay, 0.25f, PF_GROUP3)
	ADD_REALPROP_FLAG(PS2Gravity, 15.0f, PF_GROUP3)
	ADD_LONGINTPROP_FLAG(PS2RampUpType, 1, PF_GROUP3)
	ADD_LONGINTPROP_FLAG(PS2RampDownType, 1, PF_GROUP3)
	ADD_BOOLPROP_FLAG(PS2Align, DFALSE, PF_GROUP3)
	ADD_STRINGPROP_FLAG(PS2ParticleFile, "SpriteTextures\\lensflare_1.dtx", PF_GROUP3)

	ADD_REALPROP(SoundRadius, 200.0f)
	ADD_STRINGPROP(RampUpSound, "")
	ADD_STRINGPROP(LoopSound, "")
	ADD_STRINGPROP(RampDownSound, "")
	END_CLASS_DEFAULT(CClientWarpGateSFX, CClientSFX, NULL, NULL)

	typedef struct CClientWeaponSFX_t
	{
		BaseClass m_BaseClass;
	}CClientWeaponSFX;
			
	BEGIN_CLASS(CClientWeaponSFX)
	END_CLASS_DEFAULT_FLAGS(CClientWeaponSFX, CClientSFX, NULL, NULL, CF_HIDDEN)
		
	typedef struct ParticleSystem_t
	{
	BaseClass m_BaseClass;
	}ParticleSystem;
	BEGIN_CLASS(ParticleSystem)
	ADD_BOOLPROP(Static, 1)
	ADD_LONGINTPROP(ParticleFlags, 0)
	ADD_REALPROP(BurstWait, 0.0f)
	ADD_REALPROP(ParticlesPerSecond, 0.0f)
	ADD_REALPROP_FLAG(EmissionRadius, 0.0f, PF_RADIUS)
	ADD_REALPROP(MinimumVelocity, 0.0f)
	ADD_REALPROP(MaximumVelocity, 0.0f)
	ADD_REALPROP(VelocityOffset, 0.0f)
	ADD_REALPROP(ParticleLifetime, 5.0f)
	ADD_REALPROP(ParticleRadius, 1000.0f)
	ADD_REALPROP(Gravity, -500.0f)
	ADD_REALPROP(RotationVelocity, 0.0f)
	ADD_STRINGPROP(TextureName, "SpecialFX\\ParticleTextures\\particle.dtx")
	ADD_COLORPROP(Color1, 255.0f, 255.0f, 255.0f)
	ADD_COLORPROP(Color2, 255.0f, 0.0f, 0.0f)
	END_CLASS_DEFAULT_FLAGS(ParticleSystem, CClientSFX, NULL, NULL, CF_ALWAYSLOAD)

		typedef struct PolyGrid_t
	{
		BaseClass m_BaseClass;
	}PolyGrid;
		BEGIN_CLASS(PolyGrid)
		ADD_VECTORPROP_FLAG(Dims, PF_DIMS | PF_LOCALDIMS)
		ADD_COLORPROP(Color1, 255.0f, 255.0f, 255.0f)
		ADD_COLORPROP(Color2, 255.0f, 255.0f, 255.0f)
		ADD_STRINGPROP(SpriteSurfaceName, "Sprites\\VolumeBrushSprites\\Water1.spr")
		ADD_REALPROP(XScaleMin, 15.0f)
		ADD_REALPROP(XScaleMax, 15.0f)
		ADD_REALPROP(YScaleMin, 15.0f)
		ADD_REALPROP(YScaleMax, 15.0f)
		ADD_REALPROP(XScaleDuration, 10.0f)
		ADD_REALPROP(YScaleDuration, 10.0f)
		ADD_REALPROP(XPan, 10.0f)
		ADD_REALPROP(YPan, 10.0f)
		ADD_REALPROP(Alpha, 0.7f)
		ADD_LONGINTPROP(NumPolies, 160)
		PROP_DEFINEGROUP(PlasmaInfo, PF_GROUP1)
		ADD_LONGINTPROP_FLAG(PlasmaType, 1, PF_GROUP1)
		ADD_LONGINTPROP_FLAG(Ring1Rate, 50, PF_GROUP1)
		ADD_LONGINTPROP_FLAG(Ring2Rate, 10, PF_GROUP1)
		ADD_LONGINTPROP_FLAG(Ring3Rate, 30, PF_GROUP1)
		ADD_LONGINTPROP_FLAG(Ring4Rate, 20, PF_GROUP1)

		END_CLASS_DEFAULT_FLAGS(PolyGrid, CClientSFX, NULL, NULL, CF_ALWAYSLOAD)
		
			typedef struct Rain_t
		{
			BaseClass m_BaseClass;
		}Rain;
			BEGIN_CLASS(Rain)
			ADD_REALPROP(Density, 0.0f)
			ADD_VECTORPROP_FLAG(Dims, PF_DIMS)
			ADD_REALPROP(Lifetime, 1.0f)
			ADD_VECTORPROP(Direction)
			ADD_BOOLPROP(AddGravity, DTRUE)
			ADD_REALPROP(ParticleScale, 1.0f)
			ADD_REALPROP(Spread, 0.0f)
			ADD_BOOLPROP(Triggered, DFALSE)
			ADD_COLORPROP(Color1, 200.0f, 255.0f, 255.0f)
			ADD_COLORPROP(Color2, 40.0f, 50.0f, 50.0f)
			ADD_REALPROP(TimeLimit, 0.0f)
			ADD_REALPROP(Pulse, 0.0f)
			END_CLASS_DEFAULT(Rain, CClientSFX, NULL, NULL)

				
			
#pragma endregion
		
#pragma region CAMERA
typedef struct CameraObj_t
{
	BaseClass m_BaseClass;
} CameraObj;
BEGIN_CLASS(CameraObj)
ADD_LONGINTPROP(Type, 0)
ADD_REALPROP(ActiveTime, -1)
ADD_BOOLPROP(AllowPlayerMovement, DFALSE)
ADD_BOOLPROP(StartActive, DFALSE)
ADD_BOOLPROP(IsListener, DTRUE)
ADD_BOOLPROP(HidePlayer, DFALSE)
ADD_BOOLPROP_FLAG(TypeActionMode, DFALSE, PF_GROUP6)
END_CLASS_DEFAULT(CameraObj, B2BaseClass, NULL, NULL)


typedef struct CameraSpot_t
{
	BaseClass m_BaseClass;
} CameraSpot;

BEGIN_CLASS(CameraSpot)
END_CLASS_DEFAULT_FLAGS(CameraSpot, B2BaseClass, NULL, NULL, CF_ALWAYSLOAD)
#pragma endregion

#pragma region TRIGGERS

typedef struct Trigger_t
{
	BaseClass m_BaseClass;
} Trigger;

BEGIN_CLASS(Trigger)
ADD_VECTORPROP_FLAG(Dims, PF_DIMS)
ADD_REALPROP(ResetTime, 0.0f)
ADD_STRINGPROP(ActivationSound, "")
ADD_REALPROP(SoundRadius, 200.0f)
ADD_STRINGPROP(TargetName1, "")
ADD_STRINGPROP(MessageName1, "")
ADD_REALPROP(MessageDelay, 0.0f)
ADD_STRINGPROP(TargetName2, "")
ADD_STRINGPROP(MessageName2, "")
ADD_REALPROP(MessageDelay2, 0.0f)
ADD_STRINGPROP(TargetName3, "")
ADD_STRINGPROP(MessageName3, "")
ADD_REALPROP(MessageDelay3, 0.0f)
ADD_STRINGPROP(TargetName4, "")
ADD_STRINGPROP(MessageName4, "")
ADD_REALPROP(MessageDelay4, 0.0f)
PROP_DEFINEGROUP(AdditionalTargets, PF_GROUP1)
ADD_STRINGPROP_FLAG(TargetName5, "", PF_GROUP1)
ADD_STRINGPROP_FLAG(MessageName5, "", PF_GROUP1)
ADD_REALPROP_FLAG(MessageDelay5, 0.0f, PF_GROUP1)
ADD_STRINGPROP_FLAG(TargetName6, "", PF_GROUP1)
ADD_STRINGPROP_FLAG(MessageName6, "", PF_GROUP1)
ADD_REALPROP_FLAG(MessageDelay6, 0.0f, PF_GROUP1)
ADD_STRINGPROP_FLAG(TargetName7, "", PF_GROUP1)
ADD_STRINGPROP_FLAG(MessageName7, "", PF_GROUP1)
ADD_REALPROP_FLAG(MessageDelay7, 0.0f, PF_GROUP1)
ADD_STRINGPROP_FLAG(TargetName8, "", PF_GROUP1)
ADD_STRINGPROP_FLAG(MessageName8, "", PF_GROUP1)
ADD_REALPROP_FLAG(MessageDelay8, 0.0f, PF_GROUP1)
ADD_STRINGPROP_FLAG(TargetName9, "", PF_GROUP1)
ADD_STRINGPROP_FLAG(MessageName9, "", PF_GROUP1)
ADD_REALPROP_FLAG(MessageDelay9, 0.0f, PF_GROUP1)
ADD_STRINGPROP_FLAG(TargetName10, "", PF_GROUP1)
ADD_STRINGPROP_FLAG(MessageName10, "", PF_GROUP1)
ADD_REALPROP_FLAG(MessageDelay10, 0.0f, PF_GROUP1)

ADD_BOOLPROP(TouchActivate, DTRUE)
ADD_BOOLPROP(PlayerActivate, DTRUE)
ADD_BOOLPROP(AIActivate, DTRUE)
ADD_BOOLPROP(ObjectActivate, DFALSE)
ADD_BOOLPROP(TriggerRelayActivate, DTRUE)
ADD_BOOLPROP(NamedObjectActivate, DFALSE)
ADD_STRINGPROP(ActivationObjectName, "")

ADD_LONGINTPROP(ActivationCount, 1)
ADD_BOOLPROP(Locked, DFALSE)
//	ADD_STRINGPROP(LockedMsg, "")
ADD_STRINGPROP(LockedSound, "")
//	ADD_STRINGPROP(UnlockedMsg, "")
ADD_STRINGPROP(UnlockedSound, "")
ADD_STRINGPROP(UnlockKeyName, "Key")
END_CLASS_DEFAULT(Trigger, B2BaseClass, NULL, NULL)

typedef struct BigTrigger_t
{
	BaseClass m_BaseClass;
} BigTrigger;

BEGIN_CLASS(BigTrigger)
END_CLASS_DEFAULT(BigTrigger, Trigger, NULL, NULL)

typedef struct ToggleTrigger_t
{
	BaseClass m_BaseClass;
} ToggleTrigger;

BEGIN_CLASS(ToggleTrigger)
ADD_STRINGPROP(OffMessageName1, "")
ADD_STRINGPROP(OffMessageName2, "")
ADD_STRINGPROP(OffMessageName3, "")
ADD_STRINGPROP(OffMessageName4, "")
ADD_STRINGPROP(OffMessageName5, "")
ADD_STRINGPROP(OffMessageName6, "")
ADD_STRINGPROP(OffMessageName7, "")
ADD_STRINGPROP(OffMessageName8, "")
ADD_STRINGPROP(OffMessageName9, "")
ADD_STRINGPROP(OffMessageName10, "")
ADD_BOOLPROP(StartOn, DFALSE)
END_CLASS_DEFAULT(ToggleTrigger, Trigger, NULL, NULL)

typedef struct CinematicTrigger_t
{
	BaseClass m_BaseClass;
} CinematicTrigger;

BEGIN_CLASS(CinematicTrigger)
ADD_REALPROP(Delay1, 0.0f)
ADD_STRINGPROP(Sound1, "")
ADD_STRINGPROP(WhoPlaysSound1, "")
ADD_STRINGPROP(StartSoundTriggerTarget1, "")
ADD_STRINGPROP(StartSoundTriggerMsg1, "")
ADD_REALPROP(Delay2, 0.0f)
ADD_STRINGPROP(Sound2, "")
ADD_STRINGPROP(WhoPlaysSound2, "")
ADD_STRINGPROP(StartSoundTriggerTarget2, "")
ADD_STRINGPROP(StartSoundTriggerMsg2, "")
ADD_REALPROP(Delay3, 0.0f)
ADD_STRINGPROP(Sound3, "")
ADD_STRINGPROP(WhoPlaysSound3, "")
ADD_STRINGPROP(StartSoundTriggerTarget3, "")
ADD_STRINGPROP(StartSoundTriggerMsg3, "")
ADD_REALPROP(Delay4, 0.0f)
ADD_STRINGPROP(Sound4, "")
ADD_STRINGPROP(WhoPlaysSound4, "")
ADD_STRINGPROP(StartSoundTriggerTarget4, "")
ADD_STRINGPROP(StartSoundTriggerMsg4, "")
ADD_REALPROP(Delay5, 0.0f)
ADD_STRINGPROP(Sound5, "")
ADD_STRINGPROP(WhoPlaysSound5, "")
ADD_STRINGPROP(StartSoundTriggerTarget5, "")
ADD_STRINGPROP(StartSoundTriggerMsg5, "")
ADD_REALPROP(Delay6, 0.0f)
ADD_STRINGPROP(Sound6, "")
ADD_STRINGPROP(WhoPlaysSound6, "")
ADD_STRINGPROP(StartSoundTriggerTarget6, "")
ADD_STRINGPROP(StartSoundTriggerMsg6, "")
ADD_REALPROP(Delay7, 0.0f)
ADD_STRINGPROP(Sound7, "")
ADD_STRINGPROP(WhoPlaysSound7, "")
ADD_STRINGPROP(StartSoundTriggerTarget7, "")
ADD_STRINGPROP(StartSoundTriggerMsg7, "")
ADD_REALPROP(Delay8, 0.0f)
ADD_STRINGPROP(Sound8, "")
ADD_STRINGPROP(WhoPlaysSound8, "")
ADD_STRINGPROP(StartSoundTriggerTarget8, "")
ADD_STRINGPROP(StartSoundTriggerMsg8, "")
ADD_REALPROP(Delay9, 0.0f)
ADD_STRINGPROP(Sound9, "")
ADD_STRINGPROP(WhoPlaysSound9, "")
ADD_STRINGPROP(StartSoundTriggerTarget9, "")
ADD_STRINGPROP(StartSoundTriggerMsg9, "")
ADD_REALPROP(Delay10, 0.0f)
ADD_STRINGPROP(Sound10, "")
ADD_STRINGPROP(WhoPlaysSound10, "")
ADD_STRINGPROP(StartSoundTriggerTarget10, "")
ADD_STRINGPROP(StartSoundTriggerMsg10, "")
ADD_BOOLPROP_FLAG(TypeActionMode, DFALSE, PF_GROUP6)
END_CLASS_DEFAULT(CinematicTrigger, B2BaseClass, NULL, NULL)

typedef struct ConversationTrigger_t
{
	BaseClass m_BaseClass;
} ConversationTrigger;

BEGIN_CLASS(ConversationTrigger)
ADD_STRINGPROP(WaveFile, "default.wav")
ADD_STRINGPROP(WaveFile2, "")
ADD_STRINGPROP(WaveFile3, "")
ADD_STRINGPROP(WaveFile4, "")
ADD_STRINGPROP(WaveFile5, "")
ADD_STRINGPROP(WaveFile6, "")
ADD_STRINGPROP(WaveFile7, "")
ADD_STRINGPROP(WaveFile8, "")

ADD_LONGINTPROP(CharacterType, 0)
ADD_BOOLPROP(RepeatLastMessage, DFALSE)
ADD_BOOLPROP(LoopToFirstMessage, DFALSE)

ADD_STRINGPROP_FLAG(ActivationSound, "", PF_HIDDEN)
ADD_REALPROP_FLAG(SoundRadius, 200.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName1, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName1, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName2, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName2, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay2, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName3, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName3, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay3, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName4, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName4, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay4, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName5, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName5, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay5, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName6, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName6, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay6, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName7, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName7, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay7, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName8, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName8, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay8, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName9, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName9, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay9, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName10, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName10, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay10, 0.0f, PF_HIDDEN)
ADD_BOOLPROP(TouchActivate, DFALSE)
ADD_BOOLPROP(PlayerActivate, DTRUE)
ADD_BOOLPROP(AIActivate, DFALSE)
ADD_BOOLPROP(ObjectActivate, DFALSE)
ADD_BOOLPROP(TriggerRelayActivate, DFALSE)
ADD_BOOLPROP_FLAG(TypeActionMode, DFALSE, PF_GROUP6)
END_CLASS_DEFAULT(ConversationTrigger, Trigger, NULL, NULL)

typedef struct ExitTrigger_t
{
	BaseClass m_BaseClass;
} ExitTrigger;

BEGIN_CLASS(ExitTrigger)
ADD_STRINGPROP(NextWorld, "")
ADD_STRINGPROP(StartPointName, "start")
ADD_BOOLPROP(EndEpisode, DFALSE)
ADD_BOOLPROP(SubWorld, DFALSE)
ADD_REALPROP_FLAG(ResetTime, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName1, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName1, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName2, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName2, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay2, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName3, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName3, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay3, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName4, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName4, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay4, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName5, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName5, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay5, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName6, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName6, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay6, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName7, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName7, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay7, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName8, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName8, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay8, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName9, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName9, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay9, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName10, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName10, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay10, 0.0f, PF_HIDDEN)
ADD_BOOLPROP(TouchActivate, DFALSE)
ADD_BOOLPROP(PlayerActivate, DTRUE)
ADD_BOOLPROP(AIActivate, DFALSE)
ADD_BOOLPROP(ObjectActivate, DFALSE)
ADD_BOOLPROP(TriggerRelayActivate, DTRUE)
END_CLASS_DEFAULT(ExitTrigger, Trigger, NULL, NULL)

typedef struct ObjectivesTrigger_t
{
	BaseClass m_BaseClass;
} ObjectivesTrigger;

BEGIN_CLASS(ObjectivesTrigger)
ADD_LONGINTPROP(ResourceNum, 0)
ADD_STRINGPROP(TitleToDisplay, "Objective #1:")
ADD_STRINGPROP(TextToDisplay, "Use the '|' character to force a line break...")
ADD_STRINGPROP(Sound, "Sounds\\Thunder.wav")

ADD_STRINGPROP_FLAG(ActivationSound, "", PF_HIDDEN)
ADD_REALPROP_FLAG(SoundRadius, 200.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName1, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName1, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName2, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName2, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay2, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName3, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName3, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay3, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName4, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName4, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay4, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName5, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName5, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay5, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName6, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName6, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay6, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName7, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName7, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay7, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName8, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName8, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay8, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName9, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName9, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay9, 0.0f, PF_HIDDEN)
ADD_STRINGPROP_FLAG(TargetName10, "", PF_HIDDEN)
ADD_STRINGPROP_FLAG(MessageName10, "", PF_HIDDEN)
ADD_REALPROP_FLAG(MessageDelay10, 0.0f, PF_HIDDEN)
ADD_BOOLPROP(TouchActivate, DFALSE)
ADD_BOOLPROP(PlayerActivate, DTRUE)
ADD_BOOLPROP(AIActivate, DFALSE)
ADD_BOOLPROP(ObjectActivate, DFALSE)
ADD_BOOLPROP(TriggerRelayActivate, DFALSE)
END_CLASS_DEFAULT(ObjectivesTrigger, Trigger, NULL, NULL)

#pragma endregion

#pragma region DESTRUCTABLE

typedef struct CDestructableBrush_t
{
	BaseClass m_BaseClass;
} CDestructableBrush;

BEGIN_CLASS(CDestructableBrush)
ADD_STRINGPROP(DamageTriggerTarget, "") \
ADD_STRINGPROP(DamageTriggerMessage, "") \
ADD_STRINGPROP(DeathTriggerTarget, "") \
ADD_STRINGPROP(DeathTriggerMessage, "") \
ADD_BOOLPROP(TriggerDestroyOnly, DFALSE) \
ADD_STRINGPROP(SpawnObject, "") \
ADD_VECTORPROP(SpawnObjectVel) \
ADD_BOOLPROP(CanDamage, DTRUE)
ADD_VISIBLE_FLAG(1, 0)
ADD_SOLID_FLAG(1, 0)
ADD_GRAVITY_FLAG(0, 0)
ADD_REALPROP(HitPoints, 0.0f)
ADD_REALPROP(ObjectMass, 100.0f)
ADD_BOOLPROP(Destructable, DTRUE)
ADD_BOOLPROP(Pushable, DFALSE)
ADD_BOOLPROP(BoxPhysics, DTRUE)
ADD_BOOLPROP(AllowMarks, DTRUE)
ADD_BOOLPROP(FireThrough, DFALSE)
ADD_LONGINTPROP(SurfaceType, 0)
PROP_DEFINEGROUP(DebrisStuff, PF_GROUP2) \
	ADD_LONGINTPROP_FLAG(Amount, 10, PF_GROUP2) \
	ADD_REALPROP_FLAG(Scale, 1.0f, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Stone, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Metal, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Wood, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Energy, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Glass, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Terrain, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Plastic, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Flesh, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Liquid, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Exploding, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Custom, DFALSE, PF_GROUP2) \
	ADD_STRINGPROP_FLAG(CustomTexture, "", PF_GROUP2) \
	ADD_STRINGPROP_FLAG(CustomSound, "", PF_GROUP2) \
	ADD_STRINGPROP_FLAG(CustomModel, "", PF_GROUP2) \
	ADD_REALPROP_FLAG(ExplodeDamage, 100, PF_GROUP2) \
	ADD_REALPROP_FLAG(DamageRadius, 200, PF_GROUP2) \
END_CLASS_DEFAULT(CDestructableBrush, B2BaseClass, NULL, NULL)

typedef struct WorldModelDebris_t
{
	BaseClass m_BaseClass;
} WorldModelDebris;
BEGIN_CLASS(WorldModelDebris)
PROP_DEFINEGROUP(RotatingStuff, PF_GROUP1) \
ADD_BOOLPROP_FLAG(StartOn, DTRUE, PF_GROUP1) \
ADD_STRINGPROP_FLAG(SpinUpSound, "", PF_GROUP1) \
ADD_STRINGPROP_FLAG(BusySound, "", PF_GROUP1) \
ADD_STRINGPROP_FLAG(SpinDownSound, "", PF_GROUP1) \
ADD_REALPROP_FLAG(SoundRadius, 1000.0f, PF_RADIUS | PF_GROUP1) \
ADD_REALPROP_FLAG(XAxisRevTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(XAxisSpinUpTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(XAxisSpinDownTime, 0.0f, PF_GROUP1) \
ADD_BOOLPROP_FLAG(XRotateForward, DTRUE, PF_GROUP1) \
ADD_REALPROP_FLAG(YAxisRevTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(YAxisSpinUpTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(YAxisSpinDownTime, 0.0f, PF_GROUP1) \
ADD_BOOLPROP_FLAG(YRotateForward, DTRUE, PF_GROUP1) \
ADD_REALPROP_FLAG(ZAxisRevTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(ZAxisSpinUpTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(ZAxisSpinDownTime, 0.0f, PF_GROUP1) \
ADD_BOOLPROP_FLAG(ZRotateForward, DTRUE, PF_GROUP1) \
ADD_VISIBLE_FLAG(0, PF_HIDDEN)
ADD_SOLID_FLAG(0, PF_HIDDEN)
ADD_GRAVITY_FLAG(0, PF_HIDDEN)
ADD_VECTORPROP_VAL(InitialVelocity, 0, 0, 0)
ADD_REALPROP(GravityMultiplier, 1.0f)
END_CLASS_DEFAULT(WorldModelDebris, CDestructableBrush, NULL, NULL)


typedef struct CDestructableModel_t
{
	BaseClass m_BaseClass;
} CDestructableModel;

BEGIN_CLASS(CDestructableModel)
ADD_STRINGPROP(DamageTriggerTarget, "") \
ADD_STRINGPROP(DamageTriggerMessage, "") \
ADD_STRINGPROP(DeathTriggerTarget, "") \
ADD_STRINGPROP(DeathTriggerMessage, "") \
ADD_BOOLPROP(TriggerDestroyOnly, DFALSE) \
ADD_STRINGPROP(SpawnObject, "") \
ADD_VECTORPROP(SpawnObjectVel) \
ADD_BOOLPROP(CanDamage, DTRUE)
ADD_VISIBLE_FLAG(1, 0)
ADD_SOLID_FLAG(1, 0)
ADD_GRAVITY_FLAG(1, 0)
ADD_SHADOW_FLAG(1, 0)
ADD_STRINGPROP_FLAG(InitFilename, "", PF_DIMS | PF_LOCALDIMS)
ADD_STRINGPROP(InitSkin, "")
ADD_VECTORPROP(InitDims)
ADD_STRINGPROP(DamageFilename, "")
ADD_STRINGPROP(DamageSkin, "")
ADD_VECTORPROP(DamageDims)			//SCHLEGZ: added damaged state dims
ADD_STRINGPROP(DestroyFilename, "")
ADD_STRINGPROP(DestroySkin, "")
ADD_VECTORPROP(DestroyDims)
ADD_BOOLPROP(DestroyVisible, DTRUE)
ADD_BOOLPROP(DestroySolid, DTRUE)
ADD_BOOLPROP(DestroyGravity, DTRUE)
ADD_REALPROP(HitPoints, 100.0f)
ADD_REALPROP(DamageHitPoints, 50.0f)
ADD_REALPROP(ObjectMass, 100.0f)
ADD_REALPROP(Alpha, 1.0f)
ADD_BOOLPROP(Destructable, DTRUE)
ADD_BOOLPROP(Pushable, DFALSE)
ADD_LONGINTPROP(SurfaceType, 0)
ADD_REALPROP(ModelScale, 1.0f)
ADD_COLORPROP(TintColor, 0.0f, 0.0f, 0.0f)
ADD_BOOLPROP(Chrome, 0)
ADD_STRINGPROP(SlidingSound, "")
PROP_DEFINEGROUP(DebrisStuff, PF_GROUP2) \
	ADD_LONGINTPROP_FLAG(Amount, 10, PF_GROUP2) \
	ADD_REALPROP_FLAG(Scale, 1.0f, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Stone, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Metal, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Wood, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Energy, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Glass, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Terrain, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Plastic, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Flesh, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Liquid, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Exploding, DFALSE, PF_GROUP2) \
	ADD_BOOLPROP_FLAG(Custom, DFALSE, PF_GROUP2) \
	ADD_STRINGPROP_FLAG(CustomTexture, "", PF_GROUP2) \
	ADD_STRINGPROP_FLAG(CustomSound, "", PF_GROUP2) \
	ADD_STRINGPROP_FLAG(CustomModel, "", PF_GROUP2) \
	ADD_REALPROP_FLAG(ExplodeDamage, 100, PF_GROUP2) \
	ADD_REALPROP_FLAG(DamageRadius, 200, PF_GROUP2) \
END_CLASS_DEFAULT(CDestructableModel, B2BaseClass, NULL, NULL)


typedef struct RotatingBrush_t
{
	BaseClass m_BaseClass;
} RotatingBrush;

BEGIN_CLASS(RotatingBrush)
ADD_BOOLPROP_FLAG(AllowMarks, DFALSE, PF_HIDDEN)
PROP_DEFINEGROUP(RotatingStuff, PF_GROUP1) \
ADD_BOOLPROP_FLAG(StartOn, DTRUE, PF_GROUP1) \
ADD_STRINGPROP_FLAG(SpinUpSound, "", PF_GROUP1) \
ADD_STRINGPROP_FLAG(BusySound, "", PF_GROUP1) \
ADD_STRINGPROP_FLAG(SpinDownSound, "", PF_GROUP1) \
ADD_REALPROP_FLAG(SoundRadius, 1000.0f, PF_RADIUS | PF_GROUP1) \
ADD_REALPROP_FLAG(XAxisRevTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(XAxisSpinUpTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(XAxisSpinDownTime, 0.0f, PF_GROUP1) \
ADD_BOOLPROP_FLAG(XRotateForward, DTRUE, PF_GROUP1) \
ADD_REALPROP_FLAG(YAxisRevTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(YAxisSpinUpTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(YAxisSpinDownTime, 0.0f, PF_GROUP1) \
ADD_BOOLPROP_FLAG(YRotateForward, DTRUE, PF_GROUP1) \
ADD_REALPROP_FLAG(ZAxisRevTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(ZAxisSpinUpTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(ZAxisSpinDownTime, 0.0f, PF_GROUP1) \
ADD_BOOLPROP_FLAG(ZRotateForward, DTRUE, PF_GROUP1) \
END_CLASS_DEFAULT(RotatingBrush, CDestructableBrush, NULL, NULL)

typedef struct RotatingModel_t
{
	BaseClass m_BaseClass;
} RotatingModel;

BEGIN_CLASS(RotatingModel)
PROP_DEFINEGROUP(RotatingStuff, PF_GROUP1) \
ADD_BOOLPROP_FLAG(StartOn, DTRUE, PF_GROUP1) \
ADD_STRINGPROP_FLAG(SpinUpSound, "", PF_GROUP1) \
ADD_STRINGPROP_FLAG(BusySound, "", PF_GROUP1) \
ADD_STRINGPROP_FLAG(SpinDownSound, "", PF_GROUP1) \
ADD_REALPROP_FLAG(SoundRadius, 1000.0f, PF_RADIUS | PF_GROUP1) \
ADD_REALPROP_FLAG(XAxisRevTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(XAxisSpinUpTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(XAxisSpinDownTime, 0.0f, PF_GROUP1) \
ADD_BOOLPROP_FLAG(XRotateForward, DTRUE, PF_GROUP1) \
ADD_REALPROP_FLAG(YAxisRevTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(YAxisSpinUpTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(YAxisSpinDownTime, 0.0f, PF_GROUP1) \
ADD_BOOLPROP_FLAG(YRotateForward, DTRUE, PF_GROUP1) \
ADD_REALPROP_FLAG(ZAxisRevTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(ZAxisSpinUpTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(ZAxisSpinDownTime, 0.0f, PF_GROUP1) \
ADD_BOOLPROP_FLAG(ZRotateForward, DTRUE, PF_GROUP1) \
END_CLASS_DEFAULT(RotatingModel, CDestructableModel, NULL, NULL)

#pragma endregion

#pragma region PROJECTILES

typedef struct CProjectile_t
{
	BaseClass m_BaseClass;
} CProjectile;
BEGIN_CLASS(CProjectile)
END_CLASS_DEFAULT_FLAGS(CProjectile, BaseClass, NULL, NULL, CF_HIDDEN)

typedef struct CGrenade_t
{
	CProjectile m_CProjectile;
} CGrenade;

BEGIN_CLASS(CGrenade)
END_CLASS_DEFAULT_FLAGS(CGrenade, CProjectile, NULL, NULL, CF_HIDDEN)

#pragma endregion

typedef struct DetailSprite_t
{
	BaseClass m_BaseClass;
} DetailSprite;

BEGIN_CLASS(DetailSprite)
ADD_STRINGPROP(Filename, "")
ADD_REALPROP(ScaleX, 1.0f)
ADD_REALPROP(ScaleY, 1.0f)
ADD_BOOLPROP(FlushWithWorld, DFALSE)
ADD_BOOLPROP(Rotatable, DTRUE)
ADD_BOOLPROP(Chromakey, DFALSE)
ADD_BOOLPROP(Repeat, DFALSE)
ADD_LONGINTPROP(RepeatX, 1)
ADD_LONGINTPROP(RepeatY, 1)
ADD_REALPROP(SpacingX, 0.0f)
ADD_REALPROP(SpacingY, 0.0f)
END_CLASS_DEFAULT(DetailSprite, B2BaseClass, NULL, NULL)

typedef struct RotatingSprite_t
{
	DetailSprite m_DetailSprite;
} RotatingSprite;
BEGIN_CLASS(RotatingSprite)
PROP_DEFINEGROUP(RotatingStuff, PF_GROUP1) \
ADD_BOOLPROP_FLAG(StartOn, DTRUE, PF_GROUP1) \
ADD_STRINGPROP_FLAG(SpinUpSound, "", PF_GROUP1) \
ADD_STRINGPROP_FLAG(BusySound, "", PF_GROUP1) \
ADD_STRINGPROP_FLAG(SpinDownSound, "", PF_GROUP1) \
ADD_REALPROP_FLAG(SoundRadius, 1000.0f, PF_RADIUS | PF_GROUP1) \
ADD_REALPROP_FLAG(XAxisRevTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(XAxisSpinUpTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(XAxisSpinDownTime, 0.0f, PF_GROUP1) \
ADD_BOOLPROP_FLAG(XRotateForward, DTRUE, PF_GROUP1) \
ADD_REALPROP_FLAG(YAxisRevTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(YAxisSpinUpTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(YAxisSpinDownTime, 0.0f, PF_GROUP1) \
ADD_BOOLPROP_FLAG(YRotateForward, DTRUE, PF_GROUP1) \
ADD_REALPROP_FLAG(ZAxisRevTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(ZAxisSpinUpTime, 0.0f, PF_GROUP1) \
ADD_REALPROP_FLAG(ZAxisSpinDownTime, 0.0f, PF_GROUP1) \
ADD_BOOLPROP_FLAG(ZRotateForward, DTRUE, PF_GROUP1) \
END_CLASS_DEFAULT(RotatingSprite, DetailSprite, NULL, NULL)

typedef struct Door_t
{
	BaseClass m_BaseClass;
} Door;

BEGIN_CLASS(Door)
ADD_VISIBLE_FLAG(1, 0)
ADD_SOLID_FLAG(1, 0)
ADD_REALPROP(Speed, 0.0f)			//  movement speed
ADD_REALPROP(MoveDist, 0.0f)		//  distance to open
ADD_VECTORPROP(MoveDir)				//  direction to open
ADD_STRINGPROP(OpenBusySound, "")	//  sound to play while opening
ADD_STRINGPROP(OpenStopSound, "")	//  sound to play when done opening
ADD_STRINGPROP(CloseBusySound, "")	//  sound to play while closing
ADD_STRINGPROP(CloseStopSound, "")	//  sound to play when done closing
ADD_REALPROP_FLAG(SoundRadius, 1000.0f, PF_RADIUS) //  radius of all sounds
ADD_REALPROP(WaitTime, 0.0f)		//  length of time to stay open
ADD_REALPROP(OpenDelay, 0.0f)		// Length of time to wait before opening
ADD_VECTORPROP_FLAG(TriggerDims, PF_DIMS)	//  Dimensions for trigger box
ADD_REALPROP(ClosingSpeed, 0.0f)	//  movement speed while closing
ADD_STRINGPROP(PortalName, "")		// A Portal brush name
ADD_LONGINTPROP(Waveform, 0)
ADD_BOOLPROP(BoxPhysics, DTRUE)		// Door uses "box physics"
ADD_BOOLPROP(TriggerClosed, DFALSE)	// Door must be triggered to close
ADD_BOOLPROP(StartOpen, DFALSE)		// Door starts in open position
ADD_BOOLPROP(RemainsOpen, DFALSE)	// One-time door, remains open after opening

ADD_BOOLPROP(SelfTrigger, DFALSE)	// Door creates it's own trigger
ADD_BOOLPROP(FireThrough, DFALSE)	// Can shoot through the door.
PROP_DEFINEGROUP(SelfTriggerOpts, PF_GROUP1)
ADD_BOOLPROP_FLAG(TouchActivate, DFALSE, PF_GROUP1)
ADD_BOOLPROP_FLAG(PlayerActivate, DTRUE, PF_GROUP1)
ADD_BOOLPROP_FLAG(AIActivate, DTRUE, PF_GROUP1)
ADD_BOOLPROP_FLAG(ObjectActivate, DFALSE, PF_GROUP1)
ADD_BOOLPROP_FLAG(TriggerRelayActivate, DTRUE, PF_GROUP1)
ADD_BOOLPROP_FLAG(NamedObjectActivate, DFALSE, PF_GROUP1)
ADD_STRINGPROP_FLAG(ActivationObjectName, "", PF_GROUP1)
ADD_BOOLPROP_FLAG(Locked, DFALSE, PF_GROUP1)
ADD_STRINGPROP_FLAG(LockedSound, "", PF_GROUP1)
ADD_STRINGPROP_FLAG(UnlockedSound, "", PF_GROUP1)
ADD_STRINGPROP_FLAG(UnlockKeyName, "Key", PF_GROUP1)

END_CLASS_DEFAULT(Door, B2BaseClass, NULL, NULL)

typedef struct RotatingDoor_t
{
	Door m_Door;
} RotatingDoor;
BEGIN_CLASS(RotatingDoor)
ADD_REALPROP_FLAG(MoveDist, 0.0f, PF_HIDDEN)	//  hide some of our
ADD_VECTORPROP_FLAG(MoveDir, PF_HIDDEN)			//  parent's properties
ADD_VECTORPROP_FLAG(RotationPoint, 0)			//  point to rotate around
ADD_VECTORPROP_FLAG(RotationAngles, 0)			//  where to rotate to
ADD_BOOLPROP(BoxPhysics, DFALSE)				// Door does NOT use "box physics"
ADD_BOOLPROP(PushPlayerBack, DTRUE)
END_CLASS_DEFAULT(RotatingDoor, Door, NULL, NULL)


typedef struct Explosion_t
{
	BaseClass m_BaseClass;
} Explosion;

BEGIN_CLASS(Explosion)
ADD_STRINGPROP(Model, "Models\\Explosions\\Explosion_3.abc")
ADD_STRINGPROP(Skin, "Skins\\Explosions\\Explosion_1.dtx")
ADD_STRINGPROP(Sound, "Sounds\\exp_tnt.wav")
ADD_REALPROP_FLAG(SoundRadius, 1000.0f, PF_RADIUS)
ADD_REALPROP_FLAG(DamageRadius, 200.0f, PF_RADIUS)
ADD_VECTORPROP(RotateSpeed)
ADD_REALPROP(MaxDamage, 50.0f)
ADD_REALPROP(MinScale, 0.1f)
ADD_REALPROP(MaxScale, 1.0f)
ADD_BOOLPROP(CreateLight, DTRUE)
ADD_COLORPROP(LightColor, 255, 255, 255)
ADD_BOOLPROP(CreateSmoke, DTRUE)
ADD_BOOLPROP(CreateShockwave, DFALSE)
ADD_STRINGPROP(ShockwaveFile, "Sprites\\Shockring.spr")
ADD_VECTORPROP(ShockwaveScaleMin)
ADD_VECTORPROP(ShockwaveScaleMax)
ADD_REALPROP(ShockwaveDuration, 0.0f)
ADD_REALPROP(Delay, 0.0f)
END_CLASS_DEFAULT(Explosion, B2BaseClass, NULL, NULL)

typedef struct FireFX_t
{
	BaseClass m_BaseClass;
} FireFX;

BEGIN_CLASS(FireFX)
ADD_STRINGPROP(PlaceFireOn, "MyName")	    //  Object to place the fire on
//	ADD_REALPROP(BurnTime, 0.0f)	            //  Burn time
//	ADD_STRINGPROP(FireType, "small")	        //  Small/Medium/Large
END_CLASS_DEFAULT(FireFX, B2BaseClass, NULL, NULL)

typedef struct FlagObject_t
{
	BaseClass m_BaseClass;
} FlagObject;

BEGIN_CLASS(FlagObject)
ADD_STRINGPROP(ObjectName, "CTF_Flag")					// Item name
ADD_LONGINTPROP(TeamID, 0)								// Team ID (1 or 2)
END_CLASS_DEFAULT(FlagObject, B2BaseClass, NULL, NULL)

typedef struct FlagStand_t
{
	BaseClass m_BaseClass;
} FlagStand;
BEGIN_CLASS(FlagStand)
ADD_STRINGPROP(ObjectName, "CTF_FlagStand")						// Item name
ADD_LONGINTPROP(TeamID, 0)										// Team ID (1 or 2)
END_CLASS_DEFAULT(FlagStand, B2BaseClass, NULL, NULL)

typedef struct GameStartPoint_t
{
	BaseClass m_BaseClass;
} GameStartPoint;
BEGIN_CLASS(GameStartPoint)
ADD_BOOLPROP(Multiplayer, DFALSE)
ADD_STRINGPROP(TriggerTarget, "")
ADD_STRINGPROP(TriggerMessage, "")
ADD_LONGINTPROP(TeamID, 0)				// Team ID (1 or 2, or 0 for any)
END_CLASS_DEFAULT_FLAGS(GameStartPoint, StartPoint, NULL, NULL, CF_ALWAYSLOAD)

typedef struct CGib_t
{
	BaseClass m_BaseClass;
} CGib;

BEGIN_CLASS(CGib)
ADD_STRINGPROP(DamageTriggerTarget, "") \
ADD_STRINGPROP(DamageTriggerMessage, "") \
ADD_STRINGPROP(DeathTriggerTarget, "") \
ADD_STRINGPROP(DeathTriggerMessage, "") \
ADD_BOOLPROP(TriggerDestroyOnly, DFALSE) \
ADD_STRINGPROP(SpawnObject, "") \
ADD_VECTORPROP(SpawnObjectVel) \
ADD_BOOLPROP(CanDamage, DTRUE)
ADD_STRINGPROP(InitFilename, "")
ADD_STRINGPROP(InitSkin, "")
ADD_LONGINTPROP(InitFlags, (FLAG_VISIBLE | FLAG_RAYHIT | FLAG_GRAVITY | FLAG_SHADOW))
ADD_STRINGPROP(InitAnim, "")
ADD_REALPROP(HitPoints, 20.0f)
ADD_REALPROP(ObjectMass, 10.0f)
ADD_BOOLPROP(Kickable, DTRUE)
END_CLASS_DEFAULT(CGib, B2BaseClass, NULL, NULL)

typedef struct Key_t
{
	BaseClass m_BaseClass;
} Key;

BEGIN_CLASS(Key)
ADD_REALPROP(TimeStamp, 0.0f)
ADD_STRINGPROP(SoundName, "")
ADD_REALPROP_FLAG(SoundRadius, 0.0f, PF_RADIUS)
ADD_BOOLPROP(LoopSound, DFALSE)
ADD_STRINGPROP(MessageTarget, "")
ADD_STRINGPROP(MessageName, "")
ADD_STRINGPROP(BPrintMessage, "")
END_CLASS_DEFAULT_FLAGS(Key, B2BaseClass, NULL, NULL, CF_ALWAYSLOAD)

typedef struct KeyFramer_t
{
	BaseClass m_BaseClass;
} KeyFramer;

BEGIN_CLASS(KeyFramer)
ADD_STRINGPROP(ObjectName, "")
ADD_STRINGPROP(BaseKeyName, "")
ADD_BOOLPROP(StartActive, DFALSE)
ADD_BOOLPROP(Looping, DFALSE)
END_CLASS_DEFAULT(KeyFramer, B2BaseClass, NULL, NULL)

typedef struct LightFX_t
{
	BaseClass m_BaseClass;
} LightFX;


BEGIN_CLASS(LightFX)
ADD_STRINGPROP(DamageTriggerTarget, "") \
ADD_STRINGPROP(DamageTriggerMessage, "") \
ADD_STRINGPROP(DeathTriggerTarget, "") \
ADD_STRINGPROP(DeathTriggerMessage, "") \
ADD_BOOLPROP(TriggerDestroyOnly, DFALSE) \
ADD_STRINGPROP(SpawnObject, "") \
ADD_VECTORPROP(SpawnObjectVel) \
ADD_BOOLPROP(CanDamage, DTRUE)
ADD_REALPROP(HitPoints, 1.0f)
//		ADD_LONGINTPROP(Flags, 1)           
ADD_BOOLPROP(LightSwitch, DTRUE)
ADD_REALPROP(LifeTime, 0.0f)
ADD_LONGINTPROP(NumColorCycles, 0.0f)
ADD_COLORPROP(Color1, 255.0f, 255.0f, 255.0f)
ADD_REALPROP(Color1Time, 0.0f)
ADD_COLORPROP(Color2, 255.0f, 255.0f, 255.0f)
ADD_REALPROP(Color2Time, 0.0f)
ADD_COLORPROP(Color3, 255.0f, 255.0f, 255.0f)
ADD_REALPROP(Color3Time, 0.0f)
ADD_LONGINTPROP(NumIntensityCycles, 0.0f)
ADD_REALPROP(IntensityMin, 0.5f)
ADD_REALPROP(IntensityMax, 1.0f)
ADD_REALPROP(IntensityMinTime, 0.0f)
ADD_REALPROP(IntensityMaxTime, 0.0f)
ADD_REALPROP(IntensityRampUpTime, 0.0f)
ADD_REALPROP(IntensityRampDownTime, 0.0f)
ADD_LONGINTPROP(NumRadiusCycles, 0.0f)
ADD_REALPROP_FLAG(RadiusMin, 500.0f, PF_RADIUS)
ADD_REALPROP_FLAG(RadiusMax, 0.0f, PF_RADIUS)
ADD_REALPROP(RadiusMinTime, 0.0f)
ADD_REALPROP(RadiusMaxTime, 0.0f)
ADD_REALPROP(RadiusRampUpTime, 0.0f)
ADD_REALPROP(RadiusRampDownTime, 0.0f)
ADD_STRINGPROP(RampUpSound, "")
ADD_STRINGPROP(RampDownSound, "")
#ifdef RIOT_BUILD
END_CLASS_DEFAULT_FLAGS(LightFX, BaseClass, NULL, NULL, CF_ALWAYSLOAD)
#else
END_CLASS_DEFAULT_FLAGS(LightFX, BaseClass, NULL, NULL, CF_ALWAYSLOAD | CF_HIDDEN)
#endif

typedef struct PathPoint_t
{
	BaseClass m_BaseClass;
} PathPoint;

BEGIN_CLASS(PathPoint)
ADD_STRINGPROP(ActionTarget, "")
ADD_STRINGPROP(ActionMessage, "")
END_CLASS_DEFAULT_FLAGS(PathPoint, B2BaseClass, NULL, NULL, CF_ALWAYSLOAD)

typedef struct RandomSoundFX_t
{
	BaseClass m_BaseClass;
} RandomSoundFX;

BEGIN_CLASS(RandomSoundFX)
ADD_BOOLPROP(InitiallyOn, DTRUE)
ADD_BOOLPROP(PositionalSound, DTRUE)		// Sound should be positional, not localized
ADD_BOOLPROP(SequentialPlay, DFALSE)		// Sounds should be played in sequence.
ADD_BOOLPROP(LoopSequence, DFALSE)			// Loop sequential playing
ADD_REALPROP(PosRangeRadius, 0.0f)			// Sound should be positional, placed withing this radius

ADD_REALPROP_FLAG(SoundRadius, 1000.0f, PF_RADIUS)
ADD_LONGINTPROP(Volume, 100)
ADD_BOOLPROP(Ambient, 1)

ADD_REALPROP(MinWaitTime, 60.0f)
ADD_REALPROP(MaxWaitTime, 60.0f)

ADD_STRINGPROP(SoundFile1, "")
ADD_STRINGPROP(SoundFile2, "")
ADD_STRINGPROP(SoundFile3, "")
ADD_STRINGPROP(SoundFile4, "")
ADD_STRINGPROP(SoundFile5, "")
ADD_STRINGPROP(SoundFile6, "")
ADD_STRINGPROP(SoundFile7, "")
ADD_STRINGPROP(SoundFile8, "")
ADD_STRINGPROP(SoundFile9, "")
ADD_STRINGPROP(SoundFile10, "")
END_CLASS_DEFAULT(RandomSoundFX, B2BaseClass, NULL, NULL)

typedef struct Script_t
{
	BaseClass m_BaseClass;
} Script;

BEGIN_CLASS(Script)
ADD_STRINGPROP(ScriptName, "script.txt")	//  Script file to load
ADD_REALPROP(StartTime, 0.0f)	            //  Start time, or wait for Trigger
END_CLASS_DEFAULT_FLAGS(Script, B2BaseClass, NULL, NULL, CF_ALWAYSLOAD)

typedef struct SeeingEye_t
{
	BaseClass m_BaseClass;
} SeeingEye;

BEGIN_CLASS(SeeingEye)
ADD_STRINGPROP(DamageTriggerTarget, "") \
ADD_STRINGPROP(DamageTriggerMessage, "") \
ADD_STRINGPROP(DeathTriggerTarget, "") \
ADD_STRINGPROP(DeathTriggerMessage, "") \
ADD_BOOLPROP(TriggerDestroyOnly, DFALSE) \
ADD_STRINGPROP(SpawnObject, "") \
ADD_VECTORPROP(SpawnObjectVel) \
ADD_BOOLPROP(CanDamage, DTRUE)
END_CLASS_DEFAULT_FLAGS(SeeingEye, BaseClass, NULL, NULL, CF_HIDDEN)

typedef struct SmellHint_t
{
	BaseClass m_BaseClass;
} SmellHint;

BEGIN_CLASS(SmellHint)
END_CLASS_DEFAULT_FLAGS(SmellHint, B2BaseClass, NULL, NULL, CF_ALWAYSLOAD)

typedef struct SoccerGoal_t
{
	BaseClass m_BaseClass;
} SoccerGoal;

BEGIN_CLASS(SoccerGoal)
ADD_LONGINTPROP(TeamID, 1)
ADD_BOOLPROP(Directional, DFALSE)
ADD_ROTATIONPROP(GoalDirection)
ADD_BOOLPROP(BoxPhysics, DTRUE)
ADD_STRINGPROP(ScoreSound, "")
ADD_REALPROP(ScoreSoundRadius, 1000.0f)
ADD_STRINGPROP(ScoreTarget, "")
ADD_STRINGPROP(ScoreMsg, "")
END_CLASS_DEFAULT_FLAGS(SoccerGoal, B2BaseClass, NULL, NULL, CF_ALWAYSLOAD)

typedef struct SoccerBall_t
{
	BaseClass m_BaseClass;
} SoccerBall;
BEGIN_CLASS(SoccerBall)
END_CLASS_DEFAULT(SoccerBall, B2BaseClass, NULL, NULL)

typedef struct SoundFX_t
{
	BaseClass m_BaseClass;
} SoundFX;

BEGIN_CLASS(SoundFX)
ADD_BOOLPROP(StartOn, DTRUE)
ADD_STRINGPROP(RampUpSound, "")
ADD_STRINGPROP(RampDownSound, "")
ADD_STRINGPROP(Sound, "")
ADD_LONGINTPROP(Priority, 0.0f)
ADD_REALPROP_FLAG(OuterRadius, 500.0f, PF_RADIUS)
ADD_REALPROP_FLAG(InnerRadius, 100.0f, PF_RADIUS)
ADD_LONGINTPROP(Volume, 100.0f)
ADD_BOOLPROP(Ambient, 1)
ADD_BOOLPROP(FileStream, 0)
END_CLASS_DEFAULT(SoundFX, B2BaseClass, NULL, NULL)


typedef struct SparksObj_t
{
	BaseClass m_BaseClass;
} SparksObj;

BEGIN_CLASS(SparksObj)
ADD_BOOLPROP(SparkSwitch, DTRUE)        \
ADD_LONGINTPROP(Type, 0)                \
ADD_REALPROP(SparkCountMin, 10.0f)      \
ADD_REALPROP(SparkCountMax, 30.0f)      \
ADD_REALPROP(SparkDuration, 0.4f)       \
ADD_REALPROP(SparkEmissionRadius, 0.7f) \
ADD_REALPROP(DelaySecsMin, 0.5f)        \
ADD_REALPROP(DelaySecsMax, 2.0f)        \
ADD_REALPROP(MaxSecs, 0.0f)             \
ADD_STRINGPROP(SparkSound, "Sounds\\lightpop2.wav")    \
END_CLASS_DEFAULT_FLAGS(SparksObj, B2BaseClass, NULL, NULL, CF_ALWAYSLOAD)

typedef struct Spawner_t
{
	BaseClass m_BaseClass;
} Spawner;

BEGIN_CLASS(Spawner)
ADD_STRINGPROP(SpawnObject, "")
ADD_VECTORPROP_VAL(MinVelocity, 0, 500, 0)
ADD_VECTORPROP_VAL(MaxVelocity, 0, 500, 0)
ADD_STRINGPROP(Sound, "")
ADD_REALPROP(SoundRadius, 500.0f)
ADD_BOOLPROP(UseTriggerObjPos, DTRUE)
ADD_BOOLPROP(StartActive, DFALSE)
ADD_LONGINTPROP(RespawnCount, -1)
ADD_REALPROP(RespawnRate, 1)
ADD_BOOLPROP(CreateRiftEffect, DFALSE)
END_CLASS_DEFAULT(Spawner, B2BaseClass, NULL, NULL)

typedef struct Tchernotronic_t
{
	BaseClass m_BaseClass;
} Tchernotronic;

BEGIN_CLASS(Tchernotronic)
ADD_STRINGPROP_FLAG(Filename, "Models\\WorldObjects\\Technoberg.abc", PF_HIDDEN)
ADD_STRINGPROP_FLAG(Skin, "Skins\\WorldObjects\\Technoberg.dtx", PF_HIDDEN)
ADD_STRINGPROP(DestroyTriggerTarget, "")
ADD_STRINGPROP(DestroyTriggerMessage, "")
END_CLASS_DEFAULT(Tchernotronic, B2BaseClass, NULL, NULL)


typedef struct TripLaser_t
{
	BaseClass m_BaseClass;
} TripLaser;

BEGIN_CLASS(TripLaser)
ADD_STRINGPROP_FLAG(Filename, "Models\\default.abc", PF_HIDDEN)
ADD_STRINGPROP_FLAG(Skin, "Skins\\ammo\\beamred.dtx", PF_HIDDEN)
ADD_VECTORPROP_VAL_FLAG(Dims, 1.0f, 20.0f, 1.0f, PF_DIMS | PF_LOCALDIMS)
ADD_COLORPROP(Color, 255.0f, 0.0f, 0.0f)
ADD_REALPROP(Alpha, 0.5f)
ADD_BOOLPROP(StartOn, DFALSE)
ADD_STRINGPROP(TouchTriggerTarget, "")
ADD_STRINGPROP(TouchTriggerMessage, "")
ADD_STRINGPROP(Sound, "")
ADD_STRINGPROP(TouchSound, "")
ADD_REALPROP(Damage, 10.0f)
END_CLASS_DEFAULT(TripLaser, B2BaseClass, NULL, NULL)

#pragma region VOLUMES

typedef struct VolumeBrush_t
{
	BaseClass m_BaseClass;
} VolumeBrush;

BEGIN_CLASS(VolumeBrush)
ADD_VISIBLE_FLAG(0, 0)
ADD_REALPROP(Viscosity, 0.0f)
ADD_BOOLPROP(Hidden, DFALSE)
ADD_BOOLPROP(ShowSurface, DTRUE)
ADD_STRINGPROP(SpriteSurfaceName, "")
ADD_BOOLPROP(FogEnable, DFALSE)
ADD_REALPROP(FogFarZ, 300.0f)
ADD_REALPROP(FogNearZ, -100.0f)
ADD_COLORPROP(FogColor, 0.0f, 0.0f, 0.0f)
ADD_REALPROP(XScaleMin, 15.0f)
ADD_REALPROP(XScaleMax, 25.0f)
ADD_REALPROP(YScaleMin, 15.0f)
ADD_REALPROP(YScaleMax, 25.0f)
ADD_REALPROP(XScaleDuration, 60.0f)
ADD_REALPROP(YScaleDuration, 60.0f)
ADD_REALPROP(SurfaceHeight, 2.0f)
ADD_COLORPROP(SurfaceColor1, 255.0f, 255.0f, 255.0f)
ADD_COLORPROP(SurfaceColor2, 255.0f, 255.0f, 255.0f)
ADD_REALPROP(SurfaceAlpha, 0.7f)
ADD_LONGINTPROP(Code, 0)
ADD_VECTORPROP_VAL(Current, 0.0f, 0.0f, 0.0f)
ADD_REALPROP(Damage, 0.0f)
ADD_LONGINTPROP(DamageType, 0)
ADD_LONGINTPROP(NumSurfacePolies, 160)
ADD_BOOLPROP(Locked, DFALSE)
ADD_BOOLPROP(UnlockKeyRemove, DFALSE)
ADD_STRINGPROP(UnlockKeyName, "")
END_CLASS_DEFAULT(VolumeBrush, B2BaseClass, NULL, NULL)

typedef struct Water_t
{
	BaseClass m_BaseClass;
} Water;

BEGIN_CLASS(Water)
ADD_STRINGPROP(SpriteSurfaceName, "Sprites\\WaterBlue.spr")
ADD_REALPROP_FLAG(Viscosity, 0.5f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(Code, 1, PF_HIDDEN)
ADD_REALPROP(Damage, 0.0f)
ADD_LONGINTPROP(DamageType, 6)
ADD_BOOLPROP_FLAG(Locked, DFALSE, PF_HIDDEN)
ADD_BOOLPROP_FLAG(UnlockKeyRemove, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(UnlockKeyName, "", PF_HIDDEN)
END_CLASS_DEFAULT(Water, VolumeBrush, NULL, NULL)

typedef struct Blood_t
{
	BaseClass m_BaseClass;
} Blood;
BEGIN_CLASS(Blood)
ADD_STRINGPROP(SpriteSurfaceName, "Sprites\\WaterBlood.spr")
ADD_REALPROP_FLAG(Viscosity, 0.8f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(Code, 2, PF_HIDDEN)
ADD_REALPROP_FLAG(Damage, 0.0f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(DamageType, 6, PF_HIDDEN)
ADD_BOOLPROP_FLAG(Locked, DFALSE, PF_HIDDEN)
ADD_BOOLPROP_FLAG(UnlockKeyRemove, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(UnlockKeyName, "", PF_HIDDEN)
END_CLASS_DEFAULT(Blood, VolumeBrush, NULL, NULL)

typedef struct Acid_t
{
	BaseClass m_BaseClass;
} Acid;

// Acid
BEGIN_CLASS(Acid)
ADD_STRINGPROP(SpriteSurfaceName, "Sprites\\WaterAcid.spr")
ADD_REALPROP_FLAG(Viscosity, 0.5f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(Code, 3, PF_HIDDEN)
ADD_BOOLPROP_FLAG(Locked, DFALSE, PF_HIDDEN)
ADD_BOOLPROP_FLAG(UnlockKeyRemove, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(UnlockKeyName, "", PF_HIDDEN)
END_CLASS_DEFAULT(Acid, VolumeBrush, NULL, NULL)


typedef struct Ladder_t
{
	BaseClass m_BaseClass;
} Ladder;
// Ladders
BEGIN_CLASS(Ladder)
ADD_BOOLPROP_FLAG(ShowSurface, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(SpriteSurfaceName, "", PF_HIDDEN)
ADD_REALPROP_FLAG(SurfaceHeight, 0.0f, PF_HIDDEN)
ADD_COLORPROP_FLAG(SurfaceColor1, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_COLORPROP_FLAG(SurfaceColor2, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleMin, 15.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleMax, 25.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleMin, 15.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleMax, 25.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleDuration, 10.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleDuration, 10.0f, PF_HIDDEN)
ADD_VECTORPROP_VAL_FLAG(Current, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(Viscosity, 0.0f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(Code, 5, PF_HIDDEN)
ADD_REALPROP_FLAG(Damage, 0.0f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(DamageType, 0, PF_HIDDEN)
ADD_BOOLPROP_FLAG(Locked, DFALSE, PF_HIDDEN)
ADD_BOOLPROP_FLAG(UnlockKeyRemove, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(UnlockKeyName, "", PF_HIDDEN)
END_CLASS_DEFAULT(Ladder, VolumeBrush, NULL, NULL)
typedef struct Conveyor_t
{
	BaseClass m_BaseClass;
} Conveyor;

BEGIN_CLASS(Conveyor)
ADD_BOOLPROP_FLAG(ShowSurface, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(SpriteSurfaceName, "", PF_HIDDEN)
ADD_REALPROP_FLAG(SurfaceHeight, 0.0f, PF_HIDDEN)
ADD_COLORPROP_FLAG(SurfaceColor1, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_COLORPROP_FLAG(SurfaceColor2, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleMin, 15.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleMax, 25.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleMin, 15.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleMax, 25.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleDuration, 10.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleDuration, 10.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(Viscosity, 0.0f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(Code, 6, PF_HIDDEN)
ADD_REALPROP_FLAG(Damage, 0.0f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(DamageType, 0, PF_HIDDEN)
ADD_BOOLPROP_FLAG(Locked, DFALSE, PF_HIDDEN)
ADD_BOOLPROP_FLAG(UnlockKeyRemove, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(UnlockKeyName, "", PF_HIDDEN)
END_CLASS_DEFAULT(Conveyor, VolumeBrush, NULL, NULL)

typedef struct CraneControl_t
{
	BaseClass m_BaseClass;
} CraneControl;

BEGIN_CLASS(CraneControl)
ADD_BOOLPROP_FLAG(ShowSurface, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(SpriteSurfaceName, "", PF_HIDDEN)
ADD_REALPROP_FLAG(SurfaceHeight, 0.0f, PF_HIDDEN)
ADD_COLORPROP_FLAG(SurfaceColor1, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_COLORPROP_FLAG(SurfaceColor2, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleMin, 15.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleMax, 25.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleMin, 15.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleMax, 25.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleDuration, 10.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleDuration, 10.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(Viscosity, 0.0f, PF_HIDDEN)
ADD_LONGINTPROP(Code, 7)
ADD_REALPROP_FLAG(Damage, 0.0f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(DamageType, 0, PF_HIDDEN)
ADD_BOOLPROP(Locked, DTRUE)
ADD_BOOLPROP(UnlockKeyRemove, DTRUE)
ADD_STRINGPROP(UnlockKeyName, "Lever")
END_CLASS_DEFAULT(CraneControl, VolumeBrush, NULL, NULL)

typedef struct Damage_t
{
	BaseClass m_BaseClass;
} Damage;
BEGIN_CLASS(Damage)
ADD_BOOLPROP_FLAG(ShowSurface, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(SpriteSurfaceName, "", PF_HIDDEN)
ADD_REALPROP_FLAG(SurfaceHeight, 0.0f, PF_HIDDEN)
ADD_COLORPROP_FLAG(SurfaceColor1, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_COLORPROP_FLAG(SurfaceColor2, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleMin, 15.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleMax, 25.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleMin, 15.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleMax, 25.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleDuration, 10.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleDuration, 10.0f, PF_HIDDEN)
ADD_VECTORPROP_VAL_FLAG(Current, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(Viscosity, 0.0f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(Code, 8, PF_HIDDEN)
ADD_REALPROP(Damage, 100.0f)
ADD_LONGINTPROP(DamageType, 0)
ADD_BOOLPROP_FLAG(Locked, DFALSE, PF_HIDDEN)
ADD_BOOLPROP_FLAG(UnlockKeyRemove, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(UnlockKeyName, "", PF_HIDDEN)
END_CLASS_DEFAULT(Damage, VolumeBrush, NULL, NULL)

typedef struct Minefield_t
{
	BaseClass m_BaseClass;
} Minefield;
BEGIN_CLASS(Minefield)
ADD_BOOLPROP_FLAG(ShowSurface, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(SpriteSurfaceName, "", PF_HIDDEN)
ADD_REALPROP_FLAG(SurfaceHeight, 0.0f, PF_HIDDEN)
ADD_COLORPROP_FLAG(SurfaceColor1, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_COLORPROP_FLAG(SurfaceColor2, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleMin, 15.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleMax, 25.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleMin, 15.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleMax, 25.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleDuration, 10.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleDuration, 10.0f, PF_HIDDEN)
ADD_VECTORPROP_VAL_FLAG(Current, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(Viscosity, 0.0f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(Code, 8, PF_HIDDEN)
ADD_REALPROP_FLAG(Damage, 0.0f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(DamageType, 0, PF_HIDDEN)
ADD_BOOLPROP_FLAG(Locked, DFALSE, PF_HIDDEN)
ADD_BOOLPROP_FLAG(UnlockKeyRemove, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(UnlockKeyName, "", PF_HIDDEN)
END_CLASS_DEFAULT(Minefield, VolumeBrush, NULL, NULL)

typedef struct FreeFall_t
{
	BaseClass m_BaseClass;
} FreeFall;

BEGIN_CLASS(FreeFall)
ADD_BOOLPROP_FLAG(ShowSurface, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(SpriteSurfaceName, "", PF_HIDDEN)
ADD_REALPROP_FLAG(SurfaceHeight, 0.0f, PF_HIDDEN)
ADD_COLORPROP_FLAG(SurfaceColor1, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_COLORPROP_FLAG(SurfaceColor2, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_VECTORPROP_VAL_FLAG(Current, 0.0f, 0.0f, 0.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleMin, 15.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleMax, 25.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleMin, 15.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleMax, 25.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(XScaleDuration, 10.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(YScaleDuration, 10.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(SurfaceHeight, 5.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(SurfaceAlpha, 0.7f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(NumSurfacePolies, 160, PF_HIDDEN)
ADD_REALPROP_FLAG(Viscosity, 0.0f, PF_HIDDEN)
ADD_REALPROP_FLAG(Damage, 9999999.0f, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(DamageType, 8, PF_HIDDEN)
ADD_LONGINTPROP_FLAG(Code, 9, PF_HIDDEN)
ADD_BOOLPROP_FLAG(Locked, DFALSE, PF_HIDDEN)
ADD_BOOLPROP_FLAG(UnlockKeyRemove, DFALSE, PF_HIDDEN)
ADD_STRINGPROP_FLAG(UnlockKeyName, "", PF_HIDDEN)
END_CLASS_DEFAULT(FreeFall, VolumeBrush, NULL, NULL)

typedef struct WorldProperties_t
{
	BaseClass m_BaseClass;
} WorldProperties;

BEGIN_CLASS(WorldProperties)
ADD_STRINGPROP_FLAG(Name, "noname", PF_HIDDEN)
ADD_VECTORPROP_FLAG(Pos, PF_HIDDEN)
ADD_ROTATIONPROP_FLAG(Rotation, PF_HIDDEN)
ADD_STRINGPROP(WorldName, "")
ADD_STRINGPROP(Author, "")
ADD_STRINGPROP(CDTrack, "")
ADD_STRINGPROP(InstrumentFiles, "")
ADD_STRINGPROP(AmbientList, "")
ADD_STRINGPROP(CruisingList, "")
ADD_STRINGPROP(HarddrivingList, "")
ADD_STRINGPROP(MusicDirectory, "")
ADD_STRINGPROP(StartCutscene, "")
ADD_STRINGPROP(EndCutscene, "")

ADD_BOOLPROP(FogEnable, DFALSE)
ADD_COLORPROP(FogColor, 127.0f, 127.0f, 127.0f)
ADD_REALPROP(FogNearZ, 1.0f)
ADD_REALPROP(FogFarZ, 5000.0f)
ADD_BOOLPROP(SkyFog, DFALSE)
ADD_REALPROP(SkyFogNearZ, 100.0f)
ADD_REALPROP(SkyFogFarZ, 1000.0f)
ADD_REALPROP(FarZ, 5000.0f)
ADD_COLORPROP(ModelAdd, 0, 0, 0)
ADD_COLORPROP(ModelDirAdd, 0, 0, 0)

ADD_STRINGPROP(PanSkyTexture, "")
ADD_BOOLPROP(PanSky, 0)
ADD_REALPROP(PanSkyOffsetX, 10.0f)
ADD_REALPROP(PanSkyOffsetZ, 10.0f)
ADD_REALPROP(PanSkyScaleX, 10.0f)
ADD_REALPROP(PanSkyScaleZ, 10.0f)
ADD_VECTORPROP_VAL(Gravity, 0, -2000.0f, 0)

ADD_STRINGPROP(EnvironmentMap, "")
//	ADD_COLORPROP(LightScale, 255.0f, 255.0f, 255.0f)
ADD_STRINGPROP(SoftSky, "textures\\environmentmaps\\clouds\\clouds")

END_CLASS_DEFAULT_FLAGS(WorldProperties, B2BaseClass, NULL, NULL, CF_ALWAYSLOAD)

typedef struct WreckingBall_t
{
	BaseClass m_BaseClass;
} WreckingBall;
BEGIN_CLASS(WreckingBall)
END_CLASS_DEFAULT_FLAGS(WreckingBall, B2BaseClass, NULL, NULL, CF_ALWAYSLOAD)

typedef struct ExitHint_t
{
	BaseClass m_BaseClass;
} ExitHint;

BEGIN_CLASS(ExitHint)
END_CLASS_DEFAULT_FLAGS(ExitHint, B2BaseClass, NULL, NULL, CF_ALWAYSLOAD)

#pragma endregion
DEFINE_CLASSES()