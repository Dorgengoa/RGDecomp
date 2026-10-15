#include "types.h"

/* ONE symbol, TWO entries: a 4-word virtual tail-call thunk (vtable slot
   0x80 = declared virtual index 30) then the accessor.  Every token below is
   read off EquipSlotFindNthLinkedThunk_39f2e0.s itself. */

struct G {
    u8    pad00[0x1C];
    void *m1C;
};

struct Self {
    u8   pad00[0xA];
    s16  mA;
};

class V0039F2E0 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
};

extern G *D_00483748;
extern "C" void *ObjFindById_3bb3a0(void *p, s32 k);

extern "C" void EquipSlotFindNthLinkedThunk_39f2e0(V0039F2E0 *o)
{
    o->v30();
}

extern "C" void *func_0039F2E0_e1(Self *s)
{
    G *g;

    if (s->mA < 0) {
        return 0;
    }
    g = D_00483748;
    if (g != 0) {
        return ObjFindById_3bb3a0(g->m1C, s->mA);
    }
    return 0;
}
