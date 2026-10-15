#include "types.h"

typedef struct Sub00426b50 {
    u8 pad[0x44];
} Sub00426b50;

typedef struct Elem00426b50 {
    u8 pad0[0x7C];
    s16 n7C;
    u8 pad7e[0x8C - 0x7E];
    Sub00426b50 *subs;
    u8 pad90[4];
    s32 h94;
} Elem00426b50;

typedef struct List00426b50 {
    u8 pad0[0xC];
    Elem00426b50 *elems;
} List00426b50;

typedef struct Obj00426b50 {
    s32 pad0;
    List00426b50 *list;
} Obj00426b50;

extern s32 GroupEntryMatchesKey_3f40e0(s32, s32);
extern s32 D_004644A8[];

static inline Elem00426b50 *getElem(List00426b50 *l, s32 i, s32 n)
{
    return (i >= 0 && i < n) ? &l->elems[i] : 0;
}

static inline Sub00426b50 *getSub(Elem00426b50 *e, s32 j)
{
    return (j >= 0 && j < e->n7C) ? &e->subs[j] : 0;
}

Sub00426b50 *TreasureBoxViewGetAt_426b50(Obj00426b50 *o, s32 idx)
{
    s32 acc;
    s32 c;
    s32 i;
    s32 n;
    s32 j;
    Elem00426b50 *e;

    if (o->list == 0) {
        return 0;
    }
    acc = 0;
    n = D_004644A8[0];
    for (i = 0; i < n; i++) {
        j = idx - acc;
        e = getElem(o->list, i, n);
        if (e != 0 && e->h94 != 0 && GroupEntryMatchesKey_3f40e0(e->h94, -1) != 0) {
            c = e->n7C;
            if (j >= 0 && j < c) {
                return getSub(e, j);
            }
            acc += c;
        }
    }
    return 0;
}
