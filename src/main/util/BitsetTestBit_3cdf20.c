#include "types.h"

/* Is bit `index` set in a bitmap of 64-bit words?

   The 64-bit `dsllv` and `ld` name the word type; `srl` rather than `sra` on
   the word index names `index` as unsigned; and the trailing
   `sltu $2, $0, $2` is the u8 bool idiom on a `!= 0`. */

u8 BitsetTestBit_3cdf20(u64 *bits, u32 index)
{
    u8 set;

    set = (bits[index >> 6] & (1ULL << (index & 0x3F))) != 0;
    return set;
}
