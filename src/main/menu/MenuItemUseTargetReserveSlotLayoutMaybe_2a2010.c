#include "types.h"
#pragma optimization_level 3

typedef struct { s16 x, y; } Pt;
typedef struct Ent {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 pad6[13];
    s16 f20;
    s16 f22;
    s16 f24;
    s16 pad26[13];
    s16 f40;
    s16 f42;
    s8 pad44[0x1C];
} Ent;

typedef struct { Pt a[21]; } T1;
typedef struct { s16 a[21]; } T2;
typedef struct { s16 v; s16 pad[15]; } Ent2;
typedef struct { s8 pad[0x20]; Ent2 *list; } Res;

extern Ent *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern s8 *GetGameData_1fede0(void);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern Res *UiFindWidget_290460(s32, s32);
extern Pt D_00450E60[21];
extern s16 D_00450EC0[21];

#define E(j) ((Ent *)((s8 *)base + ((j) << 5)))
#define F(j) ((Ent *)((s8 *)base + (j) * 32))
s32 MenuItemUseTargetReserveSlotLayoutMaybe_2a2010(s32 *arg0, s32 arg1) {
    Pt t1[3][7];
    s16 t2[3][7];
    Ent *base;
    s32 n;
    s32 row;
    s32 i;
    s32 j;
    Res *res;
    Ent2 *list;

    base = UiGetWidgetSprite_28fe10(*arg0, arg1, 0);
    if (base == 0) {
        return 0;
    }
    { s32 t = PartyCountReserve_3c1c20(*(s32 *)(GetGameData_1fede0() + 0x18), 1, 1); n = t; }
    row = n - 5;
    if (row <= 0) {
        row = 0;
    }
    *(T1 *)t1 = *(T1 *)D_00450E60;
    for (i = 0; i < n; i++) {
        j = i * 3;
        E(j)->f0 = t1[row][i].x;
        E(j)->f2 = E(j)->f22 = E(j)->f42 = t1[row][i].y;
        E(j)->f20 = E(j)->f0 + E(j)->f4;
        if (row == 2) {
            E(j)->f24 = 0x22;
        } else {
            E(j)->f24 = 0x2A;
        }
        E(j)->f40 = E(j)->f20 + E(j)->f24;
    }
    base[n].f0 = -1;
    *(T2 *)t2 = *(T2 *)D_00450EC0;
    res = UiFindWidget_290460(*arg0, 0x103);
    if (res == 0) {
        return 1;
    }
    list = res->list;
    if (list == 0) {
        return 2;
    }
    for (i = 0; i < n; i++) {
        list[i].v = t2[row][i];
    }
    list[n].v = -1;
    return 0;
}
