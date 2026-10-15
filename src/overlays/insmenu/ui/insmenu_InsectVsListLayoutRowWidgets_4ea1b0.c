#include "types.h"

/* insmenu 0x004EA1B0 (224 bytes) -- walk the item rows and set each one's tint
 * and Y, brightening the rows below `lit` back to full.
 *
 * ★ The repeated `addiu $3, $16, 0x32` + `andi $5, $3, 0xFFFF` at all three
 * call sites is the CALLEE's u16 id parameter, recomputed rather than CSEd,
 * so the source passes the plain `i + 0x32` and the mask is the prototype's.
 * ★ `sll 3 / subu / sll 3 / addu` is a multiply by 57, the row pitch.
 * ★ The bound is recomputed every iteration (`addiu $3, $18, -0x1` sits inside
 * the latch), so it is written as `i < n - 1` and not hoisted into a local.
 *
 * ⚠⚠  * CLOSED (L3, 2026-08-26), 56/56 words byte-identical.  D_0047D3D4 was NOT A
 * GLOBAL: 0x0047D1D0-0x0047D7FF is mwcc's `.lit4` FLOAT LITERAL POOL and
 * asm/data/main_data.data.s reads `.float 0.400000006` at that address.  The
 * one-token fix is `dim = 0.4f;` with the `extern f32` DELETED.  All three
 * residue words -- the entire "retail materialises lui $2,0x3F800000 before the
 * id add" story below -- fell out at once, because a pool entry is a known
 * constant with no alias hazard and schedules freely, while a load of an extern
 * global is pinned at its use.  See [[mwcc-float-literal-pool]].
 *
 * !!! ADMISSION IS BLOCKED ON A PIPELINE PORT, NOT ON MATCHING.  Writing the
 * literal makes mwcc emit a `.lit4` section with an `@N` symbol and an
 * R_MIPS_LITERAL relocation; scripts/i_olink.py has NO `.lit4` pass, so linking
 * this unit as it stands leaves the gp immediate at 0 -- ONE wrong word, which
 * a length guard would pass.  scripts/t_lit4.py already does the retarget and
 * is called from t_olink for title; i_olink needs the same call.
 * PROOF: bare `build/dv_osbuild.py insmenu` -> 1 bad at 0x004EA270 (ours
 * C78C0000, retail C78C8264); the SAME object through build/lit4_im03.py (a
 * one-line clone of t_lit4.py) -> MATCH.
 * Every prior enumeration in this file (7 source spellings, 117 pragmas) held
 * the `extern f32` spelling FIXED, which is why they were uniformly negative.
 *
 * SUPERSEDED PARK NOTE FOLLOWS.
 * PARKED AT 3 WORDS AND THE LENGTH IS RIGHT (56 words) -- deliberately OUT
 * of config/ocunits/insmenu.txt; the length guard would pass it.
 * The residue is scheduling in the FIRST call's argument setup only: retail
 * materialises `lui $2, 0x3F800000` BEFORE `addiu $3, $16, 0x32` and so the id
 * add lands in $3; ours does the add first and takes $2.  The second call site,
 * where all four float arguments are 1.0f, already matches.
 * Enumerated and NULL: the global read inline instead of via `dim`, `dim`
 * declared first, explicit `(u16)` casts at all three sites, `u32` callee
 * parameters, `57 * i` vs `i * 57`, a named `one = 1.0f` local (7 spellings,
 * build/imv_ea1b0.py) -- and the full 117-variant knob screen
 * (build/im_s10_knob_ea1b0.txt), every cell at 3 or worse.
 * ⚠ A `row = i + 0x32;` local scores 47: the id is RECOMPUTED at each site by
 * design, so do not re-try hoisting it.
 */

extern const u8 D_004FA180[];

extern void func_2905B0(const void *a, u16 id, f32 r, f32 g, f32 b, f32 t);
extern void func_290F60(const void *a, u16 id, s32 x, s32 y);

void insmenu_InsectVsListLayoutRowWidgets_4ea1b0(s32 id, s32 n, s32 lit)
{
    s32 i;
    f32 dim;

    for (i = 0; i < n - 1; i++) {
        dim = 0.4f;
        func_2905B0(D_004FA180, i + 0x32, dim, dim, dim, 1.0f);
        func_290F60(D_004FA180, i + 0x32, id, i * 57 + 0x26);
        if (i < lit) {
            func_2905B0(D_004FA180, i + 0x32, 1.0f, 1.0f, 1.0f, 1.0f);
        }
    }
}
