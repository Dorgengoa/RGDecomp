#include "types.h"

typedef struct Ent { u8 b[0xCC]; } Ent;

typedef struct Self {
    u8   pad000[0x3A];
    s16  m3A;
    u8   pad03C[0x8];
    Ent *m44;
} Self;

extern s32 MapDataGetId_1e7bd0(Ent *p);

Ent *MapRecTableFindBlockById_1dd410(Self *self, s32 k)
{
    Ent *p;
    s32  i;

    if (k < 0) {
        return 0;
    }
    p = self->m44;
    if (p == 0) {
        return 0;
    }
    for (i = 0; i < self->m3A; i++, p++) {
        if (MapDataGetId_1e7bd0(p) == k) {
            return p;
        }
    }
    return 0;
}
