/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialClearConfirmAnswer_4f2970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Job { s32 f00; } Job;

typedef struct Scr {
    u8    pad00[0x40];
    void *f40;
    void *f44;
    u8    pad48[0x30];
    u8    f78;
} Scr;

extern void *D_004807EC;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryMaterialClearConfirmAnswer_4f2970(Scr *o, s32 v)
{
    Job *q;

    switch ((s8)v) {
    case 0:
        q = ((Job *)FactoryGetRequestPtr_367ec0());
        q->f00 = 0xA;
        o->f78 = 3;
        UiEntryListSelectByTag_28ea90(o->f44, 0x894E, 0);
        break;
    case 1:
        UiEntryListSelectByTag_28ea90(o->f44, 0x891C, 0);
        o->f78 = 0;
        break;
    }
    UiSetWidgetVisible_290010(o->f40, 0x68, 1, -1);
    UiSetWidgetVisible_290010(o->f40, 0x64, 1, -1);
    UiSetWidgetVisible_290010(o->f40, 0x63, 1, -1);
    UiFadeWidgetAlpha_290690(o->f40, 0x6A, 0.0f, -0.125f, -1.0f);
    UiFadeWidgetAlpha_290690(D_004807EC, 0x97, 0.0f, -0.125f, -1.0f);
}
