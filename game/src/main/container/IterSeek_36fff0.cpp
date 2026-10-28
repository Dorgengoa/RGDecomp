/* rgp:protos */
#line 1
#include "types.h"

struct B36FFF0 {
    VC_VPTR_MEMBER;
    s32 v1(s16 i, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s16, int, int), 0xC, i, rgp_fwd2, rgp_fwd3); }
};
struct O36FFF0 : B36FFF0 {};
struct T36FFF0 { struct O36FFF0 *f00; s16 f04; s16 f06; };

extern "C" s32 IterSeek_36fff0(struct T36FFF0 *p, s32 i, int rgp_a2, int rgp_a3)
{
    if (i >= 0) {
        if (i < p->f04) {
            p->f06 = (s16)i;
            return p->f00->v1((s16)i, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
        }
        return 0;
    }
    return 0;
}
