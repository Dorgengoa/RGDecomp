/* rgp:protos */
#define RGP_SELF_insect_InsectBattleRematchPromptDraw_4f14e0 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"
/* insect 0x004F14E0 -- 544 bytes, 136 instructions, 17 calls, 10 conditional
 * branches.  The record publisher: clamps four counters and writes eleven
 * fields per row.
 *
 * ★★★★★★ THIS IS THE FIRST APPLICATION OF [[at-compare-class]] IN INSECT, AND
 * THE FUNCTION CARRIES BOTH OF ITS FORMS.  Seven of the overlay's 52 inverted
 * `$at` sites are here -- the densest in the image.  A compare's destination
 * follows the branch's TAKEN-CONDITION OPERATOR TOKEN, not liveness:
 *
 *   if-clamp   `slti $1, $19, 0x3E8` feeding `bnez`  =>  source wrote `> 999`.
 *              `>= 1000` is the same predicate and the same instruction, but it
 *              puts the result in a GPR.
 *   loop latch `slti $1, $20, 0x3` feeding `bnel`    =>  source wrote `i <= 2`.
 *              `i < 3` is a GPR.  In a latch the ONLY `$at` spellings are the
 *              or-equal ones.
 *
 * Both tokens here are what a person would actually write -- you clamp to a
 * maximum of 999 with `> 999`, and you count 1..2 with `<= 2`.  The trap is
 * that m2c and a careful transcription both normalise them to `>= 1000` and
 * `< 3`, which is right length, right instruction, wrong register, seven times.
 *
 * `p` is a `u16 *` over an `s16[8]`: the copy loop reads with `lh` (signed
 * elements) and every later read is `lhu`.  One view per width is what produces
 * both, and the clamped values are `s32` locals -- a `u16` local would need a
 * mask at the 999 assignment that retail does not have.
 *
 * MATCHED ix31: the residue was never a source-spelling axis --
 * `#pragma optimization_level 3` (the default is 4) closes it outright.
 * The residue is `lhu $19, 0xC($30)` against our `lhu $19, 0xBC($29)`: the same
 * address, the same instruction, a different BASE REGISTER.  mwcc knows
 * `p == $29 + 0xB0` and folds the constant-offset read to the frame pointer,
 * while keeping `$30` for the INDEXED reads in the same block.  That is the
 * class [[overlay-c-pipeline]] records for insmenu as "the frame displacement
 * we fold and retail does not", closed there as a bounded negative over 23
 * spellings -- so this was NOT swept.  Three spellings were tried and are
 * recorded so they are not re-run: `*(p + 6)` (identical object), and defining
 * `p` above the copy loop with `dst = p` (+1 word, `len 0x224 vs 0x220`).
 *
 * `p = spB0;` sits in the `beqz`'s delay slot, which is a PLAIN branch, so the
 * slot runs on both edges: it is a statement ahead of the guard, not one inside
 * an arm.
 */

typedef struct Ins {
    u8  pad000[0x87C];
    void *f87C;                 /* +0x087C */
    u8  pad880[0x5DA8 - 0x880];
    s32 f5DA8;                  /* +0x5DA8 */
} Ins;

typedef struct Hit { u8 pad00[0x28]; void *f28; } Hit;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleRematchPromptDraw_4f14e0(Ins *o)
{
    s16 spB0[8] __attribute__((aligned(16)));
    s16 spA0[8] __attribute__((aligned(16)));
    u16 *p;
    u8 *base;
    s32 i;
    s32 a;
    s32 b;
    s32 c;
    s32 e;
    u8 *rec;
    s32 j;
    s16 *src;
    s16 *dst;
    s32 n;
    Hit *s;
    void *r;

    if (insect_InsectBattleTestFlag_50da40(o, 0x18) == 0) {
        return;
    }
    UiDrawWidgets_291910(o->f87C);
    insect_InsectBattleCalcWinStats_4f0820(spA0, o);
    src = spA0;
    dst = spB0;
    n = 7;
    do {
        *dst = *src;
        src++;
        dst++;
        n = n - 1;
    } while (n > 0);
    p = (u16 *)spB0;
    if (o->f5DA8 == 0) {
        return;
    }
    r = ResGroupListFindById_42c500(GetMenuResGroup_206a40(), 0x3E8);
    if (r == 0) {
        return;
    }
    s = ((Hit *)ResGroupListFindElemById_42a2e0(r, 0x7661));
    if (s == 0) {
        return;
    }
    base = s->f28;
    for (i = 1; i <= 2; i++) {
        j = i - 1;
        a = p[6];
        b = p[j + 2];
        c = p[j + 4];
        e = p[j];
        if (a > 999) {
            a = 999;
        }
        if (b > 999) {
            b = 999;
        }
        if (c > 999) {
            c = 999;
        }
        if (e > 100) {
            e = 100;
        }
        rec = base + j * 0xB0;
        insect_InsectBattleDrawNumberRec_4f1490(o, rec);
        insect_InsectBattleDrawMsgRec_4f1440(o, rec + 0x10, 0x7D1);
        insect_InsectBattleDrawNumberRec_4f1490(o, rec + 0x20);
        insect_InsectBattleDrawMsgRec_4f1440(o, rec + 0x30, 0x7D2);
        insect_InsectBattleDrawNumberRec_4f1490(o, rec + 0x40);
        insect_InsectBattleDrawMsgRec_4f1440(o, rec + 0x50, 0x7D3);
        insect_InsectBattleDrawNumberRec_4f1490(o, rec + 0x60);
        insect_InsectBattleDrawMsgRec_4f1440(o, rec + 0x70, 0x7D4);
        insect_InsectBattleDrawMsgRec_4f1440(o, rec + 0x80, 0x7D5);
        insect_InsectBattleDrawNumberRec_4f1490(o, rec + 0x90);
        insect_InsectBattleDrawMsgRec_4f1440(o, rec + 0xA0, 0x7D6);
    }
}
