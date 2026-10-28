/* rgp:protos */
#define RGP_SELF_PlanetAreaQueryCount_415400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A414_FUN_00415400 {
    u8 pad000[0x4];
    void *m4;
    s16 m8;
} A414_FUN_00415400;

/*rgp*/

s32 PlanetAreaQueryCount_415400(A414_FUN_00415400 *p)
{
    s32 r;

    if (p->m4 != 0) {
        r = PlanetAreaCountInGroup_415530(p->m4, p->m8);
    } else {
        r = 0;
    }
    return r;
}
