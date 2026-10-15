#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

s32 MemStackNew_14e1b0(s32, s32);
s32 S16ArrayGetData_1ce1c0(void *);
s32 S16ArrayAlloc_1ce1d0(void *, s32, s32);
s32 S16ArrayReset_1ce240(void *);
s32 LoaderUnitReset_1ce370(s32);

void LoaderInit_1cde60(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i;

    (*(s32 *)((u8 *)(arg0) + 0x10)) = 0;
    (*(s32 *)((u8 *)(arg0) + 0x14)) = 0;
    (*(s32 *)((u8 *)(arg0) + 0x18)) = 0;
    (*(s32 *)((u8 *)(arg0) + 0x1C)) = 0;
    S16ArrayReset_1ce240((u8 *)arg0 + 0x20);
    S16ArrayReset_1ce240((u8 *)arg0 + 0x28);
    S16ArrayReset_1ce240((u8 *)arg0 + 0x30);
    if (arg5 == 0) {
        return;
    }
    (*(s32 *)((u8 *)(arg0) + 0x10)) = MemStackNew_14e1b0(arg1 * 0x98, arg5);
    (*(s32 *)((u8 *)(arg0) + 0x14)) = arg1;
    S16ArrayAlloc_1ce1d0((u8 *)arg0 + 0x20, arg2, arg5);
    S16ArrayAlloc_1ce1d0((u8 *)arg0 + 0x28, arg3, arg5);
    S16ArrayAlloc_1ce1d0((u8 *)arg0 + 0x30, arg4, arg5);
    if ((*(s32 *)((u8 *)(arg0) + 0x10)) == 0 || S16ArrayGetData_1ce1c0((u8 *)arg0 + 0x20) == 0 || S16ArrayGetData_1ce1c0((u8 *)arg0 + 0x28) == 0 || S16ArrayGetData_1ce1c0((u8 *)arg0 + 0x30) == 0) {
        (*(s32 *)((u8 *)(arg0) + 0x10)) = 0;
        (*(s32 *)((u8 *)(arg0) + 0x14)) = 0;
        S16ArrayReset_1ce240((u8 *)arg0 + 0x20);
        S16ArrayReset_1ce240((u8 *)arg0 + 0x28);
        S16ArrayReset_1ce240((u8 *)arg0 + 0x30);
    } else {
        for (i = 0; i < (*(s32 *)((u8 *)(arg0) + 0x14)); i++) {
            LoaderUnitReset_1ce370((*(s32 *)((u8 *)(arg0) + 0x10)) + i * 0x98);
        }
    }
}
