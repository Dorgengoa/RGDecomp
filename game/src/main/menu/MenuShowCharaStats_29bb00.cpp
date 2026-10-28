/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct StatE {
    u8 pad0[8];
    s64 val;
    u8 pad10[0x10];
} StatE;

typedef struct Row {
    s16 lvl;
    s16 a;
    s16 b;
} Row;

typedef struct Tbl {
    Row r[11];
} Tbl;

typedef struct Menu {
    u8 pad0[0x4C4];
    s32 x4C4;
} Menu;

typedef struct World {
    u8 pad0[0x18];
    void *x18;
} World;

class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v140(s32 a0) { return VCM(s32, (void *, s32), 0x140, a0); }
    
    s32 v148(s32 a0) { return VCM(s32, (void *, s32), 0x148, a0); }
    
    s32 v150(s32 a0) { return VCM(s32, (void *, s32), 0x150, a0); }
    
    s32 v158(s32 a0) { return VCM(s32, (void *, s32), 0x158, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v3F0(s32 a0, s32 a1) { return VCM(s32, (void *, s32, s32), 0x3F0, a0, a1); }
    u8 pad4[8];
    s32 xC;
};

extern "C" {
StatE *UiGetWidgetSubItem_28f2b0(s32, s32, s32);
World *GetGameData_1fede0(void);
Chr *PartyGetSlotChara_3c2fb0(void *, s32);
void UiSetSubItemFlags_28ef30(s32, s32, long long, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
s32 MsgTableLookup_28aa30(void *, s32);
void UiLayoutStringGlyphs_28a800(s32, s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void UiSetSubItemGlyphUvW_28f0c0(s32, s32, s32, s32);
}

extern "C" f32 D_0047D354;
extern "C" f32 D_0047D278;
extern "C" Tbl D_00450C50;
extern "C" void *D_004823D8;

#define ZERON(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_ != 0) while (n_) { *p_ = 0; n_--; p_++; } }

extern "C" s32 MenuShowCharaStats_29bb00(Menu *m, s32 id) {
    s16 base[6];
    s32 lvl;
    s32 i;
    Tbl tb __attribute__((aligned(16)));
    s16 j;
    s32 l;
    s32 h;
    Chr *c;
    StatE *st;
    s32 b;

    st = UiGetWidgetSubItem_28f2b0(m->x4C4, 0xDE, 0);
    if (st == 0) return 0;
    c = PartyGetSlotChara_3c2fb0(GetGameData_1fede0()->x18, id);
    if (c == 0) goto done;
    st[0].val = c->v148(1);
    st[1].val = c->v158(1);
    st[2].val = c->v150(1);
    st[3].val = c->v3F0(0, 1);
    st[4].val = c->v3F0(1, 1);
    st[5].val = c->v140(1);
    ZERON(base, 0xC);
    base[0] = c->v148(0);
    base[1] = c->v158(0);
    base[2] = c->v150(0);
    base[3] = c->v3F0(0, 0);
    base[4] = c->v3F0(1, 0);
    base[5] = c->v140(0);
    for (i = 0; i < 6; i++) {
        UiSetSubItemFlags_28ef30(m->x4C4, 0xDE, (long long)(0x1A0), -1, i);
        if (st[i].val < (b = *(s16 *)((u32)&base[i]))) {
            UiSetSubItemFlags_28ef30(m->x4C4, 0xDE, (long long)(0x80), 1, i);
        } else if (b == st[i].val) {
            UiSetSubItemFlags_28ef30(m->x4C4, 0xDE, (long long)(0x20), 1, i);
        } else {
            UiSetSubItemFlags_28ef30(m->x4C4, 0xDE, (long long)(0x100), 1, i);
        }
    }
    UiSetWidgetColor_2905b0(m->x4C4, 0xDD, D_0047D354, D_0047D354, D_0047D278, 1.0f);
    UiSetWidgetColor_2905b0(m->x4C4, 0xDE, D_0047D354, D_0047D278, D_0047D278, 1.0f);
    {
        s16 *sp = (s16 *)&D_00450C50;
        s16 *dp = (s16 *)&tb;
        s32 n = 0x21;
        do {
            n--;
            *dp = *sp;
            sp++;
            dp++;
        } while (n > 0);
    }
    h = UiGetWidgetSprite_28fe10(m->x4C4, 0x22C, 0);
    UiLayoutStringGlyphs_28a800(h, MsgTableLookup_28aa30(D_004823D8, 0x839), 0, 0xAC, -2);
    h = UiGetWidgetSprite_28fe10(m->x4C4, 0x22D, 0);
    UiLayoutStringGlyphs_28a800(h, MsgTableLookup_28aa30(D_004823D8, 0x83A), 0, 0x109, -2);
    h = UiGetWidgetSprite_28fe10(m->x4C4, 0x22E, 0);
    UiLayoutStringGlyphs_28a800(h, MsgTableLookup_28aa30(D_004823D8, 0x83B), 0, 0x109, -2);
    h = UiGetWidgetSprite_28fe10(m->x4C4, 0x22F, 0);
    UiLayoutStringGlyphs_28a800(h, MsgTableLookup_28aa30(D_004823D8, 0x83C), 0, 0x109, -2);
    lvl = c->xC;
    for (j = 0; (l = *(s16 *)((u32)&tb.r[j])) >= 0; j++) {
        if (lvl == l) {
            s32 o = j << 1; o = (o + j) << 1;
            UiLayoutStringGlyphs_28a800(UiGetWidgetSprite_28fe10(m->x4C4, 0x22A, 0), MsgTableLookup_28aa30(D_004823D8, *(s16 *)((u8 *)&tb.r[0].a + o)), 0, 0xAC, -2);
            UiLayoutStringGlyphs_28a800(UiGetWidgetSprite_28fe10(m->x4C4, 0x22B, 0), MsgTableLookup_28aa30(D_004823D8, *(s16 *)((u8 *)&tb.r[0].b + o)), 0, 0xAC, -2);
            if (lvl == 8) {
                UiSetWidgetsVisibleById_291110(m->x4C4, 0x22B, 0, 1);
                UiSetWidgetsVisibleById_291110(m->x4C4, 0x22E, 0, 1);
                UiSetSubItemGlyphUvW_28f0c0(m->x4C4, 0xDE, 0, 1);
                UiSetSubItemGlyphUvW_28f0c0(m->x4C4, 0xDE, 0, 4);
            } else {
                UiSetWidgetsVisibleById_291110(m->x4C4, 0x22B, 1, 1);
                UiSetWidgetsVisibleById_291110(m->x4C4, 0x22E, 1, 1);
                UiSetSubItemGlyphUvW_28f0c0(m->x4C4, 0xDE, 0xC, 1);
                UiSetSubItemGlyphUvW_28f0c0(m->x4C4, 0xDE, 0xC, 4);
            }
            break;
        }
    }
    for (i = 0; i < 6; i++) {
        if (st[i].val >= 999) st[i].val = 999;
    }
done:
    return 1;
}
