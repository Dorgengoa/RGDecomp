/* rgp:protos */
#define RGP_SELF_LoadingScreenSetProgress_343190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_004E897C[];
extern f32 D_004E8980[];
extern f32 D_004E8984[];

void LoadingScreenSetProgress_343190(f32 a, f32 b)
{
    D_004E897C[0] = D_004E8980[0];
    D_004E8980[0] = a;
    D_004E8984[0] = b;
    if (a >= 1.0f) {
        D_004E8980[0] = 1.0f;
    }
}
