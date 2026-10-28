/* rgp:protos */
#define RGP_SELF_GsPktSetScissor_28c2e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The 64-bit argument is a packed (x, x+w, y, y+h) quad of 16-bit fields. */

typedef struct Rect {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void GsPktSetScissor_28c2e0(void *a, Rect *r, s32 use, Rect *off)
{
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    void *p;

    if (use) {
        if (a == 0) {
            return;
        }
        GsPktOpenPrim_13f730(a, 6);
        x = r->x;
        y = r->y;
        w = r->w;
        h = r->h;
        if (off != 0) {
            x += off->x;
            y += off->y;
            w += off->w;
            h += off->h;
        }
        GsPktWriteAD_13ec80(a, 0x40,
                     (s64)x | ((s64)(x + w) << 16) |
                     ((s64)y << 32) | ((s64)(y + h) << 48));
        GsPktClose_13f5b0(a);
    } else {
        if (a == 0) {
            return;
        }
        p = GetDrawCtx_15de80();
        w = DrawEnvGetWidth_1451e0(p);
        h = DrawEnvGetHeight_1451d0(p);
        GsPktOpenPrim_13f730(a, 6);
        GsPktWriteAD_13ec80(a, 0x40, ((s64)(w - 1) << 16) | ((s64)(h - 1) << 48));
        GsPktClose_13f5b0(a);
    }
}
