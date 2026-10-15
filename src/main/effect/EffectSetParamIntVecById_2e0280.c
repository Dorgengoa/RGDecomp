#include "types.h"

typedef struct Rec_002e0280 {
    s32 w[5];
} Rec_002e0280;

extern void EffectFindHandleById_2dd6c0(Rec_002e0280 *out, void *p, s32 b);
extern void EffectSetParamIntVec_2e0310(void *a, Rec_002e0280 *r, s32 c, s32 d);

void EffectSetParamIntVecById_2e0280(u8 *a0, s32 a1, s32 a2, s32 a3)
{
    Rec_002e0280 r;
    Rec_002e0280 info;

    r.w[3] = 0;
    EffectFindHandleById_2dd6c0(&info, a0 + 0x1674, a1);
    r.w[3] = info.w[3];
    r.w[2] = info.w[2];
    if (info.w[2] == -1) {
        return;
    }
    *(s64 *)&r.w[3] = *(s64 *)&info.w[3];
    *(s64 *)&r.w[0] = *(s64 *)&info.w[0];
    EffectSetParamIntVec_2e0310(a0, &r, a2, a3);
}
