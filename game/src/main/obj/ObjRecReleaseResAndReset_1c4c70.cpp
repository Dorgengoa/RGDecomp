/* rgp:protos */
#line 1
#include "types.h"

struct B0 { u8 pad000[0x1C]; s32 m1C; };

struct C0 : public B0 {
    VC_VPTR_MEMBER; void v0() { VCM0(void, 0x8); }
};

extern "C" struct C0 * ObjRecTableGet_1c3fe0(void *, int);
extern "C" void MemStackRefCountDec_14d7c0(s32);

extern "C" void ObjRecReleaseResAndReset_1c4c70(void *rgp_a0, int rgp_a1)
{
    struct C0 *o;

    o = ObjRecTableGet_1c3fe0((void *)rgp_a0, (int)rgp_a1);
    if (o == 0) {
        return;
    }
    if (o->m1C != 0) {
        MemStackRefCountDec_14d7c0(o->m1C);
        o->m1C = 0;
    }
    o->v0();
}
