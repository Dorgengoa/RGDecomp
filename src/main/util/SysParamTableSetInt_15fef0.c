#include "types.h"

/* Asymmetric guard pair, writing an 8-byte record at +0x10 whose second word
   is the OR of the last two arguments. */

typedef struct Slot8b {
    s32 a;             /* +0x00 */
    s32 b;             /* +0x04 */
} Slot8b;

typedef struct Owner10b {
    u8 pad000[0x10];
    Slot8b rec[1];     /* +0x10 */
} Owner10b;

s32 SysParamTableSetInt_15fef0(Owner10b *o, s32 index, s32 lo, s32 hi)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x80;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    o->rec[index].a = 0;
    o->rec[index].b = hi | lo;
    return 1;
}
