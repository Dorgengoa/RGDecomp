#include "types.h"
/* normal 0x0050A630 -- mode teardown.  Near-twin of normal_ThinkMenuShutdown_521160.
 * 0x004B2570 is far outside the gp window (_gp 0x00485170 +/- 0x8000), so its
 * extern must be `const` to take %hi/%lo instead of %gp_rel. */
extern const u8 D_004B2570[];
extern void normal_ShopMenuResRelease_50ad90(void);
extern void func_183960(const void *a);
extern void func_183940(const void *a);
extern void *func_206A40(void);
extern void func_42B650(void *a, s32 b);
extern s32 D_004845D4;
extern s16 D_00480638;
extern s32 D_004845B4;
extern s16 D_004845E0;
extern u8  D_004845D8;
extern s16 D_004845E4;

void normal_ShopMenuShutdown_50a630(void)
{
    normal_ShopMenuResRelease_50ad90();
    func_183960(D_004B2570);
    func_183940(D_004B2570);
    func_42B650(func_206A40(), 2);
    D_004845D4 = 0;
    D_00480638 = 1;
    D_004845B4 = 0;
    D_004845E0 = 0;
    D_004845D8 = 0;
    D_004845E4 = 0;
}
