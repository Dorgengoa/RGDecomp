/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsMenuResFree_4f3340 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F3340 -- one call on an overlay-data address, return 1.
 * insmenu_D_004FA1D0 is overlay data (outside the gp window 0x47D170..0x48D170) so the
 * extern MUST be const or it takes a %gp_rel relocation that cannot link. */
extern u8 insmenu_D_004FA1D0[];
/*rgp*/
s32 insmenu_InsectVsMenuResFree_4f3340(void)
{
    LoadHandleArrayFree_28b0f0(insmenu_D_004FA1D0, 3);
    return 1;
}
