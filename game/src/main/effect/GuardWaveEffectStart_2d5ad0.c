/* rgp:protos */
#define RGP_SELF_GuardWaveEffectStart_2d5ad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern f32 D_0047D1E8 __attribute__((section(".sdata")));

void GuardWaveEffectStart_2d5ad0(void *arg0, s32 arg1, s16 arg2, s16 arg3, f32 fparg0)
{
    s32 temp_3;
    s32 var_7;
    u8 *temp_6;

    *(s32 *)((u8 *)arg0 + 0) = 1;
    *(f32 *)((u8 *)arg0 + 0x38) = fparg0;
    *(f32 *)((u8 *)arg0 + 0x38) = 40.0f;
    sceVu0CopyVector((u8 *)arg0 + 0x10, (void *)arg1);
    var_7 = 0;
    *(u32 *)((u8 *)arg0 + 0x1C) = 0x3F800000;
    do {
        temp_6 = (u8 *)arg0 + (var_7 * 4);
        temp_3 = var_7 * 2;
        var_7 += 1;
        *(f32 *)(temp_6 + 0x20) = D_0047D1E8;
        *(f32 *)(temp_6 + 0x28) = D_0047D1E8;
        *(u16 *)((u8 *)arg0 + temp_3 + 0x34) = 1;
    } while (var_7 < 2);
    *(u16 *)((u8 *)arg0 + 0x30) = 0;
    *(s16 *)((u8 *)arg0 + 0x32) = 6;
    *(s16 *)((u8 *)arg0 + 0x40) = arg2;
    *(s16 *)((u8 *)arg0 + 0x42) = arg3;
}
