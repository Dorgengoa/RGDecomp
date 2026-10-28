/* rgp:protos */
#define RGP_SELF_ActInfoEfctEnd_23e2e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_004BCE60[4];
extern s16 D_004BCE8C[8];
extern u8 D_004BCE20[16];

/*rgp*/

s32 ActInfoEfctEnd_23e2e0(void *a, s32 k)
{
    s16 n;

    if (k != 0) return 0;
    if (D_004BCE60[0] != 0) {
        n = D_004BCE8C[0];
        if (n < 0x80) goto ok;
    }
    return 1;
ok:
    ActCfgTableSetEfctCount_223c20(D_004BCE20, n + 1);
    return 1;
}
