#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

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
    virtual u8 *v22();
};

extern "C" s32 ScriptSlotGetInt_3348b0(E8 *);
extern "C" f32 ScriptSlotGetFloat_334890(E8 *);

extern "C" struct C400 *D_004826E0;

extern "C" s32 ScriptCmdEffectElemSetUvRect_3315c0(E8 *p0, s32 p1)
{
    s32 i;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    s32 n;
    u8 *base;
    s32 end;
    u8 *e;

    if (p1 != 5 && p1 != 6) {
        return 0;
    }
    i = ScriptSlotGetInt_3348b0(p0++);
    a = ScriptSlotGetFloat_334890(p0++);
    b = ScriptSlotGetFloat_334890(p0++);
    c = ScriptSlotGetFloat_334890(p0++);
    d = ScriptSlotGetFloat_334890(p0++);
    n = 1;
    if (p1 == 6) {
        n = ScriptSlotGetInt_3348b0(p0);
    }
    base = D_004826E0->v22();
    if (base == 0) {
        return 0;
    }
    end = n + i;
    while (i < end) {
        e = base + i * 192;
        *(f32 *)(e + 0x10) = a;
        *(f32 *)(e + 0x14) = b;
        *(f32 *)(e + 0x18) = c;
        *(f32 *)(e + 0x1C) = d;
        i++;
    }
    return 1;
}
