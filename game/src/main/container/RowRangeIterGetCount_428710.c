/* rgp:protos */
#define RGP_SELF_RowRangeIterGetCount_428710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A28710 {
    u8 pad000[0x4];
    s32 m4;
    s16 m8;
    s16 mA;
} A28710;

s32 RowRangeIterGetCount_428710(A28710 *p)
{
    s16 a;
    s16 b;

    if (p->m4 == 0) return 0;
    a = p->m8;
    if (a >= 0) {
        b = p->mA;
        if (b >= 0) goto ok;
    }
    return 0;
ok:
    return b - a + 1;
}
