#include "types.h"

class VE_003FE230 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void DataTableGetCount_3fdf40(s32 p);

extern "C" void ContainerViewGetAtFwd_3fe230(VE_003FE230 *o)
{
    o->v2();
}

extern "C" void func_003FE230_e1(VE_003FE230 *o)
{
    o->v2();
}

extern "C" void func_003FE230_e2(s32 p)
{
    DataTableGetCount_3fdf40((p + -0x88));
}
