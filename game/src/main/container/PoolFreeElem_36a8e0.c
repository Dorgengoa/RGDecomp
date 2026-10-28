/* rgp:protos */
#define RGP_SELF_Clear 1
#define RGP_SELF_Get 1
#define RGP_SELF_IsSet 1
#define RGP_SELF_PoolFreeElem_36a8e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x8];
    s32 base;
    u8 padC[0x4];
    s32 size;
    s32 count;
    u8 pad18[0x4];
    s32 used;
    s32 bits;
} Pool;

static inline s32 IsSet(Pool *p, s32 i)
{
    s32 w;
    s32 b;
    s32 t;
    s32 ok;
    if ((u32)i >= (u32)p->count) {
        ok = 0;
    } else {
        w = i / 32;
        b = i % 32;
        t = *(s32 *)(p->bits + w * 4);
        ok = ((t & (1 << b)) != 0);
    }
    return ok;
}

static inline s32 Get(Pool *p, s32 i)
{
    s32 w;
    s32 b;
    s32 t;
    s32 ok;

    if ((u32)i >= (u32)p->count) {
        return 0;
    }
    if ((u32)i >= (u32)p->count) {
        ok = 0;
    } else {
        w = i / 32;
        b = i % 32;
        t = *(s32 *)(p->bits + w * 4);
        ok = ((t & (1 << b)) != 0);
    }
    if (ok != 0) {
        return p->base + i * p->size;
    }
    return 0;
}

static inline void Clear(Pool *p, s32 i)
{
    s32 w;
    s32 *q;
    s32 v;
    if ((u32)i < (u32)p->count) {
        w = i / 32;
        q = (s32 *)(*(s32 *)((u8 *)p + 0x20) + w * 4);
        v = *(volatile s32 *)q;
        *q = v & ~(1 << (i % 32));
    }
}

s32 PoolFreeElem_36a8e0(Pool *p, s32 i)
{
    if ((u32)i >= (u32)p->count) {
        return 0;
    }
    if (p->base == 0 || p->count <= 0 || p->bits == 0) {
        return 0;
    }
    if (p->used <= 0) {
        return 0;
    }
    if (IsSet(p, i) == 0) {
        return 0;
    }
    if (Get(p, i) == 0) {
        return 0;
    }
    Clear(p, i);
    p->used--;
    return 1;
}
