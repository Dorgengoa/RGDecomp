#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern s32 LoaderGetData_1cd490(s32, s32, void *);
extern s32 EffectEntryRegisterImg_2db8c0(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1A];
    s16 m1A;
};

s32 EffectEntryFinishImg_2dba30(struct Obj0 *p0)
{
    s32 v2C;
    s32 r0;
    s16 t0;
    s32 r1;
    s32 t1;
    s32 r2;

    r0 = GetLoaderMgr_1f59d0();
    v2C = 0;
    t0 = p0->m1A;
    r1 = LoaderGetData_1cd490(r0, t0, &v2C);
    t1 = v2C;
    r2 = EffectEntryRegisterImg_2db8c0(p0, r1, t1);
    return r2;
}
