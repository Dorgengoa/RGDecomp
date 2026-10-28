/* rgp:protos */
#define RGP_SELF_SceneSoundMutePop_2f6670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN SceneSoundMutePop_2f6670 -- pop of the push in SceneSoundMutePush_2f6710.  The counter
   is read ONCE into a local: retail keeps it in $3 across both tests
   and the store sits in the second branch's delay slot. */

extern s32 D_00482768;
extern f32 D_0047EF70;
extern f32 D_0047EF74;
extern f32 D_0047EF78;
extern f32 D_0047EF7C;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void SceneSoundMutePop_2f6670(void)
{
    s32 n;
    u8 *o;

    n = D_00482768;
    if (n < 0) {
        return;
    }
    n = n - 1;
    D_00482768 = n;
    if (n < 0) {
        o = GetCurrentScene_1f5be0();
        GameSceneSoundSlot5SetVolume_1d0620(o, D_0047EF70);
        GameSceneSoundSetVolumeNow_1d0400(o, D_0047EF74);
        GameSceneSoundSlot4SetVolume_1d0630(o, D_0047EF78);
        GameSceneSoundSetVolumeScale_1d11d0(o, D_0047EF7C);
        SoundNoteListSetVolumeScale_1b4ab0(o + 0xB0A4, 1.0f);
        D_0047EF70 = 1.0f;
        D_0047EF74 = 1.0f;
        D_0047EF78 = 1.0f;
        D_0047EF7C = 1.0f;
    }
}
