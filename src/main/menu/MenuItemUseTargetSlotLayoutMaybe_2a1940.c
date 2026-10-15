#include "types.h"

typedef struct {
    s16 a;
    s16 b;
} Pair;



typedef struct {
    s16 a;
    s16 b;
    s16 c;
    u8 pad[26];
} Ent;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} Glob;

extern Ent *UiGetWidgetSprite_28fe10(s8 *, s32, s32);
extern Glob *GetGameData_1fede0(void);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern Pair D_00450F80[30];
typedef struct { Pair p[30]; } T30;

s32 MenuItemUseTargetSlotLayoutMaybe_2a1940(s8 **arg0, s32 arg1)
{
    Pair t[30];
    Ent *e;
    Ent *e2;
    Glob *g;
    Pair *row;
    s32 n;
    s32 m;
    s32 k;
    u32 i;

    e = UiGetWidgetSprite_28fe10(*arg0, arg1, 0);
    if (e == NULL) {
        return 0;
    }
    g = GetGameData_1fede0();
    m = PartyCountMembers_3c2010(g->unk18, 1, 1);
    n = PartyCountReserve_3c1c20(g->unk18, 1, 1);
    *(T30 *)t = *(T30 *)D_00450F80;
    k = n - 5;
    if (k <= 0) {
        k = 0;
    }
    row = &t[k * 10];
    for (i = 0; (s32)i < (s32)m; i++) {
        e[i].a = row[i].a;
        e[i].b = row[i].b;
    }
    e2 = &e[m];
    for (i = 0; (s32)i < n; i++) {
        e2[i].a = row[i + 3].a;
        e2[i].b = row[i + 3].b;
        if (k == 2) {
            e2[i].c = 0x2E;
        } else {
            e2[i].c = 0x36;
        }
    }
    e[m + n].a = -1;
    return 0;
}
