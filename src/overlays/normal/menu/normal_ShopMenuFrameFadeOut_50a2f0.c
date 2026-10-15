/* MATCH -- byte-identical (session 19, lane r2d).  CLOSED by
 * [[mwcc-float-literal-pool]]: D_0047D4D4 and D_0047D4D8 are NOT gp externs,
 * they are entries in mwcc's float LITERAL POOL (0x0047D1D0-0x0047D7FF), and
 * the words at those addresses read -0.1f and 0.1f.  Writing the literals lets
 * the load hoist freely (an extern is pinned at its use by the alias hazard),
 * which is exactly retail's prologue schedule.  2 bad -> MATCH.
 * The object carries a `.lit4` section; scripts/n_olink.py:375 already calls
 * t_lit4.patch, which retargets it onto retail's pool and empties the section.
 * A bare dv_osbuild/pk_obytecheck run reads this unit as 4 bad -- that is the
 * un-retargeted R_MIPS_LITERAL displacement, NOT a defect.  Score it with the
 * retarget applied (build/wf-normal/var/r2d/lit.py). */
#include "types.h"
/* normal 0x0050A2F0 -- tint pass on the static overlay object D_00527C40. */
extern const u8 D_00527C40[];
extern void func_290690(const void *a, u16 id, f32 x, f32 y, f32 z);
extern void func_290F50(const void *a, u16 id, s32 c, s32 d, s32 e, f32 x);

s32 normal_ShopMenuFrameFadeOut_50a2f0(void)
{
    func_290690(D_00527C40, 1, 0.0f, -0.1f, 1.0f);
    func_290F50(D_00527C40, 4, -0x30, -0xF, 0, 0.1f);
    func_290690(D_00527C40, 4, 0.0f, -0.1f, -1.0f);
    func_290690(D_00527C40, 3, 0.0f, -0.1f, -1.0f);
    return 1;
}
