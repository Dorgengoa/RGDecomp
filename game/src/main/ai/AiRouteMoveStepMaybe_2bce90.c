/* rgp:protos */
#define RGP_SELF_AiRouteMoveStepMaybe_2bce90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec { f32 x, y, z, w; } Vec;
typedef struct Obj {
    u8 pad0[0x250];
    s8 unk250;
    u8 pad251[0xF];
    s8 unk260;
    u8 pad261[0x2B];
    s32 unk28C;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D5D0;

void AiRouteMoveStepMaybe_2bce90(Obj *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6) {
    Vec spE0 __attribute__((aligned(16)));
    Vec spD0 __attribute__((aligned(16)));
    Vec spC0 __attribute__((aligned(16)));
    Vec spB0 __attribute__((aligned(16)));
    Vec spA0 __attribute__((aligned(16)));
    Vec sp90 __attribute__((aligned(16)));
    f32 spd;
    f32 dy;
    f32 r;
    f32 a;
    f32 b;
    s32 tgt;
    s32 other;

    other = arg3;
    if (arg1 == NULL || (tgt = *arg1) == 0) {
        return;
    }
    VecCopy_1cbe30(&spC0, arg2);
    spd = AiGetApproachMarginMaybe_2c0fc0(arg0);
    if (other != 0 && ((short)CharaGetActionMode_213850(other)) == 7) {
        spd *= D_0047D5D0;
    }
    if (arg0->unk260 != 0 && arg6 < 62500 && arg0->unk250 < 3) {
        spd *= 0.5f;
        other = AiRouteCalcDirMaybe_2bd2c0(arg0, tgt, arg2, &spE0, spd, arg6 * arg6);
        VecCopy_1cbe30(&spD0, arg2);
    } else {
        spd = AiRouteAvoidCharasMaybe_2bd800(arg0, arg1, &spD0, &spE0, arg2, spd, arg6);
        if (arg4 != 0) {
            AiRouteDetourCameraLineMaybe_2bd4f0(arg0, arg1, &spD0, &spE0, spd);
        }
    }
    AiClimbOrJumpWall_2be720(arg0, arg1, &spD0, arg5);
    if (other != 0) {
        CharaGetPos_2388a0(other, &spB0);
        CharaGetVelocity_238890(other, &spA0);
        CharaGetPos_2388a0(tgt, &sp90);
        dy = spB0.y - sp90.y;
        dy = (dy < 0.0f) ? -dy : dy;
        if (dy < 40.0f) {
            r = (CharaGetCollRadius_2386a0(other) + (AiGetKeepDistanceMaybe_2c0f90(arg0) + CharaGetCollRadius_2386a0(tgt))) *
                (CharaGetCollRadius_2386a0(other) + (AiGetKeepDistanceMaybe_2c0f90(arg0) + CharaGetCollRadius_2386a0(tgt)));
            if (VecDistSqXZ_1cb390(&spB0, &sp90) < r && VecLengthSqXZ_1cb450(&spA0, 0) < 4.0f) {
                arg0->unk28C = 2;
            }
        }
    }
    AiMoveDispatch_2be5f0(arg0, arg1, &spD0, &spE0, spd);
}
