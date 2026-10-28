/* rgp:protos */
#define RGP_SELF_CfgVmGetString_42f3d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00468D68[];

typedef struct Q_0042f3d0 {
    u8 pad0[8];
    s32 f8;
} Q_0042f3d0;

typedef struct S_0042f3d0 {
    u8 pad0[0x408];
    s32 f408;
    s32 f40C;
    Q_0042f3d0 *f410;
    u8 pad414[4];
    u8 *f418;
    u8 *f41C;
} S_0042f3d0;

u8 *CfgVmGetString_42f3d0(S_0042f3d0 *self, s32 i)
{
    Q_0042f3d0 *q;
    u8 *p;
    u8 *r;
    if (self->f408 == 0) goto zero;
    if (self->f40C <= 0) goto zero;
    q = self->f410;
    if (q == 0) goto zero;
    p = self->f418;
    if (p != 0) goto g1;
zero:
    return 0;
g1:
    if (i == -1) return D_00468D68;
    if (i == -2) goto zero2;
    if (i >= 0) goto g2;
zero2:
    return 0;
g2:
    if (i < q->f8) goto ok;
    return 0;
ok:
    r = self->f41C;
    if (r != 0) return r + i;
    return p + i;
}
