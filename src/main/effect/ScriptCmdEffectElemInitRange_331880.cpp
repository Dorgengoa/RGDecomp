#include "types.h"
typedef struct { s32 a, b; } E8_331880;
struct CMgr331880 {
    u8 pad000[0x190];
    virtual void *v0();
    virtual void *v1();
    virtual void *v2();
    virtual void *v3();
    virtual void *v4();
    virtual void *v5();
    virtual void *v6();
    virtual void *v7();
    virtual void *v8();
    virtual void *v9();
    virtual void *v10();
    virtual void *v11();
    virtual void *v12();
    virtual void *v13();
    virtual void *v14();
    virtual void *v15();
    virtual void *v16();
    virtual void *v17();
    virtual void *v18();
    virtual void *v19();
    virtual void v20(s32, s32, s32);
};
extern "C" s32 ScriptSlotGetInt_3348b0(E8_331880 *);
extern "C" s32 ScriptSlotGetCodeAddr_334870(E8_331880 *);
extern "C" s32 GetEffectMgr_2d9040(void);
extern void *D_004826E0;

extern "C" s32 ScriptCmdEffectElemInitRange_331880(E8_331880 *p0, s32 p1)
{
    s32 a;
    s32 b;
    s32 c;

    if (p1 != 2 && p1 != 3) {
        return 0;
    }
    a = ScriptSlotGetInt_3348b0(p0++);
    b = ScriptSlotGetCodeAddr_334870(p0++);
    c = 1;
    if (p1 == 3) {
        c = ScriptSlotGetInt_3348b0(p0);
    }
    if (D_004826E0 == 0) {
        return 0;
    }
    GetEffectMgr_2d9040();
    ((CMgr331880 *)D_004826E0)->v20(b, a, c);
    return 1;
}
