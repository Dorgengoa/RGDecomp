#include "types.h"

/* Event-stream opcode dispatcher: reads one byte at p, hands the two objects
   OpStackPop_3da040(ctx) returns to a per-opcode handler, and returns p + 1.

   Retail FALLS THROUGH the `bnez $18` into `daddu $2,$0,$0`, so the source
   guard is `if (p == 0) return 0;`.  The two OpStackPop_3da040 calls take the SAME
   argument and are not CSEd; the FIRST result is the handler's SECOND argument
   ($17) and the second result is its FIRST ($16).

   MEASURED, two words: `op = *p;` must be written BEFORE the first call --
   OpStackPop_3da040 may write through `p`, so a read placed after it cannot sink
   into the jal's delay slot and costs a `nop`.  And `op` is an `s32`, not a
   `u8`: a `u8` makes mwcc mask the switch operand (`andi $2,$20,0xFF`) where
   retail feeds `sltiu $1,$20,0x18` straight off the `lbu`.

   jtbl_00466700 is 24 entries and entry 0 points at .L003DAAC4 -- the shared
   `addiu $2,$18,0x1` that every arm and the out-of-range `beql` also reach --
   so `case 0:` is an EMPTY ARM that still needs its label (the cohort's reading
   2).  Entries 1..23 are the identity permutation over the physical blocks, so
   the source spells case 0 first and then 1..23 in order.

   `VariantPoolAlloc_3da080(ctx, 1)` is written INSIDE each of the 23 non-empty arms, not
   once after the switch: case 0 reaches .L003DAAC4 without it.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  ScriptBinaryOpExec_3da740  00466700  60   # jtbl_00466700, 24 cases */

extern void *OpStackPop_3da040(s32);
extern void VariantPoolAlloc_3da080(s32, s32);

extern void VariantPow_36b0f0(void *, void *);
extern void *VariantLogicalNot_36b2b0(void *);
extern void *VariantBitNot_36b480(void *);
extern void VariantShl_36b620(void *, void *);
extern void VariantShr_36b880(void *, void *);
extern void VariantXor_36bae0(void *, void *);
extern void VariantOr_36bd40(void *, void *);
extern void VariantAnd_36bfa0(void *, void *);
extern void VariantMod_36c200(void *, void *);
extern void VariantDiv_36c4d0(void *, void *);
extern void VariantMul_36c7a0(void *, void *);
extern void VariantSub_36ca80(void *, void *);
extern void VariantAdd_36ccf0(void *, void *);
extern void VariantLogicalOr_36cf60(void *, void *);
extern void VariantLogicalAnd_36d230(void *, void *);
extern void VariantLessEqual_36d500(void *, void *);
extern void VariantGreaterEqual_36d7a0(void *, void *);
extern void VariantLess_36da40(void *, void *);
extern void VariantGreater_36dcc0(void *, void *);
extern void VariantNotEqual_36df40(void *, void *);
extern void VariantEqual_36e1e0(void *, void *);
extern void VariantFireGetCallbackOnce_36e4c0(void *, s32, s32);
extern void VariantToInteger_36ea70(void *);
extern void VariantCopy_36f5e0(void *, void *, s32);

u8 *ScriptBinaryOpExec_3da740(s32 ctx, s32 a1, s32 a2, u8 *p)
{
    void *a;
    void *b;
    s32 op;

    if (p == 0) {
        return 0;
    }
    op = *p;
    a = OpStackPop_3da040(ctx);
    b = OpStackPop_3da040(ctx);
    if (a == 0 || b == 0) {
        return 0;
    }
    switch (op) {
    case 0:
        break;
    case 1:
        VariantEqual_36e1e0(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 2:
        VariantNotEqual_36df40(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 3:
        VariantGreater_36dcc0(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 4:
        VariantLess_36da40(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 5:
        VariantGreaterEqual_36d7a0(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 6:
        VariantLessEqual_36d500(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 7:
        VariantLogicalAnd_36d230(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 8:
        VariantLogicalOr_36cf60(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 9:
        VariantFireGetCallbackOnce_36e4c0(b, 0, 0);
        VariantCopy_36f5e0(b, a, 1);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 10:
        VariantAdd_36ccf0(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 11:
        VariantSub_36ca80(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 12:
        VariantMul_36c7a0(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 13:
        VariantDiv_36c4d0(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 14:
        VariantToInteger_36ea70(b);
        VariantToInteger_36ea70(a);
        VariantDiv_36c4d0(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 15:
        VariantMod_36c200(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 16:
        VariantAnd_36bfa0(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 17:
        VariantOr_36bd40(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 18:
        VariantXor_36bae0(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 19:
        VariantPow_36b0f0(b, a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 20:
        VariantLogicalNot_36b2b0(b);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 21:
        VariantBitNot_36b480(b);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 22:
        VariantShl_36b620(VariantBitNot_36b480(b), a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    case 23:
        VariantShr_36b880(VariantBitNot_36b480(b), a);
        VariantPoolAlloc_3da080(ctx, 1);
        break;
    }
    return p + 1;
}
