/* rgp:protos */
#define RGP_SELF_normal_FieldHudWidget80CarryOpenMaybe_4f97b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F97B0 -- one-shot open of widget 0x80, latch +0x3D8 = 0xA. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x3D8 - 0x37A];
    s16 f3D8;
} Obj;

extern void *D_00481BBC;          /* gp - 0x35B4 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudWidget80CarryOpenMaybe_4f97b0(Obj *p)
{
    if (p->f378 != 0) {
        UiSetWidgetsVisibleById_291110(p, 0x80, 1, 1);
        UiSetTextString_28f510(p, 0x80, MsgTableLookup_28aa30(D_00481BBC, 0x5B), 0);
        UiSetWidgetPos_290f60(p, 0x80, 0x33, 0x14A);
        UiSetWidgetAlpha_2907a0(p, 0x80, 1.0f);
        p->f3D8 = 0xA;
    }
}
