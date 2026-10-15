#include "types.h"

typedef struct Big_FUN_00273c20 {
    u8 pad[0x1D74];
    s16 arr[0x14];   /* +0x1D74, 20 entries indexed by arg1 */
} Big_FUN_00273c20;

void MesWinAddLineWidth_273c20(Big_FUN_00273c20 *arg0, s32 arg1, s64 arg2)
{
    s16 *p;

    if (arg2 < 0 || arg1 < 0 || arg1 >= 0x14) {
        return;
    }
    arg0->arr[arg1] += (s16)arg2;
}
