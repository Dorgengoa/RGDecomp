#define KO 3
#define KC 1
#define KI 1
#include "types.h"
#ifndef KO
#define KO 3
#endif
#ifndef KE
#define KE 0
#endif
#if KO == 3
#pragma optimization_level 3
#elif KO == 4
#pragma opt_common_subs off
#endif

typedef struct { s16 a; s16 _2; s16 b, c, d, e, f, g; } Rect;
typedef struct {
    Rect r0;
    u8 p10[0x10];
    Rect r20;
    u8 p30[0x16];
    s16 f46;
    u8 p48[0x1E];
    s16 f66;
} Spr;
typedef struct { u8 pad[0x20]; void *p20; } Ent;

#ifndef KC
#define KC 0
#endif
#if KC
#define CQ const
#else
#define CQ
#endif
extern CQ s16 D_00462AC0[3][7];
extern CQ s16 D_00462AF0[3][7];
extern CQ s16 D_00462B20[3][7];
extern CQ s16 D_00462B50[3][7];
extern CQ s16 D_00462B80[3][3];
extern s16 D_0047F7D8;
extern s16 D_0047F7DA;
extern s16 D_0047F7DC;

u8 *GetGameData_1fede0(void);
s32 PartyCountMembers_3c2010(s32, s32, s32);
Ent *UiFindWidget_290460(void *, u16);
void UiSetWidgetPos_290f60(void *, u16, s32, s32);
void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);

#pragma opt_lifetimes off
s32 MenuCharaSelTabsLayoutMaybe_356160(u8 *arg0, s32 arg1, s32 arg2)
{
    void *ptrs[3];
    s16 c[3];
    u8 *g;
    s32 n;
    Ent *e;
    Spr *q;
    CQ s16 *row;
    s32 i;
    s32 k;
    u16 id;

    g = GetGameData_1fede0();
    if (g == 0) return 1;
    n = PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1);
    if (arg2 >= n) arg2 = n - 1;

    e = UiFindWidget_290460(*(void **)(arg0 + 0x5C), 0xBE);
    if (e == 0) return 0;
    q = e->p20;
    if (q == 0) return 0;
    q->r0.g = 0;
    q->r0.f = 0;
    q->r0.c = 0;
    q->r0.b = 0;
    q->r20.a = D_00462AC0[arg2][0];
    q->r20.b = D_00462AC0[arg2][1];
    q->r20.c = D_00462AC0[arg2][2];
    q->r20.d = D_00462AC0[arg2][3];
    q->r20.e = D_00462AC0[arg2][4];
    q->r20.f = D_00462AC0[arg2][5];
    q->r20.g = D_00462AC0[arg2][6];
    q->f46 = 0x66;
    q->f66 = 0x58;

    e = UiFindWidget_290460(*(void **)(arg0 + 0x5C), 0xBF);
    if (e == 0) return 0;
    q = e->p20;
    if (q == 0) return 0;
    q->r0.a = D_00462AF0[arg2][0];
    q->r0.b = D_00462AF0[arg2][1];
    q->r0.c = D_00462AF0[arg2][2];
    q->r0.d = D_00462AF0[arg2][3];
    q->r0.e = D_00462AF0[arg2][4];
    q->r0.f = D_00462AF0[arg2][5];
    q->r0.g = D_00462AF0[arg2][6];
    q->r20.a = D_00462B20[arg2][0];
    q->r20.b = D_00462B20[arg2][1];
    q->r20.c = D_00462B20[arg2][2];
    q->r20.d = D_00462B20[arg2][3];
    q->r20.e = D_00462B20[arg2][4];
    q->r20.f = D_00462B20[arg2][5];
    q->r20.g = D_00462B20[arg2][6];
    q->f46 = 0x58;
    q->f66 = 0x58;

    e = UiFindWidget_290460(*(void **)(arg0 + 0x5C), 0xC0);
    if (e == 0) return 0;
    q = e->p20;
    if (q == 0) return 0;
    q->r0.a = D_00462B50[arg2][0];
    q->r0.b = D_00462B50[arg2][1];
    q->r0.c = D_00462B50[arg2][2];
    q->r0.d = D_00462B50[arg2][3];
    q->r0.e = D_00462B50[arg2][4];
    q->r0.f = D_00462B50[arg2][5];
    q->r0.g = D_00462B50[arg2][6];
    q->r20.g = 0;
    q->r20.f = 0;
    q->r20.c = 0;
    q->r20.b = 0;
    q->f46 = 0x58;
    q->f66 = 0x66;
    UiSetWidgetsVisibleById_291110(*(void **)(arg0 + 0x5C), 0xC0, 0, 1);

    for (i = 0; i < 3; i++) {
        e = UiFindWidget_290460(*(void **)(arg0 + 0x5C), i + 0xBE);
        if (e == 0) return 0;
        ptrs[i] = e->p20;
    }
    c[0] = D_0047F7D8;
    c[1] = D_0047F7DA;
    c[2] = D_0047F7DC;
    i = 0;
    row = D_00462B80[arg2];
    for (; i < 3; i++) {
        e = UiFindWidget_290460(*(void **)(arg0 + 0x5C), i + 0xBE);
        if (e == 0) return 0;
#if KI
        k = row[i];
        e->p20 = ptrs[k];
        id = k + 0xBE;
#else
        k = row[i];
        id = k + 0xBE;
        e->p20 = ptrs[k];
#endif
        if (UiFindWidget_290460(*(void **)(arg0 + 0x5C), id) == 0) return 0;
        UiSetWidgetPos_290f60(*(void **)(arg0 + 0x5C), id, c[i], 0x10);
    }
    return 0;
}
