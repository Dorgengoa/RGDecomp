/* rgp:protos */
#define RGP_SELF_CharaMoveReqGetVelocity_219380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 CharaMoveReqGetVelocity_219380(u8 *arg0, u32 *arg1)
{
    s32 n;

    n = *(s32 *)(arg0 + 0x10);
    if (n > 0) {
        switch (*(s32 *)(arg0 + 0x18) & 2) {
        case 0:
            VecDivScalar_1cbbf0(arg1, arg0, (f32)n);
            return 1;
        case 2:
            VecScale_1cbca0(arg1, arg0, (2.0f * (f32)(n - *(s32 *)(arg0 + 0x14))) / ((f32)n * (f32)n));
            return 1;
        }
    }
    if (n <= 0) {
        arg1[0] = 0;
        arg1[1] = 0;
        arg1[2] = 0;
        arg1[3] = 0;
        return 0;
    }
    return 1;
}
