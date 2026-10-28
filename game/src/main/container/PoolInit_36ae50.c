/* rgp:protos */
#define RGP_SELF_PoolInit_36ae50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct Buf {
    u32 f0;
    u32 f4;
    u32 f8;
    u32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u32 f20;
    u32 f24;
} Buf;

typedef struct Heap {
    u8 pad0[0x2C];
    s32 f2C;
    u8 pad30[4];
    s32 f34;
} Heap;

/*rgp*/
/*rgp*/
extern void *memset(u32, s32, u32);

s32 PoolInit_36ae50(Buf *o, Heap *h, s32 w, s32 hh, s32 align)
{
    s32 avail;
    u32 size;
    u32 blocks;
    u32 n;
    s32 al;
    s32 r;
    s32 d;
    s32 rem;
    s32 q;
    u32 t;
    s32 n0;

    if (h == NULL) {
        return 0;
    }
    if (w <= 0 || align <= 0) {
        return 0;
    }
    avail = (h->f34 - h->f2C) * 16;
    o->f0 = 0;
    o->f4 = 0;
    o->f8 = 0;
    o->fC = 0;
    o->f10 = 0;
    o->f14 = 0;
    o->f18 = 0;
    o->f1C = 0;
    o->f20 = 0;
    o->f24 = 0;
    o->f10 = w;
    o->f18 = align;
    if (o->f10 <= 0) {
        return 1;
    }
    if (o->f18 > 0) {
        rem = o->f10 % o->f18 > 0;
        q = o->f10 / o->f18;
        rem = (s32)((u32)q + rem);
        o->f10 = rem * o->f18;
    }
    if (hh > 0) {
        o->f14 = hh;
    } else {
        o->f14 = avail / o->f10;
    }
    for (;;) {
        size = o->f14 * o->f10;
        o->f4 = size;
        o->fC = size;
        blocks = (size >> 4) + ((size & 0xF) != 0);
        o->f4 = o->f14 * o->f10;
        if ((u32)avail >= o->f4 + blocks * 16) {
            break;
        }
        if (--o->f14 <= 0) {
            return 0;
        }
    }
    o->f0 = MemStackAllocQw_14d950(h, blocks);
    if (o->f0 == 0) {
        return 0;
    }
    o->f8 = o->f0;
    al = o->f18;
    if (al > 0) {
        r = UModDi3_13a430(o->f0, al);
        if (r > 0) {
            d = al - r;
            o->f8 += d;
            o->fC -= d;
            o->f14 = (s32)o->fC / o->f10;
        }
    }
    if (o->f14 > 0) {
        t = o->f14;
        n = (t >> 2) + ((t & 3) != 0);
        o->f24 = n;
        o->f20 = MemStackAllocQw_14d950(h, (n >> 4) + ((n & 0xF) != 0));
        if (o->f20 == 0) {
            return 0;
        }
    }
    if (o->f0 != 0 && (s32)o->f4 > 0) {
        memset(o->f0, 0, o->f4);
    }
    if (o->f20 != 0 && (s32)o->f24 > 0) {
        memset(o->f20, 0, o->f24);
    }
    o->f1C = 0;
    return 1;
}
