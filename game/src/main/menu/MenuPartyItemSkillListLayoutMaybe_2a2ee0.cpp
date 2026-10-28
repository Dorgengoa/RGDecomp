/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct {
    s16 m0;
    s16 m2;
    u8 pad4[0x100];
    s16 m104;
} Win;

typedef struct {
    s16 m0;
    s16 m2;
    s32 m4;
    s32 m8;
    s32 mC;
} Row;

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f5C() { return VCM0(s32, 0x5C); }
    s32 f60() { return VCM0(s32, 0x60); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f368() { return VCM0(s32, 0x368); }
};

extern "C" {
u8 * GetGameData_1fede0(void);
s32 MsgTableLookup_28aa30(s32, s32);
void UiSetSubItemGlyphUvSize_28f100(s32, s32, s32, s32, s32);
void UiSetSubItemPos_28f200(s32, s32, s32, s32, s32);
Row *UiGetWidgetText_28f620(s32, u16, s32);
void UiSetSpriteSizeUvSize_28f670(s32, u16, s32, s32, s32, s32, s32);
void UiSetSpritePos_28fd10(s32, u16, s32, s32, s32);
Win *UiGetWidgetSprite_28fe10(s32, u16, s32);
void UiSetWidgetPos_290f60(s32, u16, s32, s32);
void UiSetWidgetSubItemValue_291250(s32, s32, s32, s64);
u8 *MenuGetSelItem_2a02d0(s32 *);
Unit *PartyGetSlotChara_3c2fb0(s32, s32);
s32 SkillFlowCountByItemMaybe_3e97c0(u8 *, s32, s32, s32, s32, s32, s32);
s32 MenuPartyItemSkillListLayoutMaybe_2a2ee0(s32 *arg0, u16 arg1, u16 arg2, u16 arg3, s32 arg4, s32 arg5);
}

s32 MenuPartyItemSkillListLayoutMaybe_2a2ee0(s32 *arg0, u16 arg1, u16 arg2, u16 arg3, s32 arg4, s32 arg5) {
    Win *w;
    Row *rows;
    s32 bx;
    s32 by;
    u8 *mgr;
    s32 cnt;
    s32 i;
    Unit *u;
    u8 *info;
    s32 k;
    s32 x;
    s32 y;
    s32 id;
    s32 r;
    u8 *q;
    f32 f;

    w = UiGetWidgetSprite_28fe10(*arg0, arg1, 0);
    if (w == 0) {
        return 0;
    }
    rows = UiGetWidgetText_28f620(*arg0, arg1, 0);
    if (rows == 0) {
        return 0;
    }
    bx = w->m0 - w->m104 - 0x10;
    by = w->m2;
    mgr = GetGameData_1fede0();
    cnt = 0;
    i = 0;
    do {
        u = PartyGetSlotChara_3c2fb0(*(s32 *)(mgr + 0x18), i);
        if (u != 0 && u->f368() == 0) {
            cnt++;
        }
        i++;
    } while (i < 8);
    info = MenuGetSelItem_2a02d0(arg0);
    if (info == 0) {
        return 0;
    }
    i = 0;
    do {
        UiSetSpriteSizeUvSize_28f670(*arg0, arg3, 0, 0, 0, 0, i);
        UiSetSubItemGlyphUvSize_28f100(*arg0, arg4, 0, 0, i);
        i++;
    } while (i < 8);
    k = 0;
    i = 0;
    do {
        rows[k].m0 = -1;
        u = PartyGetSlotChara_3c2fb0(*(s32 *)(mgr + 0x18), i);
        if (u != 0 && u->f368() == 0) {
            x = bx + 0x20;
            y = by + 8 + i * 0x1A;
            rows[k].m0 = x;
            rows[k + 1].m2 = y;
            rows[k].m2 = y;
            rows[k].m4 = u->f60();
            rows[k + 1].m0 = x + 0x50;
            id = **(s16 **)(info + 0x10);
            r = SkillFlowCountByItemMaybe_3e97c0(mgr, id, u->f5C(), 0, 1, 1, 0);
            if (r > 0) {
                rows[k + 1].m4 = MsgTableLookup_28aa30(arg5, 0x3F2);
                rows[k + 1].mC = 0xFF303030;
                rows[k].mC = 0xFF303030;
                UiSetSpritePos_28fd10(*arg0, arg3, x + 0xA0, y, i);
                UiSetSpriteSizeUvSize_28f670(*arg0, arg3, 0x1C, 0x14, 0x24, 0x14, i);
                UiSetSubItemPos_28f200(*arg0, arg4, x + 0xB8, y + 3, i);
                UiSetWidgetSubItemValue_291250(*arg0, arg4, i, r);
                UiSetSubItemGlyphUvSize_28f100(*arg0, arg4, 0xC, 0x10, i);
            } else {
                rows[k + 1].m4 = MsgTableLookup_28aa30(arg5, 0x3F3);
                rows[k + 1].mC = 0xFF202020;
                rows[k].mC = 0xFF202020;
            }
            k += 2;
        }
        i++;
    } while (i < 8);
    w = UiGetWidgetSprite_28fe10(*arg0, arg2, 0);
    if (w == 0) {
        return 0;
    }
    if (cnt == 1) {
        w->m0 = -1;
    } else {
        w->m0 = 0xC;
    }
    f = cnt - 1;
    *(f32 *)((u8 *)w + 0x14) = *(f32 *)((u8 *)w + 0x34) = *(f32 *)((u8 *)w + 0x54) = f;
    UiSetWidgetPos_290f60(*arg0, arg2, bx, by);
    return 1;
}
