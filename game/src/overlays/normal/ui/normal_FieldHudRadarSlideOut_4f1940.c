/* rgp:protos */
#define RGP_SELF_normal_FieldHudRadarSlideOut_4f1940 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F1940 -- sibling of normal_FieldHudRadarShow_4f19e0 for the same widget id. */
typedef struct Obj { u8 pad000[0x430]; s8 f430; } Obj;

extern f32  D_0047DB7C;
extern f32  D_0047DD14;
extern f32  D_0047DD18;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudRadarSlideOut_4f1940(Obj *p)
{
    UiSetWidgetAlpha_2907a0(p, 0x25, 1.0f);
    UiFadeWidgetAlpha_290690(p, 0x25, D_0047DB7C, -1.0f, -1.0f);
    UiMoveWidgetUniform_290f50(p, 0x25, 0x258, 0x140, D_0047DD14, 0);
    UiFadeWidgetAlpha_290690(p, 0x54, 0.0f, D_0047DD18, -1.0f);
    normal_FieldHudAllySuggestCancel_4eec90(p);
    p->f430 = 1;
}
