#include "types.h"

struct C400_00330310 {
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
    virtual s32 v22();
};

struct Ent_00330310 {
    u8 pad000[0x8C];
    f32 m8C;
    u8 pad[0x30];
};

struct S8_00330310 {
    u8 b[8];
};

extern "C" s32 ScriptSlotGetInt_3348b0(struct S8_00330310 *);
extern "C" f32 ScriptSlotGetFloat_334890(struct S8_00330310 *);
extern "C" s32 D_004826E0;

extern "C" s32 ScriptCmdEffectElemSetAlphaVel_330310(struct S8_00330310 *p0, s32 p1)
{
    s32 idx;
    s32 cnt;
    f32 val;
    s32 base;
    s32 i;

    switch (p1) {
    case 3:
    case 2:
        idx = ScriptSlotGetInt_3348b0(p0++);
        val = ScriptSlotGetFloat_334890(p0++);
        cnt = 1;
        if (p1 == 3) {
            cnt = ScriptSlotGetInt_3348b0(p0);
        }
        base = ((struct C400_00330310 *)D_004826E0)->v22();
        if (base == 0) {
            return 1;
        }
        for (i = idx; i < cnt + idx; i++) {
            ((struct Ent_00330310 *)base)[i].m8C = val;
        }
        return 1;
    }
    return 0;
}
