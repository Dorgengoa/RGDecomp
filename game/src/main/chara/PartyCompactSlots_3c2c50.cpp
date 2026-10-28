#pragma optimization_level 3
#include "types.h"

struct Self {
    u8 pad0[0x18E];
    s16 m18E;
    s16 a[3];
    s16 b[7];
};

struct Ent {
    u8 pad0[0x234];
    u8 m234;
};

struct G {
    u8 pad0[0x14];
    void *m14;
};

extern "C" G *D_00483890;
extern "C" s32 PartyCountMembers_3c2010(Self *, s32, s32);
extern "C" Ent *CharaMgrPoolFindById_3a8c60(void *, s32);
extern "C" s32 PartyPromoteReserve_3c17c0(Self *, s32, s32, s32);


extern "C" bool PartyCompactSlots_3c2c50(Self *self)
{
    bool changed;
    s32 iter;
    s32 last;
    s32 j;
    bool moved;
    s32 k;
    s32 n;
    bool found;
    s32 i;
    s32 m;
    s16 id;
    Ent *e;

    if (D_00483890 == 0) {
        return false;
    }
    changed = false;
    for (iter = 0; iter < 2; iter++) {
        last = 0;
        for (j = 0; j < 3; j++) {
            if (self->a[j] < 0) {
                break;
            }
            last = j;
        }
        if (last == 2) {
            break;
        }
        moved = false;
        for (k = 2; last < k; k--) {
            if (self->a[k - 1] < 0) {
                self->a[k - 1] = self->a[k];
                self->a[k] = -1;
                changed = true;
                moved = changed;
            }
        }
        if (!moved) {
            break;
        }
    }
    for (iter = 0; iter < 6; iter++) {
        last = 0;
        for (j = 0; j < 7; j++) {
            if (self->b[j] < 0) {
                break;
            }
            last = j;
        }
        if (last == 6) {
            break;
        }
        moved = false;
        for (k = 6; last < k; k--) {
            if (self->b[k - 1] < 0) {
                self->b[k - 1] = self->b[k];
                self->b[k] = -1;
                changed = true;
                moved = changed;
            }
        }
        if (!moved) {
            break;
        }
    }
    n = PartyCountMembers_3c2010(self, 1, 1);
    found = false;
    for (i = 0; i < n; i++) {
        if (self->a[i] == self->m18E) {
            found = true;
            break;
        }
    }
    if (!found) {
        self->m18E = self->a[0];
        if (self->m18E < 0) {
            for (m = 0; m < 6; m++) {
                id = self->b[m];
                if (id < 0) {
                    continue;
                }
                e = CharaMgrPoolFindById_3a8c60(D_00483890->m14, id);
                if (e == 0) {
                    continue;
                }
                if (!(e->m234 & 1)) {
                    continue;
                }
                changed = PartyPromoteReserve_3c17c0(self, id, 0, 0) != 0;
                break;
            }
        }
    }
    return changed;
}
