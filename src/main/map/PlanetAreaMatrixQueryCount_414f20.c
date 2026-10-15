#include "types.h"

typedef struct A414_FUN_00414f20 {
    u8 pad000[0x4];
    void *m4;
    s16 m8;
} A414_FUN_00414f20;

extern s32 PlanetAreaMatrixCountInGroup_415040(void *a, s16 b);

s32 PlanetAreaMatrixQueryCount_414f20(A414_FUN_00414f20 *p)
{
    s32 r;

    if (p->m4 != 0) {
        r = PlanetAreaMatrixCountInGroup_415040(p->m4, p->m8);
    } else {
        r = 0;
    }
    return r;
}
