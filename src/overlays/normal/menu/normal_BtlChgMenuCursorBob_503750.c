/* === SESSION 52 (2026-09-08, SOLO): **BYTE-IDENTICAL**, MERGED.  Five
 * sessions of "nothing reachable from C lets retail's D_004844E8 load cross
 * the register saves" ended on a lever that was ALREADY WRITTEN DOWN -- in the
 * sibling normal_BtlChgMenuAbilityConfirmCursorBobCb_4fc380, which is merged and does exactly this:
 *
 *     extern const f32 D_004844E8 __attribute__((section(".sdata")));
 *     dd = (*(f32*)&D_004844E8);          / * read through the const decl * /
 *     dd += 0.1570796371f;
 *     (*(f32*)&D_004844E8) = dd;          / * write through a cast * /
 *
 * MECHANISM ([[mwcc-const-sdata-load-hoist]]): the function BOTH READS AND
 * WRITES this gp global, and mwcc will not hoist a load of a WRITTEN extern
 * across the prologue's stack stores.  Declaring the extern `const` removes
 * the alias barrier so the load schedules first; the `.sdata` section
 * attribute is what keeps it gp-addressed (plain `extern const` is
 * lui-addressed and costs 5 words -- measured on 004fc380).  The s32 header
 * below diagnosed the residue EXACTLY right ("a .lit4 load HOISTS across the
 * prologue stores, a gp EXTERN load does NOT") and named the missing half; it
 * just never tried const-ing the extern.
 * `volatile` on the first read is INERT here (004fc380 needs it, this one does
 * not): both spellings give object 8c7c4a6e.  Installed without it.
 * MEASURED NULLS at the OLD baseline, so they are not re-ground: reading the
 * global into a local first, `explicit_add`, `0.157f + X`, an inline
 * `*(const f32 *)&X` cast at the read site, `0.0f < X`, and a named 0.0f seed
 * are ALL still 8 bad (three distinct objects, same 8 addresses -- the
 * schedule does not move).  The const DECLARATION is the whole lever.
 * ⚠ CHECK BEFORE COPYING: no other TU declares D_004844E8 (grepped). */
#include "types.h"
/* normal 0x00503750 -- the phase-advance / func_290F50 readout family; the
 * matched normal_FUN_004FCF10 is the template.  The two gp floats at
 * -0x7DA0 (0x0047D3D0) / -0x7F74 (0x0047D1FC) are MAIN's `.lit4` POOL, not
 * variables: they are written as the literals 0.1570796371f and 3.14159274f
 * and the link retargets them.  Score with build/wf-normal/s32/nscore.py --
 * plain dv_osbuild.py reads the unresolved `@N` GPREL field as a bad word.
 *
 * SESSION 32 (lane nc32p) -- PARKED at 57 words / 8 bad, LENGTH CORRECT,
 * 212 measured arms over 7 bulk decks, THREE distinct objects reached.
 *
 * The residue is ONE scheduling fact, not a spelling.  Register ALLOCATION
 * is already retail's (f2 = the global, f1 = the 0.157 literal, s1/s2/s0 =
 * a0/a2/a3); the 8 words are a pure PERMUTATION of the 12-word prologue:
 *   retail  sp | Lg | ra | Lk | sq s2 | sq s1 | mtc1 | sq s0 | daddu s1 |
 *           add.s | daddu s2 | daddu s0
 *   ours    sp | ra | Lk | sq s2 | mtc1 | sq s1 | daddu s2 | sq s0 |
 *           daddu s1 | Lg | daddu s0 | add.s
 * where Lg = `lwc1 $f2,-0xC88($gp)` and Lk = `lwc1 $f1,-0x7DA0($gp)`.
 * Retail hoists the GLOBAL load above `sd $ra`; we hoist the LITERAL load
 * and leave the global load pinned at its use.
 *
 * MEASURED MECHANISM: a `.lit4` load HOISTS across the prologue stores, a
 * gp EXTERN load does NOT.  Spelling 0.1570796371f as `extern f32
 * D_0047D3D0` inverts the pair into retail's RELATIVE order (Lg before Lk)
 * but pins both at the use -- 57 words / 11 bad, object 91892a0b3083.  So
 * the missing half is whatever lets retail's load of D_004844E8 cross the
 * register saves; nothing reachable from C in this lane does that.
 *
 * ARMED NULLS at this baseline (identity arm reproduced 8 bad in every
 * deck): the whole call-argument axis (6 shapes x 2 bodies x 3 `t`
 * spellings, all ONE object); C++ with extern "C" (exactly the C object);
 * 43 pragma arms incl. every opt_* / scheduling / usefloatacc /
 * fast_fptosi name and a bogus-name arming arm; `volatile` and
 * `const`-cast spellings of the global; union / struct / array spellings;
 * signature width and a 5th parameter; constant respellings.  The only
 * other correct-length object is 6ac448a510f4 (also 8 bad) which merely
 * SWAPS f1/f2 -- a step away from retail, not a cross half.
 *
 * Class oracle is EMPTY: only 6 of 20,184 retail listings put a gp load
 * between `addiu $sp` and `sd $ra` -- MenuCursorBobUpdate_2a9c00, MenuWidgetPulseColor_2b3200,
 * MenuPartyFadeSequenceStep_2b9240, NpcObjTableCharaLoadUpdate_2faac0 (none decompiled) and the two normal siblings
 * normal_BtlChgMenuAbilityConfirmCursorBobCb_4fc380 / this one.  Merged normal_BtlChgMenuTacticsCursorBobCb_4fcf10 has the same
 * C and does NOT hoist, so the lever is not in the phase-advance spelling.
 */
/* SESSION n38f (2026-09-06): tried a differently-shaped rewrite carried over
 * from build/wf-parked/normal/normal_BtlChgMenuCursorBob_503750.c (a separate lineage of
 * this draft) -- named locals `h`/`w` for the two computed sums, direct
 * `p->f000` field access instead of `r->f00`, and the phase float named as
 * `v` before being written back.  CONFIRMED INERT: still 57 words / 8 bad,
 * and --verbose shows the SAME 8-instruction residue class as this header's
 * s32 diagnosis (the Lg/Lk prologue-load permutation) -- a different C
 * shape does not reach past the scheduling floor either.  Reverted to the
 * Rec-struct spelling below; do not re-try the Box/h/w rewrite. */
typedef struct Rec {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    u8  pad08[0x10 - 8];
    s16 f10;
    s16 f12;
} Rec;

extern const f32 D_004844E8 __attribute__((section(".sdata")));   /* gp - 0xC88 */
extern void *D_0048449C;          /* gp - 0xCD4 */

extern f32  func_128FD0(f32 x);
extern void func_290F50(void *p, s32 id, s32 c, s32 d, s32 e, f32 x);

s32 normal_BtlChgMenuCursorBob_503750(Rec *r, s32 unused, s32 x, s32 y)
{
    f32 t;
    f32 dd;

    dd = (*(f32*)&D_004844E8);
    dd += 0.1570796371f;
    (*(f32*)&D_004844E8) = dd;
    if ((*(f32*)&D_004844E8) > 0.0f) {
        (*(f32*)&D_004844E8) = (*(f32*)&D_004844E8) - 3.14159274f;
    }
    t = 12.0f * func_128FD0((*(f32*)&D_004844E8));
    func_290F50(D_0048449C, 0x40,
                (s32)((f32)x + (t + (f32)(r->f00 + r->f10 * r->f04))),
                y + (r->f02 + r->f12 * r->f06), 0, 0.5f);
    return 1;
}
