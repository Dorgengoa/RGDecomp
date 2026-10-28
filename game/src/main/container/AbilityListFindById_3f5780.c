/* rgp:protos */
#define RGP_SELF_AbilityListFindById_3f5780 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_003f5780 {
    s16 f0;
    u8 pad2[0xA];
} E_003f5780;

typedef struct S_003f5780 {
    u8 pad0[8];
    s32 f8;
    E_003f5780 *fC;
} S_003f5780;

E_003f5780 *AbilityListFindById_3f5780(S_003f5780 *self, s32 key)
{
    E_003f5780 *p = self->fC;
    s32 n;
    s32 j;
    if (p == 0) goto zero;
    n = self->f8;
    if (n > 0) goto ok;
zero:
    return 0;
ok:
    j = 0;
    while (j < n) {
        if (p->f0 == key) return p;
        j++;
        p++;
    }
    return 0;
}
