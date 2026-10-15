#include "types.h"

typedef struct Ent {
    s16 a;
    s16 b;
    s16 c;
} Ent;

typedef struct Tbl {
    Ent e[11];
} Tbl;

typedef struct Box {
    u8 pad0[4];
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE;
} Box;

typedef struct Item {
    u8 pad0[0x20];
    Box *x20;
} Item;

typedef struct G {
    u8 pad0[0x18];
    s32 x18;
} G;

typedef struct Obj {
    u8 pad0[0x5C];
    s32 x5C;
} Obj;

typedef struct Info {
    u8 pad0[0x2C];
    s16 x2C;
} Info;

extern G *GetGameData_1fede0(void);
extern Item *UiFindWidget_290460(s32 arg0, u16 arg1);
extern Info *CharaGetIconRecMaybe_3ae3e0(s32 arg0);
extern s32 PartyCountMembers_3c2010(s32 arg0, s32 arg1, s32 arg2);
extern s32 PartyGetMemberChara_3c2420(s32 arg0, s32 arg1);
extern Tbl D_00453C80;

static inline s32 Cnt(s32 a) { return PartyCountMembers_3c2010(a, 1, 1); }
s32 MenuTacticsMemberFaceSprites_356ad0(Obj *arg0, u16 arg1)
{
    Tbl t;
    s32 base;
    s16 *src;
    s16 *dst;
    s32 c;
    G *g;
    s32 n;
    s32 i;
    s32 j;
    Item *it;
    Box *b;
    s32 r;
    s16 k;
    s32 m;

    src = (s16 *)&D_00453C80;
    dst = (s16 *)&t;
    c = 33;
    do {
        c--;
        *dst = *src;
        src++;
        dst++;
    } while (c > 0);
    g = GetGameData_1fede0();
    n = Cnt(g->x18);
    for (i = 0; i < 3; i++) {
        it = UiFindWidget_290460(arg0->x5C, arg1 + i);
        if (it != 0) {
            b = it->x20;
            if (b != 0) {
                b->xC = 0;
                b->x4 = 0;
                b->xE = 0;
                b->x6 = 0;
            }
        }
    }
    for (j = 0; j < n; j++) {
        it = UiFindWidget_290460(arg0->x5C, arg1 + j);
        if (it == 0) {
            continue;
        }
        b = it->x20;
        if (b == 0) {
            continue;
        }
        r = PartyGetMemberChara_3c2420(g->x18, j);
        if (r == 0) {
            continue;
        }
        k = CharaGetIconRecMaybe_3ae3e0(r)->x2C;
        b->x8 = 0;
        b->xA = 0;
        for (m = 0; m < 10; m++) {
            if (k == t.e[m].a) {
                b->x8 = t.e[m].b;
                b->xA = t.e[m].c;
                b->xC = 0x36;
                b->x4 = 0x36;
                b->xE = 0x40;
                b->x6 = 0x40;
            }
        }
    }
    return 1;
}
