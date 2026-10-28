/* rgp:protos */
#line 1
#include "types.h"

struct B00370100 {
    VC_VPTR_MEMBER; s16 v0(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s16, (void *, int, int, int), 0x8, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};
struct O00370100 : B00370100 {};
struct T00370100 { struct O00370100 *f00; s16 f04; s16 f06; };

extern "C" void IterAttach_370100(struct T00370100 *p, struct O00370100 *a, int rgp_a2, int rgp_a3)
{
    if (a != 0) {
        p->f00 = a;
    }
    p->f04 = 0;
    if (p->f00 != 0) {
        p->f04 = p->f00->v0((int)(long)(a), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    }
    p->f06 = 0;
    p->f06 = -1;
}
