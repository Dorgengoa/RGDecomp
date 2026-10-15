#include "types.h"

struct Rec330980 {
    u8 pad00[0x90];
    u8 m90[0x30];
};

struct E330980 {
    u8 b[8];
};

class Base330980 {
public:
    u8 pad[0x190];
};

class Vt330980 : public Base330980 {
public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual struct Rec330980 *make();
};

extern "C" class Vt330980 *D_004826E0;
extern "C" s32 ScriptSlotGetInt_3348b0(struct E330980 *q);
extern "C" f32 ScriptSlotGetFloat_334890(struct E330980 *q);
extern "C" void sceVu0CopyVector(void *dst, f32 *src);

extern "C" s32 ScriptCmdEffectElemSetColorAccel_330980(struct E330980 *q, s32 kind)
{
    s32 idx;
    struct Rec330980 *base;
    f32 v[4];
    s32 n;
    s32 end;

    if (kind != 5 && kind != 6) {
        return 0;
    }
    idx = ScriptSlotGetInt_3348b0(q++);
    base = D_004826E0->make();
    if (base == 0) {
        return 1;
    }
    v[0] = ScriptSlotGetFloat_334890(q++);
    v[1] = ScriptSlotGetFloat_334890(q++);
    v[2] = ScriptSlotGetFloat_334890(q++);
    v[3] = ScriptSlotGetFloat_334890(q++);
    sceVu0CopyVector(base[idx].m90, v);
    n = 1;
    if (kind == 6) {
        n = ScriptSlotGetInt_3348b0(q);
    }
    end = n - (-idx);
    while (idx < end) {
        sceVu0CopyVector(base[idx].m90, v);
        idx++;
    }
    return 1;
}
