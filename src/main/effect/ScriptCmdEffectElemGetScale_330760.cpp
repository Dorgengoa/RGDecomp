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
    virtual f32* v22();
};

struct E8 { s32 a; s32 b; };

extern "C" s32 ScriptSlotGetInt_3348b0(struct E8 *);
extern "C" s32 ScriptSlotStoreIntRef_3347f0(struct E8 *, s32);
extern "C" void ScriptSlotStoreFloatRef_3347d0(struct E8 *, f32);

extern "C" s32 D_004826E0;

extern "C" s32 ScriptCmdEffectElemGetScale_330760(struct E8 *p0, s32 p1)
{
    s32 r0;
    s32 t0;
    f32* r1;
    s32 r2;

    if (p1 != 3) {
        return 0;
    }
    r0 = ScriptSlotGetInt_3348b0(p0++);
    t0 = D_004826E0;
    r1 = ((struct C400 *)t0)->v22();
    if (r1 == 0) {
        ScriptSlotStoreIntRef_3347f0(p0++, 1);
        ScriptSlotStoreIntRef_3347f0(p0, 1);
    } else {
        ScriptSlotStoreFloatRef_3347d0(p0++, r1[r0*48+10]);
        ScriptSlotStoreFloatRef_3347d0(p0, r1[r0*48+11]);
    }
    return 1;
}
