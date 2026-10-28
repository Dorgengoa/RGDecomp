/* rgp:protos */
#define RGP_SELF_MenuItemGridMarkInUse_2a4860 1
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
extern s32 D_004659F0[0x10];
extern s32 D_004659F8[0x10];
extern s32 D_00465B18[0x10];
extern s32 D_00465B20[0x10];

typedef struct A2a4860 { u8 pad0[0x14]; s32 unk14; } A2a4860;

s32 MenuItemGridMarkInUse_2a4860(u8 *arg0, s32 arg1)
{
    s32 lo;
    s32 hi;
    s32 i;
    s32 t2;
    s32 t20;
    u8 *node;
    s8 flag;
    u8 *p16;
    s32 range1;
    s32 range2;
    s32 ok;

    MenuFillItemGrid_2a4b40((void *)arg0, (int)arg1);
    node = ((u8 *)UiGetWidgetSprite_28fe10(*(s32 *)(arg0 + 0x0), arg1, 0));
    if (node == NULL) {
        return 0;
    }
    flag = *(s8 *)(arg0 + 0x11);
    p16 = ((u8 *)GetGameData_1fede0());
    if (((A2a4860 *)arg0)->unk14 == 9) {
        range1 = D_00465B18[0];
        flag = 0;
        range2 = D_00465B20[0];
    } else {
        range1 = D_004659F0[0];
        range2 = D_004659F8[0];
    }
    lo = InvMakeIdFromCategory_3c88b0(*(s32 *)(p16 + 0x18), *(s32 *)(arg0 + 0x14), flag, 0, 0);
    {
        s32 hh = InvMakeIdFromCategory_3c88b0(*(s32 *)(p16 + 0x18), *(s32 *)(arg0 + 0x14), flag, range1 - 1, range2 - 1);
        hi = hh;
    }
    for (i = lo; i < hi + 1; i++) {
        t2 = ((s32)InvFindByInvId_3c87d0(*(s32 *)(p16 + 0x18), i, 0));
        if (t2 != 0) {
            t20 = ((s32)InvObjCastToItem4B0_3d3cd0(t2, 0, 0, 0));
            ok = ((s32)PartyFindItemHolder_3d4c20(t2)) != 0;
            if (ok) {
                *(s16 *)(node + 0x4) = 0x28;
                *(s16 *)(node + 0x6) = 0x2D;
            } else if (t20 != 0 && CageRecIsPlaced_3d0d20(t20) != 0) {
                *(s16 *)(node + 0x4) = 0x28;
                *(s16 *)(node + 0x6) = 0x2D;
            } else {
                *(s16 *)(node + 0x6) = 0;
                *(s16 *)(node + 0x4) = 0;
                *(s16 *)(node + 0xE) = 0;
                *(s16 *)(node + 0xC) = 0;
            }
        } else {
            *(s16 *)(node + 0x6) = 0;
            *(s16 *)(node + 0x4) = 0;
            *(s16 *)(node + 0xE) = 0;
            *(s16 *)(node + 0xC) = 0;
        }
        node += 0x20;
    }
    *(s16 *)(node + 0x0) = -1;
    return 1;
}
