/* rgp:protos */
#define RGP_SELF_MenuCatalogRankListSetup_35da20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
#pragma opt_loop_invariants off

typedef struct Item { u8 pad0[4]; s32 m4; u8 pad8[4]; s16 mC; s16 mE; s16 m10; s16 m12; } Item;
typedef struct List { u8 pad[0x10]; s32 count; Item *items; } List;
typedef struct L94 { u8 pad[0x14]; List *list; } L94;
typedef struct L8 { u8 pad[0x94]; L94 *m94; } L8;
typedef struct Game { u8 pad[8]; L8 *m8; u8 pad2[4]; s32 m10; } Game;
typedef struct Elem { u8 pad0[4]; s16 m4; s16 m6; u8 pad8[2]; s16 mA; u8 padC[2]; s16 mE; u8 pad10[2]; s16 m12; s16 m14; s16 m16; s16 m18; s16 m1A; } Elem;
typedef struct Win {
    u8 pad0[0x1D0];
    f32 m1D0;
    u8 pad1D4[0x200 - 0x1D4];
    u8 m200;
    u8 pad201[0x218 - 0x201];
    s32 m218;
    s32 m21C;
    u8 pad220[0x230 - 0x220];
    s32 m230;
    s32 m234;
    u8 pad238[0x274 - 0x238];
    s32 m274;
    s32 m278;
    u8 pad27C[0x288 - 0x27C];
    s32 m288;
    s32 m28C;
} Win;

extern char D_00462C58[];
extern s16 D_0047F838;
extern char D_004E8E20[][4];

extern void Sprintf_1343b8(char *buf, char *fmt, s32 v);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MenuCatalogRankListSetup_35da20(Win *w)
{
    s32 a;
    s32 b;
    Game *g;
    List *list;
    s32 i;
    Item *it;
    Elem *e;
    s32 found;
    s32 j;
    s32 save;
    char *buf;


    g = ((Game *)GetGameData_1fede0());
    i = 0;
    list = g->m8->m94->list;
    D_0047F838 = -1;
    do {
        s32 v;
        UiSetTextColor_290a40(w->m274, 0x1F3, 0xFF303030, i);
        it = &list->items[i];
        buf = D_004E8E20[i];
        Sprintf_1343b8(buf, D_00462C58, it->mC);
        UiSetTextString_28f510(w->m274, 0x208, buf, i);
        UiSetTextString_28f510(w->m274, 0x1F3, ((char *)RankEntryGetName_3fda80(it)), i);
        { s32 m4 = it->m4; UiSetWidgetSubItemValue_291250(w->m274, 0x208, i, (long long)(m4)); }
        MenuCatalogRankTrendIconUvMaybe_35cc90(w, it->m10, &a, &b);
        UiSetSpriteUv_28f970(w->m274, 0x203, a, b, i);
        v = it->mC;
        if ((v > 0 && v <= 10) || v == 20 || v == 30 || v == 40 || v == 50) {
            s32 lim;
            UiSetSpriteSizeUvSize_28f670(w->m274, 0x204, 0x14, 0x16, 0x14, 0x16, i);
            lim = ((short)StateVarGet_3ccac0(g->m10, 0xF));
            if (lim <= 0 || lim > 100) {
                lim = 100;
            }
            if (it->mC < lim) {
                UiSetSpriteU_28f930(w->m274, 0x204, 0x24, i);
            } else {
                UiSetSpriteU_28f930(w->m274, 0x204, 0x38, i);
            }
        } else {
            UiSetSpriteSizeUvSize_28f670(w->m274, 0x204, 0, 0, 0, 0, i);
        }
        if (((short)RankEntryGetId_3fdaa0(it)) == 0) {
            D_0047F838 = i;
        }
        i++;
    } while (i < 10);
    w->m1D0 = 0.0f;
    w->m1D0 = UiPageScrollBarLayout_289710(w, 0x1F8, 0x116, 10, list->count, 0);
    UiSetWidgetPos_290f60(w->m274, 0x1F8, 0x173, 0x1D);
    e = ((Elem *)UiEntryListFindByTag_28ea40(w->m278, 0x24));
    e->m12 = list->count - 1;
    e->m14 = w->m218;
    e->m16 = w->m21C;
    e->m18 = w->m230;
    e->m1A = w->m234;
    w->m288 = w->m21C;
    w->m28C = w->m234;
    if (w->m200 != 0) {
        w->m200 = 0;
        found = 0;
        for (j = 0; j < list->count; j++) {
            if (((short)RankEntryGetId_3fdaa0(&list->items[j])) == 0) {
                found = j;
                break;
            }
        }
        if (found < 91) {
            e->m16 = 0;
            e->m1A = found;
            w->m288 = 0;
            w->m28C = found;
        } else {
            e->m16 = found - 90;
            e->m1A = 90;
            w->m288 = found - 90;
            w->m28C = 90;
        }
    }
    UiSetWidgetPos_290f60(w->m274, 0x1F8, 0x173, (s32)(29.0f + (f32)e->m1A * w->m1D0));
    UiSetWidgetPos_290f60(w->m274, 0x20E, e->m4, e->m6 + e->m16 * e->mA);
    MenuCatalogPlaceRowCursor_360350(w);
    save = e->m16;
    e->m16 = e->mE;
    MenuCatalogRankRowsFill_35cd70(w);
    e->m16 = save;
}
