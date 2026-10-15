#include "types.h"

/* beql INTO the arm = a compiled switch; the compare chain is emitted in
   REVERSE source order, so the source case order is the reverse of the
   chain: 0..8, 0xF, 0x10, 0x11, then the 9..0xD group, then 0x1F, 0x20, 0x12.
   The arm blocks are laid out in that same (source) order, which confirms it.
   dsll32/dsra32 ..,24 on the switch operand = an s8 parameter. */

extern void *GetCurrentScene_1f5be0(void);
extern void CameraSetDefaultParams_309260(void *, void *);
extern void CameraAimFromLookAt_309180(void *, void *);
extern void CameraResetParams_3090a0(void *, void *);
extern void CameraModeSetupNop_309090(void *, void *);
extern void CameraModeSetupTwoTarget_309050(void *, void *);
extern void CameraModeSetupTrack_309000(void *, void *);
extern void CameraModeSetupNop_308ff0(void *, void *);
extern void CameraModeSetupNop_308fe0(void *, void *);
extern void CameraModeSetupNop_308fd0(void *, void *);
extern void CameraModeSetupInsectBattle_308e40(void *, void *);
extern void CameraModeSetupNop_308e30(void *, void *);
extern void CameraModeSetupMaybe_308df0(void *, void *);
extern void CameraModeSetupDebugFree_308f00(void *, void *);
extern void CameraModeSetupLockTargetMaybe_308ae0(void *, void *);
extern void CameraFollowParamsSetDefault_308d10(void *, void *);
extern void CameraModeSetupZoom_308a60(void *, void *);
extern void CameraShakeStop_305950(void *);

void CameraApplyMode_309490(void *a, s8 op)
{
    void *r;

    r = GetCurrentScene_1f5be0();
    switch (op) {
    case 0:
        CameraSetDefaultParams_309260(a, r);
        break;
    case 1:
        CameraAimFromLookAt_309180(a, r);
        break;
    case 2:
        CameraResetParams_3090a0(a, r);
        break;
    case 3:
        CameraModeSetupNop_309090(a, r);
        break;
    case 4:
        CameraModeSetupTwoTarget_309050(a, r);
        break;
    case 5:
        CameraModeSetupTrack_309000(a, r);
        break;
    case 6:
        CameraModeSetupNop_308ff0(a, r);
        break;
    case 7:
        CameraModeSetupNop_308fe0(a, r);
        break;
    case 8:
        CameraModeSetupNop_308fd0(a, r);
        break;
    case 0xF:
        CameraModeSetupInsectBattle_308e40(a, r);
        break;
    case 0x10:
        CameraModeSetupNop_308e30(a, r);
        break;
    case 0x11:
        CameraModeSetupMaybe_308df0(a, r);
        break;
    case 9:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
        CameraModeSetupDebugFree_308f00(a, r);
        break;
    case 0x1F:
        CameraModeSetupLockTargetMaybe_308ae0(a, r);
        break;
    case 0x20:
        CameraFollowParamsSetDefault_308d10(a, r);
        break;
    case 0x12:
        CameraModeSetupZoom_308a60(a, r);
        break;
    }
    CameraShakeStop_305950(a);
}
