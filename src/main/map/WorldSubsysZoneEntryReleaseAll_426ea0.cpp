#include "types.h"

class E {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    u8 pad004[0x94];
};

struct Holder {
    u8 pad000[0xC];
    E *m0C;
};

struct BigD { s32 v; s32 pad[3]; };
extern BigD D_004644A8;

extern "C" void WorldSubsysZoneEntryReleaseAll_426ea0(Holder *o)
{
    E  *p;
    s32 n;
    s32 i;

    p = o->m0C;
    if (p == 0) {
        return;
    }
    n = D_004644A8.v;
    for (i = 0; i < n; i++, p++) {
        p->v6();
    }
}
