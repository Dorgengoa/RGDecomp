/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuReset_4f10f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A {
    u8    pad00[0x5C];
    f32   f5C;
    u8    pad60[0x4];
    void *f64;
    u8    pad68[0xC];
    s32   f74;
    u8    f78;
} A;

extern f32 D_0047D4F4;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryMenuReset_4f10f0(A *o)
{
    f32 v;

    v = D_0047D4F4;
    o->f74 = 0;
    o->f5C = -3.1415927f;
    UiSetSpriteSizeUvSize_28f670(o->f64, 0x18, 0, 0, 0, 0, 0);
    UiSetSpriteUv_28f970(o->f64, 0x19, 0x40, 0xC0, 0);
    UiSetSpritePos_28fd10(o->f64, 0x19, 0xB, 0x31, 0);
    UiSetSpriteSizeUvSize_28f670(o->f64, 4, 0, 0, 0, 0, 3);
    UiSetSpriteSizeUvSize_28f670(o->f64, 4, 0x73, 0x1E, 0x4C, 0x18, 4);
    UiSetWidgetPos_290f60(o->f64, 4, 0xF, 0);
    UiSetWidgetVisible_290010(o->f64, 0xC, 0, -1);
    UiSetWidgetVisible_290010(o->f64, 0x1A, 0, -1);
    o->f78 = 0;
}
