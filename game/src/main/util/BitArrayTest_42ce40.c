/* rgp:protos */
#define RGP_SELF_BitArrayTest_42ce40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* `and $2,$3,$2` : the shift mask is the LEFT operand. */

struct Bits;

struct Bits {
    u32 *m00;
    u32 m04;
    u32 m08;
};

s32 BitArrayTest_42ce40(struct Bits *p, s32 idx)
{
    if ((u32)idx < p->m08) {
        return ((1 << (idx & 0x1F)) & p->m00[idx >> 5]) != 0;
    }
    return 0;
}
