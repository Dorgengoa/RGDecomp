#include "types.h"

class VE_003D5CC0 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void ContainerViewGetAtFwd_3d5cc0(VE_003D5CC0 *o)
{
    o->v2();
}

extern "C" s32 func_003D5CC0_e1(void)
{
    return 0x30;
}
