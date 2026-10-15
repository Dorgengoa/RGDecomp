#include "types.h"

typedef unsigned __int128 u128;
struct Vec4 { f32 x, y, z, w; } __attribute__((aligned(16)));

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
extern "C" void sceVu0AddVector(f32 *, f32 *, f32 *);
extern void *D_004826E0;

extern "C" s32 ScriptCmdEffectElemRampColor_32ff90(Slot *args, s32 argc)
{
    Vec4 v0;
    Vec4 v1;
    Vec4 v2;
    s32 i;
    s32 cnt;
    u8 *p;
    s32 limit;

    cnt = 1;
    i = ScriptSlotGetInt_3348b0(args++);
    v0.x = ScriptSlotGetFloat_334890(args++);
    v0.y = ScriptSlotGetFloat_334890(args++);
    v0.z = ScriptSlotGetFloat_334890(args++);
    v0.w = ScriptSlotGetFloat_334890(args++);
    v1.x = ScriptSlotGetFloat_334890(args++);
    v1.y = ScriptSlotGetFloat_334890(args++);
    v1.z = ScriptSlotGetFloat_334890(args++);
    v1.w = ScriptSlotGetFloat_334890(args++);
    v2.x = ScriptSlotGetFloat_334890(args++);
    v2.y = ScriptSlotGetFloat_334890(args++);
    v2.z = ScriptSlotGetFloat_334890(args++);
    v2.w = ScriptSlotGetFloat_334890(args++);
    if (argc >= 0xB) {
        cnt = ScriptSlotGetInt_3348b0(args);
    }
    limit = i + cnt;
    for (; i < limit; i++) {
        p = ((CMgr *)D_004826E0)->v22() + i * 0xC0;
        if (p == 0) {
            return 0;
        }
        *(u128 *)(p + 0xB0) = *(u128 *)&v0;
        sceVu0AddVector((f32 *)&v0, (f32 *)&v0, (f32 *)&v1);
        sceVu0AddVector((f32 *)&v1, (f32 *)&v1, (f32 *)&v2);
    }
    return 1;
}
