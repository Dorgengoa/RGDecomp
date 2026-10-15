#include "types.h"
#pragma opt_propagation off
typedef struct A2 { u8 pad[0x38]; u16 x38; } A2;
extern void NumPutPadOutput_1a4610(s32 arg0, volatile s32 sp5C, A2 *arg2, s32 arg3, s8 *arg4, s32 arg5, void *arg6, s32 arg7);
extern s32 NumPutFormatU64_1a4970(A2 *arg0, s32 arg1, void *arg2);

void NumPutHex_1a4370(s32 arg0, volatile s32 sp5C, A2 *arg2, s32 arg3, s32 arg4)
{
    s8 buf[2];
    s8 sp60[0x28];
    s32 n;
    s8 *p;
    s8 **pp;

    pp = &p;
    *pp = buf;
    n = 0;
    if ((u16)(arg2->x38 & 0x200) != 0) {
        p[0] = 0x30;
        if ((u16)(arg2->x38 & 0x4000) != 0) {
            p[1] = 0x58;
        } else {
            p[1] = 0x78;
        }
        n += 2;
    }
    NumPutPadOutput_1a4610(arg0, sp5C, arg2, arg3, buf, n, sp60, NumPutFormatU64_1a4970(arg2, arg4, sp60));
}
