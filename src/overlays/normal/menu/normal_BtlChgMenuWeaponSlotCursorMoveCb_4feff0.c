#include "types.h"
/* normal 0x004FEFF0 -- nudge widget 0x3F and stamp its child's +0x02 with
 * f12*25 (mwcc splits the constant into two x*5 steps).  The `beql` on the
 * gp-handle null test carries the shared `ld $31`. */

typedef struct Rec { u8 pad00[0x12]; s16 f12; } Rec;
typedef struct Node { u8 pad00[2]; s16 f02; } Node;
typedef struct Widget { u8 pad00[0x20]; Node *f20; } Widget;

extern void *D_0048449C;          /* gp - 0xCD4 */

extern void    func_290F60(void *p, s32 id, s32 c, s32 d);
extern Widget *func_290460(void *p, s32 id);

s32 normal_BtlChgMenuWeaponSlotCursorMoveCb_4feff0(Rec *r)
{
    Widget *w;

    if (D_0048449C != NULL) {
        func_290F60(D_0048449C, 0x3F, 7, 6);
        w = func_290460(D_0048449C, 0x3F);
        if (w != NULL) {
            if (w->f20 != NULL) {
                w->f20->f02 = r->f12 * 25;
            }
        }
    }
    return 1;
}
