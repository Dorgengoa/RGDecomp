/* rgp:protos */
#define RGP_SELF_EventStrAlloc_301b90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00482898;
extern s32 D_0048289C;

/*rgp*/

s32 EventStrAlloc_301b90(s32 size)
{
    s32 n;
    s32 p;

    if (D_00482898 == 0 || D_0048289C == 0) return 0;
    n = AlignUp4_1cace0(size);
    if (n <= 0) return 0;
    p = AlignUp4_1cace0(D_0048289C);
    if (D_00482898 - p + 0x10000 < n) return 0;
    D_0048289C = p + n;
    return p;
}
