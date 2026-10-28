/* rgp:protos */
#define RGP_SELF_insect_InsectBattleSetFlag_50dad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050DAD0 -- 10 instructions.  The twin of insect_InsectBattleClearFlag_50da90: the
 * SET half of the same 64-bit bitmap.  `sllv` on a plain `1` keeps the mask an
 * int expression, which sign-extends into the 64-bit `or`. */

typedef struct Bits {
    u8  pad000[0x5DB8];
    u64 m5DB8[1];                   /* +0x5DB8 */
} Bits;

void insect_InsectBattleSetFlag_50dad0(Bits *b, s32 i)
{
    b->m5DB8[i >> 5] |= 1 << (i & 31);
}
