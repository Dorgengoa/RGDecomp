#include "types.h"
/* insmenu 0x004F3340 -- one call on an overlay-data address, return 1.
 * D_004FA1D0 is overlay data (outside the gp window 0x47D170..0x48D170) so the
 * extern MUST be const or it takes a %gp_rel relocation that cannot link. */
extern const u8 D_004FA1D0[];
extern void func_28B0F0(const void *a, s32 b);
s32 insmenu_InsectVsMenuResFree_4f3340(void)
{
    func_28B0F0(D_004FA1D0, 3);
    return 1;
}
