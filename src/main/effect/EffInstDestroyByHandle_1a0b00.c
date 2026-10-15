/* PARKED at triage (0 round trips): m2c's draft references `unksp66`
 * (an invented name, never declared) alongside declared sp68/sp6A/sp6C/sp6E
 * -- a 16-bit hash/index pair aliasing pattern that needs a raw-asm trace of
 * the stack frame to pin down correctly. Deferred to preserve lane
 * throughput. See asm/matchings/main/EffInstDestroyByHandle_1a0b00.s. */
/* s49m: 10-bad */
#include "types.h"
#pragma optimization_level 3

typedef struct Handle {
    u16 idx : 16;
    u16 gen : 16;
} Handle;

typedef struct Pool {
    u8 pad0[0xC];
    s32 heap;
    u8 pad10[0xE4 - 0x10];
    s32 unkE4;
    u32 count;
    s32 *items;
    u8 padF0[8];
    u32 *gens;
} Pool;

extern void EffDefUnlinkInstance_19a600(s32, s32);
extern void MemStackHeapFree_14dcb0(s32, s32);
extern void EffHdlRelease_1a3040(s32 *, Handle);

static inline s32 isnull(Handle *h)
{
    return !(*(u32 *)h != 0);
}

static inline s32 ne(u32 a, u32 b) { return a != b; }
static inline s32 *Lookup(Pool *p, Handle *hp)
{
    if (isnull(hp)) {
        return NULL;
    }
    if (hp->idx >= p->count || ne(p->gens[hp->idx], hp->gen)) {
        return NULL;
    }
    return &p->items[hp->idx];
}

void EffInstDestroyByHandle_1a0b00(Pool *arg0, Handle arg1)
{
    Handle h2;
    Handle h1;
    s32 *e;
    s32 obj;
    s32 heap;

    h1 = arg1;
    e = Lookup(arg0, &h1);
    obj = e != NULL ? *e : 0;
    if (obj == 0) {
        return;
    }
    if (obj != 0) {
        heap = arg0->heap;
        EffDefUnlinkInstance_19a600(*(s32 *)(obj + 0xD4), obj);
        MemStackHeapFree_14dcb0(heap, *(s32 *)(obj + 0xE4));
    }
    h2 = arg1;
    if (Lookup(arg0, &h2) != NULL) {
        EffHdlRelease_1a3040(&arg0->unkE4, arg1);
    }
}
