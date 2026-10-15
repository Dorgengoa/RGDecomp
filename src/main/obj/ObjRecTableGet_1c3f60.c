#include "objrec.h"

/* Bounds-checked lookup into the 0x3B18 table (0x28-byte records). */

typedef struct Owner3B14 {
    u8 pad000[0x3B14];
    s32 count;         /* +0x3B14 */
    u8 rec[1];         /* +0x3B18, 0x28 bytes each */
} Owner3B14;

/* ★★★★★★ THE ASYMMETRIC GUARD PAIR -- SOLVED 2026-08-22 (third session), and
   the same three-line edit closed all four functions in the class:
   ObjRecTableGet_1c3f60, ObjRecTableGet_1c3fe0, RecStackGetSlot_1c4330, EventCastIdListGet_24b190.

   Retail packs the two guards ASYMMETRICALLY. The negative guard FOLDS -- a
   `bltzl` straight to the epilogue carrying the return value in its own delay
   slot, two words. The bounds guard does NOT -- it spends three, and the third
   is an EMPTY delay slot:

       bltzl  $5, EPI            <- outer guard, folded
        daddu $2, $0, $0
       lw     $2, 0x3B14($4)
       slt    $2, $5, $2
       bnel   $2, $0, FOUND      <- bounds guard
        sll   $2, $5, 2
       daddu  $2, $0, $0         <- the value...
       b      EPI                <- ...NOT sunk into this delay slot
        nop
     FOUND:
       ...compute...
     EPI:
       jr $31

   ⇒ **BOTH GUARDS `goto` THE SAME LABEL, AND THE LABEL GOES PHYSICALLY BEFORE
   THE COMPUTE BLOCK, which the compute then needs its own `goto` to reach:**

       if (index < 0) goto none;
       ok = index < o->count;
       if (ok != 0) goto found;
     none:
       return 0;
     found:
       return &o->rec[index * 0x28];

   ★★★★★ WHY IT WORKS, because the mechanism generalises and the spelling does
   not. The shared label gives that block TWO predecessors while mwcc is
   scheduling. An instruction can only be sunk into an unconditional `b`'s
   delay slot if every path reaching the `b` also executes it -- with a second
   predecessor jumping in, `daddu $2,$0,$0` no longer dominates the branch and
   the slot has to stay empty. mwcc then folds the OUTER guard's copy of the
   return value into its own likely-branch delay slot, which is why the same
   edit fixes both halves at once. The two predecessors do not survive into the
   final code (the outer branch ends up going straight to the epilogue), so
   **there is no label in the reference at that point and nothing in the
   disassembly says the block ever had one.**
   ⇒ Generalise: **an unfilled delay slot before an unconditional branch is a
   statement about the block's PREDECESSORS, not about the scheduler.** ★ The
   arm that proves it: `#pragma schedule off` reproduces this block exactly
   (`daddu`/`b`/`nop`) while unfilling every other delay slot in the function
   -- 19 words against retail's 15 -- so the shape is a fill decision, and the
   fill is blocked structurally rather than globally.

   ⚠⚠ THE PREVIOUS SESSION MEASURED FIVE SPELLINGS AND REJECTED THE CLASS AS
   OPEN. None of them was this one, and the near-misses are instructive:
     both guards their own `return 0`      15 words,  8 bad
     single-exit local + two `goto out`    15 words,  8 bad (identical output)
     `if (index >= 0) { ... }` wrapper     15 words,  9 bad (outer right only)
     both guards `goto none` AT THE TAIL   14 words (one short)
     outer wrap + inner `goto none`        13 words (two short)
   The fourth is one character away from the answer: the shared label is right,
   its POSITION is not. At the tail it is after the compute, the compute falls
   through instead of being jumped to, and the second predecessor never exists.
   ⇒ **A `goto`-to-a-shared-label recipe is only half a recipe until the
   label's POSITION is written down too** -- the same lesson as the
   AnimKeyFindSpan_155ff0 cold-block note ("read the reference's block ORDER off the
   addresses and put the label where the addresses say"), reached from the
   other side.
   ⚠ And it is NOT the EventPlayerInit_249c60 shared-`none:` recipe, which is
   asymmetric the other way (outer shares, inner returns on its own). That one
   was tried here too, third session: 14 words, one short. */
void *ObjRecTableGet_1c3f60(Owner3B14 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < o->count;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0x28];
}
