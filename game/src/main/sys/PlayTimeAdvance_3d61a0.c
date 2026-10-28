/* rgp:protos */
#define RGP_SELF_PlayTimeAdvance_3d61a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj003d61a0 {
    u8 pad0[0x8];
    s64 unk8;
} Obj003d61a0;

/*rgp*/
/*rgp*/
/*rgp*/

unsigned long long PlayTimeAdvance_3d61a0(Obj003d61a0 *self, float rgp_f0)
{
    s64 temp;

    temp = self->unk8;
    self->unk8 = ((s64)__builtin_bit_cast(long long, dpadd(__builtin_bit_cast(double, (long long)(temp)), fptodp((float)rgp_f0))));
    return DoubleToU64_13ab28(__builtin_bit_cast(double, (long long)(self->unk8)));
}
