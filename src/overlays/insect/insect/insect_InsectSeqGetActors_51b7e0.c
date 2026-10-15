#include "types.h"
/* insect 0x0051B7E0 -- 208 B / 52 words.
 * BRANCH POLARITY READ PER TEST:
 *   - the 0x5EF1 flag test is `bne $3, $2` PAST its arm, with `daddu $5,$0,$0`
 *     in the delay slot: an if/else-if CHAIN in source order, i.e.
 *     `sel = 0; if (g->m5EF1 == 1) sel = 1;` -- the literal 1 in $2 is shared
 *     by the compare and the assignment.
 *   - both zero checks are `beql`, which ANNULS its delay slot on the
 *     not-taken path, so each delay-slot instruction belongs to the TAKEN
 *     side: `daddu $4, $19, $0` is the else arm's argument setup for
 *     insect_InsectBattleGetSpecialRec_50db30 (one-arg -- its own listing touches only $4), and
 *     `ld $31` is the exit.
 * $18 (= g + 0x4960) and $17 (= g + 0x51C4) are materialised immediately
 * after $19 and held in CALLEE-SAVED registers across two calls each -- that
 * is what naming them in locals does; an `&g->sub` written at the use site
 * would be a plain `addiu $4, $19, imm` next to its jal instead.
 * The record pointer stays in $2 (dead after its last load), so it is never
 * copied to a callee-saved register: r->m12 / r->m13 are read at the call
 * argument site. */

typedef struct Rec {
    s32 m00;                    /* +0x00 */
    u8  pad04[0x0C - 0x04];
    s32 m0C;                    /* +0x0C */
    u8  pad10[2];
    s8  m12;                    /* +0x12 */
    s8  m13;                    /* +0x13 */
} Rec;

typedef struct Base {
    u8 pad0000[0x4960];
    u8 sub4960[0x51C4 - 0x4960];
    u8 sub51C4[0x5EF1 - 0x51C4];
    u8 m5EF1;                   /* +0x5EF1 */
} Base;

typedef struct Out {
    s32 m00;                    /* +0x00 */
    s32 m04;                    /* +0x04 */
    s32 m08;                    /* +0x08 */
} Out;

extern Base *func_31A8D0(void);
extern s32   insect_InsectBattleTestFlag_50da40(Base *g, s32 sel);
extern Rec  *insect_InsectAiGetAction_522300(u8 *p);
extern s32   insect_InsectBoardGetPiece_4ee9a0(u8 *p, s32 a, s32 b);
extern s32   insect_InsectBattleGetSpecialRec_50db30(Base *g);
extern s32   insect_InsectBattleGetActorSlot_50db40(Base *g, s32 n);

void insect_InsectSeqGetActors_51b7e0(Out *out)
{
    Base *g;
    u8   *p;
    u8   *q;
    Rec  *r;
    s32   sel;

    g = func_31A8D0();
    p = g->sub4960;
    q = g->sub51C4;
    sel = 0;
    if (g->m5EF1 == 1) {
        sel = 1;
    }
    if (insect_InsectBattleTestFlag_50da40(g, sel) != 0) {
        r = insect_InsectAiGetAction_522300(q);
        if (r != 0) {
            out->m00 = r->m00;
            out->m08 = r->m0C;
            out->m04 = insect_InsectBoardGetPiece_4ee9a0(p, r->m12, r->m13);
        }
    } else {
        out->m08 = insect_InsectBattleGetSpecialRec_50db30(g);
        out->m00 = insect_InsectBattleGetActorSlot_50db40(g, 2);
        out->m04 = insect_InsectBattleGetActorSlot_50db40(g, 3);
    }
}
