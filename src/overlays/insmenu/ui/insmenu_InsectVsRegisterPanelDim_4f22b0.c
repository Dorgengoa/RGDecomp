#include "types.h"

/* insmenu 0x004F22B0 (84 bytes, 21 instructions) -- BYTE-IDENTICAL
 * (L1 84-byte-family pass, 2026-08-26).  Widget tint helper, one of a
 * SEVEN-MEMBER family (0x004EEF70 0x004EFB40 0x004F0450 0x004F0F20 0x004F1A30
 * 0x004F22B0 0x004F29C0) differing only in the two field ids.
 *
 * ** THE LEVER -- this closed all seven at once. **  The first three float
 * arguments are the LITERAL 0.6f, not a global.  The old draft wrote
 * `extern f32 D_0047D288;` (gp - 0x7EE8) and sat at 4 bad words, recorded for
 * six sessions as a bounded "gp-float prologue rotation" negative.
 * 0x0047D1D0-0x0047D7FF is not a table of globals: it is mwcc's `.lit4` FLOAT
 * LITERAL POOL, and the word at 0x0047D288 is 0x3F19999A = 0.6f.  Both
 * spellings emit `lwc1 $f12, -0x7EE8($28)`, but mwcc PINS a load of an extern
 * global at its use while a pool entry is a known constant with no alias
 * hazard and hoists freely -- which is precisely retail's schedule
 * (`lui $2,0x3F80 / lwc1 $f12,gp / lui $4,%hi / sd $31 / mtc1 $2,$f15 /
 * addiu $4,%lo`).  Writing the literal fixed the rotation with no pragma, no
 * local, no volatile and no declaration reorder.  Same finding as title's
 * 0x004E9F00; see memory levers.d/mwcc-float-literal-pool.md.
 *
 * ** LINK DEPENDENCY -- READ BEFORE ADDING THIS TO config/ocunits/insmenu.txt. **
 * The literal makes mwcc emit a `.lit4` section with an `@N` symbol and an
 * R_MIPS_LITERAL relocation, so the object's own `lwc1` immediate is 0 until
 * the pool address is resolved.  title solves this in scripts/t_olink.py
 * (lines 391-399, calling t_lit4.patch); scripts/i_olink.py has NO such hook,
 * so as of this pass the insmenu link would emit `C78C0000` where retail has
 * `C78C8118` -- ONE bad word, at text+0x8.  Scored MATCH through
 * build/os_im01.py, which is dv_osbuild plus that retarget (build/lit4_im01.py).
 * The insmenu lcf already never collects `.lit4`, so the port is the hook only.
 *
 * `lui 0xFF1A / ori` is a 32-bit unsigned colour constant; the two `mov.s`
 * copies are one value passed as three float arguments.
 */

extern const u8 D_004FA180[];

extern void func_2905B0(const void *a, s32 b, f32 x, f32 y, f32 z, f32 w);
extern void func_2907D0(const void *a, s32 b, s32 rgba, s32 d);

void insmenu_InsectVsRegisterPanelDim_4f22b0(void)
{
    func_2905B0(D_004FA180, 0x15, 0.6f, 0.6f, 0.6f, 1.0f);
    func_2907D0(D_004FA180, 0x3D, 0xFF1A1A1A, 1);
}
