#include "types.h"

/* gp-relative scalar guard; retail FALLS THROUGH into the body when the value
   is non-negative.  SoundNextPlayHandle_1b81c0 takes no argument (nothing writes $4 between
   the previous call and it) -- m2c's surplus argument is a leftover register.
   The 1.0f is built with lui/mtc1 => write the literal. */

extern s32 D_00482A4C;

extern s32 GetCurrentScene_1f5be0(void);
extern s32 GameSceneSoundSlot5GetHandle_1d0790(s32 a);
extern s32 SoundNextPlayHandle_1b81c0(void);
extern void SoundPlayScaledVolume_1b9520(s32 a, s32 b, s32 c, f32 t);
extern void TargetMngClearTarget_313c00(void);

void TargetMngCancel_313a70(void)
{
    s32 a;
    s32 h;
    s32 c;

    if (D_00482A4C >= 0) {
        a = GetCurrentScene_1f5be0();
        h = GameSceneSoundSlot5GetHandle_1d0790(a);
        c = SoundNextPlayHandle_1b81c0();
        SoundPlayScaledVolume_1b9520(h, 5, c, 1.0f);
    }
    TargetMngClearTarget_313c00();
}
