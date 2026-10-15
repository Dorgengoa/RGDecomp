#include "types.h"

/* Gives a block back: the size at +0x2C is returned to the owner's running
   total at +0x8 and the four fields that describe the loan are cleared. A
   leaf with no frame at all.

   ⚠ RESIDUE: 3 words, and it is a SCHEDULING difference, not a spelling.
   Retail loads the addend `self->unk2C` FIRST and the accumulator
   `owner->unk8` second, then writes `addu v1, v1, a1`; mwcc loads the
   accumulator first and writes `addu v1, a1, v1`. Both are the same source
   expression -- only the load order and the register assignment differ.
   SIX spellings were measured and every one emitted the identical three
   words, so the `+`'s operand order is fully canonicalised here:

     1. `owner->unk8 += self->unk2C;`                       (this one)
     2. `size = self->unk2C; owner->unk8 = owner->unk8 + size;`
     3. `size = self->unk2C; owner->unk8 = size + owner->unk8;`
     4. `owner->unk8 = self->unk2C + owner->unk8;`          (no local)
     5. guard as an early `return` instead of an if-block
     6. an inlined `static` helper taking the addend as a parameter -- the
        "a temp register may be an OUTGOING ARGUMENT" reading of a1, which
        is the most promising story for retail's order and still did not
        reproduce it

   ⚠ Hoisting `size = self->unk2C;` ABOVE the null guard is not a seventh
   spelling: it fills the `beqz`'s nop and the function comes out 12 words. */

typedef struct Owner0014dad0 {
    u8 pad0[0x8];
    s32 unk8;
} Owner0014dad0;

typedef struct Obj0014dad0 {
    u8 pad0[0x28];
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x34 - 0x30];
    s32 unk34;
    Owner0014dad0 *unk38;
} Obj0014dad0;

void MemStackReturnToOwnerMaybe_14dad0(Obj0014dad0 *self)
{
    Owner0014dad0 *owner;
    s32 size;

    owner = self->unk38;
    if (owner == 0) {
        return;
    }
    size = *(volatile s32 *)&self->unk2C;
    owner->unk8 = owner->unk8 + size;
    self->unk38 = 0;
    self->unk28 = 0;
    self->unk34 = 0;
    self->unk2C = 0;
}
