/* rgp:protos */
#define RGP_SELF_title_TitleLoadTick_4eed60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EED60 -- one guarded call then three unconditional
 * ones.  The incoming first argument is never used; only the second is, as
 * the guard.
 *
 * `lui $5, 0x4B` + `addiu $5, $5, 0x2570` is the absolute address of a
 * main-image object, so it has to be `const` -- a plain extern comes out
 * gp-relative.
 */

extern void *D_004841E8;
extern void *D_00484174;
extern u8 D_004B2570;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleLoadTick_4eed60(void *o, s32 flag)
{
    if (flag != 0) {
        UiEntryListSelectByTag_28ea90(D_004841E8, 0x7532, 0);
    }
    SaveStepAndGetStatus_37bac0(0);
    MenuGridCursorInput_28e170(D_004841E8, (void *)&D_004B2570, 0, 0);
    SaveProgressBarUpdate_3774d0(D_00484174);
    return 1;
}
