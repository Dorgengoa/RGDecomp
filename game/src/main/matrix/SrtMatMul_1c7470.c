/* rgp:protos */
#define RGP_SELF_SrtMatMul_1c7470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sp001c7470 {
    u8 pad0[0x40];
} Sp001c7470;

/*rgp*/
/*rgp*/

void SrtMatMul_1c7470(u8 *arg0, s32 arg1, s32 arg2)
{
    u8 *base;
    Sp001c7470 sp30 __attribute__((aligned(16)));

    base = arg0;
    MatFromSRT_1caf40(&sp30, base, base + 0x10, base + 0x20);
    MatMul_1cb700(arg1, arg2, &sp30);
}
