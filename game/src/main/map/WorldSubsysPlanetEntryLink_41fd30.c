/* rgp:protos */
#define RGP_SELF_WorldSubsysPlanetEntryLink_41fd30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_0041fd30 { u8 b[192]; } E_0041fd30;

typedef struct B_0041fd30 {
    u8 pad0[8];
    s16 f8;
} B_0041fd30;

typedef struct S_0041fd30 {
    u8 pad0[4];
    void *f4;
    E_0041fd30 *f8;
} S_0041fd30;

/*rgp*/

s32 WorldSubsysPlanetEntryLink_41fd30(S_0041fd30 *self, B_0041fd30 *b, int rgp_a2, int rgp_a3)
{
    s32 i;
    E_0041fd30 *p;
    E_0041fd30 *e;
    if (b != 0) goto g1;
    return 0;
g1:
    i = b->f8;
    if (i < 0) goto zero;
    if (i < 2) goto ok;
zero:
    return 0;
ok:
    p = self->f8;
    e = 0;
    if (p != 0) {
        e = &p[i];
    }
    if (e != 0) {
        WorldSubsysLinkIds_420640(e, self->f4, 0, (int)rgp_a3);
    }
    return 1;
}
