/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsPlaceWait_4f01a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct B {
    u8  pad00[0x16];
    s16 f16;
    u8  pad18[0x2];
    s16 f1A;
} B;

typedef struct C {
    s32 f00;
} C;

typedef struct A {
    u8    pad00[0x64];
    s32   f64;
    s32   f68;
    u8    pad6C[0x1C];
    u8    f88;
    u8    pad89[0x3];
    void *f8C;
    void *f90;
} A;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryPartsPlaceWait_4f01a0(A *o)
{
    B    *r;
    C    *q;
    void *p;

    if (o->f88 == 1) {
        q = ((C *)FactoryGetRequestPtr_367ec0());
        if (q->f00 == 0) {
            p = SceneSoundGetSlot0HandleCur_207df0();
            SoundPlayScaledVolume_1b9520(p, 6, 0, 1.0f);
            UiEntryListSelectByTag_28ea90(o->f90, 0x88F4, 0);
            r = ((B *)UiEntryListFindByTag_28ea40(o->f90, 0x88F4));
            r->f16 = o->f64;
            r->f1A = o->f68;
            UiFadeWidgetAlpha_290690(o->f8C, 0x42, 1.0f, 0.125f, -1.0f);
            UiFadeWidgetAlpha_290690(o->f8C, 0x4C, 1.0f, 0.125f, -1.0f);
            UiFadeWidgetAlpha_290690(o->f8C, 0x45, 0.0f, -0.125f, -1.0f);
            UiFadeWidgetAlpha_290690(o->f8C, 0x47, 0.0f, -0.125f, -1.0f);
            o->f88 = 0;
        }
    }
}
