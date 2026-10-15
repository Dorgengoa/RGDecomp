#include "types.h"

struct B_001e0c70 {
    u8 pad[0x1B0];
};

struct C_001e0c70 : public B_001e0c70 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4(f32);
    virtual void v5();
    virtual void v6();
    virtual void v7();
};

extern "C" void MapEntryShow_1e0c70(C_001e0c70 *p)
{
    s32 q;

    q = *(s32 *)((s32)p + 0x790);
    if (q == 0) return;
    if ((*(s32 *)(q + 0x40) & 1) == 0) return;
    p->v4(1.0f);
    p->v7();
}
