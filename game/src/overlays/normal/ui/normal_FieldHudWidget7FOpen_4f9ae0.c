/* rgp:protos */
#define RGP_SELF_normal_FieldHudWidget7FOpen_4f9ae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9AE0 -- open the 0x7F widget.  _gp = 0x00485170, so -0x35B4
 * is D_00481BBC (a pointer, 4 bytes, so it stays in small data).  $4 is never
 * reloaded for the first func_291110 call: it is still the incoming a0. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x3A2 - 0x37A];
    s16 f3A2;
    u8  pad3A4[0x3D8 - 0x3A4];
    s16 f3D8;
    u8  pad3DA[0x4A0 - 0x3DA];
    s16 f4A0;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00481BBC;                                /* _gp - 0x35B4 */

void normal_FieldHudWidget7FOpen_4f9ae0(Obj *p, s32 sel)
{
    if (p->f378 == 0) {
        return;
    }
    if (p->f3A2 != 0) {
        return;
    }
    if (p->f3D8 != 0) {
        UiSetWidgetsVisibleById_291110(p, 0x7F, 0, 1);
        return;
    }
    UiSetWidgetsVisibleById_291110(p, 0x7F, 1, 1);
    if (sel != 0) {
        UiSetTextString_28f510(p, 0x7F, MsgTableLookup_28aa30(D_00481BBC, 0), 0);
        UiSetSpriteX_28fcd0(p, 0x7F, 3, 0);
    } else {
        UiSetTextString_28f510(p, 0x7F, MsgTableLookup_28aa30(D_00481BBC, 1), 0);
        UiSetSpriteX_28fcd0(p, 0x7F, -1, 0);
    }
    UiSetWidgetPos_290f60(p, 0x7F, 0x10, 0x14A);
    UiSetWidgetAlpha_2907a0(p, 0x7F, 1.0f);
    p->f4A0 = 1;
}
