/* rgp:protos */
#define RGP_SELF_normal_FieldHudWidget86Open_4f94b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F94B0 -- one-shot open of widget 0x86.  Guard on the s16 at
 * +0x378 (the whole family shares it); latch s16 at +0x4A6. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x4A6 - 0x37A];
    s16 f4A6;
} Obj;

extern void *D_00481BBC;          /* gp - 0x35B4 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudWidget86Open_4f94b0(Obj *p)
{
    if (p->f378 != 0) {
        UiSetTextString_28f510(p, 0x86, MsgTableLookup_28aa30(D_00481BBC, 0x5A), 0);
        UiSetWidgetsVisibleById_291110(p, 0x86, 1, 1);
        UiSetWidgetPos_290f60(p, 0x86, 0x14, 0x5A);
        UiSetWidgetAlpha_2907a0(p, 0x86, 1.0f);
        p->f4A6 = 1;
    }
}
