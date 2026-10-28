/* rgp:protos */
#define RGP_SELF_OptionsApply_1fe350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Cfg1fe350 {
    u8 pad00[0x12];
    s16 m12;
    s16 m14;
    s16 m16;
    s16 m18;
    s16 m1A;
} Cfg1fe350;

typedef struct A1fe350 {
    u8 pad00[0xC];
    Cfg1fe350 *m0C;
} A1fe350;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void OptionsApply_1fe350(void)
{
    A1fe350 *a;
    void *b;
    void *c;

    a = ((A1fe350 *)GetGameData_1fede0());
    b = GetStreamMgr_207ea0();
    c = GetCurrentScene_1f5be0();
    SoundSetOutputMode_1bb3e0(a->m0C->m12 == 0);
    SoundStreamSetOutputMode_1bc6e0(a->m0C->m12 == 0);
    StreamMgrSetChanGain_1d63f0(b, 0, (f32)a->m0C->m14 / 10.0f);
    GameSceneSoundSetOptionVolume_1d11f0(c, (f32)a->m0C->m16 / 10.0f);
    StreamMgrSetChanGain_1d63f0(b, 1, (f32)a->m0C->m18 / 10.0f);
    StreamMgrSetChanGain_1d63f0(b, 2, (f32)a->m0C->m18 / 10.0f);
    CameraSetOptionFlag_309cf0((a->m0C->m1A & 1) == 1);
}
