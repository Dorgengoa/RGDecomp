#include "types.h"

extern s32 GetObjRefTable_313de0(void);
extern void * HandleRegistryLookup_314aa0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xA48];
    s32 mA48;
};

struct Obj1 {
    u8 pad000[0xB6];
    s16 mB6;
};

struct Obj1 *CharaJudgeObjRelease_213ca0(struct Obj0 *p0)
{
    s32 r0;
    s32 t0;
    struct Obj1 *r1;

    r0 = GetObjRefTable_313de0();
    t0 = p0->mA48;
    r1 = HandleRegistryLookup_314aa0(r0, t0);
    if (r1 != 0) {
        r1->mB6 = 1;
    }
    p0->mA48 = -1;
    return r1;
}
