/* rgp:protos */
#define RGP_SELF_EffectSetParamIntById_2e04a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Rec_002e04a0 {
    s32 w[5];
} Rec_002e04a0;

/*rgp*/
/*rgp*/

void EffectSetParamIntById_2e04a0(u8 *a0, s32 a1, s32 a2, s32 a3)
{
    Rec_002e04a0 r __attribute__((aligned(16)));
    Rec_002e04a0 info __attribute__((aligned(16)));

    r.w[3] = 0;
    EffectFindHandleById_2dd6c0(&info, a0 + 0x1674, a1);
    r.w[3] = info.w[3];
    r.w[2] = info.w[2];
    if (info.w[2] == -1) {
        return;
    }
    *(s64 *)&r.w[3] = *(s64 *)&info.w[3];
    *(s64 *)&r.w[0] = *(s64 *)&info.w[0];
    EffectSetParamInt_2e0530(a0, &r, a2, a3);
}
