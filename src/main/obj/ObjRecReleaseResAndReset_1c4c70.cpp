#include "types.h"

struct B0 { u8 pad000[0x1C]; s32 m1C; };

struct C0 : public B0 {
    virtual void v0();
};

extern "C" struct C0 *ObjRecTableGet_1c3fe0(void);
extern "C" void MemStackRefCountDec_14d7c0(s32);

extern "C" void ObjRecReleaseResAndReset_1c4c70(void)
{
    struct C0 *o;

    o = ObjRecTableGet_1c3fe0();
    if (o == 0) {
        return;
    }
    if (o->m1C != 0) {
        MemStackRefCountDec_14d7c0(o->m1C);
        o->m1C = 0;
    }
    o->v0();
}
