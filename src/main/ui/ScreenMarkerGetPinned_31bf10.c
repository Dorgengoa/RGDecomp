#include "types.h"

typedef struct Tbl_FUN_0031bf10 {
    u8 pad000[0x120];
    s8 t[1];
} Tbl_FUN_0031bf10;

s32 ScreenMarkerGetPinned_31bf10(Tbl_FUN_0031bf10 *o, s32 i)
{
    if (i >= 0x20) i = 0x1F;
    return o->t[i];
}
