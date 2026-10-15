#include "types.h"

void MinimapWorldToMapXZ_32c280(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3)
{
    f32 val0;
    f32 val8;
    f32 denom;

    val8 = *(f32 *)((u8 *)arg0 + 0x8) - fparg2;
    val0 = *(f32 *)((u8 *)arg0 + 0x0) - fparg1;
    denom = fparg0 * fparg3;
    val0 = val0 / denom;
    val8 = val8 / denom;
    *(f32 *)((u8 *)arg0 + 0x0) = val0;
    *(s32 *)((u8 *)arg0 + 0x4) = 0;
    *(f32 *)((u8 *)arg0 + 0x8) = val8;
}
