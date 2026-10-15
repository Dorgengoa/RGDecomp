#include "types.h"

typedef struct {
    s32 m0;
    s16 m4;
    s16 m6;
} Iter;

typedef struct {
    s16 v[9];
} Tbl;

typedef struct {
    s16 m0;
    u8 m2;
    u8 m3;
    s32 m4;
    s32 m8;
} Ent;

extern u8 *GetGameData_1fede0(void);
extern void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
extern void UiSetSpriteU_28f930(s32, s32, s32, s32);
extern u8 *UiFindWidget_290460(s32, u16);
extern void MenuListSetCount_29b590(u8 *, s32);
extern Ent *IterSeek_36fff0(Iter *, s32);
extern Ent *IterNext_370040(Iter *);
extern void IterInit_370170(Iter *, s32 *);
extern s32 EquipSlotGetScaledCost_3a05c0(s32);
extern void CharaAbilityViewCtor_3a8180(s32 *, s32, s32, s32);
extern s32 CharaFindSlotByRecId_3ad390(s32, s32);
extern s32 CharaHasAbilityOrHigher_3adf10(s32, s32, s32, s32);
extern s32 PartyGetSlotChara_3c2fb0(s32, s32);
extern s32 AbilityDataGetCost_3f5ca0(Ent *);
extern Tbl D_00450CC0;


s32 MenuCharaAbilityListFill_29b180(u8 *self, s32 idx, s32 arg2) {
    Iter it;
    s32 buf[6];
    Tbl tbl;
    s32 o;
    s32 r;
    s32 n;
    Ent *e;
    s32 i;
    u8 *w;
    u8 *a;
    u8 *b;
    u8 *c;
    s32 q;
    s32 k;

    r = PartyGetSlotChara_3c2fb0(*(s32 *)(GetGameData_1fede0() + 0x18), idx);
    o = r;
    if (r == 0) {
        return 0;
    }
    CharaAbilityViewCtor_3a8180(buf, r, -1, -1);
    IterInit_370170(&it, buf);
    n = it.m4;
    MenuListSetCount_29b590(self, n);
    e = IterSeek_36fff0(&it, arg2);
    for (i = 0; i < 5; i++) {
        w = UiFindWidget_290460(*(s32 *)(self + 0x4C4), i + 0x126);
        if (w == 0) {
            return 0;
        }
        a = *(u8 **)(w + 0x20);
        if (a == 0) {
            return 0;
        }
        b = *(u8 **)(w + 0x24);
        if (b == 0) {
            return 0;
        }
        c = *(u8 **)(w + 0x28);
        if (c == 0) {
            return 0;
        }
        *(s8 *)(c + 0xA) = 2;
        if (i < n && e != 0) {
            *(s32 *)(c + 4) = e->m8;
            *(s32 *)(c + 0xC) = 0xFF303030;
            UiSetSpriteSizeUvSize_28f670(*(s32 *)(self + 0x4C4), 0x12B, 0x18, 0x16, 0x18, 0x16, i);
            if (e->m2 == 0) {
                *(s16 *)(a + 0xC) = 0x14;
                *(s16 *)(a + 4) = 0x14;
                *(s16 *)(a + 0xE) = 0x10;
                *(s16 *)(a + 6) = 0x10;
                q = CharaFindSlotByRecId_3ad390(o, e->m0);
                if (q != 0) {
                    *(s64 *)(b + 8) = EquipSlotGetScaledCost_3a05c0(q);
                } else {
                    *(s64 *)(b + 8) = AbilityDataGetCost_3f5ca0(e);
                }
                *(s16 *)(b + 0x16) = 0xC;
                *(s16 *)(b + 0x18) = 0x10;
            } else {
                *(s16 *)(a + 0xE) = 0;
                *(s16 *)(a + 0xC) = 0;
                *(s16 *)(a + 6) = 0;
                *(s16 *)(a + 4) = 0;
                *(s16 *)(b + 0x18) = 0;
                *(s16 *)(b + 0x16) = 0;
            }
            {
                s16 *s = D_00450CC0.v;
                s16 *d = tbl.v;
                s32 m = 9;
                do {
                    m--;
                    *d = *s;
                    s++;
                    d++;
                } while (m > 0);
            }
            k = 0;
            switch (e->m3) {
            case 1:
                k = 1;
                break;
            case 2:
                k = 0;
                break;
            case 3:
                k = 2;
                break;
            case 4:
                k = 3;
                break;
            case 5:
                k = 4;
                break;
            case 11:
                k = 5;
                break;
            case 12:
                k = 6;
                break;
            case 13:
                k = 7;
                break;
            case 14:
                k = 8;
                break;
            }
            UiSetSpriteU_28f930(*(s32 *)(self + 0x4C4), 0x12B, tbl.v[k], i);
            if (CharaHasAbilityOrHigher_3adf10(o, e->m0, 1, 1) != 0) {
                UiSetSpriteSizeUvSize_28f670(*(s32 *)(self + 0x4C4), 0x12C, 0, 0, 0, 0, i);
            } else {
                UiSetSpriteSizeUvSize_28f670(*(s32 *)(self + 0x4C4), 0x12C, 0x1C, 0xE, 0x1C, 0xE, i);
            }
        } else {
            *(s32 *)(c + 4) = 0;
            *(s16 *)(a + 0xE) = 0;
            *(s16 *)(a + 0xC) = 0;
            *(s16 *)(a + 6) = 0;
            *(s16 *)(a + 4) = 0;
            *(s16 *)(b + 0x18) = 0;
            *(s16 *)(b + 0x16) = 0;
            UiSetSpriteSizeUvSize_28f670(*(s32 *)(self + 0x4C4), 0x12B, 0, 0, 0, 0, i);
            UiSetSpriteSizeUvSize_28f670(*(s32 *)(self + 0x4C4), 0x12C, 0, 0, 0, 0, i);
        }
        e = IterNext_370040(&it);
    }
    return 1;
}
