/* rgp:protos */
#define RGP_SELF_MeshMaterialDescInitShadowProjMaybe_14bb40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memset(void *, s32, s32);
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    u128 m10;
    u128 m20;
    u8 pad030[0x10];
    s32 m40;
    s32 m44;
    s32 m48;
    u8 m4C;
    u8 m4D;
    u8 m4E;
    u8 m4F;
    u8 m50;
    u8 m51;
    u8 m52;
    u8 m53;
};

void MeshMaterialDescInitShadowProjMaybe_14bb40(struct Obj0 *p0)
{
    memset(p0, 0, 0x60);
    VecSetOnes4_13e170(p0);
    p0->m10 = 0;
    p0->m20 = 0;
    p0->m40 = 0xA;
    p0->m44 = 0x3A;
    p0->m48 = 7;
    p0->m4C = 1;
    p0->m4D = 5;
    p0->m4E = 1;
    p0->m4F = 0;
    p0->m50 = 2;
    p0->m51 = 0;
    p0->m52 = 1;
    p0->m53 = 0;
}
