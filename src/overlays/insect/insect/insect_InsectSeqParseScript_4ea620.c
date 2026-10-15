#include "types.h"
/* insect 0x004EA620 -- 236 B / 59 words.  Sibling of the func_134A98 loader
 * family seeded by src/wf/insect/insect_InsectAbilityTableLoad_51d0b0.c.
 *
 * The guard is transcribed verbatim from the seed (and from the already-matching
 * insect_InsectBattleHelpStep_50a9f0.c, which carries the identical five-statement run
 * func_14D810 / 134BB0 / 134A98 / 14D830 / 14DAD0):
 *
 *     if (func_134BB0(NAME) < 0x10) { func_134A98(obj, NAME); }
 *
 * with `extern u32 func_134BB0(const char *)` -- the UNSIGNED return is what
 * makes the compare `sltiu $1,$2,0x10`, and the `beql` PAST the call means the
 * call is the fall-through, i.e. a plain positive `if`.  The object handed to
 * func_134A98 is `&a->f04`, which is also what the NEXT statement
 * (func_14D830) takes -- that is why `addiu $4,$18,0x4` appears three times
 * around the branch.
 *
 * The script-VM tail is insect_InsectFormationParseScript_4efde0.c's, verbatim: the same 0xED0-byte
 * frame at $29+0x40 and the same func_15F140/15F270/15F1B0/15F3F0 quartet.
 * !! THIS member has NO context publish -- there is no `sw ..,0x0($28)` in the
 * listing, so no gp global is written across the run call, and there is no
 * trailing `a->m64 = 0` pair either.  Read the gp stores per member.
 *
 * !! THE 14DB10 GUARD MATERIALISES ITS BOOLEAN.  Retail spends a
 * `sltu $2,$0,$2` between the `lw 0x28` and the `bnel` -- a plain
 * `if (h->m28 == 0)` branches on the loaded word directly and is ONE WORD
 * SHORT (that was this unit's whole residue).  The cast-to-u8 of the
 * comparison is the same lever normal_ShopMenuSellItemStatusLayout_50ef80.c uses,
 * `(u8)(func_3D4C20(p) != 0)`.  MEASURED, 14 spellings in one sweep:
 *   0 bad, ONE identical object (26270f0f) --
 *     (u8)(x != 0) == 0 / !(u8)(x != 0) / (s32)(x != 0) == 0 / (u16)(x != 0) == 0
 *     / (u8)(x > 0) == 0 / !!x == 0 / (u8)!!x == 0 / the same with s32 m28
 *   INERT, object == baseline (8a675049), one word short --
 *     x == 0 / (x != 0) == 0 / !(x > 0) / ((x != 0) & 1) == 0 / x <= 0
 *   s32 m28 with `x <= 0` is live but still short (3223b0c0).
 * So the CAST is load-bearing and the member's signedness is not.
 *
 * Frame proof: 3 sq'd callee-saved GPRs (0x30) + sd $31 at 0x30 -> 0x38,
 * rounded to 0x40, + 0xED0 of locals = 0xF10.  Matches `addiu $29,$29,-0xF10`.
 */

typedef struct ScriptVm { u8 raw[0xED0]; } ScriptVm;

typedef struct Obj {
    void *m00;                  /* +0x00 -- the loader handle */
    u8    f04[1];               /* +0x04 -- the sub-object the loader fills */
} Obj;

typedef struct Han {
    u8  pad00[0x28];
    u32 m28;                    /* +0x28 */
} Han;

extern const u8   D_00523B20[];
extern const char D_005248E8[];

extern s32   func_14DB10(void *h, s32 b, s32 c, s32 d);
extern void *func_14D950(void *h, s32 n);
extern void  func_14D810(void *a, void *p, s32 n);
extern void  func_14D830(void *a);
extern void  func_14DAD0(void *h);
extern void  func_134A98(void *a, const char *t);
extern u32   func_134BB0(const char *t);
extern void  func_15F140(ScriptVm *vm);
extern void  func_15F270(ScriptVm *vm, const u8 *cmds);
extern void  func_15F1B0(ScriptVm *vm, s32 b, s32 c);
extern void  func_15F3F0(ScriptVm *vm);

void insect_InsectSeqParseScript_4ea620(Obj *a, s32 b, s32 c, Han *h)
{
    ScriptVm sp40;

    if (h != 0) {
        a->m00 = h;
        if ((u8)(h->m28 != 0) == 0) {
            func_14DB10(h, 2, 0, 0x40);
        }
        func_14D810(a->f04, func_14D950(a->m00, 0x280), 0x280);
        if (func_134BB0(D_005248E8) < 0x10) {
            func_134A98(a->f04, D_005248E8);
        }
        func_14D830(a->f04);
        func_14DAD0(a->m00);
        func_15F140(&sp40);
        func_15F270(&sp40, D_00523B20);
        func_15F1B0(&sp40, b, c);
        func_15F3F0(&sp40);
    }
}
