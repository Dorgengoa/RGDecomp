/* rgp:protos */
#define RGP_SELF_SysTickThreadMain_1c33f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 WaitSema(s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00481554;
extern s32 D_0047E248;
extern s32 D_0047E250;

void SysTickThreadMain_1c33f0(void)
{
    while (D_0047E248 >= 0) {
        WaitSema(D_0047E248);
        PadVibrationTick_1837a0();
        if (D_00481554 != 0) {
            SoundSeqPlayersUpdateAll_1bb110(1.0f);
        }
        {
            u8 *q = ((u8 *)GetStaticScene_1c6c70()) + 0xAE20U;
            SoundCategoryFadeUpdate_1b5f20(q, 1.0f);
        }
        D_0047E250 = 1;
    }
}
