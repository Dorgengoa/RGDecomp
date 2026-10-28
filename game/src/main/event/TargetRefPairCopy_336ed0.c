/* rgp:protos */
#define RGP_SELF_TargetRefPairCopy_336ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_00336ed0 {
    u8 pad0[0x30];
    u8 f30[0x30];
    s32 f60;
    s32 f64;
} S_00336ed0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TargetRefPairCopy_336ed0(S_00336ed0 *self, s32 p1, s32 p2, s32 flag)
{
    s32 r;
    TargetRefPairReset_337080(self);
    if (p1 == 0) goto zero;
    if (p2 != 0) goto ok;
zero:
    return 0;
ok:
    r = TargetRefPairGetRec_336fd0(p1);
    self->f60 = r;
    if (r == 0) return 0;
    if (TargetRefCopy_2e7140(self, ((s32)TargetRefPairGetFirst_336ff0(p1)), p2) == 0) return 0;
    if (TargetRefCopy_2e7140((u8 *)self + 0x30, ((s32)TargetRefPairGetSecond_336fe0(p1)), p2) == 0) return 0;
    self->f64 = TargetRefPairGetMask_336fc0(p1);
    if (flag != 0) {
        TargetRefStashId_2e61b0(self);
        TargetRefStashId_2e61b0(self->f30);
    }
    return 1;
}
