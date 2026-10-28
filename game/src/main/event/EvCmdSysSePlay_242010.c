/* rgp:protos */
#define RGP_SELF_EvCmdSysSePlay_242010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdSysSePlay_242010(void *rgp_a0)
{
    s32 m;

    m = ScriptGetInt_2490f0((void *)rgp_a0);
    switch (m) {
    case 0:
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 0, 1.0f);
        return 1;
    case 1:
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 6, 0, 1.0f);
        return 1;
    case 2:
        return 1;
    case 3:
        return 1;
    }
    return 0;
}
