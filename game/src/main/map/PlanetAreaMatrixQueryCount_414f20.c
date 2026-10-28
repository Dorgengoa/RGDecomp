/* rgp:protos */
#define RGP_SELF_PlanetAreaMatrixQueryCount_414f20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A414_FUN_00414f20 {
    u8 pad000[0x4];
    void *m4;
    s16 m8;
} A414_FUN_00414f20;

/*rgp*/

s32 PlanetAreaMatrixQueryCount_414f20(A414_FUN_00414f20 *p)
{
    s32 r;

    if (p->m4 != 0) {
        r = PlanetAreaMatrixCountInGroup_415040(p->m4, (long long)(p->m8));
    } else {
        r = 0;
    }
    return r;
}
