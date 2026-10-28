/* rgp:protos */
#define RGP_SELF_GetN1 1
#define RGP_SELF_MenuPartyRowLayoutMaybe_340f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_lifetimes off

typedef struct Ent {
    s16 m0;
    s16 pad2[3];
    struct AB { s16 a; s16 b; } ab;
    u8 padC[0x14];
} Ent;

typedef struct Win {
    u8 pad0[0x20];
    Ent *m20;
} Win;

typedef struct Party {
    u8 pad0[0x18E];
    s16 m18E;
} Party;

typedef struct Ctx {
    u8 pad0[0x18];
    Party *m18;
} Ctx;

typedef struct Obj {
    u8 pad0[0x5C];
    s32 m5C;
} Obj;

typedef struct Chr {
    u8 pad0[0x2C];
    s16 m2C;
} Chr;

typedef struct Map {
    s16 key;
    struct AB ab;
} Map;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Map D_00462730[10];

static inline s32 GetN1(Party *p) { return PartyCountMembers_3c2010(p, 1, 1); }
s32 MenuPartyRowLayoutMaybe_340f00(Obj *arg0, s32 arg1)
{
    Ctx *c;
    s32 n1;
    s32 n2;
    Win *w;
    Ent *e;
    s32 i;
    s32 j;
    s32 id;
    s16 key;
    Map *m;
    s16 a;
    s16 b;

    c = ((Ctx *)GetGameData_1fede0());
    if (c == NULL) {
        return 0;
    }
    n1 = GetN1(c->m18);
    n2 = PartyCountReserve_3c1c20(c->m18, 1, 1);
    w = ((Win *)UiFindWidget_290460(arg0->m5C, 0x19D));
    if (w == NULL) {
        return 0;
    }
    e = w->m20;
    if (e == NULL) {
        return 0;
    }
    for (i = 0; i < n1; i++) {
        e->m0 = i * 50 + 0x18;
        id = ((short)PartyGetMemberId_3c2490(c->m18, i));
        if (id == c->m18->m18E) {
            e->ab.b = 0;
        } else {
            e->ab.b = 0x10;
        }
        e++;
    }
    e->m0 = -1;
    w = ((Win *)UiFindWidget_290460(arg0->m5C, arg1));
    if (w == NULL) {
        return 0;
    }
    e = w->m20;
    if (e == NULL) {
        return 0;
    }
    n1 += n2;
    for (i = 0; i < n1; i++) {
        id = PartyGetSlotChara_3c2fb0(c->m18, i);
        if (id == 0) {
            return 0;
        }
        key = ((Chr *)CharaGetIconRecMaybe_3ae3e0(id))->m2C;
        e->m0 = i * 50;
        e->ab.a = 0;
        e->ab.b = 0;
        for (j = 0; j < 10; j++) {
            m = &D_00462730[j];
            if (key == m->key) {
                e->ab = m->ab;
            }
        }
        e++;
    }
    e->m0 = -1;
    return 1;
}
