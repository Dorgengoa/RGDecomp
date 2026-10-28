/* rgp:protos */
#define RGP_SELF_MenuPartySwapAnimStart_29b5a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Pt { s16 x; s16 y; } Pt;
typedef struct PtTab { Pt p[8]; } PtTab;
typedef struct Ent { s16 id; s16 a; s16 b; } Ent;
typedef struct Spr { Pt pos; u8 pad4[4]; s16 x8; s16 xA; } Spr;
typedef struct Node { u8 pad0[0x20]; Spr *spr; } Node;
typedef struct Grp { u8 pad0[0x18]; s32 x18; } Grp;
typedef struct Info { u8 pad0[0x2C]; s16 x2C; } Info;
typedef struct Self { u8 pad0[0x4C4]; s32 x4C4; } Self;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern PtTab D_00450CA0;
extern Ent D_00450820[10];
extern f32 D_0047D6C4;

s32 MenuPartySwapAnimStart_29b5a0(Self *self, s32 a, s32 b) {
    Pt tbl[8] __attribute__((aligned(16)));
    s32 x0, y0, x1, y1;
    Grp *g;
    Node *n;
    Spr *s1;
    Spr *s0;
    s32 e;
    s32 id0;
    s32 id1;
    s32 i;
    Ent *ep;
    s32 dx;
    s32 dy;

    *(PtTab *)tbl = D_00450CA0;
    g = ((Grp *)GetGameData_1fede0());
    if (g == 0) return 3;
    n = ((Node *)UiFindWidget_290460(self->x4C4, 0x11F));
    if (n == 0) return 1;
    s1 = n->spr;
    if (s1 == 0) return 2;
    s1->pos.x = tbl[a].x;
    s1->pos.y = tbl[a].y;
    n = ((Node *)UiFindWidget_290460(self->x4C4, 0x120));
    if (n == 0) return 1;
    s0 = n->spr;
    if (s0 == 0) return 2;
    s0->pos.x = tbl[b].x;
    s0->pos.y = tbl[b].y;
    e = PartyGetSlotChara_3c2fb0(g->x18, a);
    if (e == 0) return 4;
    id0 = ((Info *)CharaGetIconRecMaybe_3ae3e0(e))->x2C;
    e = PartyGetSlotChara_3c2fb0(g->x18, b);
    if (e == 0) return 4;
    id1 = ((Info *)CharaGetIconRecMaybe_3ae3e0(e))->x2C;
    s1->xA = 0;
    s1->x8 = 0;
    s0->xA = 0;
    s0->x8 = 0;
    for (i = 0; i < 10; i++) {
        if (id0 == D_00450820[i].id) {
            s1->x8 = D_00450820[i].a;
            s1->xA = D_00450820[i].b;
        }
        if (id1 == D_00450820[i].id) {
            ep = (Ent *)((u8 *)D_00450820 + (i * 3 << 1));
            s0->x8 = ep->a;
            s0->xA = ep->b;
        }
    }
    UiGetWidgetPos_2910a0(self->x4C4, 0xB6, &x0, &y0);
    x0 += s1->pos.x;
    y0 += s1->pos.y;
    UiGetWidgetPos_2910a0(self->x4C4, 0xB6, &x1, &y1);
    x1 += s0->pos.x;
    y1 += s0->pos.y;
    dx = x1 - x0;
    dy = y1 - y0;
    UiSetWidgetsVisibleById_291110(self->x4C4, 0x11F, 1, 1);
    UiSetWidgetsVisibleById_291110(self->x4C4, 0x120, 1, 1);
    UiMoveWidget_290e00(self->x4C4, 0x11F, dx, dy, 3, D_0047D6C4, 0.0f);
    UiMoveWidget_290e00(self->x4C4, 0x120, -dx, -dy, 3, D_0047D6C4, 0.0f);
    MenuSetMoveTarget_29f9d0(self, dx, dy);
    return 0;
}
