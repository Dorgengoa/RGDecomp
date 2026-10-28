/* rgp:protos */
#define RGP_SELF_HandleTableGetDeref_1a0ca0 1
#define RGP_SELF_lookup 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Resolve a handle to the object it names, or NULL.  Same handle-table lookup
   as HandleTableGet_1a1d50 (read that unit for the spellings), but over a table
   embedded at +0xE8 of a larger owner and holding 4-byte POINTER slots, so the
   index shift is shared between the tag probe and the slot address. */

typedef union Handle {
    u32 all;
    struct { u16 idx; u16 gen; } h;
} Handle;

typedef struct Obj Obj;

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

Obj *HandleTableGetDeref_1a0ca0(Owner *t, Handle h)
{
    Obj **p = lookup(t, h);

    return p != NULL ? *p : NULL;
}
