/* rgp:protos */
#define RGP_SELF_RevelationBoardDrawSprite_34c170 1
#define RGP_SELF_RevelationBoardPktSetColorLerp_34ce10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 v;
} FArg;

/*rgp*/
/*rgp*/
extern void RevelationBoardPktSetColorLerp_34ce10(s32, s32, s32, s32, s32, s32, s32, s32, FArg);
extern s16 D_004539F0[];
extern s16 D_004539F2[];
extern s16 D_004539F4[];
extern s16 D_004539F6[];

void RevelationBoardDrawSprite_34c170(s32 a0, s32 arg1, s32 idx, s32 x, s32 y, s32 w, s32 h, s32 t3, FArg f)
{
    s32 x0;
    s32 y0;
    s32 dw;
    s32 dh;
    s32 u0, u2, u3, u4, u5, u6, u7;

    x0 = D_004539F0[idx * 4];
    y0 = D_004539F2[idx * 4];
    dw = D_004539F4[idx * 4];
    dh = D_004539F6[idx * 4];
    if (w < 0) {
        w = dw;
    }
    if (h < 0) {
        h = dh;
    }
    RevelationBoardPktSetColorLerp_34ce10(u0, arg1, u2, u3, u4, u5, u6, u7, f);
    GsPktSetUV_13ed60(arg1, x0, y0);
    GsPktSetXYZPixel_13f110(arg1, x, y, 0);
    GsPktSetUV_13ed60(arg1, x0 + dw, y0 + dh);
    GsPktSetXYZPixel_13f110(arg1, x + w, y + h, 0);
}
