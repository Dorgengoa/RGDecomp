/* rgp:protos */
#define RGP_SELF_MenuPartyReserveSlotLayoutMaybe_29c680 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct Pair { s16 x, y; } Pair;
typedef struct R { s16 x, y, w, h; u8 pad[0x18]; } R;
typedef struct E60 { R r[3]; } E60;
typedef struct E20 { s16 f0; s16 f2; s16 f4; s16 f6; s16 f8; s16 fA; s16 fC; s16 fE; u8 pad[0x10]; } E20;
typedef struct Mgr { u8 pad[0x18]; s32 f18; } Mgr;
typedef struct Info { u8 pad[0x234]; u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; } Info;
typedef struct Obj { u8 pad[0x4C4]; s32 f4C4; } Obj;

typedef struct H21 { s16 a[21]; } H21;
typedef struct P21 { Pair a[21]; } P21;
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
#define E(j) ((Ent *)((s8 *)ents + ((j) << 5)))
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Pair D_00450B90[21];
extern s16 D_00450BF0[21];
extern s16 D_00450C20[21];

s32 MenuPartyReserveSlotLayoutMaybe_29c680(Obj *arg0, s32 arg1) {
    s16 *hd;
    s32 j2;
    s32 i;
    Pair t1[3][7] __attribute__((aligned(16)));
    Pair *ps;
    s32 n;
    s32 i3;
    s16 *s2row;
    s16 *px;
    Pair pr __attribute__((aligned(16)));
    s16 yv;
    E20 *b;
    E20 *a;
    s16 *pw;
    s16 *s3row;
    Pair *pd;
    s32 lvl;
    s32 k;
    E60 *ents;
    E60 *e;
    s32 kb1;
    s32 x;
    s16 t2[3][7] __attribute__((aligned(16)));
    s16 t3[3][7] __attribute__((aligned(16)));
    Mgr *mgr;
    s16 * hs_1;
    R *r1;
    s16 *hs;


    ents = UiGetWidgetSprite_28fe10(arg0->f4C4, arg1, 0);
    if (ents == 0) return 0;
    mgr = ((Mgr *)GetGameData_1fede0());
    n = PartyCountReserve_3c1c20(mgr->f18, 1, 1);
    n = (s32)(u32)n;
    lvl = n - 5;
    if (lvl <= 0) lvl = 0;
    *(P21 *)t1 = *(P21 *)D_00450B90;
    for (i = 0; i < n; i++) {
        i3 = i * 3;
        E(i3)->f0 = t1[lvl][i].x;
        E(i3)->f2 = E(i3)->f22 = E(i3)->f42 = t1[lvl][i].y;
        E(i3)->f20 = E(i3)->f0 + E(i3)->f4;
        if (lvl == 2) {
            E(i3)->f24 = 0x22;
        } else {
            E(i3)->f24 = 0x2A;
        }
        E(i3)->f40 = E(i3)->f20 + E(i3)->f24;
    }
    ents[n].r[0].x = -1;
    *(H21 *)t2 = *(H21 *)D_00450BF0;
    *(H21 *)t3 = *(H21 *)D_00450C20;
    a = UiGetWidgetSprite_28fe10(arg0->f4C4, 0x103, 0);
    if (a == 0) return 0;
    b = UiGetWidgetSprite_28fe10(arg0->f4C4, 0x102, 0);
    if (b == 0) return 0;
    for (j2 = 0; j2 < n; j2++) {
        a[j2].f0 = t2[lvl][j2];
        b[j2].f0 = t3[lvl][j2];
        if (((Info *)PartyGetReserveChara_3c1d20(mgr->f18, j2))->b2) {
            b[j2].fC = 0x15;
            b[j2].f4 = 0x15;
            b[j2].fE = 0x18;
            b[j2].f6 = 0x18;
        } else {
            b[j2].fE = 0;
            b[j2].f6 = 0;
            b[j2].fC = 0;
            b[j2].f4 = 0;
        }
    }
    a[n].f0 = -1;
    b[n].f0 = -1;
    return 1;
}
