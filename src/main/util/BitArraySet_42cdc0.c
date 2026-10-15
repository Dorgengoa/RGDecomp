#include "types.h"

/* Bitset set/clear.  sltu => the bound compare is unsigned; sra => the index
   is signed.  Retail falls through into the SET arm, so `val != 0` is the
   source's if body and the shared `p->m00` load is duplicated into the beql
   delay slot. */

struct Bits;

struct Bits {
    u32 *m00;
    u32 m04;
    u32 m08;
};

void BitArraySet_42cdc0(struct Bits *p, s32 idx, s32 val)
{
    if ((u32)idx < p->m08) {
        if (val != 0) {
            p->m00[idx >> 5] |= 1 << (idx & 0x1F);
        } else {
            p->m00[idx >> 5] &= ~(1 << (idx & 0x1F));
        }
    }
}
