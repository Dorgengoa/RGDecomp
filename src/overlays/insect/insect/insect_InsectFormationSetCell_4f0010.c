#include "types.h"
/* insect 0x004F0010 -- 8 instructions.  The `sb` of the value rides the
 * `blez` delay slot; the 0x80 set is a read-modify-write of the SAME byte, so
 * the address is a named pointer local and not two `p[i]` expressions. */

void insect_InsectFormationSetCell_4f0010(u8 *base, s32 idx, u8 v, s32 n)
{
    u8 *p;

    p = base + idx;
    *p = v;
    if (n > 0) {
        *p = *p | 0x80;
    }
}
