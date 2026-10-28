/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegPwAskAgainStep_4ecbe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004ECBE0 (184 bytes, 48 instructions) -- one page's per-frame
 * update.  Every exit sets the "handled" gp flag and returns 1.
 *
 * ★ `addiu $2, $0, 0x1` immediately before `sb $2, -0xE6C($28)` is the
 * recorded "a constant stored and ALSO returned is one addiu in $2" shape:
 * `D_00484304 = 1; return 1;`, not a scratch register.
 *
 * ★ BLOCK ORDER names the guard polarity twice.  `bnez $2, .L004ED054` puts
 * the D_0048430C != 0 work AFTER the == 0 work, so the source tests `== 0`
 * and the != 0 path is the else.  `bnel` at 0x004ED05C branches away on
 * != 0 carrying `sb $0, -0xE64` in its LIKELY slot, so clearing the flag
 * belongs to the taken side.
 *
 * ★ The 0x004ED078 block is the `insmenu_InsectVsRegPwPanelIsHidden_4f04f0() == 0` arm and retail
 * lays it out LAST, after the outer else -- the cold-block `goto`.  Written as
 * a plain else it lands between the two arms it is not adjacent to.
 */

extern u8 D_00484304;       /* gp - 0xE6C */
extern u8 D_0048430C;       /* gp - 0xE64 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsRegPwAskAgainStep_4ecbe0(void)
{
    if (insmenu_InsectVsTwoPlayerPanelIsVisible_4f1b20()) {
        D_00484304 = 1;
        return 1;
    }
    if (D_0048430C == 0) {
        if (insmenu_InsectVsTitleBannerIsStill_4f2ea0() == 0) {
            D_00484304 = 1;
            return 1;
        }
        if (insmenu_InsectVsRegPwPanelIsHidden_4f04f0() == 0) {
            goto cold;
        }
        insmenu_InsectVsRegPwPanelOpen_4f04b0();
        insmenu_InsectVsTitleBannerSlideIn_4f2ef0();
        D_00484304 = 1;
        return 1;
    }
    if (insmenu_InsectVsRegPwPanelIsOpaque_4f0580() == 0) {
        D_00484304 = 1;
        return 1;
    }
    D_0048430C = 0;
    return 1;
cold:
    D_00484304 = 1;
    insmenu_InsectVsRegPwPanelDim_4f0450();
    insmenu_InsectVsConfirmDialogOpen_4ee7c0(0x26);
    return 1;
}
