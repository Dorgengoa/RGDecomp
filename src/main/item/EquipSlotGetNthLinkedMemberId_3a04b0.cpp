#include "types.h"

struct R { u8 pad[0xC]; s32 f0C; };

struct O {
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void v011();
    virtual void v012();
    virtual R *vf();
};

extern "C" s32 EquipSlotGetNthLinkedMemberId_3a04b0(O *o)
{
    R *r = o->vf();
    if (r != 0) return r->f0C;
    return -1;
}
