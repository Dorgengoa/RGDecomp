#include "types.h"

/* Asymmetric guard pair, writing an 8-byte record: 0x20 entries at +0x410. */

typedef struct Slot8a {
    s32 a;             /* +0x00 */
    s32 b;             /* +0x04 */
} Slot8a;

typedef struct Owner410 {
    u8 pad000[0x410];
    Slot8a rec[1];     /* +0x410 */
} Owner410;

s32 SysParamTableSetFloat_15feb0(Owner410 *o, s32 index, s32 value)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x20;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    o->rec[index].b = value;
    o->rec[index].a = 0;
    return 1;
}
