/* rg-override: replaces game/src/main/sound/SoundIopInit_1b7160.c sha256 05633473a122eca9ef1659b3e583c7556d989ac2fa36ec63d19d1184308de457
 * why: native audio (docs/NATIVE-AUDIO.md, PLAN.md D9): the sound driver init also
 *      starts the native engine (rg_audio_game_init: bus volumes, reverb, effects as the
 *      driver init below sets them) unless RG_AUDIO=hle.  The original IOP-side init
 *      (sceSdRemote init, master volumes, SK settings) runs only while the HLE still
 *      serves something: RG_AUDIO=hle/compare, or RG_AUDIO_PCM/RG_AUDIO_MOVIE=hle. */
/* rgp:protos */
#define RGP_SELF_SoundIopInit_1b7160 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_audio.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_0047E1F0;
extern u8 D_0049D540[];

void SoundIopInit_1b7160(void)
{
    s32 i;

    SoundInitStub_165600();
    if (rg_audio_hle_needed()) {
        D_0047E1F0 = SdRemoteInitMasterVolume_165608(5);
        SoundIopSendCmdG0S2_1656b8(0, 0x8F, 0x880);
        SoundIopSendCmdG0S2_1656b8(3, 0x83, 0x105, 0, 0);
        SoundIopSendCmdG0S2_1656b8(3, 0x82, 0);
        SoundIopSendCmdG0S2_1656b8(3, 0x80, 0x7F, 0x7F);
    }

    for (i = 0; i < 0x27; i++) {
        D_0049D540[i] = 0;
    }
    if (rg_audio_mode() != RG_AUDIO_HLE) {
        rg_audio_game_init();
    }
}
