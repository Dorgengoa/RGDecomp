#include "types.h"

/* Sibling of RecordSetKind_431110, which is the SAME function shifted by four bytes in
   the sub-object (it writes ->m04 / ->m14 where this one writes ->m00 / ->m10)
   and re-reads ctx->m1188 the same way.  That second `lw $2,0x1188($4)` is a
   SEPARATE SOURCE READ -- write it through ctx, not through the local p.

   Retail FALLS THROUGH the `beq $5,$3` into the switch, so the source guard is
   the positive `if (mode != old)`, and the `sw $5,0x0($2)` in that branch's
   delay slot means the store is unconditional and precedes the compare.
   jtbl_00468FE0 is the identity permutation over 0..7, so the eight arms are in
   source order and each is one call with a different immediate.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  RecordSetMode_431310  00468FE0  20   # jtbl_00468FE0, 8 cases */

extern s32 RecordSetKind_431110(void *, s32);

struct Sub {
    s32 m00;
    s32 m04;
    u8 pad008[0x8];
    s32 m10;
};

struct Ctx {
    u8 pad0000[0x1188];
    struct Sub *m1188;
};

s32 RecordSetMode_431310(struct Ctx *ctx, s32 mode)
{
    struct Sub *p;
    s32 old;

    p = ctx->m1188;
    old = p->m00;
    p->m00 = mode;
    if (mode != old) {
        ctx->m1188->m10 = old;
        switch (mode) {
        case 0:
            RecordSetKind_431110(ctx, 0);
            break;
        case 1:
            RecordSetKind_431110(ctx, 10);
            break;
        case 2:
            RecordSetKind_431110(ctx, 20);
            break;
        case 3:
            RecordSetKind_431110(ctx, 30);
            break;
        case 4:
            RecordSetKind_431110(ctx, 40);
            break;
        case 5:
            RecordSetKind_431110(ctx, 50);
            break;
        case 6:
            RecordSetKind_431110(ctx, 60);
            break;
        case 7:
            RecordSetKind_431110(ctx, 70);
            break;
        }
    }
    return 1;
}
