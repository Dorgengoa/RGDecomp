#include "types.h"
#pragma opt_common_subs off
extern void VecAdd_1cbdc0(void *, void *, void *);
extern void MovCfgMoveItemEval_312640(s32, void *, f32, f32);

void NamedCompListSumVec_3123b0(void *arg0, void *arg1, f32 fparg0, f32 fparg1) {
    u8 sp60[0x10];
    s32 var_16;
    s32 var_19;

    *(s32 *)((u8 *)arg1 + 0) = 0;
    *(s32 *)((u8 *)arg1 + 4) = 0;
    *(s32 *)((u8 *)arg1 + 8) = 0;
    *(s32 *)((u8 *)arg1 + 0xC) = 0;
    var_16 = *(s32 *)((u8 *)arg0 + 4);
    if ((var_16 == 0) || (*(s32 *)((u8 *)arg0 + 8) <= 0)) {
        return;
    }
    for (var_19 = 0; var_19 < *(s32 *)((u8 *)arg0 + 8); var_19++, var_16 += 0x14) {
        MovCfgMoveItemEval_312640(var_16, sp60, fparg0, fparg1);
        VecAdd_1cbdc0(arg1, arg1, sp60);
    }
}
