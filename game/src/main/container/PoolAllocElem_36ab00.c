/* rgp:protos */
#define RGP_SELF_PoolAllocElem_36ab00 1
#define RGP_SELF_getElem 1
#define RGP_SELF_setBit 1
#define RGP_SELF_testBit 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[8];
    u8 *unk8;
    u8 padC[4];
    u32 unk10;
    s32 unk14;
    u8 pad18[4];
    s32 unk1C;
    u32 *unk20;
} Pool;

/*rgp*/
extern void memset(void *dst, s32 val, u32 n);

static inline void setBit(Pool *p, s32 i)
{
    if ((u32)i < (u32)p->unk14) {
        s32 w = i / 32;
        s32 *q = (s32 *)(*(s32 *)((u8 *)p + 0x20) + w * 4);
        s32 v = *(volatile s32 *)q;
        *q = v | (1 << (i % 32));
    }
}

static inline s32 testBit(Pool *p, s32 i)
{
    if ((u32)i < (u32)p->unk14) {
        return (p->unk20[i / 32] & (1 << (i % 32))) != 0;
    }
    return 0;
}

static inline u8 *getElem(Pool *p, s32 i)
{
    s32 w;
    s32 b;
    s32 t;
    s32 ok;

    if ((u32)i >= (u32)p->unk14) {
        return 0;
    }
    if ((u32)i >= (u32)p->unk14) {
        ok = 0;
    } else {
        w = i / 32;
        b = i % 32;
        t = *(s32 *)((u8 *)p->unk20 + w * 4);
        ok = ((t & (1 << b)) != 0);
    }
    if (ok != 0) {
        return p->unk8 + i * p->unk10;
    }
    return 0;
}

void *PoolAllocElem_36ab00(Pool *p, u32 size, s32 *out)
{
    s32 idx;
    u8 *r;

    if (out != NULL) {
        *out = -1;
    }
    if (p->unk8 == NULL || p->unk14 <= 0 || p->unk20 == NULL) {
        return NULL;
    }
    { s32 ok = p->unk1C < p->unk14; if (!ok) return NULL; }
    if (p->unk10 < size) return NULL;
    idx = PoolFindFreeSlot_36ad40(p);
    if (idx >= 0) goto ok;
    return NULL;
ok:
    setBit(p, idx);
    p->unk1C++;
    r = getElem(p, idx);
    if (out != NULL) {
        *out = idx;
    }
    memset(r, 0, p->unk10);
    return r;
}
