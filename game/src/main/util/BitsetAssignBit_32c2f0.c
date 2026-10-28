/* rgp:protos */
#define RGP_SELF_BitsetAssignBit_32c2f0 1
#include "port/game_protos.h"
#line 1
/* BitsetAssignBit_32c2f0 -- BYTE-IDENTICAL to merged BitsetAssignBit_3eedd0 (76 B); source cloned
   by build/zz/s23_clonesrc.py, symbol renamed, nothing else
   changed.  Verified by sha1 over the retail bytes. */
#include "types.h"

/* 64-bit bitset set/clear.  `srl` on the index says the index is UNSIGNED.
   The word index is computed ONCE before the branch (retail's `srl $7,$5,6`
   is the first instruction and both arms reuse $7), so it is a named local;
   recomputing it in each arm costs a word. */

u64 *BitsetAssignBit_32c2f0(u64 *p, u32 bit, s32 set)
{
    u32 idx;
    u64 m;

    idx = bit >> 6;
    m = (u64)1 << (bit & 0x3F);
    if (set) {
        p[idx] |= m;
    } else {
        p[idx] &= ~m;
    }
    return p;
}
