#include "types.h"

class E {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    void v6() { VCM0(void, 0x20); }
    u8 pad004[0x94];
};

struct Holder {
    u8 pad000[0xC];
    E *m0C;
};

struct BigD { s32 v; s32 pad[3]; };
extern "C" BigD D_004644A8;

extern "C" void WorldSubsysZoneEntryReleaseAll_41c390(Holder *o)
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
