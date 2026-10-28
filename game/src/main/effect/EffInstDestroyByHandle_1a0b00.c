/* rgp:protos */
#define RGP_SELF_EffHdlRelease_1a3040 1
#define RGP_SELF_EffInstDestroyByHandle_1a0b00 1
#define RGP_SELF_Lookup 1
#define RGP_SELF_isnull 1
#define RGP_SELF_ne 1
#include "port/game_protos.h"
#line 1
/* PARKED at triage (0 round trips): m2c's draft references `unksp66`
 * (an invented name, never declared) alongside declared sp68/sp6A/sp6C/sp6E
 * -- a 16-bit hash/index pair aliasing pattern that needs a raw-asm trace of
 * the stack frame to pin down correctly. Deferred to preserve lane
 * throughput. See asm/matchings/main/EffInstDestroyByHandle_1a0b00.s. */
/* s49m: 10-bad */
#include "types.h"
#pragma optimization_level 3

typedef struct Handle {
    __extension__ unsigned short idx : 16;
    unsigned short  : 0, gen : 16;
} __attribute__((aligned(2))) Handle;

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

/*rgp*/
/*rgp*/
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
    Handle h2 __attribute__((aligned(16)));
    Handle h1 __attribute__((aligned(16)));
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
