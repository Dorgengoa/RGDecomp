/* rgp:protos */
#define RGP_SELF_insect_InsectAiGetStep_5229a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005229A0 -- 56 B / 14 words.  A DOWNWARD scan of a 5-element s32
 * array member, returning the first element that is not -1, else -1.
 *
 * The address form `addu $2,$4,$2` with `sll $2,$5,2` and `lw 0x14($2)` is
 * base + i*4 + 0x14, i.e. an ARRAY MEMBER at +0x14 -- not a scaled struct
 * stride.  Its twin insect_InsectAiGetState_522a50 reads the same shape at +0x00, and
 * 0x00 + 5*4 == 0x14, so the two arrays are adjacent members of one record
 * (the same Ins insect_InsectAiBeginTurn_522ba0 fills with two 5-iteration -1 loops at
 * +0x00 and +0x14).
 *
 * The loaded value is a NAMED LOCAL: it stays in $2 across the compare and is
 * the return value with no reload.  `beql $2,$3` INTO the loop test with the
 * `i--` in the delay slot is mwcc's branch-likely form of
 * `if (v != -1) return v;` -- the taken edge skips the if body.
 * -1 is hoisted into $3 because `bne` has no immediate form. */
typedef struct Ins {
    s32 f00[5];                     /* +0x00 */
    s32 f14[5];                     /* +0x14 */
} Ins;

s32 insect_InsectAiGetStep_5229a0(Ins *o)
{
    s32 i;
    s32 v;

    for (i = 4; i >= 0; i--) {
        v = o->f14[i];
        if (v != -1) {
            return v;
        }
    }
    return -1;
}
