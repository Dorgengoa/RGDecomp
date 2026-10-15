#include "types.h"

extern s32 WaitSema(s32);
extern void PadVibrationTick_1837a0(void);
extern void SoundSeqPlayersUpdateAll_1bb110(f32);
extern u8 *GetStaticScene_1c6c70(void);
extern void SoundCategoryFadeUpdate_1b5f20(u8 *, f32);

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
            u8 *q = GetStaticScene_1c6c70() + 0xAE20U;
            SoundCategoryFadeUpdate_1b5f20(q, 1.0f);
        }
        D_0047E250 = 1;
    }
}
