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

extern "C" s32 ScriptCmdEffectElemAddColor_32fce0(Slot *args, s32 argc)
{
    s32 cnt;
    s32 i;
    f32 d, c, b, a;
    u8 *base;
    s32 limit;
    u8 *e;

    if (argc != 5 && argc != 6) {
        return 0;
    }
    i = ScriptSlotGetInt_3348b0(args++);
    a = ScriptSlotGetFloat_334890(args++);
    b = ScriptSlotGetFloat_334890(args++);
    c = ScriptSlotGetFloat_334890(args++);
    d = ScriptSlotGetFloat_334890(args++);
    cnt = 1;
    if (argc == 6) {
        cnt = ScriptSlotGetInt_3348b0(args);
    }
    base = ((CMgr *)D_004826E0)->v22();
    if (base == 0) {
        return 1;
    }
    limit = i + cnt;
    for (; i < limit; i++) {
        e = base + i * 0xC0;
        if (e == 0) {
            return 0;
        }
        *(f32 *)(e + 0xB0) = *(f32 *)(e + 0xB0) + a;
        *(f32 *)(e + 0xB4) = *(f32 *)(e + 0xB4) + b;
        *(f32 *)(e + 0xB8) = *(f32 *)(e + 0xB8) + c;
        *(f32 *)(e + 0xBC) = *(f32 *)(e + 0xBC) + d;
    }
    return 1;
}
