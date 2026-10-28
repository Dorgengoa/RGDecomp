/* rgp:protos */
#define RGP_SELF_MenuCatalogRankRowsFill_35cd70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Item { u8 pad0[4]; s32 m4; u8 pad8[4]; s16 mC; u8 padE[2]; s16 m10; u8 pad12[2]; } Item;
typedef struct List { u8 pad0[0x14]; Item *items; } List;
typedef struct L94 { u8 pad0[0x14]; List *list; } L94;
typedef struct L8 { u8 pad0[0x94]; L94 *m94; } L8;
typedef struct Wld { u8 pad0[8]; L8 *m8; u8 padC[4]; s32 m10; } Wld;
typedef struct Win { u8 pad0[0x16]; s16 m16; u8 pad18[2]; s16 m1A; } Win;
typedef struct Self { u8 pad0[0x274]; s32 m274; s32 m278; } Self;

extern void Sprintf_1343b8(char *, const char *, s32);
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
extern char D_00462C58[];
extern s16 D_0047F838;
extern char D_004E8E20[];

void MenuCatalogRankRowsFill_35cd70(Self *self)
{
    s32 a;
    s32 b;
    Wld *w;
    List *list;
    Win *t;
    s32 base;
    s32 i;
    Item *it;
    char *buf;
    s32 n;
    s32 lim;

    w = ((Wld *)GetGameData_1fede0());
    list = w->m8->m94->list;
    t = ((Win *)UiEntryListFindByTag_28ea40(self->m278, 0x24));
    base = t->m16 + t->m1A;
    if (t->m16 == 9) {
        base -= 9;
    }
    D_0047F838 = -1;
    i = 0;
    do {
        UiSetTextColor_290a40(self->m274, 0x1F3, 0xFF303030, i);
        it = list->items + (base + i);
        buf = D_004E8E20 + i * 4;
        Sprintf_1343b8(buf, D_00462C58, it->mC);
        UiSetTextString_28f510(self->m274, 0x208, buf, i);
        UiSetTextString_28f510(self->m274, 0x1F3, ((char *)RankEntryGetName_3fda80(it)), i);
        UiSetWidgetSubItemValue_291250(self->m274, 0x208, i, (long long)((s32)(u32)it->m4));
        MenuCatalogRankTrendIconUvMaybe_35cc90(self, it->m10, &a, &b);
        UiSetSpriteUv_28f970(self->m274, 0x203, a, b, i);
        n = it->mC;
        if ((n > 0 && n <= 10) || n == 20 || n == 30 || n == 40 || n == 50) {
            UiSetSpriteSizeUvSize_28f670(self->m274, 0x204, 0x14, 0x16, 0x14, 0x16, i);
            lim = ((short)StateVarGet_3ccac0(w->m10, 0xF));
            if (lim <= 0 || lim > 0x64) {
                lim = 0x64;
            }
            if (it->mC < lim) {
                UiSetSpriteU_28f930(self->m274, 0x204, 0x24, i);
            } else {
                UiSetSpriteU_28f930(self->m274, 0x204, 0x38, i);
            }
        } else {
            UiSetSpriteSizeUvSize_28f670(self->m274, 0x204, 0, 0, 0, 0, i);
        }
        if (((short)RankEntryGetId_3fdaa0(it)) == 0) {
            D_0047F838 = i;
        }
        i++;
    } while (i < 10);
}
