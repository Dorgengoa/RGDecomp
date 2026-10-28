/* rgp:protos */
#define RGP_SELF_CameraApplyMode_309490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* beql INTO the arm = a compiled switch; the compare chain is emitted in
   REVERSE source order, so the source case order is the reverse of the
   chain: 0..8, 0xF, 0x10, 0x11, then the 9..0xD group, then 0x1F, 0x20, 0x12.
   The arm blocks are laid out in that same (source) order, which confirms it.
   dsll32/dsra32 ..,24 on the switch operand = an s8 parameter. */

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void CameraApplyMode_309490(void *a, s8 op)
{
    void *r;

    r = GetCurrentScene_1f5be0();
    switch (op) {
    case 0:
        CameraSetDefaultParams_309260(a);
        break;
    case 1:
        CameraAimFromLookAt_309180(a);
        break;
    case 2:
        CameraResetParams_3090a0(a);
        break;
    case 3:
        CameraModeSetupNop_309090();
        break;
    case 4:
        CameraModeSetupTwoTarget_309050(a);
        break;
    case 5:
        CameraModeSetupTrack_309000(a, r, 0, 0);
        break;
    case 6:
        CameraModeSetupNop_308ff0();
        break;
    case 7:
        CameraModeSetupNop_308fe0();
        break;
    case 8:
        CameraModeSetupNop_308fd0();
        break;
    case 0xF:
        CameraModeSetupInsectBattle_308e40(a);
        break;
    case 0x10:
        CameraModeSetupNop_308e30();
        break;
    case 0x11:
        CameraModeSetupMaybe_308df0(a);
        break;
    case 9:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
        CameraModeSetupDebugFree_308f00(a);
        break;
    case 0x1F:
        CameraModeSetupLockTargetMaybe_308ae0(a, r);
        break;
    case 0x20:
        CameraFollowParamsSetDefault_308d10();
        break;
    case 0x12:
        CameraModeSetupZoom_308a60(a);
        break;
    }
    CameraShakeStop_305950(a);
}
