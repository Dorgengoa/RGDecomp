/* rgp:protos */
#define RGP_SELF_NumPutHex_1a4370 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
typedef struct A2 { u8 pad[0x38]; u16 x38; } A2;
/*rgp*/
/*rgp*/

void NumPutHex_1a4370(s32 arg0, volatile s32 sp5C, A2 *arg2, s32 arg3, s32 arg4)
{
    s8 buf[2];
    s8 sp60[0x28] __attribute__((aligned(16)));
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
    NumPutPadOutput_1a4610(arg0, sp5C, arg2, arg3, buf, n, sp60, NumPutFormatU64_1a4970(arg2, (unsigned long long)(arg4), sp60));
}
