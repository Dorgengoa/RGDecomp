#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s16 h10;
} Obj;

extern s32 Sprintf_1343b8(s32, s32);
extern s32 PadIsTriggered_1839f0(void *, s32);
extern s32 PlayMenuSe_289ef0();
extern s32 UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern s32 InsectCageSePlay_3844b0(void *, s32);
extern s32 MenuObjTeardown_387d60(s32);
extern s32 UiFitCenterWindow_388270(s32, s32);
extern s32 InsectCageMenuFormatMsgForCursor_388430(s32, s32);
extern s32 InsectCageMenuRefreshPreview_3896a0(s32);
extern s32 InsectCageMenuMsgLookup_389d30(s32);
extern s32 InsectCageMenuRemoveDialogClose_38c5f0(s32);
extern s32 InsectCageMenuDialogButtonFocus_38c660(Obj *, s32, s32);
extern s32 InsectCageMenuDialogTwoButtonLayout_38c740(void);
extern s32 InsectCageMenuSetStateFlagMaybe_390aa0(s32, s32);
extern s32 InsectCageMenuSelectEntry_390d40(s32, s32);
extern s32 InsectCageMenuGetCursorObj_390f70(void);
extern s32 InsectCageMenuGetCurCageItem_391030(void);
extern s32 InsectCageMenuGetCageItem_391060(s32);
extern s32 InsectRecSlotCountItems_3cfb80(s32);
extern s32 InsectRecSlotRemoveItem_3cfde0(s32, s32, s32);
extern s32 D_004832A0;
extern s32 D_00483304;
extern s32 D_0048330C;
extern s8 D_004833D4;
extern s8 D_004833D8;
extern s8 D_004833DC;
extern u8 D_004B2570[];
extern s32 D_004E94FC[];

s32 InsectCageMenuRemoveConfirm_38c1c0(Obj *obj, s32 ctx) {
    s32 w;
    s32 flags;
    s32 ok;
    s32 sum;
    s32 i;

    flags = D_004E94FC[0];
    switch (D_004833D4) {
    case 0:
        if (flags & 0x40) {
            if (PadIsTriggered_1839f0(D_004B2570, 12) == 0) {
                break;
            }
            D_004833D8 = (D_004833D8 != 0) ^ 1;
            if (D_004833D8 == 0) {
                UiSetWidgetVisible_290010(ctx, 0x75E4, 1, -1);
                UiSetWidgetVisible_290010(D_0048330C, 0x7602, 1, -1);
                UiSetWidgetVisible_290010(ctx, 0xC350, 0, -1);
                InsectCageMenuRefreshPreview_3896a0(0);
            } else {
                D_004833DC = obj->h10;
                UiSetWidgetVisible_290010(ctx, 0x75E4, 0, -1);
                UiSetWidgetVisible_290010(D_0048330C, 0x7602, 0, -1);
                UiSetWidgetVisible_290010(ctx, 0xC350, 1, -1);
                InsectCageMenuRefreshPreview_3896a0(InsectCageMenuGetCursorObj_390f70());
            }
            PlayMenuSe_289ef0(0xB);
            break;
        }
        if (D_004833D8 == 1) {
            obj->h10 = D_004833DC;
            break;
        }
        if (D_004833D8 != 0) {
            break;
        }
        if (flags & 1) {
            PlayMenuSe_289ef0(4);
            InsectCageMenuDialogButtonFocus_38c660(obj, ctx, 0);
        } else if (flags & 4) {
            PlayMenuSe_289ef0(6);
            InsectCageMenuRemoveDialogClose_38c5f0(ctx);
        } else if (flags & 2) {
            if (obj->h10 == 1) {
                PlayMenuSe_289ef0(5);
                InsectCageMenuRemoveDialogClose_38c5f0(ctx);
                break;
            }
            ok = 0;
            sum = 0;
            for (i = 0; i < 3; i++) {
                if (InsectCageMenuGetCageItem_391060(i) != 0) {
                    sum += InsectRecSlotCountItems_3cfb80(InsectCageMenuGetCageItem_391060(i));
                }
            }
            if (sum == 5) {
                ok = 1;
            }
            if (ok) {
                PlayMenuSe_289ef0(5);
                Sprintf_1343b8(D_00483304 + 0xE80, InsectCageMenuMsgLookup_389d30(0x5DE));
                InsectCageMenuSetStateFlagMaybe_390aa0(6, 0);
                InsectCageMenuDialogTwoButtonLayout_38c740();
                obj->h10 = 1;
                InsectCageMenuDialogButtonFocus_38c660(obj, ctx, 1);
                D_004833D4++;
            } else {
                D_004833D4 = 10;
            }
        }
        break;
    case 1:
        if (flags & 1) {
            InsectCageMenuDialogButtonFocus_38c660(obj, ctx, 0);
            PlayMenuSe_289ef0(4);
        } else if (flags & 4) {
            PlayMenuSe_289ef0(6);
            InsectCageMenuRemoveDialogClose_38c5f0(ctx);
        } else if (flags & 2) {
            if (obj->h10 == 1) {
                PlayMenuSe_289ef0(5);
                InsectCageMenuRemoveDialogClose_38c5f0(ctx);
            } else {
                D_004833D4 = 10;
            }
        }
        break;
    case 10:
        UiSetWidgetVisible_290010(ctx, 0x75E4, 0, -1);
        UiSetWidgetVisible_290010(D_0048330C, 0x7602, 0, -1);
        UiSetWidgetVisible_290010(ctx, 0x754E, 1, -1);
        InsectCageMenuFormatMsgForCursor_388430(D_00483304 + 0x200, 0x5DD);
        UiFitCenterWindow_388270(0x754E, 1);
        UiSetWidgetVisible_290010(ctx, 0xC350, 0, -1);
        InsectCageMenuRefreshPreview_3896a0(0);
        InsectCageMenuSetStateFlagMaybe_390aa0(6, 0);
        w = *(s32 *)(InsectCageMenuGetCursorObj_390f70() + 0x96C);
        InsectRecSlotRemoveItem_3cfde0(InsectCageMenuGetCurCageItem_391030(), w, 1);
        MenuObjTeardown_387d60(InsectCageMenuGetCursorObj_390f70());
        InsectCageSePlay_3844b0(&D_004832A0, 6);
        D_004833D4++;
        break;
    case 11:
        if (flags & 6) {
            PlayMenuSe_289ef0(5);
            UiSetWidgetVisible_290010(ctx, 0x754E, 0, -1);
            InsectCageMenuSelectEntry_390d40(0x7531, 0);
        }
        break;
    }
    return 1;
}
