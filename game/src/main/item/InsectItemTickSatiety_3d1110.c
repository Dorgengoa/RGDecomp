/* rgp:protos */
#define RGP_SELF_InsectItemTickSatiety_3d1110 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
extern u8 D_0045B078[0x400];
extern u8 D_00465D80[0x400];
extern u8 D_00465D90[0x400];
extern s32 D_004838E8;

s32 InsectItemTickSatiety_3d1110(void *self, f32 f0)
{
    void *sub;

    if (D_004838E8 == 0) {
        return 0;
    }
    sub = *(void **)((u8 *)self + 0x18);
    if (*(s8 *)((u8 *)sub + 0x18) > 0) {
        *(f32 *)((u8 *)sub + 0x30) = *(f32 *)((u8 *)sub + 0x30) + f0;
        sub = *(void **)((u8 *)self + 0x18);
        if (!(*(f32 *)((u8 *)sub + 0x30) < (60.0f * *(const f32 *)D_00465D90 * *(const f32 *)D_0045B078) / (f32)*(const s32 *)D_00465D80)) {
            *(s8 *)((u8 *)sub + 0x18) = *(s8 *)((u8 *)sub + 0x18) - 1;
            *(f32 *)((u8 *)(*(void **)((u8 *)self + 0x18)) + 0x30) = 0.0f;
        }
    }
    return 1;
}
