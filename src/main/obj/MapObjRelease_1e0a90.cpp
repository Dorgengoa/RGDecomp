#include "types.h"

struct C432 {
    u8 pad000[0x1B0];
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
};

extern "C" s32 GetDrawCtxNameTable_15de40(void);
extern "C" s32 NameTableFreeGroup_158ac0(s32, s32);
extern "C" s32 LoaderReleaseHandle_1ccb70(void *);
extern "C" s32 ModelObjExEffectsStopAll_1b0870(s32);
extern "C" s32 MapObjReset_1e0b00(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    s32 m10;
};

extern "C" s32 MapObjRelease_1e0a90(struct Obj0 *p0)
{
    s32 r0;
    s32 t0;
    s32 r1;
    s32 r2;
    s32 t1;
    s32 rv5;
    s32 r3;
    s32 t2;
    s32 r4;
    s32 r6;

    r0 = GetDrawCtxNameTable_15de40();
    t0 = p0->m10;
    r1 = NameTableFreeGroup_158ac0(r0, t0);
    r2 = LoaderReleaseHandle_1ccb70(p0);
    t1 = p0->m0C;
    rv5 = r2;
    if (t1 != 0) {
        r3 = ModelObjExEffectsStopAll_1b0870(t1);
        t2 = p0->m0C;
        r4 = ((struct C432 *)t2)->v20();
        rv5 = r4;
    }
    r6 = MapObjReset_1e0b00(p0);
    return r6;
}
