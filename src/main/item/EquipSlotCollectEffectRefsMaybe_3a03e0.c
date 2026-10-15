#include "types.h"

/* Three nested guards (global pointer non-null, its +0x44 field non-null,
   arg0's +0x4 field non-null) around a forwarding call whose result becomes
   this function's own return value; any failed guard instead returns the
   4th argument unchanged.  This ABI passes up to 8 integer args in
   registers (a0-a3 then t0-t3), so m2c's original 6-wide guess for the
   callee is plausible despite the tiny 0x10-byte frame -- confirmed against
   other already-matched 5/6-arg externs in the tree (e.g.
   src/s31a/MeshRaycastWrapper_16f610.c, src/s31a/StringCtorFromCStr_1a2110.c).  AbilityDataCollectEffectRefsMaybe_3f4290 is not
   itself matched yet.

   ⚠ RESIDUE: 24 words against retail's 25, otherwise the RIGHT SHAPE --
   same three guards, same `bnel`-with-shared-exit pattern on the inner two,
   same dedicated early epilogue on the outer one.  Retail unconditionally
   saves BOTH incoming a1 *and* a2 into callee-saved t1/t0 right at entry
   (`daddu $9,$5,$0` then `daddu $8,$6,$0`), before the first guard even
   runs.  Saving a1 is required -- register a1 gets reused for the t5 temp
   (`lw $5,0x4($4)`) -- but a2's register is NEVER otherwise touched, so an
   explicit `s32 savedA2 = a2;` is a value the compiler can (and does) prove
   redundant and deletes.  Marking it `volatile` stops the deletion but
   forces a real 0x10-byte stack spill (frame grows to 0x20, 5 bad words in
   a completely different shape) instead of the plain register copy retail
   emits -- worse, not better.  No spelling tried gets mwcc to keep a dead
   register-to-register copy without also making it memory-resident:
   swapping declaration order of savedA2/result, initialising it at
   declaration vs. by a separate statement, and reordering the guard
   early-returns were all inert (still 24, same missing instruction). */

typedef struct Obj03e0 {
    u8 pad0[0x44];
    s32 unk44;
} Obj03e0;

typedef struct Arg03e0 {
    u8 pad0[0x4];
    s32 unk4;
} Arg03e0;

extern Obj03e0 *D_0048374C;
extern s32 AbilityDataCollectEffectRefsMaybe_3f4290(s32, s32, s32, s32, s32);

s32 EquipSlotCollectEffectRefsMaybe_3a03e0(Arg03e0 *a0, s32 a1, s32 a2, s32 a3)
{
    s32 result;
    s32 t3;
    s32 t5;

    result = a3;
    if (D_0048374C == 0) {
        return result;
    }
    t3 = D_0048374C->unk44;
    if (t3 == 0) {
        return result;
    }
    t5 = a0->unk4;
    if (t5 == 0) {
        return result;
    }
    result = AbilityDataCollectEffectRefsMaybe_3f4290(t3, t5, a1, a2, a3);
    return result;
}
