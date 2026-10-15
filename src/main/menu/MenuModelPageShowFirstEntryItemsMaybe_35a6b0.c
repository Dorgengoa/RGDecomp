#include "types.h"


typedef struct Ent {
    s16 *p;
    u8 x : 1;
    u8 f : 1;
} Ent;

typedef struct Slot {
    u8 pad0[4];
    Ent e[3];
} Slot;

typedef struct Self {
    u8 pad0[0x68];
    Slot *slot;
    u8 pad6C[0x78 - 0x6C];
    u8 b78[0x20];
    u8 b98[0x20];
    u8 bB8[0x20];
    u8 padD8[0x134 - 0xD8];
    s32 h;
} Self;

extern void GetGameData_1fede0(void);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern void UiSetSpriteFlags_290bd0(s32, s32, s32, s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiSetItemIconUv_288e50(s32, s32, s32, s32);
extern void ItemRowGetNameOrUnknownMaybe_3cd8b0(void *, void *);
extern void UiSetTextString_28f510(s32, s32, void *, s32);
extern s32 UiGetWidgetTextWidth_28f400(s32, s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
extern void UiSetTextColor_290a40(s32, s32, s32, s32);
extern u8 D_00462C20[];
extern f32 D_0047D5B8;

void MenuModelPageShowFirstEntryItemsMaybe_35a6b0(Self *self) {
    Slot *slot;
    s32 a;
    s32 b;
    s32 i;
    s32 id0;
    s32 id1;
    s32 id2;
    s16 fl[4];
    s32 ids[3];

    GetGameData_1fede0();
    slot = self->slot;
    UiSetWidgetColor_2905b0(self->h, 0x1E3, D_0047D5B8, D_0047D5B8, D_0047D5B8, 1.0f);
    UiSetSpriteFlags_290bd0(self->h, 0x1E3, 0x200, 0, 0, 0);
    UiSetSpriteFlags_290bd0(self->h, 0x1E3, 0x200, 0, 1, 0);
    UiSetSpriteFlags_290bd0(self->h, 0x1E3, 0x200, 0, 2, 0);
    UiSetWidgetVisible_290010(self->h, 0x1DD, 0, -1);
    if (slot != 0) {
    UiSetWidgetVisible_290010(self->h, 0x1DD, 1, -1);
    id2 = id1 = id0 = -1;
    if (slot->e[0].p != 0) {
        id0 = slot->e[0].p[0x2C / 2];
        UiSetItemIconUv_288e50(UiGetWidgetSprite_28fe10(self->h, 0x1E3, 0), id0, 0x18, 0x1B);
    }
    if (slot->e[1].p != 0) {
        id1 = slot->e[1].p[0x2C / 2];
        UiSetItemIconUv_288e50(UiGetWidgetSprite_28fe10(self->h, 0x1E3, 1), id1, 0x18, 0x1B);
    }
    if (slot->e[2].p != 0) {
        id2 = slot->e[2].p[0x2C / 2];
        UiSetItemIconUv_288e50(UiGetWidgetSprite_28fe10(self->h, 0x1E3, 2), id2, 0x18, 0x1B);
    }
    ItemRowGetNameOrUnknownMaybe_3cd8b0(&slot->e[0], self->b78);
    ItemRowGetNameOrUnknownMaybe_3cd8b0(&slot->e[1], self->b98);
    ItemRowGetNameOrUnknownMaybe_3cd8b0(&slot->e[2], self->bB8);
    UiSetTextString_28f510(self->h, 0x1E3, self->b78, 0);
    UiSetTextString_28f510(self->h, 0x1E3, self->b98, 1);
    UiSetTextString_28f510(self->h, 0x1E3, self->bB8, 2);
    a = UiGetWidgetTextWidth_28f400(self->h, 0x1E3, 0);
    b = UiGetWidgetTextWidth_28f400(self->h, 0x1E3, 1);
    UiSetWidgetPos_290f60(self->h, 0x258, a + 0x34, 0x10B);
    UiSetWidgetPos_290f60(self->h, 0x262, b + 0x34, 0x12E);
    ids[0] = id0;
    ids[1] = id1;
    ids[2] = id2;
    fl[0] = slot->e[0].f;
    fl[1] = slot->e[1].f;
    fl[2] = slot->e[2].f;
    for (i = 0; i < 3; i++) {
        if (fl[i] == 0) {
            if (ids[i] < 0) {
            UiSetSpriteSizeUvSize_28f670(self->h, 0x1E3, 0, 0, 0, 0, i);
            UiSetTextColor_290a40(self->h, 0x1E3, 0xFF303030, i);
            }
        } else {
            UiSetSpriteFlags_290bd0(self->h, 0x1E3, 0xA, 0, i, 0);
            UiSetTextColor_290a40(self->h, 0x1E3, 0xFF303030, i);
        }
    }
    } else {
        UiSetSpriteSizeUvSize_28f670(self->h, 0x1E3, 0, 0, 0, 0, 0);
        UiSetSpriteSizeUvSize_28f670(self->h, 0x1E3, 0, 0, 0, 0, 1);
        UiSetSpriteSizeUvSize_28f670(self->h, 0x1E3, 0, 0, 0, 0, 2);
        UiSetTextString_28f510(self->h, 0x1E3, D_00462C20, 0);
        UiSetTextString_28f510(self->h, 0x1E3, D_00462C20, 1);
        UiSetTextString_28f510(self->h, 0x1E3, D_00462C20, 2);
        a = UiGetWidgetTextWidth_28f400(self->h, 0x1E3, 0);
        b = UiGetWidgetTextWidth_28f400(self->h, 0x1E3, 1);
        UiSetWidgetPos_290f60(self->h, 0x258, a + 0x34, 0x10B);
        UiSetWidgetPos_290f60(self->h, 0x262, b + 0x34, 0x12E);
    }
}
