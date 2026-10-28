/* rgp:protos */
#define RGP_SELF_EventCueStep_2491b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 type;
    s32 id;
    s32 v;
    s32 w;
} Ev;


typedef struct {
    u8 pad[0xC];
    struct { u8 pad[0x1C]; s16 f1C; } *mC;
} Ctx1fede0;

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
extern s32 *gEventContext;

void EventCueStep_2491b0(u8 *arg0, s32 arg1)
{
    f32 f;
    s32 h;
    s32 n;
    s16 on;
    s32 i;
        Ev e __attribute__((aligned(16)));
    s32 p;
    f32 g;
    s32 w;

    f = GameSceneGetTimeStep_1ceba0(arg1);
    h = ((s32)GetStreamMgr_207ea0());
    StreamMgrUpdate_1d6940(h, f);
    GameSceneSoundUpdate_1d0860(arg1);
    on = ((Ctx1fede0 *)GetGameData_1fede0())->mC->f1C;
    n = *(s32 *)(arg0 + 0x490);
    for (i = 0; i < n; i++) {
                e = ((Ev *)*(u8 **)(arg0 + 0x494))[i];
        if (*(s32 *)(arg0 + 0x49C) != e.id) continue;
        switch (e.type) {
        case 0:
            if (on != 0) {
                MesWinOwnerStartLabel_24eae0(arg0 + 0x420, e.v, 0);
            }
            break;
        case 1:
            ScreenFadeIn_1cf740(arg1, e.v);
            break;
        case 2:
            ScreenFadeOutColor_1cf730(arg1, e.v, 0.0f, 0.0f, 0.0f);
            break;
        case 3:
            if (on != 0) {
                p = *(s32 *)(arg0 + 0x42C);
                if (p != 0) {
                    MesWinAdvance_2768f0(p);
                }
            }
            break;
        case 4:
            if (on != 0) {
                MesWinOwnerClose_24eab0(arg0 + 0x420);
            }
            break;
        case 5:
            BgmPlayNowMaybe_207530(e.v, e.w != 0);
            break;
        case 6:
            StreamMgrPlayChan_1d6670(h, 0, 0.0f);
            StreamMgrSetChanVolumeFade_1d63a0(h, 0, 0, *(f32 *)&e.v);
            break;
        case 7:
            BgmPlayTrack_2075e0(-1, 1);
            break;
        case 8:
            StreamMgrSetChanVolumeFade_1d63a0(h, 0, e.w, *(f32 *)&e.v);
            break;
        case 9:
            g = *(f32 *)&e.v;
            GameSceneSoundSetVolumeNow_1d0400(*gEventContext, g);
            GameSceneSoundSlot4SetVolume_1d0630(*gEventContext, g);
            break;
        case 10:
            g = *(f32 *)&e.v;
            w = e.w;
            GameSceneSoundFadeVolume_1d0370(*gEventContext, w, g);
            GameSceneSoundSlot4FadeTo_1d0610(*gEventContext, w, g);
            break;
        }
    }
    EventVoiceTick_24f720(arg0 + 0x420);
    *(s32 *)(arg0 + 0x49C) = *(s32 *)(arg0 + 0x49C) + 1;
}
