#include "types.h"

/* A null check on the table POINTER in front of the asymmetric guard pair:
   base at +0x04, count at +0x08, records 0x30 bytes. */

typedef struct Rec30a { u8 bytes[0x30]; } Rec30a;

typedef struct Owner04 {
    s32 unk0;
    Rec30a *rec;       /* +0x04 */
    s32 count;         /* +0x08 */
} Owner04;

void *EventRefListGetAt_3047c0(Owner04 *o, s32 index)
{
    Rec30a *rec;

    rec = o->rec;
    if (rec == 0) {
        return 0;
    }
    if (index < 0) {
        goto none;
    }
    if (o->count > index) {
        goto found;
    }
none:
    return 0;
found:
    return &rec[index];
}

/* CLOSED 2026-09-04 (MAIN s30, lane oc2) on the `$at` COMPARE CLASS.

   Retail puts the bounds compare in $at -- `slt $1, $5, $2` / `bnel $1` --
   where we emitted `slt $2, $5, $2` / `bnel $2`.  The rule
   ([[at-compare-class]]) is: WRITE THE CONDITION UNDER WHICH THE BRANCH IS
   TAKEN, keep the source's own operand order, and negate the OPERATOR.  The
   only GPR spelling is a strict `<` with the tested value on the LEFT;
   anything else lands in $at.

   !! THE CONFOUND THAT HID IT FOR THREE SESSIONS: all three previously
   recorded spellings (`index < o->count`, `o->count > index`, and "the
   compare consumed straight by the branch") went through `u8 ok = ...;
   if (ok != 0)`.  A condition MATERIALISED INTO A VARIABLE is the recorded
   way OUT of $at -- it forces a GPR whatever the operator says -- so the
   operand-order arm was measured with the lever already disabled.  Deleting
   the `u8` AND writing `o->count > index` is what closes it; either alone is
   still 2 bad.  => When sweeping this class, drop the bool first.
*/
