/* rgp:protos */
#define RGP_SELF_InsectCageMenuFeedOpen_38f090 1
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

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00464108[];
extern s32 D_004832D8;
extern s16 D_00483370;
extern u8 D_004E94C0[];
extern u8 D_004E9510[];
extern s32 D_004E9520;

s32 InsectCageMenuFeedOpen_38f090(s32 p0, s32 p1)
{
    s32 v2C;
    s32 r2;
    s32 t0;
    s32 t1;
    s32 t2;

    D_00483370 = 0;
    MenuCursorObjSetVisible_386280(D_004E94C0, 0);
    UiSetWidgetsVisibleById_291110(p1, 0x753A, 1, 1);
    r2 = InsectCageMenuGetCursorObj_390f70();
    BitArraySetReturnOld_384360((r2 + 0x986), 2, 0);
    InsectCageMenuGetCursorInvItem_38f550(&v2C);
    t0 = v2C;
    *(s32 *)&D_004E9520 = t0;
    MenuObjGetFrontPos_386000(D_004E9510, r2);
    MenuObjRandDelayMaybe_385fa0(D_004E9510);
    ModelObjPlayMotionByName_1867a0(r2, D_00464108, 0);
    BitArraySetReturnOld_384360((r2 + 0x986), 8, 0);
    t1 = D_004832D8;
    MenuObjSetShowModel_3858a0(t1, 0, r2);
    t2 = D_004832D8;
    MenuObjSetStopMotion_384a80(t2);
    return 1;
}
