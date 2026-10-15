#include "types.h"

typedef struct E_0040ecd0 { u8 b[992]; } E_0040ecd0;

typedef struct B_0040ecd0 {
    u8 pad0[8];
    s16 f8;
} B_0040ecd0;

typedef struct S_0040ecd0 {
    u8 pad0[4];
    void *f4;
    u8 pad8[4];
    E_0040ecd0 *fC;
} S_0040ecd0;

extern void WorldSubsysLinkIds_40fca0(E_0040ecd0 *, void *);

s32 WorldSubsysPlanetEntryLink_40ecd0(S_0040ecd0 *self, B_0040ecd0 *b)
{
    s32 i;
    E_0040ecd0 *p;
    E_0040ecd0 *e;
    if (b != 0) goto g1;
    return 0;
g1:
    i = b->f8;
    if (i < 0) goto zero;
    if (i < 2) goto ok;
zero:
    return 0;
ok:
    p = self->fC;
    e = 0;
    if (p != 0) {
        e = &p[i];
    }
    if (e != 0) {
        WorldSubsysLinkIds_40fca0(e, self->f4);
    }
    return 1;
}
