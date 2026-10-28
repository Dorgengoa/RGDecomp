/* rgp:protos */
#define RGP_SELF_normal_FieldHudWidget83Open_4f95b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F95B0 -- one-shot open of widget 0x83. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x49E - 0x37A];
    s16 f49E;
} Obj;

extern void *D_00481BBC;          /* gp - 0x35B4 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudWidget83Open_4f95b0(Obj *p)
{
    if (p->f378 != 0) {
        UiSetWidgetsVisibleById_291110(p, 0x83, 1, 1);
        UiSetTextString_28f510(p, 0x83, MsgTableLookup_28aa30(D_00481BBC, 0x58), 0);
        UiSetTextString_28f510(p, 0x83, MsgTableLookup_28aa30(D_00481BBC, 0x59), 1);
        UiSetTextCenteredX_28f300(p, 0x83, 0xEC, 1);
        UiSetWidgetPos_290f60(p, 0x83, 0x14, 0x5A);
        UiSetWidgetAlpha_2907a0(p, 0x83, 1.0f);
        p->f49E = 1;
    }
}
