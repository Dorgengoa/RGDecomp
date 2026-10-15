#include "types.h"

/* ONE symbol, 2 entry points.  `lw $25,0x0($4)` / `lw $25,K($25)` /
   `jr $25` is a C++ VIRTUAL tail call: slot K = 4*index + 8.  All the
   entries must come out of ONE translation unit, in listing order --
   mwcc gives each its own .text and the lcf takes them in file order. */

struct S39F330 {
    u8    pad000[0xC];
    void *m0C;
};

extern "C" bool EquipSlotSetAbility_3a07b0(void *a, void *b);
class V39F330_0 {
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
};

extern "C" void EquipSlotGetOwnerThunk_39f330(V39F330_0 *o)
{
    o->v29();
}

extern "C" s32 func_0039F330_e1(void *a, S39F330 *b)
{
    if (b == 0) return 0;
    return EquipSlotSetAbility_3a07b0(a, b->m0C);
}


