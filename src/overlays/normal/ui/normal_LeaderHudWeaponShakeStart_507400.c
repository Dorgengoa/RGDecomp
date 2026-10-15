/* MATCH -- byte-identical, session 40 (2026-09-07).  ONE edit, from 20 bad.
 *
 * The 20 words were a pure ROTATION of the $31 save/restore: retail issues
 * `sd $31` as the 3rd instruction and `ld $31` as the last-but-two, while our
 * object sank the save four slots and hoisted the restore fifteen.  Every
 * other instruction, in both objects, was already retail's and in retail's
 * order -- the C had been right since session 19.
 *
 * THE DEFECT WAS THE DATA DECLARATION, not the code.  This file spelled the
 * 0x14-byte record as six `extern const` SCALARS written through a
 * cast-away-const (`*(s32 *)&D_00527C20 = 1;`).  Its two MERGED siblings on
 * the same record -- normal_LeaderHudWeaponShakeStep_5072a0 and normal_LeaderHudResetState_5077f0 -- already
 * spelled it as ARRAYS (`extern s32 D_00527C20[4];`, indexed `[0]`), and that
 * is the spelling retail's source used.  Switching to it fixes all 20 words at
 * once.
 *
 * WHY IT MOVES THE SCHEDULER.  A `const` scalar is an object mwcc can prove
 * distinct from the stack slot holding $31, so the list scheduler is free to
 * move `sd $31`/`ld $31` across the stores into it; an incomplete-array extern
 * is not, so the save and the restore stay pinned outside every store.  This
 * is the same alias-hazard axis that closed the sibling family
 * normal_ShopMenuFrameFadeOut_50a2f0 / normal_ShopMenuBuyQtyCloseState_50d110 from the other side
 * ([[mwcc-float-literal-pool]]: a pool literal hoists, an extern is pinned).
 * ⚠ Dropping `const` alone is NOT the fix -- a non-const SCALAR extern drops
 * under the small-data threshold and the unit compiles to 31 gp-relative
 * words ([[im-gp-array-sdata-threshold]]).  The array is what buys both the
 * lui/%lo addressing AND the pin. */
#include "types.h"
/* normal 0x00507400 -- initialises the 0x14-byte overlay-data record at
 * 0x00527C20 (the shop camera shake; see normal_LeaderHudWeaponShakeStep_5072a0 for the field
 * meanings).  A real `div`/`mfhi` IS a source-level `%`; 0x41280000 is 10.5f
 * and 0x40A00000 is 5.0f. */
extern s32 D_00527C20[4];
extern s32 D_00527C24[4];
extern s32 D_00527C28[4];
extern s16 D_00527C2C[8];
extern s16 D_00527C2E[8];
extern f32 D_00527C30[4];
extern s32 func_133710(void);

s32 normal_LeaderHudWeaponShakeStart_507400(void)
{
    s32 t;

    D_00527C20[0] = 1;
    D_00527C24[0] = 8;
    D_00527C28[0] = 0x13;
    t = func_133710();
    D_00527C30[0] = 10.5f + (f32)(t % 10) / 5.0f;
    D_00527C2E[0] = 3;
    D_00527C2C[0] = 0;
    return 0;
}
