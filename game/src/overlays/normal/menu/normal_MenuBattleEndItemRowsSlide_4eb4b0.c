/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndItemRowsSlide_4eb4b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_dead_assignments off
/* SESSION 41 (n41E, SOLO): CLOSED -- LENGTH-WRONG (0x12C vs 0x134) -> BYTE-
 * IDENTICAL at 77 words.  TWO edits, neither enough alone:
 *
 * 1. `#pragma opt_dead_assignments off`, from the whole-board pragma sweep
 *    (build/wf-normal/s41/pragboard.py).  It alone fixes the LENGTH: 4 words
 *    short -> exact, 9 bad.  ARMED (a bogus pragma name reproduces the
 *    length-wrong object).  The same sweep also moved normal_BtlChgMenuItemGridLayout_5000b0 from
 *    length-wrong to right-length; that unit closed the same session.
 * 2. `pAC` and `pB0` HOISTED ABOVE the guard and the guard written THROUGH
 *    THEM (`*pB0 != *pAC`), with **pAC declared FIRST**.  Retail materialises
 *    `addiu $5,$16,0xAC` BEFORE the `c.eq.s` and `addiu $4,$16,0xB0` in the
 *    branch's delay slot -- so both pointers exist before the compare, and the
 *    branch is a plain `bc1t`, not the `bc1tl` our member-spelled compare got.
 *    ⚠ ORDER IS LOAD-BEARING: pB0 declared first is 10 bad; comparing
 *    `*pAC != *pB0` is 3; leaving the compare on the members with the pointers
 *    hoisted is LENGTH-WRONG the other way (0x138).
 *    This retires this header's own conclusion below that the residue needed
 *    retail's row pointer to be "genuinely out of scope" -- the opposite was
 *    true: the pointers had to be created EARLIER, not later.  The scope arms
 *    recorded there were all measured at the LENGTH-WRONG baseline, where no
 *    address-CSE edit could show anything ([[two-edit-cross-beats-count-ranking]]).
 */
/* normal 0x004EB4B0 -- eases each live row's bar toward its target and, once
 * parked (state 2), counts its dwell up to 100.  1.2f is MAIN's `.lit4` pool
 * entry at 0x0047D354. */
/* SESSION 38 (n38g): 74/77 words (3 short) -> 75/77 words (2 short), still
 * PARKED (right shape, short by 2).
 * Fix applied and CONFIRMED: use TWO separate named pointers `pB0`/`pAC`
 * (each `&p->fAC[i].fXX`, taken ONCE right before use) instead of a single
 * `Row *r = &p->fAC[i];` reused for every field -- retail materialises
 * SEPARATE address registers for `&fB0` and `&fAC` (computed off the row
 * base with LARGE immediate offsets, 0xB0/0xAC) rather than one shared
 * struct pointer with small member offsets. This closed 1 of the 3 missing
 * words and got the whole middle of the function into the right shape.
 * Residue (2 words short): the trailing `if (p->fAC[i].fB8 == 2) { fBA++;
 * ... }` block. Retail RECOMPUTES the row's base address from scratch here
 * (`sll $3,$17,4` / `addu $5,$18,$3`, i.e. `p + i*16` again) instead of
 * reusing the row pointer already live from the block above (which is
 * still valid and unclobbered -- our object proves it, by reusing it
 * without ill effect). Tried: giving this block its OWN named local
 * `Row *r2 = &p->fAC[i];` to try to force a fresh materialisation --
 * WORSE, not better: it allocated r2 to a whole NEW callee-saved register,
 * growing the frame by one qword (2 words in the prologue/epilogue alone)
 * and shifting every single word after the prologue by one slot (73 bad).
 * Reverted. This reads as retail's real source having the row pointer
 * genuinely OUT OF SCOPE by this point (e.g. declared inside the
 * `*pB0 != *pAC` block only), forcing a fresh `p->fAC[i]` recompute that
 * mwcc's own address-CSE nonetheless elides for OUR spelling because our
 * `p->fAC[i].fB8`/`.fBA` accesses sit in the same C scope as `pB0`/`pAC`
 * and get commoned with them regardless of C-level pointer lifetimes.
 * Also tried: nesting `pB0`/`pAC`'s declarations INSIDE the
 * `p->fAC[i].fB0 != p->fAC[i].fAC` block (closing their C scope before the
 * `fB8` test, current source shape) -- NULL, identical 75/77 object.
 * Scope alone does not break mwcc's address CSE here. */
typedef struct Row {
    f32 fAC;
    f32 fB0;
    f32 fB4;
    s16 fB8;
    s16 fBA;
} Row;

typedef struct N {
    u8  pad000[0x14];
    u8  f014[0x98];
    Row fAC[4];
} N;

extern s32 normal_D_00527000[];

/*rgp*/

void normal_MenuBattleEndItemRowsSlide_4eb4b0(N *p)
{
    s32  i;

    for (i = 0; i < 4; i++) {
        if (normal_D_00527000[i] > 0 || normal_D_00527000[i] == -0xFF) {
            f32 *pAC = &p->fAC[i].fAC;
            f32 *pB0 = &p->fAC[i].fB0;
            if (*pB0 != *pAC) {
                *pB0 += p->fAC[i].fB4;
                p->fAC[i].fB4 += 1.2f;
                if (*pB0 >= *pAC) {
                    *pB0 = *pAC;
                    p->fAC[i].fB4 = 0.0f;
                    p->fAC[i].fB8 = 2;
                }
                UiSetWidgetPos_290f60(p->f014, (i + 1) * 3, 0xF, (s32)*pB0);
            }
            if (p->fAC[i].fB8 == 2) {
                p->fAC[i].fBA++;
                if (p->fAC[i].fBA >= 0x64) {
                    p->fAC[i].fBA = 0x64;
                }
            }
        }
    }
}
