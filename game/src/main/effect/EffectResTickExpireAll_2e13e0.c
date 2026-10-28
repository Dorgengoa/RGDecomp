/* rgp:protos */
#define RGP_SELF_EffectResTickExpireAll_2e13e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Sweep the 0x30-entry, 0x70-byte table at +0x174 and expire the timed slots. */

typedef struct Sub {
    u8 pad0[0x28];
    u32 f28;                /* 0x28 */
} Sub;

typedef struct Slot {
    s32 f0;                 /* 0x00 */
    s32 f4;                 /* 0x04 */
    Sub *f8;                /* 0x08 */
    s32 fC;                 /* 0x0C */
    u8 pad10[0x4C];
    s32 f5C;                /* 0x5C */
    s32 f60;                /* 0x60 */
    u8 pad64[4];
    s32 f68;                /* 0x68 */
    u8 pad6C[1];
    u8 f6D;                 /* 0x6D */
    u8 pad6E[2];
} Slot;

typedef struct Owner {
    u8 pad0[0x58];
    u8 f58[0x11C];
    Slot slots[0x30];       /* 0x174 */
} Owner;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *dst, s32 c, s32 n);

void EffectResTickExpireAll_2e13e0(Owner *o)
{
    void *ctx;
    Slot *s;
    s32 i;
    Sub *sub;
    u8 busy;

    ctx = GetLoaderMgr_1f59d0();
    if (ctx == 0) {
        return;
    }
    s = o->slots;
    for (i = 0; i < 0x30; i++, s++) {
        if (s->f6D == 0) {
            continue;
        }
        if (s->f5C != 1) {
            continue;
        }
        if (s->f0 < 0) {
            continue;
        }
        s->f68 = s->f68 - 1;
        if (s->f68 > 0) {
            continue;
        }
        EffDefDestroy_1a0a90(o->f58, s->f4);
        if (s->f60 >= 0) {
            LoaderReleaseById_1cd340(ctx, s->f60);
        }
        sub = s->f8;
        if (sub != 0) {
            /* a u8 local is what materialises the predicate (the sltu);
               6 other spellings are 1 word short - measured */
            busy = sub->f28 > 0;
            if (!busy && s->fC != 0) {
                MemStackHeapFree_14dcb0(sub, s->fC);
            }
        }
        memset(s, 0, 0x70);
        s->f0 = -1;
        s->f60 = -1;
    }
}
