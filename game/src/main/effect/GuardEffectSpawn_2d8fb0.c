/* rgp:protos */
#define RGP_SELF_GuardEffectSpawn_2d8fb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004E0DD0[];
extern s32 D_004826A0;
/*rgp*/

void GuardEffectSpawn_2d8fb0(void *a, void *b)
{
    s32 i;

    i = D_004826A0;
    GuardEffectStart_2d53e0(&D_004E0DD0[i * 832], a, b);
    D_004826A0 = D_004826A0 + 1;
    if (D_004826A0 >= 0xC) {
        D_004826A0 = 0;
    }
}
