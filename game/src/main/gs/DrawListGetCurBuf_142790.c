/* rgp:protos */
#define RGP_SELF_DrawListGetCurBuf_142790 1
#include "port/game_protos.h"
#line 1
#include "types.h"
void *DrawListGetCurBuf_142790(s32 *p)
{
    s32   t;
    void *q;

    t = p[0] * 4;
    q = *(void **)(t + (s32)p + 8);
    /* `beql` + `daddu $2,$0,$0` in the slot is the NESTED form. */
    if (q != 0) {
        return (u8 *)q + 8;
    }
    return 0;
}
