/* rgp:protos */
#define RGP_SELF_WorldSubsysPlanetEntryLink_4023b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_004023b0 { u8 b[168]; } E_004023b0;

typedef struct B_004023b0 {
    u8 pad0[8];
    s16 f8;
} B_004023b0;

typedef struct S_004023b0 {
    u8 pad0[4];
    void *f4;
    u8 pad8[4];
    E_004023b0 *fC;
} S_004023b0;

/*rgp*/
/*rgp*/

s32 WorldSubsysPlanetEntryLink_4023b0(S_004023b0 *self, B_004023b0 *b, int rgp_a2, int rgp_a3)
{
    s32 i;
    E_004023b0 *p;
    E_004023b0 *e;
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
        WorldSubsysLinkIds_4039f0(e, self->f4, (int)rgp_a2, (int)rgp_a3);
        DataTableBuildSortedIndex_403720(e);
    }
    return 1;
}
