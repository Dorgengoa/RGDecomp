/* rgp:protos */
#define RGP_SELF_ActTimeEvntRunInRange_2281d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void ActTimeEvntRunInRange_2281d0(f32 *arg0, s32 arg1, f32 fparg0, f32 fparg1) {
    s32 sp[9] __attribute__((aligned(16)));
    f32 lo;
    f32 hi;
    f32 val;
    u8 hit;

    lo = fparg0;
    hi = lo + fparg1;
    if (lo < 0.0f) {
        lo = 0.0f;
    }
    val = *arg0;
    hit = 0;
    if ((lo > val) || (val >= hi)) {
    } else {
        hit = 1;
    }
    if (hit) {
        sp[1] = 0;
        sp[2] = 0;
        sp[3] = 0;
        sp[4] = 0;
        sp[5] = 0;
        sp[6] = 0;
        sp[7] = 0;
        sp[8] = 0;
        sp[0] = arg1;
        ScriptCallWithArgs_302770(arg0 + 1, sp, 0);
    }
}
