/* rgp:protos */
#define RGP_SELF_insect_InsectTeamSlotClearCell_5140b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005140B0 -- 16 bytes, 4 instructions.
 *
 * ⚠ `addu $3, $5, $4` with the POINTER in `rt` does NOT mean the pointer is
 * parameter two.  With the pointer as parameter ONE and the index as parameter
 * TWO, mwcc puts the scaled index in `rs`: `p[i + 0xA]` off `(u8 *p, s32 i)`
 * is byte-identical (object 7d859833), while the same expression off
 * `(s32 i, u8 *p)` emits `addu $3, $4, $5` and is one bad word.
 * A named pointer local (`q = p + i; q[0xA] = 0xFF;`) reaches the same object
 * from EITHER parameter order; `*(p + i + 0xA)`, `p[0xA + i]` and `(u8)-1`
 * are all INERT with the wrong-order baseline. */

void insect_InsectTeamSlotClearCell_5140b0(u8 *p, s32 i)
{
    p[i + 0xA] = 0xFF;
}
