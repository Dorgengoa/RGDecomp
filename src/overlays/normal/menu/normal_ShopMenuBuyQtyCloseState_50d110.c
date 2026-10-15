/* MATCH -- byte-identical (session 19, lane r2d).  CLOSED by
 * [[mwcc-float-literal-pool]]: D_0047D4BC is the pool literal -0.1f.
 * 2 bad -> MATCH.  Carries a `.lit4`; n_olink.py:375 retargets it.  Bare
 * dv_osbuild reads 4 bad -- the un-retargeted displacement, not a defect. */
#include "types.h"
/* normal 0x0050D110 -- same shape as the parked normal_ShopMenuBuyConfirmCloseState_50cb60 twins,
 * four fades then a teardown call. */
extern void *D_004845CC;
extern void *D_004845C4;
extern void func_290690(void *a, u16 id, f32 x, f32 y, f32 z);
extern void func_28EDE0(void *a, s32 b, s32 c);

s32 normal_ShopMenuBuyQtyCloseState_50d110(void)
{
    func_290690(D_004845CC, 0x48, 0.0f, -0.1f, -1.0f);
    func_290690(D_004845CC, 0x46, 0.0f, -0.1f, -1.0f);
    func_290690(D_004845CC, 0x50, 0.0f, -0.1f, -1.0f);
    func_290690(D_004845CC, 0x67, 0.0f, -0.1f, -1.0f);
    func_28EDE0(D_004845C4, 0x7535, 0);
    return 1;
}
