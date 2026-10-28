/* rgp:protos */
#define RGP_SELF_insect_InsectSeqGetTargetCell_51b710 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051B710 -- 51 instructions.  insect_InsectAiGetAction_522300 is called TWICE on
 * the same address, the first result discarded; the two `addiu $r,$18,K`
 * addresses are hoisted into callee-saved registers, so both are named locals.
 *
 * The 0x5EF1 test writes its flag through the `bne`'s delay slot, which is the
 * `f = 0;` / `if (...) f = 1;` shape and not a boolean expression. */

typedef struct Rec {
    u8 pad00[0x8];
    s8 m08;                         /* +0x08 */
    s8 m09;                         /* +0x09 */
    s8 m0A;                         /* +0x0A */
    s8 m0B;                         /* +0x0B */
    u8 pad0C[0x12 - 0x0C];
    s8 m12;                         /* +0x12 */
    s8 m13;                         /* +0x13 */
} Rec;

typedef struct Ctx {
    u8 pad0000[0x4F90];
    u8 m4F90[0x51C4 - 0x4F90];      /* +0x4F90 */
    u8 m51C4[0x5EF1 - 0x51C4];      /* +0x51C4 */
    u8 m5EF1;                       /* +0x5EF1 */
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectSeqGetTargetCell_51b710(s32 *ox, s32 *oy)
{
    Ctx *g;
    u8  *b;
    u8  *a;
    Rec *r;
    s32  f;

    g = ((Ctx *)InsectBattleGet_31a8d0());
    a = g->m51C4;
    b = g->m4F90;
    insect_InsectAiGetAction_522300(a);
    f = 0;
    if (g->m5EF1 == 1) {
        f = 1;
    }
    if (insect_InsectBattleTestFlag_50da40(g, f) != 0) {
        r = ((Rec *)insect_InsectAiGetAction_522300(a));
        if (r != 0) {
            *ox = r->m12;
            *oy = r->m13;
        }
    } else {
        r = ((Rec *)insect_InsectCursorSetFindPage_511e60(b, 0xD));
        *ox = r->m08 + r->m0A;
        *oy = r->m09 + r->m0B;
    }
}
