/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x00504EA0 -- lays out the equipment compare panel.  A 5-entry s16
 * column table is copied out of small data, then whichever of the two cursor
 * columns (f74/f76) is behind drives which three slots are re-positioned and
 * which of the two 0xE rows is used; f78 records which layout was chosen.
 * The lower half resolves the highlighted item through the iterator built by
 * func_3A8180/func_370170 and fills the 0xE name row and the 0xF value row,
 * or clears both when nothing is selected.
 *
 * ONE `lw $25,0($18) / lw $25,0x2D0($25) / jalr $25` -> C++ virtual, vptr 0,
 * slot (0x2D0-8)/4 = 178.
 * `dsll32 $7,$2,0 / dsra32 $7,$7,0` (shift ZERO) is an s32->s64 widen at a call
 * argument: func_291250's fourth parameter is s64 and the value is s32.
 * Stack locals come out in REVERSE declaration order, so `tmp` is declared
 * last to land at 0x50. */

struct Ent {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 owns(s16 k) { return VCM(s32, (void *, s16), 0x2D0, k); }   /* slot 178 -> vtable +0x2D0 */
};

typedef struct Item  { s16 f00; u8 pad02; u8 f03; u8 pad04[4]; s32 f08; } Item;
typedef struct Hold  { u8 pad00[0x24]; struct Cell *f24; } Hold;
typedef struct Cell  { u8 pad00[0x16]; s16 f16; s16 f18; } Cell;
typedef struct Panel { u8 pad00[0x74]; s16 f74; s16 f76; s16 f78; } Panel;
typedef struct Top   { u8 pad00[0x18]; s32 f18; } Top;

extern "C" s16 D_004805E0[4];         /* gp - 0x4B90, declared SHORT for small data */

extern "C" {

extern Top  *GetGameData_1fede0(void);
extern void  UiPageSetSpritePresetMaybe_289090(Panel *p, u16 id, s32 c, s32 d);
extern Hold *UiFindWidget_290460(void *w, u16 id);
extern void  UiSetTextColor_290a40(void *w, u16 id, u32 c, s32 d);
extern void  UiSetTextFont_290a80(void *w, u16 id, s32 c, s32 d);
extern void  UiSetTextStringPos_290b20(void *w, u16 id, s32 c, s32 d, s32 e, s32 f);
extern void  UiSetWidgetPos_290f60(void *w, u16 id, s32 x, s16 y);
extern void  UiSetWidgetSubItemValue_291250(void *w, u16 id, s32 c, s64 v);
extern Item * IterSeek_36fff0(void *, s32, int, int);
extern void IterInit_370170(void *, void *, int, int);
extern s32   EquipSlotGetScaledCost_3a05c0(s32 h);
extern void  CharaAbilityViewCtor_3a8180(void *dst, Ent *o, s32 c, s32 d);
extern s32   CharaFindSlotByRecId_3ad390(Ent *o, s16 k);
extern Ent  *PartyGetSlotChara_3c2fb0(s32 a, s32 k);
extern s32   AbilityDataGetCost_3f5ca0(Item *p);
extern s32 normal_BtlChgPageSetAbilityTypeIcon_505470(void *p, s32 id, s32 c);
extern s32   normal_BtlChgPageGetMember_505f90(Panel *p);
extern void *normal_UiPageGetLayout_289b60(Panel *p);

}

extern "C" s32 normal_BtlChgPageAbilityListScroll_504ea0(Panel *a)
{
    s16   tab[5];
    s32   buf[2];
    s32   tmp[6] __attribute__((aligned(16)));
    void *w;
    Top  *t;
    Item *r;
    Ent  *o;
    Hold *h;
    Cell *g;
    s16  *sp;
    s16  *dp;
    s32   c;
    s32   i;
    s32   n;
    s32   v;
    s32   u;

    w = normal_UiPageGetLayout_289b60(a);
    if (w == 0) {
        return 0;
    }
    sp = D_004805E0;
    dp = tab;
    i = 5;
    do {
        *dp = *sp;
        sp++;
        dp++;
        i--;
    } while (i > 0);
    if (a->f74 > a->f76) {
        i = 0;
        do {
            UiSetWidgetPos_290f60(w, (u16)(i * 3 + 5), 0, tab[i + 2]);
            i++;
        } while (i < 3);
        UiSetWidgetPos_290f60(w, 0xE, 0, tab[0]);
        UiSetWidgetPos_290f60(w, 0xE, 0, tab[1]);
        UiSetWidgetPos_290f60(w, 0x18, 0xD5, 0xA);
        UiSetWidgetPos_290f60(w, 0x14, 0xBF, 1);
        a->f78 = 1;
    } else if (a->f74 < a->f76) {
        i = 0;
        do {
            UiSetWidgetPos_290f60(w, (u16)(i * 3 + 5), 0, tab[i]);
            i++;
        } while (i < 3);
        UiSetWidgetPos_290f60(w, 0xE, 0, tab[4]);
        UiSetWidgetPos_290f60(w, 0xE, 0, tab[3]);
        UiSetWidgetPos_290f60(w, 0x18, 0xD5, 0xA);
        UiSetWidgetPos_290f60(w, 0x14, 0xBF, 1);
        a->f78 = 2;
    }
    t = GetGameData_1fede0();
    if (t == 0) {
        return 0;
    }
    o = PartyGetSlotChara_3c2fb0(t->f18, normal_BtlChgPageGetMember_505f90(a));
    if (o == 0) {
        return 0;
    }
    CharaAbilityViewCtor_3a8180(tmp, o, 0, -1);
    IterInit_370170(buf, tmp, 0, 0);
    r = 0;
    if (a->f78 == 1) {
        c = a->f76;
        if (c < 0) {
            c = 0;
        }
        r = IterSeek_36fff0(buf, c, 0, 0);
    } else if (a->f78 == 2) {
        r = IterSeek_36fff0(buf, a->f76 + 2, 0, 0);
    }
    if (r != 0) {
        UiSetTextStringPos_290b20(w, 0xE, r->f08, -1, -1, 0);
        UiSetTextFont_290a80(w, 0xE, 2, 0);
        UiSetTextColor_290a40(w, 0xE, 0xFF202020, 0);
        if (o->owns(r->f00) != 0) {
            UiSetTextColor_290a40(w, 0xE, 0xFF404040, 0);
        }
        h = UiFindWidget_290460(w, 0xF);
        if (h == 0) {
            return 0;
        }
        g = h->f24;
        if (g == 0) {
            return 0;
        }
        g->f16 = 0xC;
        g->f18 = 0xF;
        n = CharaFindSlotByRecId_3ad390(o, r->f00);
        if (n != 0) {
            v = EquipSlotGetScaledCost_3a05c0(n);
        } else {
            v = AbilityDataGetCost_3f5ca0(r);
        }
        u = r->f03;
        UiSetWidgetSubItemValue_291250(w, 0xF, 0, v);
        normal_BtlChgPageSetAbilityTypeIcon_505470(a, 0x14, u);
        normal_BtlChgPageSetAbilityTypeIcon_505470(a, 0x18, -1);
        return 1;
    }
    h = UiFindWidget_290460(w, 0xF);
    if (h == 0) {
        return 0;
    }
    g = h->f24;
    if (g == 0) {
        return 0;
    }
    g->f18 = 0;
    g->f16 = 0;
    UiSetWidgetSubItemValue_291250(w, 0xF, 0, 0);
    UiPageSetSpritePresetMaybe_289090(a, 0x14, 0, 0);
    UiPageSetSpritePresetMaybe_289090(a, 0x18, 5, 0);
    UiSetTextStringPos_290b20(w, 0x18, 0, -1, -1, 0);
    return 1;
}
