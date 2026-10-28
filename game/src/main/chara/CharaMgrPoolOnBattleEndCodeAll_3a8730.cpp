#include "types.h"

class VA87 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void sCC(void *p) { VCM(void, (void *, void *), 0xCC, p); }
};

struct G20 { u8 pad00[0x24C]; u8 m24C; };
struct G87 { u8 pad00[0x20]; G20 *m20; };
struct A87 { u8 pad00[0x8]; void *m8; };

extern "C" G87 *D_004837E8;
extern "C" struct BigD87 { s32 v; s32 pad[3]; } D_004659B8;
extern "C" VA87 *PoolGetUsedElem_36acb0(void *, s32);

extern "C" s32 CharaMgrPoolOnBattleEndCodeAll_3a8730(A87 *a0, void *arg)
{
    G87 *g;
    VA87 *e;
    s32 i;
    s32 n;

    g = D_004837E8;
    if (g == 0) {
        return 0;
    }
    if ((g->m20->m24C & 1) == 0) {
        return 0;
    }
    if (a0->m8 == 0) {
        return 0;
    }
    n = D_004659B8.v;
    for (i = 0; i < n; i++) {
        e = PoolGetUsedElem_36acb0(a0->m8, i);
        if (e != 0) {
            e->sCC(arg);
        }
    }
    return 1;
}
