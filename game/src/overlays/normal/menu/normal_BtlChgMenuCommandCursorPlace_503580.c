/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuCommandCursorPlace_503580 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00503580 -- rebuilds the four 0x2D..0x54 sub-widgets of the party
 * panel and writes the selected row's 25*i offset into the 0x2D record.
 * The four trailing func_290F60 calls sit INSIDE the `w != 0` arm but OUTSIDE
 * the `t != 0` arm -- the `beql` at 0x005035E0 jumps past the store only.
 * `sll 2 / addu / sll 2 / addu` is one multiply by 25. */

typedef struct Fld { u8 pad00[2]; s16 f02; } Fld;
typedef struct Wgt { u8 pad00[0x20]; Fld *f20; } Wgt;

extern void *D_00484454;          /* gp - 0xD1C */

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuCommandCursorPlace_503580(s32 a)
{
    void *o;
    s32   i;
    Wgt  *w;
    Fld  *t;

    o = normal_UiPageGetLayout_289b60(D_00484454);
    if (o == 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        UiSetWidgetPos_290f60(o, 0x2D, -0x49, 0x2E);
        w = ((Wgt *)UiFindWidget_290460(o, 0x2D));
        if (w != 0) {
            t = w->f20;
            if (t != 0) {
                if (a == i) {
                    t->f02 = (s16)(i * 25);
                }
            }
            UiSetWidgetPos_290f60(o, 0x51, -0x49, 0x2E);
            UiSetWidgetPos_290f60(o, 0x52, -0x49, 0x2E);
            UiSetWidgetPos_290f60(o, 0x53, -0x47, 0x2E);
            UiSetWidgetPos_290f60(o, 0x54, -0x4A, 0x2E);
        }
    }
    return 1;
}
