/* rgp:protos */
#define RGP_SELF_BattleEncounterStart_3a41f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Pair {
    s16 a;
    s16 b;
    s32 pad;
} Pair;

typedef struct Sub {
    u8 pad0[8];
    s16 m;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 padB[0x65];
} Sub;

typedef struct Param {
    s64 a;
    s16 c[3];
    s16 padE;
    s32 d;
    s32 e;
    void *owner;
    u8 pad1C[8];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 pad25[7];
    s16 g;
    s16 h;
    f32 i;
    u8 pad34[0x10];
    s16 count;
    s16 pad46;
    Pair arr[35];
    s16 pad160;
    s16 j;
    s16 k;
    s16 l;
    Sub sub;
} Param;

typedef struct Actor {
    s16 id;
    u8 pad2[0xA];
    u8 list[0xC];
    s16 x18;
    s16 x1A;
    s16 x1C;
    u8 pad1E[0x60];
    s8 b0 : 1;
    s8 b1 : 1;
    s8 b2 : 1;
} Actor;

typedef struct Node {
    s16 *p;
    s16 v;
} Node;

typedef struct Iter {
    s32 a;
    s32 b;
} Iter;

typedef struct World {
    u8 pad0[0x24C];
    u8 flags;
} World;

typedef struct Game {
    u8 pad0[0x10];
    s32 x10;
    u8 pad14[0xC];
    World *world;
} Game;

extern Game *D_004837C0;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 BattleEncounterStart_3a41f0(s32 arg0, Actor *actor, s32 arg2) {
    Iter it __attribute__((aligned(16)));
    Param p __attribute__((aligned(16)));
    Node *n;
    s32 z;
    u8 *l;

    if (actor == 0) {
        return 0;
    }
    if (D_004837C0 == 0) {
        return 0;
    }
    if (D_004837C0->world->flags & 1) {
        return 0;
    }
    p.a = 0;
    BattleRecordReset_3a7fd0(&p.sub);
    CharaStateReset_3a79b0(&p.a, 1, 1, 1, 1);
    l = (u8 *)actor;
    if (actor != 0) {
        l = actor->list;
    }
    IterInit_370170(&it, l, 0, 0);
    p.count = 0;
    while ((n = ((Node *)IterNext_370040(&it))) != 0) {
        if (n->p != 0) {
            Pair *q = &p.arr[p.count];
            q->a = n->v;
            q->b = *n->p;
            p.count++;
        }
    }
    z = 0;
    p.d = 0;
    p.c[0] = -1;
    p.c[1] = -1;
    p.c[2] = -1;
    p.e = 0;
    p.owner = actor;
    p.j = actor->x18;
    p.k = actor->x1A;
    p.l = actor->x1C;
    p.f0 = actor->b1 != 0;
    p.f1 = !(actor->b2 != 0);
    p.sub.m = 2;
    p.g = 0;
    p.h = 0;
    p.sub.b2 = z;
    p.i = 0.0f;
    p.sub.b3 = z;
    p.sub.b4 = z;
    if ((StateFlagTest_3ccd70(D_004837C0->x10, 0x3EC) != 0 || actor->id == 0xBBE) && !actor->b0) {
        StateFlagSet_3ccb70(D_004837C0->x10, 0x3EC, 0, 1);
        p.g = 4;
        p.i = 1800.0f;
    }
    return BattleSetupEncounter_3a3970(arg0, &p, arg2);
}
