/* rgp:protos */
#define RGP_SELF_MesWinCalcPos_2710b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x40];
    s32 unk40;
    s32 unk44;
    f32 unk48;
    f32 unk4C;
    u8 pad50[0x54 - 0x50];
    s16 unk54;
    s16 unk56;
} Obj0Arg0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D470;

void MesWinCalcPos_2710b0(Obj0Arg0 *arg0)
{
    s32 h;
    s32 a;
    s32 b;

    h = GetDrawCtx_15de80();
    if (h == 0) {
        return;
    }
    a = DrawEnvGetWidth_1451e0(h);
    b = DrawEnvGetHeight_1451d0(h);
    if (((signed char)MesWinGetFixedPos_272b60(arg0)) == 0) {
        arg0->unk40 = LerpOffsetMaybe_2726a0(0.0f, a, arg0->unk54, arg0->unk48);
        arg0->unk44 = LerpOffsetMaybe_2726a0(0.0f, b, arg0->unk56, arg0->unk4C);
        arg0->unk44 += 8;
    } else {
        arg0->unk40 = LerpOffsetMaybe_2726a0(0.0f, a, arg0->unk54, 0.5f);
        arg0->unk44 = LerpOffsetMaybe_2726a0(0.0f, b, arg0->unk56, D_0047D470);
        if (arg0->unk56 < 30) {
            arg0->unk44 += 8;
            arg0->unk44 -= 13;
        } else {
            arg0->unk44 += 8;
            arg0->unk44 += 4;
        }
    }
}
