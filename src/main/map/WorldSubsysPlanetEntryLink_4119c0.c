#include "types.h"

typedef struct E_004119c0 { u8 b[164]; } E_004119c0;

typedef struct B_004119c0 {
    u8 pad0[8];
    s16 f8;
} B_004119c0;

typedef struct S_004119c0 {
    u8 pad0[0x3C];
    E_004119c0 *f3C;
} S_004119c0;

extern void DataTableBuildSortedIndex_413eb0(E_004119c0 *);

s32 WorldSubsysPlanetEntryLink_4119c0(S_004119c0 *self, B_004119c0 *b)
{
    s32 i;
    E_004119c0 *p;
    E_004119c0 *e;
    if (b != 0) goto g1;
    return 0;
g1:
    i = b->f8;
    if (i < 0) goto zero;
    if (i < 2) goto ok;
zero:
    return 0;
ok:
    p = self->f3C;
    e = 0;
    if (p != 0) {
        e = &p[i];
    }
    if (e != 0) {
        DataTableBuildSortedIndex_413eb0(e);
    }
    return 1;
}
