#include "types.h"

typedef struct Ent { u8 b[0x58]; } Ent;

typedef struct Self {
    u8   pad000[0x38];
    s16  m38;
    u8   pad03C[6];
    Ent *m40;
} Self;

extern s32 MapDataGetId_1e7bd0(Ent *p);

Ent *MapRecTableFindShareById_1dd4a0(Self *self, s32 k)
{
    Ent *p;
    s32  i;

    if (k < 0) {
        return 0;
    }
    p = self->m40;
    if (p == 0) {
        return 0;
    }
    for (i = 0; i < self->m38; i++, p++) {
        if (MapDataGetId_1e7bd0(p) == k) {
            return p;
        }
    }
    return 0;
}
