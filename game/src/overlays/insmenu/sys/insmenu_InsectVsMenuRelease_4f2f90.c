/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsMenuRelease_4f2f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F2F90 -- teardown.  0x4B2570 / 0x4B27E0 are unsymbolised
 * main-image data addresses taken by `&extern` so they get %hi/%lo.
 * `h` is a named local because TWO calls share it: retail computes it once
 * and issues `daddu $4, $16, $0` before each. */
extern s32 D_00484104;
extern s16 D_00484300;
extern u8 D_004B2570;
extern u8 D_004B27E0;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsMenuRelease_4f2f90(void)
{
    void *h;

    if (D_00484104 != 0) {
        Zero12Bytes_4366d0(D_00484104);
    }
    insmenu_InsectVsMenuResFree_4f3340();
    PadClearRepeatAll_183960(&D_004B2570);
    PadClearStickDpadThreshold_183940(&D_004B2570);
    PadClearRepeatAll_183960(&D_004B27E0);
    PadClearStickDpadThreshold_183940(&D_004B27E0);
    h = GetMenuResGroup_206a40();
    ResGroupUnloadGroup_42b650(h, 1);
    ResGroupUnloadGroup_42b650(h, 3);
    D_00484104 = 0;
    D_00484300 = 0;
}
