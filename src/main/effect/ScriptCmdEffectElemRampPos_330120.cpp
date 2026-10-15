#include "types.h"

typedef unsigned __int128 u128;
typedef union V4 {
    u128 q;
    f32 f[4];
} V4;

struct Item {
    u8 pad0[0xA0];
    u128 unkA0;
    u8 padB0[0x10];
};

class Mgr {
    u8 pad0[0x190];
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual Item *slot60();
};

extern "C" {
void ScriptSlotsToVec4_334810(V4 *, u8 *);
s32 ScriptSlotGetInt_3348b0(s32);
void sceVu0AddVector(V4 *, V4 *, V4 *);
extern Mgr *D_004826E0;
}

extern "C" s32 ScriptCmdEffectElemRampPos_330120(s64 *arg0, s32 arg1)
{
    V4 a;
    V4 b;
    V4 c;
    s32 cnt;
    s32 i;
    s32 end;
    Item *it;
    s32 t;
    cnt = 1;
    i = ScriptSlotGetInt_3348b0((s32)arg0++);
    ScriptSlotsToVec4_334810(&a, (u8 *)arg0);
    ScriptSlotsToVec4_334810(&b, (u8 *)arg0 + 0x18);
    ScriptSlotsToVec4_334810(&c, (u8 *)arg0 + 0x30);
    t = (s32)((u8 *)arg0 + 0x48);
    if (arg1 >= 11) {
        cnt = ScriptSlotGetInt_3348b0(t);
    }
    end = i + cnt;
    for (; i < end; i++) {
        it = D_004826E0->slot60() + i;
        if (it == NULL) {
            return 0;
        }
        it->unkA0 = a.q;
        sceVu0AddVector(&a, &a, &b);
        a.f[3] = 1.0f;
        sceVu0AddVector(&b, &b, &c);
        b.f[3] = 1.0f;
    }
    return 1;
}
