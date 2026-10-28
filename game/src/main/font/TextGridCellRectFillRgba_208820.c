/* rgp:protos */
#define RGP_SELF_TextGridCellRectFillRgba_208820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void TextGridCellRectFillRgba_208820(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h,
                  f32 x, f32 y, f32 z, f32 w)
{
    f32 v[4] __attribute__((aligned(16))) = {0};

    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
    TextGridCellRectFill_208760(a, b, c, d, e, (long long)(f), (long long)(g), (long long)(h), v);
}
