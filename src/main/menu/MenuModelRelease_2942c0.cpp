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

extern "C" void DrawCtxVif1HandlerStop_15dc40(void);
extern "C" void ModelObjExEffectsStopAll_1b0870(s32);
extern "C" s32 GetDrawCtxNameTable_15de40(void);
extern "C" void NameTableFreeGroup_158ac0(s32, s32);
extern "C" void SoundBankRelease_1bb6e0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" u8 D_00482398;
extern "C" s32 D_004823D0;

extern "C" void MenuModelRelease_2942c0(void)
{
    s32 t0;
    s32 t1;
    s32 t2;
    s32 r3;

    t0 = D_004823D0;
    if (t0 != 0) {
        DrawCtxVif1HandlerStop_15dc40();
        t1 = D_004823D0;
        ModelObjExEffectsStopAll_1b0870(t1);
        t2 = D_004823D0;
        ((struct C432 *)t2)->v20();
        r3 = GetDrawCtxNameTable_15de40();
        NameTableFreeGroup_158ac0(r3, 0x288);
        SoundBankRelease_1bb6e0(5);
        D_004823D0 = 0;
        D_00482398 = 0;
        return;
    }
}
