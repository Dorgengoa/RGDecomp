#include "types.h"
/* insect 0x0050DA90 -- 13 instructions.  A 64-bit bitmap clear.  The
 * `dsll32/dsra32 ..,0` pair is the s32 mask `~(1 << (i & 31))` being widened
 * to 64 bits for the `and`, so the mask must stay an int expression. */

typedef struct Bits {
    u8 pad00[0x5DB8];
    u64 m5DB8[1];                   /* +0x5DB8 */
} Bits;

void insect_InsectBattleClearFlag_50da90(Bits *b, s32 i)
{
    b->m5DB8[i >> 5] &= ~(1 << (i & 31));
}
