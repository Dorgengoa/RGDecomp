#include "types.h"

extern s32 OstreamWriteCStr_1a1dd0(s32, void *);
extern void OstreamWriteInt_1a1f60(s32, s32);
extern void MotionEventWriteHeaderText_1b1850(void *, void *, s32);
extern u8 D_0045A9D0[];
extern u8 D_0045A9E0[];
extern u8 D_0045A9E8[];
extern u8 D_0045AA10[];
extern u8 D_0045AA18[];
extern u8 D_0045A9D8[];

struct S001B1750 {
    u8 pad000[0x28];
    s32 unk28;
    s32 unk2C;
    s8 unk30;
};

void MotionEventFootSeWriteText_1b16b0(struct S001B1750 *arg0, s32 arg1)
{
    s32 field;
    MotionEventWriteHeaderText_1b1850(arg0, D_0045AA10, arg1);
    OstreamWriteInt_1a1f60(OstreamWriteCStr_1a1dd0(arg1 + 0x18, D_0045AA18), arg0->unk28);
    field=arg0->unk2C;
    if(field>=0){OstreamWriteInt_1a1f60(OstreamWriteCStr_1a1dd0(arg1+0x18,D_0045A9D8),field);}
    OstreamWriteCStr_1a1dd0(arg1 + 0x18, D_0045A9E0);
    OstreamWriteCStr_1a1dd0(arg1 + 0x18, D_0045A9E8);
}
