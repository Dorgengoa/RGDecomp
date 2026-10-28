/* rgp:protos */
#define RGP_SELF_EvMonographChrName_2e93f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern char D_00461A20[];

extern void Sprintf_1343b8(void *p, const char *s);

s32 EvMonographChrName_2e93f0(void *a0, void *a1, s32 a2, s32 a3)
{
    if (a1 == 0 || a2 < 0 || a3 == 0) {
        return 0;
    }
    ((int (*)())Sprintf_1343b8)(a1, D_00461A20, a2, a3);
    return 1;
}
