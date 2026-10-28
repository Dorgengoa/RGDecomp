/* rgp:protos */
#define RGP_SELF_ModelMeshInitMaybe_15c8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    u128 m10;
    u128 m20;
    u128 m30;
    s32 m40;
    s32 m44;
    s32 m48;
    s32 m4C;
    u8 pad050[0x60];
    s32 mB0;
    s32 mB4;
    s32 mB8;
    s32 mBC;
    s32 mC0;
    s32 mC4;
    s32 mC8;
    s32 mCC;
    s32 mD0;
    s32 mD4;
    s32 mD8;
    s32 mDC;
    s32 mE0;
    u8 pad0E4[0xC];
    s32 mF0;
    u8 pad0F4[0xC];
    u128 m100;
    u128 m110;
    s32 m120;
    s32 m124;
    s32 m128;
    s32 m12C;
};

void ModelMeshInitMaybe_15c8c0(struct Obj0 *p0)
{
    p0->m00 = 0x8C;
    p0->m04 = 0x17C;
    p0->m08 = 0xBE;
    p0->m0C = 0xBE;
    p0->m20 = 0;
    p0->m30 = 0;
    p0->m10 = 0;
    p0->m40 = 0;
    p0->m44 = 0;
    p0->m48 = 0;
    p0->m4C = 0;
    p0->m124 = 0;
    p0->m128 = 0;
    p0->m12C = 0;
    p0->mB0 = 0;
    p0->mB4 = 0;
    p0->mB8 = 0;
    p0->mBC = 0;
    p0->mC0 = 0;
    p0->mC4 = 0;
    p0->mC8 = 0;
    p0->mCC = 0;
    p0->mD0 = 0;
    p0->mD4 = 0;
    p0->mD8 = 0;
    p0->mDC = 0;
    p0->mE0 = 0;
    p0->mF0 = 0;
    p0->m100 = 0;
    p0->m110 = 0;
    p0->m120 = 0;
}
