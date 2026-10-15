#include "types.h"

class VE_00406B50 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

extern "C" void DataTableGetCount_406ae0(s32 p);

extern "C" void ContainerViewGetAtFwd_406b50(VE_00406B50 *o)
{
    o->v2();
}

extern "C" void func_00406B50_e1(VE_00406B50 *o)
{
    o->v2();
}

extern "C" void func_00406B50_e2(s32 p)
{
    DataTableGetCount_406ae0((p + -0x88));
}
