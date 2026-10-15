#include "types.h"

/* factory.bin overlay, 0x004FE820 -- 68 words, EXACT LENGTH, 10 bad.  PARKED.
 * Session 23, lane fz23a: no arm moved a single word.
 *
 * RESIDUE A -- 0x004FE828/0x004FE82C, the SAME CLASS as 004fe500's residue:
 *   ours   50E0003F beql $7,$0,0x4FE928 / 0000102D daddu $2,$0,$0  (slot)
 *   retail 10E00003 beq  $7,$0,0x4FE838 / 00000000 nop
 * The `c == 0 || b == 0` guard's shared `return 0` block at .L004FE838
 * (`daddu $2,$0,$0; b; nop`) is byte-correct in our object and is still
 * entered by the b==0 fall-through.  mwcc additionally branch-CHAINED the
 * c==0 predecessor straight to the epilogue and duplicated the block's daddu
 * into the likely-branch delay slot.  Retail does not.  Note mwcc DOES
 * duplicate for `out == 0` at 0x004FE820 in BOTH objects, so it is not a
 * global knob; the two-predecessor block is what retail keeps shared.
 *
 * RESIDUE B -- 0x004FE900..0x004FE91C, an 8-word THREE-WAY REGISTER
 * PERMUTATION.  Every instruction and every operand ORDER already matches;
 * only the colouring and the li/lhu interleave differ:
 *     ours   b->f04=$3  mask(-4)=$4  out->f04=$6   or dst == ft
 *     retail b->f04=$6  mask(-4)=$3  out->f04=$4   or dst == fs
 * Retail loads b->f04 IN PLACE (`lhu $6,0x4($6)`, reusing the dying pointer's
 * own register); ours takes the next free register instead and the whole
 * 3-cycle follows from that.
 *   MEASURED INERT (all byte-identical to the baseline object):
 *     `t = out->f04 & ~3; out->f04 = (t | (d + (b->f04 & 3))) & 3;` (baseline)
 *     `t = d + (b->f04 & 3); out->f04 = ((out->f04 & ~3) | t) & 3;`
 *     the same with NO named temp, as one single expression
 *     swapping the `|` operands: `((d + (b->f04 & 3)) | (out->f04 & ~3)) & 3`
 *   i.e. neither WHICH subexpression is named, nor which is written first, nor
 *   the `|` operand order, is the axis.  It is the in-place load coalesce.
 */

/* ** SESSION 23 (lane fz23l): 10 -> 8 bad, 68 words.  RESIDUE A, the branch
 * chaining at 0x004FE828/0x004FE82C, is CLOSED.  The three null checks are ONE
 * `||` CHAIN WITH ONE `return 0;`, not a nested guard plus a trailing return:
 *     if (out == 0 || c == 0 || b == 0) { return 0; }
 * (was `if (out != 0) { if (c == 0 || b == 0) { return 0; } ... } return 0;`).
 * MECHANISM: with all three predecessors feeding ONE shared return-0 block,
 * mwcc threads only the FIRST of them -- `beql $5,$0,.L928` with the block's
 * `daddu $2,$0,$0` duplicated into the slot -- and leaves the second as the
 * plain `beqz $7,.L838` with a `nop`, which is retail.  Two `return 0;`
 * statements let it thread BOTH.  Same family as the 004f3a70 close: how a
 * block EXITS decides whether mwcc threads its predecessors.
 *
 * ! RESIDUE, 8 words, 0x004FE900-0x004FE91C -- the three-way register
 *   permutation, unchanged.  Retail COALESCES the `b->f04` load onto b's own
 *   dying register (`lhu $6,0x4($6)`) and then hands $3/$4 to the mask and to
 *   `out->f04` in birth order; ours refuses the coalesce and hands $3/$4/$6 to
 *   b->f04, the mask and out->f04 in birth order.  The `addiu $2,$0,1` also
 *   lands one slot earlier in ours, which follows from that.
 *   MEASURED INERT THIS SESSION, on top of the file's earlier list: naming the
 *   two RAW loads as their own statements in retail's order
 *   (`b4 = b->f04; o4 = out->f04;` then the expression) -- byte-identical, so
 *   mwcc forward-substitutes a single-use local here and NO naming arm can
 *   move this; and a SECOND SPELLING of the read side of the read-modify-write
 *   (`((u16 *)out)[2] & ~3` against the `out->f04 =` write) -- byte-identical
 *   too, mwcc folds it straight back to the same lvalue.
 *   ⇒ naming, statement order, `|` operand order and second-spelling are ALL
 *   dead here.  The only live axis left is the load/base coalesce itself.
 */

/* ★★★★★★★ SESSION 36 (2026-09-02, lane fg36): 8 -> 0 BAD, BYTE-IDENTICAL,
 * MERGED into config/ocunits/factory.txt.  ONE CAST:
 *     out->f04 = ((d + (*(volatile u16 *)&b->f04 & 3)) | (out->f04 & ~3)) & 3;
 * The volatile ACCESS-SITE pin on the `b->f04` LOAD ([[mwcc-volatile-access-
 * site-pin]]) is exactly the "load/base coalesce" handle the line above asked
 * for: pinned, the load is emitted where the source puts it -- FIRST -- while
 * `b` is dying, and mwcc reuses b's own $6 for it (`lhu $6,0x4($6)`), after
 * which the mask and `out->f04` take $3/$4 in birth order and the `or` comes
 * out dst == fs.  The pin on the `out->f04` load instead is INERT (baseline
 * object 89687a04911d), so it is the b-side load and only that.
 * RE-SWEPT AT 8 (md5 = object identity), all EXACT length:
 *   INERT (89687a04911d): the four s23 spellings (named mask first, named sum
 *     first, `|` operands swapped, the u16-pointer second spelling); the two
 *     raw loads named as `u16 b4, o4` in either declaration order and either
 *     statement order; `b4 = b->f04 & 3` named; `q = b->f04` named; the load
 *     through a `u16 *bp = &b->f04`; `rv = 1; return rv;` before or after the
 *     store; the volatile pin on `out->f04`.
 *   DISTINCT OBJECT, still 8 (22b4a9292197): `(b->f04 & 3) + d` add order.
 *   1 BAD (c49bd2324359): TWO named temps `m = out->f04 & ~3; s = d + (b->f04
 *     & 3); out->f04 = (s | m) & 3;` in either declaration/statement order, and
 *     the second-def `d += b->f04 & 3;` -- every register right, only the
 *     `or $3,$3,$6` operand order left (ours rd == rt).  A plain-C spelling
 *     that reaches 0 was not found; the volatile pin is the landing.
 */
typedef struct Pt {
    s16 f00;
    s16 f02;
    u16 f04;
} Pt;

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
} Box;

s32 factory_FactoryGridRotatePoint_4fe820(void *w, Pt *out, Pt *b, Box *c, s32 d)
{
    if (out == 0 || c == 0 || b == 0) {
        return 0;
    }
    switch (d & 3) {
    case 0:
        out->f00 = c->f00 + b->f00;
        out->f02 = c->f02 + b->f02;
        break;
    case 1:
        out->f00 = c->f00 + b->f02;
        out->f02 = c->f06 - b->f00;
        break;
    case 2:
        out->f00 = c->f04 - b->f00;
        out->f02 = c->f06 - b->f02;
        break;
    case 3:
        out->f00 = c->f04 - b->f02;
        out->f02 = c->f02 + b->f00;
        break;
    default:
        return 0;
    }
    out->f04 = ((d + (*(volatile u16 *)&b->f04 & 3)) | (out->f04 & ~3)) & 3;
    return 1;
}
