/* rgp:protos */
#define RGP_SELF_UnpackWordTriple_370d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 UnpackWordTriple_370d70(s32 arg0, u32 arg1, s32 arg2_unused, s32 arg3, s32 arg4) {
    s32 sum;
    s32 delta;

    if (arg0 == 0 || arg1 < 0xC) {
        return 0;
    }
    sum = 0;
    delta = BufReadU32_370e10((void *)arg0, (unsigned int)arg1, (void *)arg2_unused);
    arg0 = arg0 + delta;
    arg1 = arg1 - delta;
    sum = sum + delta;
    delta = BufReadU32_370e10(arg0, arg1, arg3);
    sum = sum + delta;
    return sum + BufReadU32_370e10(arg0 + delta, arg1 - delta, arg4);
}
