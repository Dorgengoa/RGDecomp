#include "types.h"

struct C400 {
    u8 pad000[0x190];
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
    virtual s32 v13();
    virtual s32 v14();
    virtual s32 v15();
    virtual s32 v16();
    virtual s32 v17();
    virtual s32 v18();
    virtual s32 v19();
    virtual s32 v20();
    virtual s32 v21();
    virtual s32 v22();
};

struct E8 { s32 a; s32 b; };

extern "C" s32 ScriptSlotGetInt_3348b0(struct E8 *);
extern "C" s32 sceVu0CopyVector(void *, s32);
extern "C" void ScriptSlotStoreVec3_334790(struct E8 *, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_004826E0;

extern "C" s32 ScriptCmdEffectElemGetPos_331340(struct E8 *p0, s32 p1)
{
    u128 v30;
    struct E8 *q;
    s32 r0;
    s32 t0;
    s32 r1;
    s32 r2;

    q = p0;
    if (p1 != 4) {
        return 0;
    }
    r0 = ScriptSlotGetInt_3348b0(q++);
    t0 = D_004826E0;
    r1 = ((struct C400 *)t0)->v22();
    if (r1 == 0) {
        return 1;
    }
    r2 = sceVu0CopyVector(&v30, ((r1 + (r0 * 0xC0)) + 0xA0));
    ScriptSlotStoreVec3_334790(q, &v30);
    return 1;
}
