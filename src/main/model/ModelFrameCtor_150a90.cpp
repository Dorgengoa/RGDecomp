#include "types.h"

class VE {
public:
    u8 pad000[0xE0];
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern void *D_0046FFA0[];

extern "C" void *ModelFrameCtor_150a90(VE *o)
{
    *(void **)((u8 *)o + 0xE0) = (void *)D_0046FFA0;
    o->v2();
    return o;
}
