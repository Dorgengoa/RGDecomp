/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuTacticsCursorBobCb_4fcf10 1
#include "port/game_protos.h"
#line 1
/* BYTE-IDENTICAL (lane L2, tag ns02) -- but ONLY THROUGH THE `.lit4`
 * RETARGET.  Scored with build/dv_oslit_ns02.py (build/lit4_ns02.py); plain
 * build/dv_osbuild.py reads the unresolved `@N` GPREL field as a bad word.
 * !! DO NOT ADD TO config/ocunits/normal.txt until normal's link path runs
 * the retarget -- unpatched the gp immediate links as 0, a WRONG image of
 * the RIGHT LENGTH.  Patch site(s) printed by the scorer:
 *   @9  -> 0x0047D3D0 (0.1570796371f)  text+0x0008  C7810000 -> C7818260
 *   @10 -> 0x0047D1FC (3.14159274f)   text+0x002C  C7800000 -> C780808C
 */
#include "types.h"
/* normal 0x004FCF10 -- widget 0x3B's wobble.  Same phase advance as
 * normal_FUN_004FC380 on its own gp slot at -0xC9C; 12.0f jitter on X only,
 * Y is the plain integer layout.  `mult` and `mult1` are the two multiply
 * pipes, not two source multiplies of different kinds. */

typedef struct Rec {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    u8  pad08[0x10 - 8];
    s16 f10;
    s16 f12;
} Rec;

extern f32   D_004844D4;          /* gp - 0xC9C  */
extern void *D_0048449C;          /* gp - 0xCD4  */

/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuTacticsCursorBobCb_4fcf10(Rec *r)
{
    f32 t;

    D_004844D4 += 0.1570796371f;
    if (D_004844D4 > 0.0f) {
        D_004844D4 -= 3.14159274f;
    }
    t = 12.0f * Sinf_128fd0(D_004844D4);
    UiMoveWidgetUniform_290f50(D_0048449C, 0x3B, (s32)(t + (f32)(r->f00 + r->f10 * r->f04)), r->f02 + r->f12 * r->f06, 0.5f, 0

);
    return 1;
}
