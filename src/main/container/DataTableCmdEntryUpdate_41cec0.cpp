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
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual struct G *v26(s32 a);
    void *m4;
    u8    pad008[0x74];
    s16   count;
};

extern Pool *D_004830F8;
extern G    *D_00483E44;
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
