/* rgp:protos */
#define RGP_SELF_DataTableCompareById_3f9000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN DataTableCompareById_3f9000 -- 112 B / 28 words.
   COLD TWIN FAMILY, n=70, 7,840 B: every one of the seventy members is
   byte-identical modulo branch-label addresses -- same `jal CompareNullness_368070`,
   same 0x0 load offsets -- so ONE reading converts all seventy.

   Two-key comparison helper.  CompareNullness_368070 orders the NULL cases (-1/0/1);
   a non-zero result returns immediately, otherwise the two s16 keys are
   compared three-way.

   The reading that settles it is the goto/label form.  Retail STRANDS two
   dead instructions -- `lh $3, 0x0($16)` at +0x3C and `slt $2, $3, $2` at
   +0x58 -- which are branch-likely delay-slot COPIES left behind because an
   explicit goto LABEL pins the block (same mechanism as
   src/event/EventSoundEntryReset_24a0f0.c).  Written with structured `if`s instead, mwcc
   MOVES those instructions into the delay slots, deletes the empty blocks and
   folds the trailing `b`, and the object is exactly THREE WORDS SHORT.
   Note the `none:` label sits physically BEFORE `found:`, which is what puts
   retail's `b .L1BC / nop` block between the bnel and the compare.  */

/*rgp*/

s32 DataTableCompareById_3f9000(void *self, s16 *a, s16 *b)
{
    s16 x;
    s16 y;
    s32 r;

    r = CompareNullness_368070(self, a, b);
    if (r != 0) {
        goto none;
    }
    if (a == NULL) {
        goto none;
    }
    if (b != NULL) {
        goto found;
    }
none:
    return r;
found:
    y = *b;
    x = *a;
    if (x < y) {
        return -1;
    }
    r = y < x;
    return r;
}
