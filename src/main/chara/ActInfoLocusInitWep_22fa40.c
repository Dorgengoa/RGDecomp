#include "types.h"

typedef struct S0022fa40 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s8 unk14;
} S0022fa40;

void ActInfoLocusInitWep_22fa40(S0022fa40 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    arg0->unk0 = 0;
    arg0->unk14 = -1;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    if (arg1 == 0 || arg2 < 0 || arg3 == 0 || arg4 == 0) {
        return;
    }
    {
        arg0->unk0 = arg1;
        arg0->unk14 = arg2;
        arg0->unkC = arg3;
        arg0->unk10 = arg4;
    }
}
