#include "types.h"

typedef struct Tbl_FUN_0031e5a0 {
    u8 pad000[0x210];
    s8 t[1];
} Tbl_FUN_0031e5a0;

s32 HpGaugeGetHop_31e5a0(Tbl_FUN_0031e5a0 *o, s32 i)
{
    if (i >= 0x10) i = 0xF;
    return o->t[i];
}
