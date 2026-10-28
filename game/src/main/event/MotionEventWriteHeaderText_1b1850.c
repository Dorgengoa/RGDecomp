/* rgp:protos */
#define RGP_SELF_MotionEventWriteHeaderText_1b1850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[4];
    s8 *unk4;
    u8 pad8[8];
    u8 unk10;
    u8 pad11[3];
    s8 *unk14;
    u8 pad18[4];
    f32 unk1C;
    f32 unk20;
} T001B1850;

/*rgp*/
/*rgp*/
extern s8 D_0045A9D0[0x10];
extern s8 D_0045A9D8[0x10];
extern s8 D_0045A9E0[0x10];
extern s8 D_0045AA38[0x10];
extern s8 D_0045AA40[0x10];
extern s8 D_0045AA48[0x10];
extern s8 D_0045AA50[0x10];
extern s8 D_0045AA60[0x10];
extern s8 D_0045AA70[0x10];

void MotionEventWriteHeaderText_1b1850(T001B1850 *arg0, s8 *arg1, s32 arg2)
{
    f32 f;
    s8 *s;

    OstreamWriteCStr_1a1dd0(((s32)OstreamWriteCStr_1a1dd0(((s32)OstreamWriteCStr_1a1dd0(arg2 + 0x18, D_0045AA40)), arg1)), D_0045A9D0);
    if (arg0->unk10 == 0) {
        s = arg0->unk14 != NULL ? arg0->unk14 : NULL;
        if (s != NULL) {
            OstreamWriteCStr_1a1dd0(((s32)OstreamWriteCStr_1a1dd0(((s32)OstreamWriteCStr_1a1dd0(arg2 + 0x18, D_0045AA38)), s)), D_0045A9D0);
        } else {
            OstreamWriteCStr_1a1dd0(arg2 + 0x18, D_0045AA48);
        }
        OstreamWriteFloat_1b25c0(((s32)OstreamWriteCStr_1a1dd0(arg2 + 0x18, D_0045A9D8)), arg0->unk1C);
        f = arg0->unk20;
        if (!(f < 0.0f)) {
            OstreamWriteFloat_1b25c0(((s32)OstreamWriteCStr_1a1dd0(arg2 + 0x18, D_0045A9D8)), f);
        }
    } else {
        OstreamWriteCStr_1a1dd0(arg2 + 0x18, D_0045AA50);
    }
    OstreamWriteCStr_1a1dd0(arg2 + 0x18, D_0045A9E0);
    if (arg0->unk4 != NULL && *arg0->unk4 != 0) {
        OstreamWriteCStr_1a1dd0(((s32)OstreamWriteCStr_1a1dd0(((s32)OstreamWriteCStr_1a1dd0(arg2 + 0x18, D_0045AA60)), *(s8 **)((u8 *)arg0 + 4))), D_0045AA70);
    }
}
