#include "types.h"
/* insmenu 0x004ED160 -- the 004EC1C0 latch with a short-circuit OR in front.
 * `bnel $2, $0, .L18C` carries `addiu $2, $0, 1` -- the constant the store at
 * .L18C uses -- so the first predicate's true edge jumps straight into the
 * `D = 1` arm.  That is `||`, and the `return 1` still belongs inside both
 * arms because retail materialises the 1 twice. */
extern s32 insmenu_InsectVsTopPanelIsVisible_4f2ac0(void);
extern s32 insmenu_InsectVsConfirmDialogIsVisible_4ee860(void);
extern u8 D_00484304;
s32 insmenu_InsectVsStateWaitFade_4ed160(void)
{
    if (insmenu_InsectVsTopPanelIsVisible_4f2ac0() != 0 || insmenu_InsectVsConfirmDialogIsVisible_4ee860() != 0) {
        D_00484304 = 1;
        return 1;
    }
    D_00484304 = 0;
    return 1;
}
