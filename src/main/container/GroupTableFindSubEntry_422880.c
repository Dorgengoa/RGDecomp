#include "types.h"

typedef struct E_00422880 {
    s16 f0;
    u8 pad2[0xE];
} E_00422880;

typedef struct R_00422880 {
    u8 pad0[0x14];
    s32 f14;
    E_00422880 *f18;
} R_00422880;

extern R_00422880 *GroupTableFindEntry_422950(void *, void *, void *);

E_00422880 *GroupTableFindSubEntry_422880(void *a, void *b, void *c, s32 d)
{
    R_00422880 *r;
    E_00422880 *p;
    s32 n;
    s32 j;
    r = GroupTableFindEntry_422950(a, b, c);
    if (r != 0) goto g1;
    return 0;
g1:
    p = r->f18;
    if (p == 0) goto zero;
    n = r->f14;
    if (n > 0) goto ok;
zero:
    return 0;
ok:
    j = 0;
    while (j < n) {
        if (p->f0 == (s16)d) return p;
        j++;
        p++;
    }
    return 0;
}
