#include "types.h"

/* Known-positive sibling shape of EventCameraCtor_254c50 (byte-identical, in cunits). */

extern void SplinePathCtor_256cc0(s32);
extern s32 EvSubMachineCtor_252070(s32);

s32 EvSubMachineSplineCtor_252090(s32 p0)
{
    s32 r1;

    SplinePathCtor_256cc0((p0 + 0x140));
    r1 = EvSubMachineCtor_252070(p0);
    return p0;
}
