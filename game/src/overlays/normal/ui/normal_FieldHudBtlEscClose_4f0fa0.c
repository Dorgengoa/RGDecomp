/* rgp:protos */
#define RGP_SELF_normal_FieldHudBtlEscClose_4f0fa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F0FA0 -- the 0x55 gauge cluster's SHOW step, the sibling of
 * normal_FUN_004F1030 (same Obj, same two guards, same 0x55 widget).
 * Guard 1 is an inverted early return (`bnez` INTO the body, `b` to the exit
 * carrying 0); guard 2 is a `beql` whose delay slot carries the shared
 * `return 1`, so it is `if (p->f386 != 0) { ... }` with the tail shared.
 * `daddu $7,$6,$0` is mwcc reusing the 1 it already materialised for arg 3.
 * Both floats are pool loads and so are named externals; 0.0f and -1.0f are
 * materialised inline (`mtc1 $0` / `lui 0xBF80`).
 */

typedef struct Obj {
    u8   pad000[0x378];
    s16  f378;
    u8   pad37A[0x386 - 0x37A];
    s16  f386;
} Obj;

extern f32 D_0047DA48;            /* gp - 0x7728 */
extern f32 D_0047D94C;            /* gp - 0x7824 */

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_FieldHudBtlEscClose_4f0fa0(Obj *p)
{
    if (p->f378 == 0) {
        return 0;
    }
    if (p->f386 != 0) {
        UiSetWidgetsVisibleById_291110(p, 0x55, 1, 1);
        UiFadeWidgetAlpha_290690(p, 0x55, 0.0f, D_0047DA48, -1.0f);
        UiMoveWidgetUniform_290f50(p, 0x55, 0x200, 0xE2, D_0047D94C, 0);
    }
    return 1;
}
