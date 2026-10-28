/* rgp:protos */
#define RGP_SELF_InsectBattleMenuFrameLayoutMaybe_392250 1
#include "port/game_protos.h"
#line 1
/* PARK 3 bad, RIGHT LENGTH (was 70 vs 72). Two fixes banked: the three guards
   are ONE `||` chain ([[levers.d/or-guard-chain-layout]]) and InsectBattleMenuFrameNineSliceMaybe_393ac0
   takes FIVE arguments -- retail leaves $a1 = arg1 untouched from entry, so
   the draft was missing the second one. Residue: retail materialises
   `var_17 = arg6` as a REAL copy (`move s1,t2`) and compares the COPY;
   mwcc propagates and compares the incoming `$t2`, assigning s1 in the
   branch delay slot instead. NULL on that: if/else form, a volatile read,
   the inverted `!=` form, a pre-assigned `var_17 = 0x74` and `< 0`. */
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
/*rgp*/

void InsectBattleMenuFrameLayoutMaybe_392250(s32 arg0, s32 arg1, void *arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7)
{
    s32 var_17;
    s32 temp_16;

    var_17 = arg6;
    if (var_17 == -1) {
        var_17 = 0x74;
    }
    if (arg1 == 0 || arg2 == NULL || arg3 == NULL) {
        return;
    }
    temp_16 = arg4 << 5;
    InsectBattleMenuFrameNineSliceMaybe_393ac0(arg0, arg1, var_17, temp_16 + 8, 0);
    UiSpriteListFillColumnMaybe_3939e0(arg0, arg2, arg4, 0, (f32)(var_17 - 4), 32.0f);
    UiQuadSetByModeRelated_3934d0(arg0, arg3, var_17 - 8, temp_16, arg5, arg7);
    *(f32 *)((u8 *)arg2 + 0x14) = 2.0f;
    *(f32 *)((u8 *)arg2 + 0x60) = 2.0f;
    *(f32 *)((u8 *)arg2 + 0x18) = 2.0f;
    *(f32 *)((u8 *)arg2 + 0x64) = 2.0f;
    *(f32 *)((u8 *)arg3 + 0x14) = 4.0f;
    *(f32 *)((u8 *)arg3 + 0x60) = 4.0f;
    *(f32 *)((u8 *)arg3 + 0x18) = 4.0f;
    *(f32 *)((u8 *)arg3 + 0x64) = 4.0f;
}
