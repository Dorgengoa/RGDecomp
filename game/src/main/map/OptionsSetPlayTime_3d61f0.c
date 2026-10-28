/* rgp:protos */
#define RGP_SELF_OptionsSetPlayTime_3d61f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T3D61F0 { u8 pad000[0x8]; s64 f8; };

/*rgp*/

void OptionsSetPlayTime_3d61f0(struct T3D61F0 *p, double b)
{
    p->f8 = ((s64)__builtin_bit_cast(long long, U64ToDouble_100370((unsigned long long)__builtin_bit_cast(long long, (double)(b)))));
}
