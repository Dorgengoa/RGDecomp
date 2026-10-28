/* rgp:protos */
#define RGP_SELF_EffInstOrFlags_1a0d20 1
#define RGP_SELF_lookup 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Set flag bits on the object a handle names.  Companion to HandleTableGetDeref_1a0ca0. */

typedef union Handle {
    u32 all;
    struct { u16 idx; u16 gen; } h;
} Handle;

typedef struct Obj {
    u8  pad000[0xC8];
    u32 mC8;
} Obj;

typedef struct Owner {
    u8    pad000[0xE8];
    u32   count;
    Obj **recs;
    u8    pad0F0[0x8];
    u32  *tags;
} Owner;

static inline Obj **lookup(Owner *t, Handle h)
{
    Handle k __attribute__((aligned(16))) = h;
    u16 g;

    if (((k.all != 0) ^ 1) != 0) {
        return NULL;
    }
    if (k.h.idx >= t->count || t->tags[k.h.idx] != (g = k.h.gen)) {
        return NULL;
    }
    return &t->recs[k.h.idx];
}

void EffInstOrFlags_1a0d20(Owner *t, Handle h, u32 bits)
{
    Obj **p = lookup(t, h);
    Obj *o = p != NULL ? *p : NULL;

    if (o != NULL) {
        o->mC8 |= bits;
    }
}
