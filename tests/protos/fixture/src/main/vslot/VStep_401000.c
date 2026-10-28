#include "types.h"
/* vslot-lane fixture (docs/PROTOS.md "vslot-lane"): slot 2 of a two-table vtable
   family.  VStepA takes (this, dt); its sibling VStepB takes (this, h, dt); the slot's
   callers push (this, h, dt).  EABI keeps dt in $f12 for both; i686 needs VStepA's
   float behind a padding GPR parameter. */
s32 VStepA_401000(u8 *o, f32 dt)
{
    *(f32 *)(o + 4) = *(f32 *)(o + 4) - dt;
    return 1;
}

s32 VStepB_401040(u8 *o, void *h, f32 dt)
{
    *(f32 *)(o + 4) = *(f32 *)(o + 4) - 2.0f * dt;
    return h != 0;
}

s32 VKind_401080(u8 *o)
{
    return 7;
}

s32 VDraw_4010c0(u8 *o)
{
    return 9;
}

/* a direct caller in the C keeps working: the padding lane is filled */
s32 VStepCall_401100(u8 *o, f32 dt)
{
    return VStepA_401000(o, dt);
}
