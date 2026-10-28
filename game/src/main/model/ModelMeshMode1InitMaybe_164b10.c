/* rgp:protos */
#define RGP_SELF_ModelMeshMode1InitMaybe_164b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;

struct Obj0 {
    u8 pad000[0x60];
    s32 m60;
    s32 m64;
    s32 m68;
    u8 pad06C[0x38];
    s32 mA4;
    s32 mA8;
    s32 mAC;
    s32 mB0;
    s32 mB4;
    s32 mB8;
    s32 mBC;
    s32 mC0;
    u8 pad0C4[0xC];
    u128 mD0;
    u128 mE0;
};

void ModelMeshMode1InitMaybe_164b10(struct Obj0 *p0)
{
    s32 r0;

    r0 = (ModelMeshBaseInitMaybe_15c970(p0), (s32)0);
    p0->m68 = 0x20;
    p0->m64 = 0x20;
    p0->m60 = 0x20;
    VecSetOnes4_13e170((struct Obj0 *)((u8 *)p0 + 0x70));
    VecSetOnes4_13e170((struct Obj0 *)((u8 *)p0 + 0x80));
    VecSetOnes4_13e170((struct Obj0 *)((u8 *)p0 + 0x90));
    p0->mA4 = 0;
    p0->mA8 = 0;
    p0->mAC = 0;
    p0->mB0 = 0;
    p0->mB4 = 0;
    p0->mB8 = 0;
    p0->mBC = 0;
    p0->mC0 = 0;
    p0->mD0 = 0;
    p0->mE0 = 0;
}
