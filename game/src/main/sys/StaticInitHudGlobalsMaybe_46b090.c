/* rgp:protos */
#define RGP_SELF_StaticInitHudGlobalsMaybe_46b090 1
#include "port/game_protos.h"
#line 1
/* PARK s16d: 1 round trip, length 0x1E8 vs retail 0x1C4 (9 words over).
   Many globals' true types are `?` in m2c's draft; declared as byte
   pointers throughout. */
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
extern s32 D_0047E5B0;
extern s32 D_004802A0;
extern u8 D_00481B68[4] __attribute__((section(".sdata")));
extern u8 D_00481B74[4] __attribute__((section(".sdata")));
extern u8 D_00481B78[4] __attribute__((section(".sdata")));
extern u8 D_00481B84[4] __attribute__((section(".sdata")));
extern s32 D_00481BB0;
extern s32 D_00481BB4;
extern u8 D_00481C28[4] __attribute__((section(".sdata")));
extern u8 D_00481C38[4] __attribute__((section(".sdata")));
extern u8 D_00481C48[4] __attribute__((section(".sdata")));
extern u8 D_004BB950[];
extern u8 D_004BBB60[];
extern u8 D_004BBBC0[];
extern u8 D_004BBC20[];
extern u8 D_004BBC80[];
extern u8 D_004BBCE0[];
extern u8 D_004BBD40[];
extern u8 D_004BBDA0[];
extern u8 D_004BBE00[];
extern u8 D_004BBE60[];
extern u8 D_004BBEC0[];
extern u8 D_004BBF20[];
extern u8 D_004BBF80[];
extern u8 D_004BBFE0[];
extern u8 D_004BC040[];
extern u8 D_004BC0A0[];
extern u8 D_004BC0A4[];
extern u8 D_004BC204[];
extern u8 D_004BC208[];
extern u8 D_004BC310[];
extern u8 D_004BC470[];
extern u8 D_004BC6C0[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void StaticInitHudGlobalsMaybe_46b090(void)
{
    u8 *p;

    IosBaseInitCtor_102bd0(D_00481B74);
    RegisterGlobalObject_100dc0(D_00481B74, IosBaseInitDtor_102ee0, D_00481B68);
    WIosBaseInitCtor_103110(D_00481B84);
    RegisterGlobalObject_100dc0(D_00481B84, WIosBaseInitDtor_103420, D_00481B78);
    MemStackCtor_14e030(D_004BB950);
    D_00481BB0 = D_004802A0;
    D_00481BB4 = D_0047E5B0;
    MemStackCtor_14e030(D_004BBB60);
    MemStackCtor_14e030(D_004BBBC0);
    MemStackCtor_14e030(D_004BBC20);
    MemStackCtor_14e030(D_004BBC80);
    MemStackCtor_14e030(D_004BBCE0);
    MemStackCtor_14e030(D_004BBD40);
    MemStackCtor_14e030(D_004BBDA0);
    MemStackCtor_14e030(D_004BBE00);
    MemStackCtor_14e030(D_004BBE60);
    MemStackCtor_14e030(D_004BBEC0);
    MemStackCtor_14e030(D_004BBF20);
    MemStackCtor_14e030(D_004BBF80);
    MemStackCtor_14e030(D_004BBFE0);
    MemStackCtor_14e030(D_004BC040);
    p = D_004BC0A4;
    do {
        MemStackCtor_14e030(p);
        p += 0x58;
    } while (p < D_004BC204);
    ArenaCtxClear_370650(D_004BC208);
    ResGroupClearAll_42c8f0(D_004BC0A0);
    ScreenMarkerMgrCtor_31bdd0(D_004BC310);
    RegisterGlobalObject_100dc0(D_004BC310, ScreenMarkerMgrDtor_31bd70, D_00481C28);
    HpGaugeCtor_31e2a0(D_004BC470);
    RegisterGlobalObject_100dc0(D_004BC470, HpGaugeDtor_31e240, D_00481C38);
    HpGaugeObjCtor_31d1c0(D_004BC6C0);
    RegisterGlobalObject_100dc0(D_004BC6C0, HpGaugeObjDtor_31d160, D_00481C48);
}
