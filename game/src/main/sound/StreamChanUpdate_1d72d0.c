/* rgp:protos */
#define RGP_SELF_StreamChanUpdate_1d72d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T1d72d0 {
    u8 pad0[0x80];
    s16 x80;
    u8 pad82[2];
    f32 x84;
    f32 x88;
    f32 x8C;
    f32 x90;
    u8 pad94[0xAC - 0x94];
    u8 xAC[4];
} T1d72d0;

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

void StreamChanUpdate_1d72d0(T1d72d0 *arg0, f32 arg1)
{
    s32 r;
    s32 t;
    f32 f;

    if (arg0->x80 < 0) {
        return;
    }
    if (((unsigned char)StreamChanIsSaveResumeReq_1d7240(arg0)) != 0) {
        StreamChanSetSaveResumeReq_1d70b0(arg0, 0);
        if (StreamPlayAllowedMaybe_2f5210() != 0) {
            SoundStreamSlotGetResumePoint_1bd020(arg0->x80, arg0->xAC);
        }
    }
    if (((unsigned char)StreamChanIsPauseReq_1d7270(arg0)) != 0) {
        StreamChanSetPauseReq_1d7140(arg0, 0);
        if (((unsigned char)StreamChanIsPlaying_1d71f0(arg0)) != 0) {
            if (StreamPlayAllowedMaybe_2f5210() != 0) {
                SoundStreamSlotPause_1bcb20(arg0->x80);
            }
            StreamChanSetPlaying_1d7020(arg0, 0);
        }
    }
    if (((unsigned char)StreamChanIsStopReq_1d7260(arg0)) != 0) {
        StreamChanSetStopReq_1d7110(arg0, 0);
        if (((unsigned char)StreamChanIsActive_1d7210(arg0)) != 0) {
            if (StreamPlayAllowedMaybe_2f5210() != 0) {
                SoundStreamSlotQueueStop_1bcd40(arg0->x80);
            }
            StreamChanSetActive_1d7050(arg0, 0);
        }
    }
    if (((unsigned char)StreamChanIsOpenReq_1d7290(arg0)) != 0) {
        StreamChanSetOpenReq_1d71a0(arg0, 0);
        r = 0;
        if (StreamPlayAllowedMaybe_2f5210() != 0) {
            if (((unsigned char)StreamChanIsLoop_1d7250(arg0)) != 0) {
                r = SoundStreamSlotOpenLoop_1bce80(arg0->x80, arg0);
            } else {
                r = SoundStreamSlotOpenOnce_1bcf10(arg0->x80, arg0);
            }
        }
        StreamChanSetActive_1d7050(arg0, r >= 0);
    }
    if (((unsigned char)StreamChanIsRestoreResumeReq_1d7230(arg0)) != 0) {
        StreamChanSetRestoreResumeReq_1d7080(arg0, 0);
        if (StreamPlayAllowedMaybe_2f5210() != 0) {
            SoundStreamSlotRestoreResumePoint_1bcfa0(arg0->x80, arg0->xAC);
        }
    }
    if (((unsigned char)StreamChanIsResumeReq_1d7280(arg0)) != 0) {
        t = SoundStreamSlotQueryState_1bd210(((short)StreamChanGetSlotId_1d72c0(arg0)));
        if (t != -1 && t != 3 && t != 4) {
            StreamChanSetResumeReq_1d7170(arg0, 0);
            if (((unsigned char)StreamChanIsActive_1d7210(arg0)) != 0) {
                if (StreamPlayAllowedMaybe_2f5210() != 0) {
                    SoundStreamSlotResume_1bcc30(arg0->x80);
                }
                StreamChanSetPlaying_1d7020(arg0, 1);
            }
        }
    }
    if (arg0->x90 != 0.0f) {
        arg0->x84 = arg0->x84 + arg0->x90 * arg1;
        if (!(arg0->x90 <= 0.0f)) {
            if (!(arg0->x84 <= arg0->x8C)) {
                arg0->x84 = arg0->x8C;
                arg0->x90 = 0.0f;
            }
        } else {
            if (arg0->x84 < arg0->x8C) {
                arg0->x84 = arg0->x8C;
                arg0->x90 = 0.0f;
            }
        }
    }
    if (((unsigned char)StreamChanIsMuted_1d71d0(arg0)) != 0) {
        f = 0.0f;
    } else {
        f = arg0->x84 * arg0->x88;
    }
    SoundStreamSlotSetVolume_1bca60(arg0->x80, f);
}
