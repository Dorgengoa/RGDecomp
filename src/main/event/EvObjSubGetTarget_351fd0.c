#include "types.h"

/* Same shape as EventRefListGetAt_3047c0: base pointer at +0xE8, count at +0xEC, records
   0x140 bytes. */

typedef struct Rec140 { u8 bytes[0x140]; } Rec140;

typedef struct OwnerE8 {
    u8 pad000[0xE8];
    Rec140 *rec;       /* +0xE8 */
    s32 count;         /* +0xEC */
} OwnerE8;

void *EvObjSubGetTarget_351fd0(OwnerE8 *o, s32 index)
{
    Rec140 *rec;

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
