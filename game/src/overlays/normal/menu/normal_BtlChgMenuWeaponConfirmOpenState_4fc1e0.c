/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuWeaponConfirmOpenState_4fc1e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FC1E0 -- lays out the item-count widget: positions widget 0x50
 * from the 0x55FA record's own geometry, then wires two icons and shows 0x49.
 * $4 is unused; the guard is on the SECOND parameter.  0x40C00000 is 6.0f. */

typedef struct Rec {
    u8  pad000[4];
    s16 f004;
    s16 f006;
    u8  pad008[2];
    s16 f00A;
    u8  pad00C[0x14 - 0xC];
    s16 f014;
    s16 f016;
    u8  pad018[2];
    s16 f01A;
} Rec;

extern void *D_004844A0;          /* gp - 0xCD0 */
extern void *D_00484454;          /* gp - 0xD1C */
extern f32   D_004844B8;          /* gp - 0xCB8 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern void *D_00481BBC;          /* gp - 0x35B4 */
extern void *D_00484498;          /* gp - 0xCD8 */
extern u8 normal_D_005278E0[];

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

s32 normal_BtlChgMenuWeaponConfirmOpenState_4fc1e0(void *unused, s32 show)
{
    Rec *r;
    Rec *q;
    f32  t;

    if (show != 0) {
        r = ((Rec *)UiEntryListFindByTag_28ea40(D_004844A0, 0x55F4));
        normal_BtlChgPageWeaponConfirmLayout_504030(D_00484454,
                            (s16)(r->f014 + r->f016 * 8 + r->f01A * 8));
        UiEntryListSelectByTag_28ea90(D_004844A0, 0x55FA, 0);
        q = ((Rec *)UiEntryListFindByTag_28ea40(D_004844A0, 0x55FA));
        q->f014 = 0;
        /* The PRODUCT must be its own statement or mwcc contracts the whole
         * expression into adda.s/madd.s; retail keeps mul.s and add.s.
         * Splitting the sum or the (f32) conversion instead does NOT work --
         * measured, twelve spellings. */
        t = 6.0f * Sinf_128fd0(D_004844B8);
        UiSetWidgetPos_290f60(D_0048449C, 0x50,
                    (s32)(t + (f32)(q->f004 + 0x52 + q->f014 * 0x50)),
                    q->f006 + 0x88 + q->f016 * q->f00A);
        UiSetSpriteU_28f930(D_0048449C, 0x4A, 0x4C, 0);
        UiSetSpriteU_28f930(D_0048449C, 0x4A, 0x18, 1);
        UiSetTextString_28f510(D_0048449C, 0x4B, MsgTableLookup_28aa30(D_00481BBC, 0x52), 3);
        UiSetTextString_28f510(D_0048449C, 0x4B, MsgTableLookup_28aa30(D_00481BBC, 0x53), 4);
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x49, 1, 1);
        UiSetWidgetPos_290f60(D_0048449C, 0x49, 0x60, 0x82);
    }
    UiSelFrameAnimStep_28d820(normal_D_005278E0, 0x28);
    StateMachineSetState_28ede0(D_00484498, 0x5610, 0);
    return 1;
}
