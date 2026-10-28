/* rgp:protos */
#define RGP_SELF_ZonePhaseSetCountByKey_414c60 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"

typedef struct E_00414c60 {
    s32 f0;
    u8 pad4[4];
} E_00414c60;

typedef struct S_00414c60 {
    u8 pad0[0x7C];
    s16 f7C;
    u8 pad7E[0xE];
    E_00414c60 *f8C;
} S_00414c60;

s32 ZonePhaseSetCountByKey_414c60(S_00414c60 *self, s32 a, s32 b)
{
    s32 k1;
    s32 k2;
    s32 n;
    s32 cnt;
    E_00414c60 *p;
    s32 j;
    s32 v;
    k1 = (s16)a;
    if (k1 < 0) goto zero;
    k2 = (s16)b;
    if (k2 >= 0) goto g1;
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
    cnt = 0;
    j = 0;
    while (j < n) {
        v = p->f0;
        if (k1 == (v / 10000000) % 100) {
            if (k2 == (v / 100000) % 10000) {
                cnt++;
            }
        }
        j++;
        p++;
    }
    return cnt;
}
