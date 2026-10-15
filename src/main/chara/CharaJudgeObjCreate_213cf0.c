#include "types.h"

extern s32 GetObjRefTable_313de0(void);
extern void * HandleRegistryLookup_314aa0(s32, s32);
extern s32 ClsnInfoInit_2281a0(void *, s32, s32, f32);
extern s32 ClsnInfoSetForce_228190(void *, f32);
extern s32 CharaSpawnClsnJudge_227c70(void *, void *, s32, void *, f32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045CA38[];

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x428];
    s32 m428;
    u8 pad42C[0x61C];
    s32 mA48;
};

struct Obj1 {
    u8 pad000[0xB6];
    s16 mB6;
};

s32 CharaJudgeObjCreate_213cf0(struct Obj0 *p0, s32 p1, s32 p2, f32 fa0)
{
    u128 v50[2];
    s32 r0;
    s32 t0;
    struct Obj1 *r1;
    s32 r2;
    s32 r3;
    s32 t1;
    s32 r4;

    r0 = GetObjRefTable_313de0();
    t0 = p0->mA48;
    r1 = HandleRegistryLookup_314aa0(r0, t0);
    if (r1 != 0) {
        r1->mB6 = 1;
    }
    p0->mA48 = -1;
    r2 = ClsnInfoInit_2281a0(v50, p1, p2, 2.0f);
    r3 = ClsnInfoSetForce_228190(v50, fa0);
    t1 = p0->m428;
    r4 = CharaSpawnClsnJudge_227c70(v50, p0, t1, D_0045CA38, -1.0f);
    p0->mA48 = r4;
    return r4;
}
