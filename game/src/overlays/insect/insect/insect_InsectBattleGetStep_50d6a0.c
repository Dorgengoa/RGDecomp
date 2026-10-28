/* rgp:protos */
#define RGP_SELF_insect_InsectBattleGetStep_50d6a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x000050D6A0 -- 68 B / 17 words.  Twin of the other member of this
 * pair; the ONLY difference is which 8-byte row array is read (0x5DD4 vs
 * 0x5E34, 0x60 apart = 12 rows of 8).
 *
 * Reading: scan the 8-entry row backwards for the last used slot.
 *   b <test>  with `addiu $2,$0,-1` in the delay slot = the -1 hoisted ONCE
 *   and used both as the compare operand and as the fall-out return value.
 *   The taken return path RECOMPUTES the address (`addu $2,$6,$4` /
 *   `addu $2,$7,$2`) instead of reusing $3, i.e. the subscript is written
 *   out a second time in the source rather than named in a local.
 */

typedef struct Ins {
    u8 pad000[0x5DD4];
    s8 f5DD4[12][8];            /* +0x5DD4 */
    s8 f5E34[12][8];            /* +0x5E34 */
} Ins;

s32 insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k)
{
    s32 i;

    for (i = 7; i >= 0; i--) {
        if (o->f5E34[k][i] != -1) {
            return o->f5E34[k][i];
        }
    }
    return -1;
}
