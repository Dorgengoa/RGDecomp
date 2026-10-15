#include "types.h"

struct C0 {
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual s32 v7();
    virtual s32 v8();
    virtual s32 v9();
    virtual s32 v10();
    virtual s32 v11();
    virtual s32 v12();
};

extern "C" s32 ItemInInvCategory0_3d4960(void *);
extern "C" s32 ItemInInvCategory9_3d48e0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x244];
    s16 m244;
};

struct Obj1 {
    u8 pad000[0x4];
    s16 m04;
};

extern "C" s32 CharaSetEquipId244_3acdd0(struct Obj0 *p0, struct Obj1 *p1)
{
    if (p1 == 0) {
        p0->m244 = -1;
        ((struct C0 *)p0)->v12();
        return 1;
    }
    if (ItemInInvCategory0_3d4960(p1) == 0) {
        if (ItemInInvCategory9_3d48e0(p1) == 0) {
            return 0;
        }
    }
    p0->m244 = p1->m04;
    ((struct C0 *)p0)->v12();
    return 1;
}
