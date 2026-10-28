/* rgp:protos */
#define RGP_SELF_ActTimeClsnInRange_228560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

u8 ActTimeClsnInRange_228560(f32 *p, f32 a, f32 len)
{
    f32 end;
    f32 x;
    u8 r;

    end = a + len;
    if (a < 0.0f) a = 0.0f;
    x = *p;
    r = 0;
    if (a > x) goto done;
    if (x >= end) goto done;
    r = 1;
done:
    return r;
}
