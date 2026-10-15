#include "types.h"


extern void GetGameData_1fede0();
extern u8 *UiEntryListFindByTag_28ea40(s32, s32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern void UiSetSpriteFlags_290bd0(s32, s32, s32, s32, s32, s32);
extern void UiSetTextColor_290a40(s32, s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void UiSetTextString_28f510(s32, s32, u8 *, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiSetItemIconUv_288e50(s32, s32, s32, s32);
extern void ItemRowGetNameOrUnknownMaybe_3cd8b0(u8 *, u8 *);
extern u8 *UiGetWidgetTextWidth_28f400(s32, s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, u8 *, s32);
extern void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
extern u8 D_00462C18[];
extern f32 D_0047D440;

#define W (*(s32 *)(self + 0x134))

void MenuModelPageShowCursorEntryItemsMaybe_359cf0(u8 *self) {
    u8 *ent; u8 *d; u8 *r0; u8 *r1; u8 *r2; u8 *r3; s32 id0; s32 id1; s32 id2; s32 i; s16 fl[3]; s32 ids[3]; f32 g;

    GetGameData_1fede0();
    ent = UiEntryListFindByTag_28ea40(*(s32 *)(self + 0x138), 0x20);
    UiSetWidgetColor_2905b0(W, 0x1E3, D_0047D440, D_0047D440, D_0047D440, 1.0f);
    UiSetSpriteFlags_290bd0(W, 0x1E3, 0x200, 0, 0, 0);
    UiSetSpriteFlags_290bd0(W, 0x1E3, 0x200, 0, 1, 0);
    UiSetSpriteFlags_290bd0(W, 0x1E3, 0x200, 0, 2, 0);
    UiSetTextColor_290a40(W, 0x1E3, 0xFF392B1D, 0);
    UiSetTextColor_290a40(W, 0x1E3, 0xFF392B1D, 1);
    UiSetTextColor_290a40(W, 0x1E3, 0xFF392B1D, 2);
    UiSetWidgetVisible_290010(W, 0x1DD, 0, -1);
    if (((u8 **)(self + 0x68))[*(s16 *)(ent + 0x16)] != 0) {
        UiSetWidgetVisible_290010(W, 0x1DD, 1, -1);
        id0 = -1;
        id1 = -1;
        d = ((u8 **)(self + 0x68))[*(s16 *)(ent + 0x16)];
        id2 = -1;
        if (*(u8 **)(d + 4) != 0) {
            id0 = *(s16 *)(*(u8 **)(d + 4) + 0x2C);
            UiSetTextString_28f510(W, 0x1E3, self + 0x78, 0);
            UiSetItemIconUv_288e50(UiGetWidgetSprite_28fe10(W, 0x1E3, 0), id0, 0x18, 0x1B);
        }
        if (*(u8 **)(d + 0xC) != 0) {
            id1 = *(s16 *)(*(u8 **)(d + 0xC) + 0x2C);
            UiSetTextString_28f510(W, 0x1E3, self + 0x98, 1);
            UiSetItemIconUv_288e50(UiGetWidgetSprite_28fe10(W, 0x1E3, 1), id1, 0x18, 0x1B);
        }
        if (*(u8 **)(d + 0x14) != 0) {
            id2 = *(s16 *)(*(u8 **)(d + 0x14) + 0x2C);
            UiSetTextString_28f510(W, 0x1E3, self + 0xB8, 2);
            UiSetItemIconUv_288e50(UiGetWidgetSprite_28fe10(W, 0x1E3, 2), id2, 0x18, 0x1B);
        }
        ItemRowGetNameOrUnknownMaybe_3cd8b0(d + 4, self + 0x78);
        ItemRowGetNameOrUnknownMaybe_3cd8b0(d + 0xC, self + 0x98);
        ItemRowGetNameOrUnknownMaybe_3cd8b0(d + 0x14, self + 0xB8);
        r2 = UiGetWidgetTextWidth_28f400(W, 0x1E3, 0);
        r3 = UiGetWidgetTextWidth_28f400(W, 0x1E3, 1);
        UiSetWidgetPos_290f60(W, 0x258, r2 + 0x34, 0x10B);
        UiSetWidgetPos_290f60(W, 0x262, r3 + 0x34, 0x12E);
        ids[0] = id0;
        ids[1] = id1;
        ids[2] = id2;
        fl[0] = (u64)*(u8 *)(d + 0x8) << 62 >> 63;
        fl[1] = (u64)*(u8 *)(d + 0x10) << 62 >> 63;
        fl[2] = (u64)*(u8 *)(d + 0x18) << 62 >> 63;
        for (i = 0; i < 3; i++) {
            if (fl[i] == 0) {
                if (ids[i] < 0) {
                    UiSetSpriteSizeUvSize_28f670(W, 0x1E3, 0, 0, 0, 0, i);
                    UiSetTextColor_290a40(W, 0x1E3, 0xFF303030, i);
                }
            } else {
                UiSetSpriteFlags_290bd0(W, 0x1E3, 0xA, 0, i, 0);
                UiSetTextColor_290a40(W, 0x1E3, 0xFF303030, i);
            }
        }
    } else {
        UiSetSpriteSizeUvSize_28f670(W, 0x1E3, 0, 0, 0, 0, 0);
        UiSetSpriteSizeUvSize_28f670(W, 0x1E3, 0, 0, 0, 0, 1);
        UiSetSpriteSizeUvSize_28f670(W, 0x1E3, 0, 0, 0, 0, 2);
        UiSetTextString_28f510(W, 0x1E3, D_00462C18, 0);
        UiSetTextString_28f510(W, 0x1E3, D_00462C18, 1);
        UiSetTextString_28f510(W, 0x1E3, D_00462C18, 2);
        r0 = UiGetWidgetTextWidth_28f400(W, 0x1E3, 0);
        r1 = UiGetWidgetTextWidth_28f400(W, 0x1E3, 1);
        UiSetWidgetPos_290f60(W, 0x258, r0 + 0x34, 0x10B);
        UiSetWidgetPos_290f60(W, 0x262, r1 + 0x34, 0x12E);
    }
}
