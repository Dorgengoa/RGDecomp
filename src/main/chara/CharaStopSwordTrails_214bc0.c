#include "types.h"

/* Walk the 0xB8-byte records at +0x584 and shut each one down. The count at
   +0x588 is RE-READ every iteration -- it is the loop condition, not a
   hoisted bound -- and the receiver has to be parked in a callee-saved
   register to survive the three calls.

   Both increments live in the for-clause, `i++, r++`. Advancing the record
   pointer in the BODY instead emits the two `addiu`s in the other order --
   body first, clause second -- which is two words wrong and nothing else. */

typedef struct Rec00214bc0 {
    u8 pad00[0x30];
    u8 unk30[0x30];
    u8 unk60[0x58];
} Rec00214bc0;

typedef struct Obj00214bc0 {
    u8 pad000[0x584];
    Rec00214bc0 *list;   /* +0x584 */
    s32 count;           /* +0x588 */
} Obj00214bc0;

extern void TargetRefClear_2e71d0(void *p);
extern void SwordTrailStop_2d7620(Rec00214bc0 *r);

void CharaStopSwordTrails_214bc0(Obj00214bc0 *self)
{
    Rec00214bc0 *r;
    s32 i;

    r = self->list;
    if (r == 0) {
        return;
    }
    for (i = 0; i < self->count; i++, r++) {
        TargetRefClear_2e71d0(r->unk30);
        TargetRefClear_2e71d0(r->unk60);
        SwordTrailStop_2d7620(r);
    }
}
