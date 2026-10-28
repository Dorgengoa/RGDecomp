/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialWaitRequest_4f31c0 1
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialWaitRequest_4f31c0(Scr *o)
{
    u8 v;

    v = o->f78;
    if (v != 1 && v != 3) {
        return 1;
    }
    if (((Job *)FactoryGetRequestPtr_367ec0())->f00 == 0) {
        if (o->f78 == 1) {
            UiSetWidgetAlpha_2907a0(o->f40, 0xB0, 1.0f);
            UiSetWidgetAlpha_2907a0(o->f40, 0x69, 0.0f);
        }
        o->f78 = 0;
        UiEntryListSelectByTag_28ea90(o->f44, 0x891C, 0);
        factory_FactoryMaterialMarkFilledRows_4f25c0(o);
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 6, 0, 1.0f);
    }
    return 0;
}
