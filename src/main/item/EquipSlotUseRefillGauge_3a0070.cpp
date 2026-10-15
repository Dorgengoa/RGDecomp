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
    virtual s32 v13();
    virtual s32 v14();
    virtual s32 v15();
    virtual s32 v16();
    virtual s32 v17();
    virtual s32 v18();
};

extern "C" s32 EquipSlotGetGaugeMax_3a02d0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s16 m0C;
    u8 pad00E[0x2];
    f32 m10;
};

extern "C" s32 EquipSlotUseRefillGauge_3a0070(struct Obj0 *p0)
{
    s32 r0;
    s16 t0;
    s32 r1;
    s32 r2;

    r0 = ((struct C0 *)p0)->v15();
    if (r0 == 0) {
        return 0;
    }
    t0 = p0->m0C;
    p0->m0C = (t0 + 1);
    r1 = ((struct C0 *)p0)->v18();
    if (r1 != 0) {
        r2 = EquipSlotGetGaugeMax_3a02d0(p0);
        p0->m10 = ((f32)r2);
    }
    return 1;
}
