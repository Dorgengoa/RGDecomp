#include "types.h"
#pragma opt_common_subs off

s32 EffHdlAssignIndex_1a41e0(u8 *, s32);                        /* extern */
s32 VectorU32InsertN_1a4e80(u8 *, s32, s32, s32 *);              /* extern */

s32 EffHdlAlloc_1a3110(u8 *arg0, u8 *arg1) {
    s32 sp4C;
    s32 sp48;
    s32 var_16;

    if (!(!((*(s32 *)((u8 *)arg0 + 0x1C)) == 0))) {
        var_16 = (*(s32 *)((u8 *)arg0 + 0x10));
        EffHdlAssignIndex_1a41e0(arg1, var_16);
        sp4C = 0;
        VectorU32InsertN_1a4e80(arg0, (*(s32 *)((u8 *)arg0 + 0x8)) + ((*(s32 *)((u8 *)arg0 + 0x4)) * 4), 1, &sp4C);
        sp48 = (s32) (*(u16 *)((u8 *)arg1 + 0x2));
        VectorU32InsertN_1a4e80(arg0 + 0xC, (*(s32 *)((u8 *)arg0 + 0x14)) + ((*(s32 *)((u8 *)arg0 + 0x10)) * 4), 1, &sp48);
    } else {
        var_16 = (*(s32 *)((u8 *)((*(s32 *)((u8 *)arg0 + 0x20)) + ((*(s32 *)((u8 *)arg0 + 0x1C)) * 4)) - 0x4));
        EffHdlAssignIndex_1a41e0(arg1, var_16);
        (*(s32 *)((u8 *)arg0 + 0x1C)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x1C)) - 1);
        *(s32 *)((*(u8 **)((u8 *)arg0 + 0x14)) + (var_16 * 4)) = (s32) (*(u16 *)((u8 *)arg1 + 0x2));
    }
    return (*(s32 *)((u8 *)arg0 + 0x8)) + (var_16 * 4);
}
