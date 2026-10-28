/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuWeaponSlotCursorMoveCb_4feff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FEFF0 -- nudge widget 0x3F and stamp its child's +0x02 with
 * f12*25 (mwcc splits the constant into two x*5 steps).  The `beql` on the
 * gp-handle null test carries the shared `ld $31`. */

typedef struct Rec { u8 pad00[0x12]; s16 f12; } Rec;
typedef struct Node { u8 pad00[2]; s16 f02; } Node;
typedef struct Widget { u8 pad00[0x20]; Node *f20; } Widget;

extern void *D_0048449C;          /* gp - 0xCD4 */

/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuWeaponSlotCursorMoveCb_4feff0(Rec *r)
{
    Widget *w;

    if (D_0048449C != NULL) {
        UiSetWidgetPos_290f60(D_0048449C, 0x3F, 7, 6);
        w = ((Widget *)UiFindWidget_290460(D_0048449C, 0x3F));
        if (w != NULL) {
            if (w->f20 != NULL) {
                w->f20->f02 = r->f12 * 25;
            }
        }
    }
    return 1;
}
