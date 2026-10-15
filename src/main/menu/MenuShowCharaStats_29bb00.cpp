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
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual s32 v140(s32);
    virtual void d79();
    virtual s32 v148(s32);
    virtual void d81();
    virtual s32 v150(s32);
    virtual void d83();
    virtual s32 v158(s32);
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual void d101();
    virtual void d102();
    virtual void d103();
    virtual void d104();
    virtual void d105();
    virtual void d106();
    virtual void d107();
    virtual void d108();
    virtual void d109();
    virtual void d110();
    virtual void d111();
    virtual void d112();
    virtual void d113();
    virtual void d114();
    virtual void d115();
    virtual void d116();
    virtual void d117();
    virtual void d118();
    virtual void d119();
    virtual void d120();
    virtual void d121();
    virtual void d122();
    virtual void d123();
    virtual void d124();
    virtual void d125();
    virtual void d126();
    virtual void d127();
    virtual void d128();
    virtual void d129();
    virtual void d130();
    virtual void d131();
    virtual void d132();
    virtual void d133();
    virtual void d134();
    virtual void d135();
    virtual void d136();
    virtual void d137();
    virtual void d138();
    virtual void d139();
    virtual void d140();
    virtual void d141();
    virtual void d142();
    virtual void d143();
    virtual void d144();
    virtual void d145();
    virtual void d146();
    virtual void d147();
    virtual void d148();
    virtual void d149();
    virtual void d150();
    virtual void d151();
    virtual void d152();
    virtual void d153();
    virtual void d154();
    virtual void d155();
    virtual void d156();
    virtual void d157();
    virtual void d158();
    virtual void d159();
    virtual void d160();
    virtual void d161();
    virtual void d162();
    virtual void d163();
    virtual void d164();
    virtual void d165();
    virtual void d166();
    virtual void d167();
    virtual void d168();
    virtual void d169();
    virtual void d170();
    virtual void d171();
    virtual void d172();
    virtual void d173();
    virtual void d174();
    virtual void d175();
    virtual void d176();
    virtual void d177();
    virtual void d178();
    virtual void d179();
    virtual void d180();
    virtual void d181();
    virtual void d182();
    virtual void d183();
    virtual void d184();
    virtual void d185();
    virtual void d186();
    virtual void d187();
    virtual void d188();
    virtual void d189();
    virtual void d190();
    virtual void d191();
    virtual void d192();
    virtual void d193();
    virtual void d194();
    virtual void d195();
    virtual void d196();
    virtual void d197();
    virtual void d198();
    virtual void d199();
    virtual void d200();
    virtual void d201();
    virtual void d202();
    virtual void d203();
    virtual void d204();
    virtual void d205();
    virtual void d206();
    virtual void d207();
    virtual void d208();
    virtual void d209();
    virtual void d210();
    virtual void d211();
    virtual void d212();
    virtual void d213();
    virtual void d214();
    virtual void d215();
    virtual void d216();
    virtual void d217();
    virtual void d218();
    virtual void d219();
    virtual void d220();
    virtual void d221();
    virtual void d222();
    virtual void d223();
    virtual void d224();
    virtual void d225();
    virtual void d226();
    virtual void d227();
    virtual void d228();
    virtual void d229();
    virtual void d230();
    virtual void d231();
    virtual void d232();
    virtual void d233();
    virtual void d234();
    virtual void d235();
    virtual void d236();
    virtual void d237();
    virtual void d238();
    virtual void d239();
    virtual void d240();
    virtual void d241();
    virtual void d242();
    virtual void d243();
    virtual void d244();
    virtual void d245();
    virtual void d246();
    virtual void d247();
    virtual void d248();
    virtual void d249();
    virtual s32 v3F0(s32, s32);
    u8 pad4[8];
    s32 xC;
};

extern "C" {
StatE *UiGetWidgetSubItem_28f2b0(s32, s32, s32);
World *GetGameData_1fede0(void);
Chr *PartyGetSlotChara_3c2fb0(void *, s32);
void UiSetSubItemFlags_28ef30(s32, s32, s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
s32 MsgTableLookup_28aa30(void *, s32);
void UiLayoutStringGlyphs_28a800(s32, s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void UiSetSubItemGlyphUvW_28f0c0(s32, s32, s32, s32);
}

extern f32 D_0047D354;
extern f32 D_0047D278;
extern Tbl D_00450C50;
extern void *D_004823D8;

#define ZERON(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_ != 0) while (n_) { *p_ = 0; n_--; p_++; } }

extern "C" s32 MenuShowCharaStats_29bb00(Menu *m, s32 id) {
    s16 base[6];
    s32 lvl;
    s32 i;
    Tbl tb;
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
        UiSetSubItemFlags_28ef30(m->x4C4, 0xDE, 0x1A0, -1, i);
        if (st[i].val < (b = *(s16 *)((u32)&base[i]))) {
            UiSetSubItemFlags_28ef30(m->x4C4, 0xDE, 0x80, 1, i);
        } else if (b == st[i].val) {
            UiSetSubItemFlags_28ef30(m->x4C4, 0xDE, 0x20, 1, i);
        } else {
            UiSetSubItemFlags_28ef30(m->x4C4, 0xDE, 0x100, 1, i);
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
