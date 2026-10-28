/* rgp:protos */
#define RGP_SELF_U64ToFloat_1003c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

f32 U64ToFloat_1003c0(s64 n)
{
    f32 t;

    if (n > 0) {
        return S64ToFloat_13aa40(n);
    }
    t = S64ToFloat_13aa40((s64)(((u64)n >> 1) | (u64)(n & 1)));
    return t + t;
}
