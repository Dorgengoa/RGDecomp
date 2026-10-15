#include "types.h"
#pragma opt_loop_invariants off
#pragma opt_propagation off

typedef struct { s32 a; s32 b; u8 *node; s32 d; } Ent_159e90;

s32 TexGroupCalcFreeVram_159e90(void *arg0, s32 arg1) {
    s32 eight;
    u8 *var_9;
    s32 var_8;
    s32 var_7;
    s32 var_6;
    s32 var_5;

    if ((arg1 < 0) || (arg1 >= *(s32 *)((u8 *)arg0 + 0xC))) return 0;
    var_9 = *(u8**)(*(u8 **)((u8*)arg0+0x1c)+arg1*16+8);
    var_8 = *(s32 *)((u8 *)arg0 + 0);
    var_7 = *(s32 *)((u8 *)arg0 + 0x14) - *(s32 *)((u8 *)arg0 + 0x10);
    eight = 8;
    while (var_9 != NULL) {
        var_6 = 0;
        if ((*(s16 *)(var_9 + 0x36) == 0) && (*(s16 *)(var_9 + 6) == eight) && (*(s32 *)(var_9 + 0x50) != 0)) {
            var_5 = 1;
            var_6 = *(u16 *)(var_9 + 0x28) * 4;
        } else {
            var_5 = 0;
        }
        if (var_5 != 0 && var_6 <= var_7) {
            var_7 -= var_6;
        } else {
            var_8 += *(u16 *)(var_9 + 0x28);
        }
        if (*(s16 *)(var_9 + 6) < 9) {
            var_8 += 4;
        }
        var_9 = *(u8 **)(var_9 + 0x64);
    }
    return *(s32 *)((u8 *)arg0 + 4) - var_8;
}
