#include "types.h"

/* The `arg0->0x68->0x38(arg0)` call assembles as `jalr $25` -- a C++
   virtual member call (see jalr-is-cpp-virtual lever), not reachable
   from any plain-C function-pointer spelling. vptr read at
   `lw $25,0x68($obj)` -> K=0x68 pad before the first virtual; slot
   0x38 -> N=(0x38-8)/4=12. Dummy virtuals declared-never-defined so
   no vtable/undefined-symbol noise. */

extern "C" s32 FadeIsVisible_186de0(void *);

class VE {
public:
    u8 pad000[0x68];
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
};

extern "C" s32 NodeObjIsVisible_194e20(void *arg0)
{
    s32 v;

    if (*(s16 *)((u8 *)arg0 + 0x32) != 0) {
        v = FadeIsVisible_186de0((u8 *)arg0 + 0x3C);
    } else {
        v = 0;
    }
    if (v == 0) {
        return 0;
    }
    ((VE *)arg0)->v12();
    return 1;
}
