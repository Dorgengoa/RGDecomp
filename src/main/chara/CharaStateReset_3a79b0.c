#include "types.h"

typedef struct A3a79b0 {
    s16 pad0;
    s16 a;      /* +2 */
    s32 b;      /* +4 */
} A3a79b0;

typedef struct B3a79b0 {
    s32 v;      /* +0 */
    s16 w;      /* +4 */
    s16 pad6;
} B3a79b0;

typedef struct C3a79b0 {
    s16 a;
    s16 b;
} C3a79b0;

typedef struct T3a79b0 {
    s64 f0;             /* 0x00 */
    s16 f8;             /* 0x08 */
    s16 fA;
    s16 fC;
    s16 padE;
    s32 f10;            /* 0x10 */
    s32 f14;
    s32 f18;
    u8 pad1C[8];        /* 0x1C */
    u8 g0 : 1;          /* 0x24 */
    u8 g1 : 1;
    u8 g2 : 1;
    u8 g3 : 1;
    u8 pad25[3];
    s32 f28;            /* 0x28 */
    s16 f2C;
    s16 f2E;
    s32 f30;            /* 0x30 */
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
    s16 f44;            /* 0x44 */
    s16 pad46;
    A3a79b0 a48[28];    /* 0x48 */
    s16 f128;           /* 0x128 */
    s16 f12A;
    B3a79b0 b12C[5];    /* 0x12C */
    s16 f154;           /* 0x154 */
    C3a79b0 c156[3];    /* 0x156 */
    s16 f162;           /* 0x162 */
    s16 f164;
    s16 f166;
    u8 f168[4];         /* 0x168 */
    s32 f16C;           /* 0x16C */
    s16 f170;           /* 0x170 */
    u8 h0 : 1;          /* 0x172 */
    u8 h1 : 1;
    u8 h2 : 1;
    u8 h3 : 1;
    u8 h4 : 1;
    u8 pad173[0x1C8 - 0x173];
    s32 f1C8;           /* 0x1C8 */
    s16 f1CC;           /* 0x1CC */
} T3a79b0;

extern const struct Big465C80 { s32 v; s32 pad[3]; } D_00465C80;
extern void BattleRecordReset_3a7fd0(void *);

void CharaStateReset_3a79b0(T3a79b0 *p, s32 a, s32 b, s32 c, s32 d)
{
    s32 i;
    s32 j;
    s32 k;
    s32 g;

    if (a != 0) {
        p->f0 = 0;
    }
    if (b != 0) {
        p->f8 = -1;
        p->fA = -1;
        p->fC = -1;
        p->f10 = 0;
        p->f14 = 0;
        p->f18 = 0;
        p->g0 = 0;
        p->g1 = 0;
        p->g2 = 0;
        p->g3 = 0;
    }
    if (c != 0) {
        p->f28 = -1;
        p->f2C = 0;
        p->f2E = 0;
        p->f30 = 0;
        p->f16C = 0;
        p->f170 = 2;
        p->h0 = 0;
        p->h1 = 0;
        p->h2 = 0;
        p->h3 = 0;
        p->h4 = 0;
        p->f40 = 0;
        p->f34 = 0;
        p->f38 = 0;
        p->f3C = 0;
        p->f44 = 0;
        for (i = 0; i < 0x1C; i++) {
            p->a48[i].a = -1;
            p->a48[i].b = 0;
        }
        p->f128 = 0;
        p->f12A = 0;
        for (j = 0; j < 5; j++) {
            p->b12C[j].v = 0;
            p->b12C[j].w = 0;
        }
        p->f154 = 0;
        for (k = 0; k < 3; k++) {
            p->c156[k].a = -1;
            p->c156[k].b = 0;
        }
        p->f1CC = 0;
        p->f162 = (s16)D_00465C80.v;
        p->f164 = 1;
        p->f166 = 1;
        BattleRecordReset_3a7fd0(&p->f168);
    }
    if (d != 0) {
        BattleRecordReset_3a7fd0(&p->f168);
        p->f170 = 0;
        p->f1C8 = 0;
    }
}
