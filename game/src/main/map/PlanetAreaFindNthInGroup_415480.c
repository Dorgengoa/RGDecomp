/* rgp:protos */
#define RGP_SELF_PlanetAreaFindNthInGroup_415480 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"

typedef struct E_FUN_00415480 {
    s32 f0;
    u8 pad4[40];
} E_FUN_00415480;

typedef struct S_FUN_00415480 {
    u8 pad0[0x7C];
    s16 f7C;
    u8 pad7E[0xE];
    E_FUN_00415480 *f8C;
} S_FUN_00415480;

E_FUN_00415480 *PlanetAreaFindNthInGroup_415480(S_FUN_00415480 *self, s32 a, s32 b)
{
    s32 key;
    s32 n;
    s32 m;
    s32 j;
    E_FUN_00415480 *p;
    s32 v;
    key = (s16)a;
    if (key < 0) goto zero;
    if (b >= 0) goto g1;
zero:
    return 0;
g1:
    n = self->f7C;
    if (n > 0) goto g2;
    return 0;
g2:
    p = self->f8C;
    if (p != 0) goto ok;
    return 0;
ok:
    m = 0;
    j = 0;
    while (j < n) {
        v = p->f0;
        if (key == (v / 10000000) % 100) {
            if (m == b) return p;
            m++;
        }
        j++;
        p++;
    }
    return 0;
}
