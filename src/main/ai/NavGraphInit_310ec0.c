/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/NavGraphInit_310ec0.s and build/b_drafts/NavGraphInit_310ec0.txt
   (m2c draft already generated, just not worked). */
/* s49m: 2 bad (right length) */
#include "types.h"

typedef struct Pool {
    u8 *base;
    u8 flag;
    u8 pad5[3];
    u16 used;
    u16 count;
    s32 size;
} Pool;

typedef struct Self {
    u8 pad0[0x90];
    u8 heapinfo[0x10];
    Pool pools[4];
    char name[0x20];
    s32 m100;
    u8 pad104[8];
    s16 m10C;
    s16 m10E;
    u8 pad110[2];
    u8 m112;
    u8 m113;
} Self;

extern void NavGraphReset_3111a0(Self *);
extern s32 AlignUp_311a80(s32, s32);
extern u8 *UskMemoryAlloc_42dae0(s32, s32, void *, s32);
extern char *strcpy(char *, const char *);

static inline s32 pinit(Pool *p, u8 *mem, u16 count, s32 esz)
{
    p->base = 0;
    p->flag = 0;
    p->used = 0;
    p->count = 0;
    p->size = 0;
    if (mem == 0) {
        return 0;
    }
    p->base = mem;
    p->used = 0;
    p->count = count;
    p->size = AlignUp_311a80(p->count * esz, 16);
    return p->size;
}

s32 NavGraphInit_310ec0(Self *self, const char *name, s32 a2, s32 a3, s32 n1, s32 n2, s32 n3, s32 heap)
{
    s32 sz1;
    s32 sz2;
    s32 sz3;
    s32 sz4;
    u8 *mem;
    s32 c3;

    NavGraphReset_3111a0(self);
    if (heap == 0) {
        goto fail;
    }
    if (name == 0 || n1 <= 0 || n2 <= 0) {
    fail:
        return 0;
    }
    sz1 = AlignUp_311a80(n2 * 20, 16);
    sz2 = AlignUp_311a80(n1 * 36, 16);
    c3 = n2 * 2;
    sz3 = AlignUp_311a80(n2 * 4, 16);
    sz4 = AlignUp_311a80(n3, 16);
    mem = UskMemoryAlloc_42dae0(heap, sz4 + (sz3 + (sz2 + sz1)), self->heapinfo, 0);
    if (mem == 0) {
        return 0;
    }
    mem += pinit(&self->pools[0], mem, n1, 36);
    mem += pinit(&self->pools[1], mem, n2, 20);
    mem += pinit(&self->pools[2], mem, c3, 2);
    pinit(&self->pools[3], mem, n3, 1);
    strcpy(self->name, name);
    self->m100 = a2;
    self->m10C = a3;
    self->m112 = !(self->m100 < 10000);
    self->m113 = 0;
    self->m10E = -1;
    return 1;
}
