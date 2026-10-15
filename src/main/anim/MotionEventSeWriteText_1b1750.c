#include "types.h"

extern s32 OstreamWriteCStr_1a1dd0(s32, void *);
extern void OstreamWriteInt_1a1f60(s32, s32);
extern void MotionEventWriteHeaderText_1b1850(void *, void *, s32);
extern u8 D_0045A9D0[];
extern u8 D_0045A9E0[];
extern u8 D_0045A9E8[];
extern u8 D_0045AA28[];
extern u8 D_0045AA30[];
extern u8 D_0045AA38[];

struct S001B1750 {
    u8 pad000[0x28];
    s32 unk28;
    u8 pad02C[4];
    s8 unk30;
};

void MotionEventSeWriteText_1b1750(struct S001B1750 *arg0, s32 arg1)
{
    MotionEventWriteHeaderText_1b1850(arg0, D_0045AA28, arg1);
    OstreamWriteInt_1a1f60(OstreamWriteCStr_1a1dd0(arg1 + 0x18, D_0045AA30), arg0->unk28);
    if (arg0->unk30 != 0) {
        OstreamWriteCStr_1a1dd0(OstreamWriteCStr_1a1dd0(OstreamWriteCStr_1a1dd0(arg1 + 0x18, D_0045AA38), &arg0->unk30), D_0045A9D0);
    }
    OstreamWriteCStr_1a1dd0(arg1 + 0x18, D_0045A9E0);
    OstreamWriteCStr_1a1dd0(arg1 + 0x18, D_0045A9E8);
}
