/* rgp:protos */
#define RGP_SELF_normal_FieldHudRadarShow_4f19e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F19E0 -- widget 0x25 setup.  The first three stores go through
 * the PARAMETER, before it is copied to the callee-saved register. */
typedef struct Obj {
    u8  pad000[0x383];
    s8  f383;
    u8  pad384[0x430 - 0x384];
    s8  f430;
    u8  pad431[0x4A8 - 0x431];
    s16 f4A8;
    u8  pad4AA[0x4F0 - 0x4AA];
    s32 f4F0;
    s32 f4F4;
} Obj;

extern f32  D_0047DB7C;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudRadarShow_4f19e0(Obj *p)
{
    p->f4A8 = 1;
    p->f4F0 = -1;
    p->f4F4 = 0;
    UiSetWidgetAlpha_2907a0(p, 0x25, 0.0f);
    UiSetWidgetPos_290f60(p, 0x25, 0x160, 0x108);
    UiFadeWidgetAlpha_290690(p, 0x25, 1.0f, D_0047DB7C, -1.0f);
    UiSetWidgetVisible_290010(p, 0x25, 1, -1);
    p->f430 = 2;
    p->f383 = 1;
}
