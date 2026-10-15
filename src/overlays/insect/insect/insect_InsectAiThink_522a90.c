#include "types.h"
/* insect 0x00522A90 -- 208 bytes, 52 instructions, jtbl_005257A0 (9 entries).
 *
 * The outer tick of the battle state machine: it dispatches on
 * insect_InsectAiGetState_522a50(o) and case 4 is what drives insect_InsectAiThinkStep_51f500.
 *
 * FIVE OF THE NINE TABLE ENTRIES POINT AT THE SHARED EXIT 0x00522B4C, so cases
 * 0, 3, 5, 6 and 8 are EMPTY CASES PRESENT IN THE SOURCE
 * ([[insect-jump-table-density]]).  Only four have bodies -- 1, 2, 4, 7 -- and
 * five cases spanning 1..7 is not dense enough for mwcc to emit a table at all,
 * so leaving the empties out turns the whole dispatch into a compare chain.
 * The range check corroborates: `sltiu $1, $2, 0x9` bounds the raw value with
 * NO bias subtraction, so the set starts at zero.
 *
 * Block order is 1, 2, 4, 7 -- ascending, which is source order for a real
 * table; the reversed-case-order rule is about a compare CHAIN and does not
 * apply here.
 *
 * The default's `beql $1,$0,.L00522B50` targets one instruction PAST the exit
 * the empty entries hold (0x00522B4C), because the branch-likely already ran
 * `ld $31,0x20($29)` in its delay slot.  Reading those two addresses as the
 * same place is what hides the empty cases.
 */

typedef struct Ins Ins;

struct Ins {
    u8  pad00[0x64];
    s32 f64;                        /* +0x64 */
    s32 f68;                        /* +0x68 */
};

extern s32  insect_InsectAiGetState_522a50(Ins *o);
extern void insect_InsectAiPushStep_522930(Ins *o, s32 k);
extern s32  insect_InsectAiGetStep_5229a0(Ins *o);
extern void insect_InsectAiPushState_5229e0(Ins *o, s32 k);
extern void insect_InsectAiThinkStep_51f500(Ins *o, s32 a);

void insect_InsectAiThink_522a90(Ins *o, s32 a)
{
    switch (insect_InsectAiGetState_522a50(o)) {
    case 0:
        break;
    case 1:
        insect_InsectAiPushState_5229e0(o, 2);
        break;
    case 2:
        insect_InsectAiPushState_5229e0(o, 4);
        insect_InsectAiPushStep_522930(o, 0x1A);
        o->f68 = 0;
        o->f64 = 0;
        break;
    case 3:
        break;
    case 4:
        insect_InsectAiThinkStep_51f500(o, a);
        if (insect_InsectAiGetStep_5229a0(o) == 0x2F) {
            insect_InsectAiPushState_5229e0(o, 7);
        }
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        insect_InsectAiPushState_5229e0(o, 8);
        break;
    case 8:
        break;
    }
}
