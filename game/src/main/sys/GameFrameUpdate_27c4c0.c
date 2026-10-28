/* rgp:protos */
#define RGP_SELF_GameFrameUpdate_27c4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 0
#pragma schedule on

/*rgp*/                           /* extern */
/*rgp*/                           /* extern */
/*rgp*/                             /* extern */
/*rgp*/                                /* extern */
/*rgp*/                              /* extern */
/*rgp*/                                  /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                  /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                 /* extern */
extern u8 D_004B2570[0x400];
extern u8 D_004B27E0[0x400];

void GameFrameUpdate_27c4c0(void) {
    GameSceneTimeScaleUpdateCur_2f76f0();
    PadBindingsUpdateFromSysParams_2f75f0();
    Nop_207f80();
    if (((unsigned char)GetTaskListChanged_1f56c0()) != 0) {
        SetTaskListChanged_1f56b0(0);
        PadUpdateVibration_184250(&(*(s32 *)D_004B2570), 0);
        PadUpdate_1843a0(&(*(s32 *)D_004B2570));
    }
    if (((unsigned char)PadIsAnalogMode_184960(&(*(s32 *)D_004B2570))) == 0) {
    PauseRequest_2f65e0(4);
    } else if ((((unsigned char)IsPad2Enabled_2882c0()) != 0) && (((unsigned char)PadIsAnalogMode_184960(&(*(s32 *)D_004B27E0))) == 0)) {
        PauseRequest_2f65e0(5);
    } else if ((PadIsHeld_183a20(&(*(s32 *)D_004B2570), 0x100) == 0) && ((PadIsTriggered_1839f0(&(*(s32 *)D_004B2570), 0x800) != 0) || ((((unsigned char)IsPad2Enabled_2882c0()) != 0) && (PadIsHeld_183a20(&(*(s32 *)D_004B27E0), 0x100) == 0) && (PadIsTriggered_1839f0(&(*(s32 *)D_004B27E0), 0x800) != 0)))) {
        if (GetGameMode_1f59c0() == 0xB && EvtCurCanSkip_26a870() != 0) {
            PauseRequest_2f65e0(1);
        } else if (((unsigned char)SaveIsBusy_376b00()) == 0) {
            PauseRequest_2f65e0(0);
        }
    }
    PauseStepUpdate_2f5fb0();
    do {

    } while (GameModeDispatch_27c670() != 0);
    PauseOverlayDraw_2f5be0();
}
