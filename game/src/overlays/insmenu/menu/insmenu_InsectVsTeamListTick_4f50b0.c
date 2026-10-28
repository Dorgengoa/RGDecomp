/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamListTick_4f50b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F50B0 (88 bytes, 22 instructions, 3 calls) -- hand the two
 * pad banks to the list widget and return the caller's handle unchanged.
 *
 * The first parameter is UNUSED -- `$4` is overwritten with 0 for the first
 * call before anything reads it -- so the arity is not visible from inside.
 * It is written as two parameters because the returned value is `$5`, which
 * only a second parameter can be.
 */

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570;
extern u8 D_004B27E0;

/*rgp*/
/*rgp*/
/*rgp*/

void *insmenu_InsectVsTeamListTick_4f50b0(s32 unused, void *h)
{
    SaveStepAndGetStatus_37bac0(0);
    MenuGridCursorInputPad2_28e100(insmenu_D_004FA1A0, (void *)&D_004B2570, (void *)&D_004B27E0, 0);
    SaveProgressBarUpdate_3774d0(insmenu_D_004FA180);
    return h;
}
