/* rgp:protos */
#define RGP_SELF_normal_FieldHudRadarTargetShow_4f12d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F12D0 -- arms the party-formation panel's 0x3E cursor widget:
 * remembers the caller's handle, sizes the cursor box and starts its blink.
 * Pass-33 LIST rank: 172 bytes, 43 instructions, ONE conditional branch,
 * 4 calls.
 *
 * `if (p->f378 != 0)` is written positively so the body FALLS THROUGH, which
 * is the recorded guard-polarity rule.
 *
 * The two float constants are `lui $2,K>>16 / mtc1 $2,$fN` -- a simple float
 * constant argument is materialised inline, NOT loaded from the pool, so 1.0f
 * and -1.0f are literals while D_0047D1E0 and D_0047D240 (both `lwc1
 * %gp_rel`) are named externals.  Only pool loads take the external rule. */

typedef struct Box { s16 x; s16 y; s16 w; s16 h; } Box;
typedef struct Row { Box a; Box b; } Row;
typedef struct Hold { u8 pad000[0x20]; Row *f020; } Hold;

typedef struct Obj {
    u8    pad000[0x378];
    s16   f378;
    u8    pad37A[0x4F0 - 0x37A];
    void *f4F0;
    s32   f4F4;
} Obj;

extern f32 D_0047D1E0;            /* gp - 0x7F90 */
extern f32 D_0047D240;            /* gp - 0x7F30 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern void normal_FieldHudRadarTargetShow_4f12d0(Obj *p, void *q);

void normal_FieldHudRadarTargetShow_4f12d0(Obj *p, void *q)
{
    Row *r;

    if (p->f378 != 0) {
        r = ((Hold *)UiFindWidget_290460(p, 0x3E))->f020;
        p->f4F0 = q;
        p->f4F4 = 0;
        r->b.x = 0x5C;
        r->b.y = 0x18;
        r->b.w = 0x18;
        r->a.w = 0x18;
        r->b.h = 0x18;
        r->a.h = 0x18;
        UiSetWidgetsVisibleById_291110(p, 0x3E, 1, 1);
        UiSetWidgetAlpha_2907a0(p, 0x3E, D_0047D1E0);
        UiFadeWidgetAlpha_290690(p, 0x3E, 1.0f, D_0047D240, -1.0f);
    }
}
