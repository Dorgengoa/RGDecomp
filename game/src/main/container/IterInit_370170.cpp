/* rgp:protos */
#line 1
#include "types.h"

struct B00370170 {
    VC_VPTR_MEMBER; s16 v0(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s16, (void *, int, int, int), 0x8, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};
struct O00370170 : B00370170 {};
struct T00370170 { struct O00370170 *f00; s16 f04; s16 f06; };

extern "C" struct T00370170 *IterInit_370170(struct T00370170 *p, struct O00370170 *a, int rgp_a2, int rgp_a3)
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
    return p;
}
