/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuWeaponConfirmCursorBobCb_4fbe20 1
#include "port/game_protos.h"
#line 1
/* BYTE-IDENTICAL (lane L2, tag ns02) -- but ONLY THROUGH THE `.lit4`
 * RETARGET.  Scored with build/dv_oslit_ns02.py (build/lit4_ns02.py); plain
 * build/dv_osbuild.py reads the unresolved `@N` GPREL field as a bad word.
 * !! DO NOT ADD TO config/ocunits/normal.txt until normal's link path runs
 * the retarget -- unpatched the gp immediate links as 0, a WRONG image of
 * the RIGHT LENGTH.  Patch site(s) printed by the scorer:
 *   @7  -> 0x0047D3F4 (0.1963495463f)  text+0x0008  C78C0000 -> C78C8284
 */
#include "types.h"
/* normal 0x004FBE20 -- sibling of normal_FUN_004FC1E0's widget-0x50 placement,
 * driven off its own record instead of the 0x55FA one.  0x40C00000 is 6.0f;
 * the PRODUCT is named so mwcc keeps mul.s + add.s instead of contracting to
 * adda.s/madd.s.  Only the X coordinate carries the jitter. */

typedef struct Rec {
    s16 f00;
    s16 f02;
    u8  pad04[2];
    s16 f06;
    u8  pad08[0x10 - 8];
    s16 f10;
    s16 f12;
} Rec;

extern f32   D_004844B8;          /* gp - 0xCB8  */
extern void *D_0048449C;          /* gp - 0xCD4  */
extern f32   D_0047D3F0;          /* gp - 0x7D80 */

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuWeaponConfirmCursorBobCb_4fbe20(Rec *r)
{
    f32 t;

    PhaseAdvanceWrapPi_28b630(&D_004844B8, 0.1963495463f);
    t = 6.0f * Sinf_128fd0(D_004844B8);
    UiMoveWidgetUniform_290f50(D_0048449C, 0x50, (s32)(t + (f32)(r->f00 + 0x52 + r->f10 * 0x50)), r->f02 + 0x88 + r->f12 * r->f06, D_0047D3F0, 0

);
    return 1;
}
