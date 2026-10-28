/* rgp:protos */
#define RGP_SELF_MapRecTableFindBlockById_1dd410 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent { u8 b[0xCC]; } Ent;

typedef struct Self {
    u8   pad000[0x3A];
    s16  m3A;
    u8   pad03C[0x8];
    Ent *m44;
} Self;

/*rgp*/

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
        if (((short)MapDataGetId_1e7bd0(p)) == k) {
            return p;
        }
    }
    return 0;
}
