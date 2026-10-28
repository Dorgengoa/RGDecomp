#include "types.h"

struct R8 { u8 b[8]; };

struct G {
    u8    pad000[0x4];
    s32   m4;
    s16   m8;
    s16   pad00A;
    s16   mC;
    u8    pad00E[0x1A];
    s32   m28;
};

class Pool {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    struct G * v26(s32 a) { return VCM(struct G *, (void *, s32), 0x70, a); }
    void *m4;
    u8    pad008[0x74];
    s16   count;
};

extern "C" Pool *D_004830F8;
extern "C" G    *D_00483E44;
extern "C" s32 VariantGetInt_15f780(R8 *q);
extern "C" s32 SlotGetInt_15f720(R8 *q);
extern "C" s32 DataTableStoreString_368ab0(Pool *p, s32 h);
extern "C" void CfgVmFindOp_42f650(void *h, s32 b, s32 c);

extern "C" s32 DataTableCmdEntryUpdate_41cec0(R8 *a)
{
    Pool *p = D_004830F8;
    G *g;

    if (p->count <= 0) return 1;
    g = p->v26(VariantGetInt_15f780(a++));
    D_00483E44 = g;
    if (g == 0) {
        CfgVmFindOp_42f650(p->m4, 4, 1);
        return 1;
    }
    SlotGetInt_15f720(a++);
    g->m4 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(a++));
    g->mC = VariantGetInt_15f780(a++);
    g->m8 = VariantGetInt_15f780(a);
    g->m28 = 0;
    return 1;
}
