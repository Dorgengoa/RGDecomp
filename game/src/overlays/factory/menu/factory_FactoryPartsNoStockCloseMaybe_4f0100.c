/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsNoStockCloseMaybe_4f0100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Scr {
    u8    pad00[0x88];
    u8    f88;
    u8    pad89[0x3];
    void *f8C;
    void *f90;
} Scr;

/*rgp*/
/*rgp*/

void factory_FactoryPartsNoStockCloseMaybe_4f0100(Scr *o)
{
    o->f88 = 0;
    UiEntryListSelectByTag_28ea90(o->f90, 0x88F4, 0);
    UiFadeWidgetAlpha_290690(o->f8C, 0x46, 0.0f, -0.125f, -1.0f);
    UiFadeWidgetAlpha_290690(o->f8C, 0x42, 1.0f, 0.125f, -1.0f);
    UiFadeWidgetAlpha_290690(o->f8C, 0x4C, 1.0f, 0.125f, -1.0f);
}
