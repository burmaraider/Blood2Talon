#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#include "ltserverobj.h"

DEFINE_CLASSES()

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
ADD_BOOLPROP(Additive, 0)
ADD_BOOLPROP(TerrainOccluder, 0)
ADD_BOOLPROP(TimeOfDay, 0)
ADD_BOOLPROP(VisBlocker, 0)
ADD_BOOLPROP(NotAStep, 0)
ADD_BOOLPROP(NoWallWalk, 0)
ADD_BOOLPROP(BlockLight, 1)

ADD_LONGINTPROP(DetailLevel, 0)
ADD_STRINGPROP(Effect, "")
ADD_STRINGPROP(EffectParam, "")
ADD_REALPROP(FrictionCoefficient, 1)
END_CLASS_DEFAULT_FLAGS(Brush, BaseClass, NULL, NULL, CF_ALWAYSLOAD)