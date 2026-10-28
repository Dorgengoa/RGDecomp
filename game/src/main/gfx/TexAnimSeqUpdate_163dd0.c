/* rgp:protos */
#define RGP_SELF_TexAnimSeqUpdate_163dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s8 type;
    s8 pad1;
    s8 idx;
    u8 pad3[0x19];
    s16 lim1C;
    s16 lim1E;
    f32 t20;
    f32 t24;
    u8 pad28[4];
    s16 dur;
    s16 mode;
} Anim;

typedef struct Node {
    struct Node *next;
    u8 pad4[0xC];
    Anim a;
} Node;

typedef struct {
    s32 n;
    s32 active[48];
    Node *head[48];
    Node *cur[48];
    s32 pad244[48];
    f32 time[48];
} Seq;

typedef struct {
    s32 pad0;
    s32 active;
    u8 pad8[0xBC];
    Node *head;
    u8 padC8[0xBC];
    Node *cur;
    u8 pad188[0x17C];
    f32 time;
} Col;

extern s32 D_00481128;

void TexAnimSeqUpdate_163dd0(Seq *s, f32 dt) {
    s32 i;
    s32 k;
    Node *nd;
    Node *nx;
    Anim *a;
    Node **pc;
    f32 *pt;
    s16 d;
    Col *c;
    s32 ty;
    s32 one;
    s32 two;

    for (i = 0; i < s->n; i++) {
        if (s->active[i] == 0) {
            continue;
        }
        nd = s->cur[i];
        if (nd == 0) {
            continue;
        }
        a = &nd->a;
        if (a == 0) {
            continue;
        }
        k = a->idx;
        if (k < 0) {
            continue;
        }
        if (k >= 0 && k < s->n) {
            s->active[k] = 1;
        }
    }
    one = 1;
    two = 2;
    for (i = 0; i < s->n; i++) {
        c = (Col *)((u8 *)s + i * sizeof(s32));
        if (c->active == 0) {
            continue;
        }
        pc = &c->cur;
        nd = *pc;
        if (nd == 0) {
            continue;
        }
        a = &nd->a;
        if (a == 0) {
            continue;
        }
        pt = &c->time;
        if (*pt < 0.0f) {
            *pt = 0.0f;
        } else if (D_00481128 == 0) {
            *pt += dt;
        }
        for (;;) {
            ty = a->type;
            if ((ty == one || ty == two) && D_00481128 == 0) {
                if (a->lim1C != 0) {
                    if (a->lim1C > 0) {
                        a->t20 += dt;
                        if (!(a->t20 < a->lim1C)) {
                            a->t20 = 0.0f;
                        }
                    } else {
                        a->t20 -= dt;
                        if (a->t20 <= 0.0f) {
                            a->t20 = -a->lim1C;
                        }
                    }
                }
                if (a->lim1E != 0) {
                    if (a->lim1E > 0) {
                        a->t24 += dt;
                        if (!(a->t24 < a->lim1E)) {
                            a->t24 = 0.0f;
                        }
                    } else {
                        a->t24 -= dt;
                        if (a->t24 <= 0.0f) {
                            a->t24 = -a->lim1E;
                        }
                    }
                }
            }
            d = a->dur;
            if (d != 0) {
                break;
            }
            nx = nd->next;
            if (nx == 0) {
                break;
            }
            nd = nx;
            a = &nx->a;
        }
        if (d < 0) {
            *pt = 0.0f;
            continue;
        }
        if (a->mode != 0) {
            if (d <= *pt) {
                *pt = 0.0f;
                s->cur[i] = nd->next;
                if (s->cur[i] == 0) {
                    *pc = s->head[i];
                }
            }
        } else {
            if (d < *pt) {
                *pt = 0.0f;
                s->cur[i] = nd->next;
                if (s->cur[i] == 0) {
                    *pc = s->head[i];
                }
            }
        }
    }
}
