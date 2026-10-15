#include "types.h"

extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void InsectCageMenuSetRowMarker_389a80(s32, s32, s32, s32);
extern void InsectCageMenuSetCursorVisible_389d00(s32);
extern s32 InsectRecFindPairEntryKind_38cf70(s32, s32);
extern s32 InsectCageMenuGetMoveTargetCageItem_38d4b0(void);
extern s32 InsectCageMenuGetMoveTargetCage_38d4e0(void);
extern void InsectCageMenuSelectEntry_390d40(s32, s32);
extern s32 InsectCageMenuGetCurCageItem_391030(void);
extern s32 InsectRecSlotGetItem_3cfb30(s32, s16);
extern void InsectRecSlotSwapItems_3cfcb0(s32, s32, s32, s32);
extern void InsectRecSlotMoveItem_3cfd50(s32, s32, s32);
extern u8 *InsectCageMenuGetCursorObjThunk_390f70(void);
extern s32 D_004832DC;
extern s16 D_004833C8;
extern s32 D_004833CC;

s32 InsectCageMenuMoveSlotConfirm_38cdd0(u8 *arg0, s32 arg1)
{
    s16 k;
    s32 flag;
    s32 m;
    s32 o;
    s32 r;
    s32 i;
    s32 t;

    k = *(s16 *)(arg0 + 0x12);
    flag = 0;
    m = InsectCageMenuGetMoveTargetCageItem_38d4b0();
    o = InsectRecSlotGetItem_3cfb30(m, k);
    if (o != 0) {
        flag = 1;
    }
    r = InsectRecFindPairEntryKind_38cf70(m, o);
    if (r > 0) {
        D_004833CC = o;
        if (r == 1) {
            D_004833C8 = 0x51E;
        } else if (r == 2) {
            D_004833C8 = 0x51F;
        }
        InsectCageMenuSelectEntry_390d40(0x753C, 1);
        return 0;
    }
    for (i = 0; i < 3; i++) {
        InsectCageMenuSetRowMarker_389a80(0, 0, i, -1);
    }
    InsectCageMenuSetRowMarker_389a80(1, 0, InsectCageMenuGetMoveTargetCage_38d4e0(), -1);
    if (flag != 0) {
        t = *(s32 *)(InsectCageMenuGetCursorObjThunk_390f70() + 0x96C);
        InsectRecSlotSwapItems_3cfcb0(m, o, InsectCageMenuGetCurCageItem_391030(), t);
    } else {
        t = *(s32 *)(InsectCageMenuGetCursorObjThunk_390f70() + 0x96C);
        InsectRecSlotMoveItem_3cfd50(m, InsectCageMenuGetCurCageItem_391030(), t);
    }
    UiSetWidgetVisible_290010(arg1, 0x7576, 0, -1);
    UiSetWidgetVisible_290010(arg1, 0x754E, 0, -1);
    InsectCageMenuSetCursorVisible_389d00(0);
    D_004832DC = o;
    InsectCageMenuSelectEntry_390d40(0x753D, 0);
    return 1;
}
