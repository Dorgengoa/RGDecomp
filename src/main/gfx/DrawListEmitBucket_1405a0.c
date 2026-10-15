#include "types.h"

typedef unsigned __int128 u128;

typedef struct Ent {
    u8 pad0[0xC];
    s32 n;          /* 0x0C */
    s32 *src;       /* 0x10 */
    s32 a14;        /* 0x14 */
    s32 a18;        /* 0x18 */
    s32 k;          /* 0x1C */
    s32 a20;        /* 0x20 */
} Ent;

typedef struct Pk {
    u8 pad0[0x28];
    u32 *base;      /* 0x28 */
    s32 n;          /* 0x2C */
} Pk;

typedef struct Ctx {
    s32 cur0;           /* 0x00 */
    u8 *cur;            /* 0x04 */
    u8 *arr[1];         /* 0x08 */
    u8 pad[0x3BBC - 0xC];
    s32 cnt;            /* 0x3BBC */
    Ent ***tbl;         /* 0x3BC0 */
    u8 pad3BC4[4];
    s32 *ntbl;          /* 0x3BC8 */
} Ctx;

extern void DrawCtxAddChangedCallTags_13fd70(Ctx *, s32, s32);
extern void MemStackAllocQw_14d950(Pk *, s32);
extern u128 D_0047DE40 __attribute__((section(".sdata")));

#define ADDR(x) ((u32)(x) & 0x0FFFFFFF)
static inline void EMITf(Ctx *o, u32 v) { *(u128 *)o->cur = D_0047DE40; ((u32 *)o->cur)[1] = ADDR(v); o->cur += 0x10; }
#define EMIT(o, v) EMITf(o, (u32)(v))

s32 DrawListEmitBucket_1405a0(Ctx *o, s32 idx)
{
    u8 *t;
    s32 last;
    u32 *hdr;
    u32 ha;
    s32 i;
    Pk *pk;
    s32 cnt;
    Ent **pp;
    Ent *prev;
    Ent *e;
    s32 n;
    s32 *src;
    s32 *psrc;
    s32 j;

    if (idx < 0 || idx >= o->cnt) {
        return 0;
    }
    if (o->tbl[(u32)idx] == 0) {
        return 1;
    }
    t = o->arr[o->cur0];
    if (t != 0) {
        pk = (Pk *)(t + 8);
    } else {
        pk = 0;
    }
    ha = (u32)pk->n * 16;
    hdr = (u32 *)((u32)pk->base + ha);
    last = 0;
    hdr[0] = 0x60000000;
    ha = ADDR(hdr);
    hdr[1] = 0;
    hdr[2] = 0x14000064;
    prev = 0;
    i = 0;
    hdr[3] = 0;
    cnt = o->ntbl[idx];
    pp = &o->tbl[idx][cnt - 1];
    while (i < cnt) {
        e = *pp;
        src = e->src;
        n = e->n;
        if (prev == 0 || n != prev->n) {
            for (j = 0; j < n; j++) {
                EMIT(o, *src);
                src++;
            }
        } else {
            psrc = prev->src;
            if (psrc != src) {
                for (j = 0; j < n; j++, src++, psrc++) {
                    if (*src != *psrc) {
                        EMIT(o, *src);
                    }
                }
            }
        }
        DrawCtxAddChangedCallTags_13fd70(o, e->a18, e->a14);
        if (last != (*pp)->k) {
            last = (*pp)->k;
            EMIT(o, last);
        }
        i++;
        *(u128 *)o->cur = D_0047DE40;
        ((u32 *)o->cur)[1] = ha;
        o->cur += 0x10;
        EMIT(o, (*pp)->a20);
        prev = *pp;
        pp--;
    }
    MemStackAllocQw_14d950(pk, 1);
    return 1;
}
