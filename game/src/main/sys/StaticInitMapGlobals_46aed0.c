/* rgp:protos */
#define RGP_SELF_StaticInitMapGlobals_46aed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00471380[];
extern u8 D_00471390[];
extern u8 D_00481AC0;
extern u8 D_00481ACC;
extern u8 D_00481AD0;
extern u8 D_00481ADC;
extern u8 D_00481AE0;
extern u8 D_00481AF0;
extern u8 D_004B8BB0[];
extern u8 D_004B8C10[];
extern u8 D_004B8C70[];
extern u8 D_004B8D50[];
extern u8 D_004BA598[];
extern u8 D_004BACC8[];
extern u8 D_004BAF20[];
extern void *D_004BAF2C[];
extern u8 D_004BAF30[];
extern u8 D_004BAF50[];
extern u8 D_004BB480[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void StaticInitMapGlobals_46aed0(void) {
    u8 *p;

    IosBaseInitCtor_102bd0(&D_00481ACC);
    RegisterGlobalObject_100dc0(&D_00481ACC, IosBaseInitDtor_102ee0, &D_00481AC0);
    WIosBaseInitCtor_103110(&D_00481ADC);
    RegisterGlobalObject_100dc0(&D_00481ADC, WIosBaseInitDtor_103420, &D_00481AD0);
    MemStackCtor_14e030(D_004B8BB0);
    MemStackCtor_14e030(D_004B8C10);
    MapSkyCtor_201be0(D_004B8D50);
    p = D_004BA598;
    do {
        MapAreaCtor_201ba0(p);
        p += 0x1CC;
    } while (p < D_004BACC8);
    MapDataCtor_201b70(D_004BACC8);
    MapMgrInit_1e5830(D_004B8C70);
    DListInit_42eae0(D_004BAF20);
    D_004BAF2C[0] = D_00471390;
    DListInit_42eae0(D_004BAF20);
    p = D_004BAF30;
    p = (u8 *)(u32)p;
    DListInit_42eae0(p);
    *(u8 **)(p + 0xC) = D_00471380;
    DListInit_42eae0(p);
    RegisterGlobalObject_100dc0(D_004BAF20, MapSequencerDtor_201ac0, &D_00481AE0);
    MinimapMgrCtor_322450(D_004BAF50);
    RegisterGlobalObject_100dc0(D_004BAF50, MinimapMgrDtor_3223f0, &D_00481AF0);
    SunaKemuClear_33bb00(D_004BB480);
}
