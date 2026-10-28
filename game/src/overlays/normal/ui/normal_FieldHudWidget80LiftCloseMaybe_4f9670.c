/* rgp:protos */
#define RGP_SELF_normal_FieldHudWidget80LiftCloseMaybe_4f9670 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9670 -- the 0x80 widget's on/off toggle on the party-formation
 * object: guarded by `p->f378`, `b != 0` fades the widget in through
 * func_290690, `b == 0` turns it off through func_291110, and BOTH paths clear
 * the 0x3DA counter.
 *
 * The 0x3DA store is written ONCE after the if/else -- retail's two copies are
 * the scheduler duplicating the shared tail into the `b` delay slot, the same
 * filler idiom normal_FUN_0050F960 records.
 * `lui 0xBF80 / mtc1 $2,$f14` is -1.0f materialised inline; only the middle
 * float is the gp pool literal D_0047DA6C.
 */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x3DA - 0x37A];
    s16 f3DA;
} Obj;

extern f32 D_0047DA6C;            /* gp - 0x7704 */

/*rgp*/
/*rgp*/

void normal_FieldHudWidget80LiftCloseMaybe_4f9670(Obj *p, s32 b)
{
    if (p->f378 != 0) {
        if (b != 0) {
            UiFadeWidgetAlpha_290690(p, 0x80, 0.0f, D_0047DA6C, -1.0f);
        } else {
            UiSetWidgetsVisibleById_291110(p, 0x80, 0, 1);
        }
        p->f3DA = 0;
    }
}
