#include "types.h"

class VE {
public:
    u8 pad000[0x14];
    virtual void v0();
};

extern void *D_00470538[];

extern "C" void *ListNodeCtor_18e1a0(VE *o)
{
    *(void **)((u8 *)o + 0x14) = (void *)D_00470538;
    o->v0();
    return o;
}
