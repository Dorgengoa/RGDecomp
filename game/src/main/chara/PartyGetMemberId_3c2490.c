/* rgp:protos */
#define RGP_SELF_PartyGetMemberId_3c2490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The s16 flavour: a short table at +0x190 with an s16 count at +0x18C, and
   TWO BYTES OF PAD between them -- see the write-up below, the missing pad
   was a real defect that read as a scheduling residue for two sessions.

   âš  Here the two guards DO share one -1 -- and the shared block sits
   PHYSICALLY BETWEEN the bounds test and the compute, which is why the bounds
   test branches FORWARD to the compute and falls through into the -1. A label
   at the end of the function produces the same code in a different order and
   is two words long. Read the block order off the addresses, as with
   AnimKeyFindSpan_155ff0's clamp. */

typedef struct Table18C {
    u8 pad000[0x18C];
    s16 count;         /* +0x18C */
    u8 pad18E[0x2];    /* the table is at 0x190, NOT 0x18E -- see below */
    s16 entry[1];      /* +0x190 */
} Table18C;

/* ★★★★★★ SOLVED 2026-08-23, 70.82% -> 100%, and it RETRACTS the entry that
   used to sit here. This was written up as "the fill-availability deficit --
   retail's plain bltz carries the next block's lh, mwcc has no such filler
   and reaches for a likely branch, and no source spelling reached it". That
   diagnosis was wrong. Three separate defects, none of them a scheduler
   deficit:

   1. THE STRUCT PUT THE TABLE AT 0x18E. `s16 count;` immediately followed by
      `s16 entry[1];` packs the array at +0x18E, and the comment claiming
      +0x190 was never checked against the layout. Retail's `lh v0, 0x190(v0)`
      said so all along and the diff showed it as an ordinary wrong
      displacement. ★ A comment asserting an offset is not evidence the
      offset is right -- add the pad and let the compiler agree with it.
   2. THE COUNT IS READ UNCONDITIONALLY. Retail's first guard is a PLAIN
      `bltz` whose delay slot holds `lh count` -- a non-likely delay slot
      always executes, so the load happens on BOTH paths, so the source reads
      it before the guard. Hoisting `n = t->count;` above `if (index < 0)`
      turns our likely branch into retail's plain one and lets the two guards
      share ONE -1. ★★★★★ **A FILLED NON-LIKELY DELAY SLOT IS A STATEMENT
      ABOUT THE SOURCE, NOT THE SCHEDULER: whatever is in it runs
      unconditionally, so it happens before the branch in the source too.**
      That is the mirror of the recorded "an unfilled slot before a `b` is
      about predecessors" reading, and it PREDICTS where that one only
      explains.
   3. THE LOCAL HAS TO BE s32. Holding the count in an `s16` makes mwcc
      re-sign-extend it with `dsll32`/`dsra32` before the compare -- two words
      -- work that the `lh` already did. Widening the local to `s32` drops
      both.

   ⚠ The old entry also claimed this class was shared with EvCmdEventStartMaybe_248450's
   inlined accessor and that neither was reachable. The shared-cause claim is
   now unsupported: check that one against these three defects rather than
   against the retracted scheduler story. */
s16 PartyGetMemberId_3c2490(Table18C *t, s32 index)
{
    s32 n;

    n = t->count;
    if (index < 0) {
        goto none;
    }
    if (index < n) {
        goto ok;
    }
none:
    return -1;
ok:
    return t->entry[index];
}
