/* rgp:protos */
#define RGP_SELF_normal_FieldHudWidget80LiftOpenMaybe_4f96d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F96D0 -- one-shot open of widget 0x80, blocked once +0x3A2 is
 * set.  The inner `bnel` carries the shared `ld $31` in its delay slot. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x3A2 - 0x37A];
    s16 f3A2;
    u8  pad3A4[0x3DA - 0x3A4];
    s16 f3DA;
} Obj;

extern void *D_00481BBC;          /* gp - 0x35B4 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudWidget80LiftOpenMaybe_4f96d0(Obj *p)
{
    if (p->f378 != 0) {
        if (p->f3A2 != 0) {
            return;
        }
        UiSetWidgetsVisibleById_291110(p, 0x80, 1, 1);
        UiSetTextString_28f510(p, 0x80, MsgTableLookup_28aa30(D_00481BBC, 0x60), 0);
        UiSetWidgetPos_290f60(p, 0x80, 0x10, 0x14A);
        UiSetWidgetAlpha_2907a0(p, 0x80, 1.0f);
        p->f3DA = 0xA;
    }
}
