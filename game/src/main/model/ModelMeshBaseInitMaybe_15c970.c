/* rgp:protos */
#define RGP_SELF_ModelMeshBaseInitMaybe_15c970 1
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
};

void ModelMeshBaseInitMaybe_15c970(struct Obj0 *p0)
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
}
