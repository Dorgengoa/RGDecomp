#include "types.h"

typedef struct Rec_002e0350 {
    s32 w[5];
} Rec_002e0350;

extern void EffectFindHandleById_2dd6c0(Rec_002e0350 *out, void *p, s32 b);
extern void EffectSetParamFloatVec_2e03e0(void *a, Rec_002e0350 *r, s32 c, s32 d);

void EffectSetParamFloatVecById_2e0350(u8 *a0, s32 a1, s32 a2, s32 a3)
{
    Rec_002e0350 r;
    Rec_002e0350 info;

    r.w[3] = 0;
    EffectFindHandleById_2dd6c0(&info, a0 + 0x1674, a1);
    r.w[3] = info.w[3];
    r.w[2] = info.w[2];
    if (info.w[2] == -1) {
        return;
    }
    *(s64 *)&r.w[3] = *(s64 *)&info.w[3];
    *(s64 *)&r.w[0] = *(s64 *)&info.w[0];
    EffectSetParamFloatVec_2e03e0(a0, &r, a2, a3);
}
