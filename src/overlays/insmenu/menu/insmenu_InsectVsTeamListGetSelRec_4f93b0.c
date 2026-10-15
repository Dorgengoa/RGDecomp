/* insmenu 0x004F93B0 (132 bytes, 33 instructions) -- the record the caption's
 * widget is sitting on, or NULL when the index is out of range.
 * BYTE-IDENTICAL (lane C1 / tag im11, 2026-08-26).  MATCH printed by
 * build/dv_osbuild.py at 33 words = 0x84/4; objdump section set is .text only
 * (no .lit4, no .rodata), so it needs no link plumbing.
 *
 * It was parked for three sessions at 2 bad words -- ONE branch and its delay
 * slot:
 *     0x004F93F8  ours bltz  $3, .L004F9420   retail bltzl $3, .L004F9424
 *     0x004F93FC  ours nop                    retail daddu $2, $0, $0
 * 21 structural spellings of the guard nest plus a 117-variant knob screen all
 * left it at 2.  Every one of them was moving the same single `return 0;`
 * around.  THE LEVER IS THE NUMBER OF `return 0;` STATEMENTS, NOT THEIR SHAPE.
 *
 * === THE MECHANISM (measured, build/mr-im11, 12 cells) ===
 * mwcc compiles `if (c) { body }` as `b!c <past the body>` and then fills that
 * branch's delay slot by STEALING THE FIRST INSTRUCTION OF THE TARGET BLOCK,
 * converting the branch to its LIKELY form and retargeting it one word further
 * on.  It will do this AT MOST ONCE PER TARGET BLOCK -- a second branch aimed
 * at the same block gets a plain branch and a nop, which is what keeps the
 * block alive.
 * Three guards here jump past their body to a `return 0`.  With ONE trailing
 * `return 0;` all three share one block, only the first (`w == 0`) gets the
 * steal, and the `n < 0` guard is left as bltz+nop -- the parked residue.
 * Give the `n >= 0` guard its OWN `return 0;` -- one at the end of the `w != 0`
 * body, one after it -- and each guard steals from a different block:
 *     w  == 0     -> beql  ... / daddu $2,$0,$0   (steals the outer return 0)
 *     n  <  0     -> bltzl ... / daddu $2,$0,$0   (steals the inner return 0)
 *     n >= 0x14   -> beqz  ... / nop              (the inner block survives)
 * and the now-predecessorless outer block is deleted, so the length is still
 * 33 words.  That is retail exactly.
 *
 * SCOPE / POLARITY CONTROLS measured in the same round trip:
 *   w01 (extra return 0 at the end of the `w != 0` body)   33 words, MATCH
 *   w02 (extra return 0 inside the `n >= 0` body instead)  34 words -- the
 *       steal moves to the `n < 0x14` branch (beql/daddu) and `n < 0` stays
 *       bltz+nop.  Same statement, wrong SCOPE, and it is the arming control:
 *       the transform follows the block, not the text.
 *   w03 (both placements)                                  31 words -- three
 *       steals, the shared block goes dead and is deleted.
 *   w05 (`else { return 0; }` on the n >= 0 test)          identical object to
 *       w01 (sha1 e9453551): the else IS the same block placement.
 * Re-confirmed as wrong-LENGTH, not wrong-bytes: v01 three early returns and
 * v02 `if (n < 0) return 0;` are both 34 words, as lane L2 recorded.
 *
 * WORKED PRECEDENT that named the transform: factory_FactoryGridCellAt_5037f0 and
 * factory_FactoryPartDefPathEnd_4fe3a0 both emit `bltzl $X, <epi> / daddu $2,$0,$0` for a
 * `< 0` guard, and in both the guard's target block is a return 0 that no
 * earlier branch has stolen from.
 *
 * (star) `sll 3 / subu / sll 5` is a multiply by 224, the record stride.
 */
#include "types.h"

/* insmenu 0x004F93B0 (132 bytes) -- the record the caption's widget is sitting
 * on, or NULL when the index is out of range.
 *
 * ★ `sll 3 / subu / sll 5` is a multiply by 224, the record stride.
 *
 * ⚠⚠ PARKED AT 2 WORDS AND THE LENGTH IS RIGHT (33 words) -- deliberately OUT
 * of config/ocunits/insmenu.txt; the length guard would pass it.
 * The residue is one branch-likely conversion: retail's `n < 0` guard is
 * `bltzl` with the shared `daddu $2, $0, $0` duplicated into its delay slot,
 * ours is a plain `bltz` + nop into the shared block.  The recorded recipe
 * (give the shared return block one more predecessor) is what took it from 4
 * words to 2 -- the nested `if (w != 0) { ... }` form below.
 * Enumerated and NULL beyond that: early `return 0` per guard, `else if`, a
 * separate `return 0` for the out-of-range case, `n >= 0x14` and `n > 0x13`
 * spellings, `&&` joins, both orders of the two range tests (13 structural
 * forms, build/imv_f93b0*.py) -- plus the 117-variant knob screen
 * (build/im_s10_knob_f93b0.txt), where every live cell breaks the LENGTH.
 */

typedef struct Rec Rec;
struct Rec {
    u8 pad00[0xE0];
};

typedef struct Ctx Ctx;
struct Ctx {
    u8  pad00[8];
    Rec field08[1];
};

typedef struct Handle Handle;
struct Handle {
    u8   pad00[0x24];
    Ctx *field24;
};

typedef struct Widget Widget;
struct Widget {
    u8  pad00[0x16];
    s16 field16;
    u8  pad18[2];
    s16 field1A;
};

extern const u8 D_004FA1A0[];

extern Handle *func_1FEDE0(void);
extern Widget *func_28EA40(const void *a, s32 id);

Rec *insmenu_InsectVsTeamListGetSelRec_4f93b0(void)
{
    Rec *base;
    Widget *w;
    s32 n;

    base = func_1FEDE0()->field24->field08;
    if (base == 0) {
        return 0;
    }
    w = func_28EA40(D_004FA1A0, 0x88BD);
    if (w != 0) {
        n = w->field1A + w->field16;
        if (n >= 0) {
            if (n < 0x14) {
                return &base[n];
            }
        }
        return 0;
    }
    return 0;
}
