#include "types.h"

struct CMgr {
    u8 pad000[0x190];
    virtual u8 *v0();
    virtual u8 *v1();
    virtual u8 *v2();
    virtual u8 *v3();
    virtual u8 *v4();
    virtual u8 *v5();
    virtual u8 *v6();
    virtual u8 *v7();
    virtual u8 *v8();
    virtual u8 *v9();
    virtual u8 *v10();
    virtual u8 *v11();
    virtual u8 *v12();
    virtual u8 *v13();
    virtual u8 *v14();
    virtual u8 *v15();
    virtual u8 *v16();
    virtual u8 *v17();
    virtual u8 *v18();
    virtual u8 *v19();
    virtual u8 *v20();
    virtual u8 *v21();
    virtual u8 *v22();
};

struct Slot { u32 lo, hi; };

extern "C" s32 ScriptSlotGetInt_3348b0(Slot *);
extern "C" f32 ScriptSlotGetFloat_334890(Slot *);
extern void *D_004826E0;

extern "C" s32 ScriptCmdEffectElemRampScale_32fe40(Slot *args, s32 argc)
{
    s32 i;
    s32 cnt;
    f32 a, b, c, d, e, f;
    u8 *p;
    s32 limit;

    cnt = 1;
    i = ScriptSlotGetInt_3348b0(args++);
    a = ScriptSlotGetFloat_334890(args++);
    b = ScriptSlotGetFloat_334890(args++);
    c = ScriptSlotGetFloat_334890(args++);
    d = ScriptSlotGetFloat_334890(args++);
    e = ScriptSlotGetFloat_334890(args++);
    f = ScriptSlotGetFloat_334890(args++);
    if (argc >= 8) {
        cnt = ScriptSlotGetInt_3348b0(args);
    }
    limit = i + cnt;
    for (; i < limit; i++) {
        p = ((CMgr *)D_004826E0)->v22() + i * 0xC0;
        if (p == 0) {
            return 0;
        }
        *(f32 *)(p + 0x28) = a;
        *(f32 *)(p + 0x2C) = b;
        a = a + c;
        b = b + d;
        c = c + e;
        d = d + f;
    }
    return 1;
}
