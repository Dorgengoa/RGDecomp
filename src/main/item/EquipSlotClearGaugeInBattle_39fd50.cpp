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
    virtual s32 v19();
    virtual s32 v20();
    virtual s32 v21();
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00483748;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x20];
    struct Obj1 *m20;
};

struct Obj1 {
    u8 pad000[0x24C];
    u8 m24C;
};

extern "C" s32 EquipSlotClearGaugeInBattle_39fd50(s32 p0)
{
    struct Obj0 * t0;
    struct Obj1 * t1;
    u8 t2;
    s32 rv1;
    s32 r0;

    t0 = D_00483748;
    if (t0 == 0) {
        return 0;
    }
    t1 = D_00483748->m20;
    t2 = D_00483748->m20->m24C;
    rv1 = 1;
    if ((t2 & 1) == 0) {
        rv1 = 0;
    } else {
        r0 = ((struct C0 *)p0)->v21();
        rv1 = 1;
    }
    return rv1;
}
