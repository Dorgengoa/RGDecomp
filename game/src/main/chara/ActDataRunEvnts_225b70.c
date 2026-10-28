/* rgp:protos */
#define RGP_SELF_ActDataRunEvnts_225b70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* the nine words at $sp+0x40 are a 36-byte local handed to ScriptCallWithArgs_302770;
   only the first is non-zero. */

typedef struct {
    void *p;
    s32 a, b, c, d, e, f, g, h;
} Ctx;

/*rgp*/

void ActDataRunEvnts_225b70(void *p, void *q)
{
    Ctx ctx __attribute__((aligned(16)));
    u8 *e;
    s32 i;

    e = *(u8 **)((u8 *)p + 0x14);
    if (e != 0) {
        ctx.p = q;
        ctx.a = 0;
        ctx.b = 0;
        ctx.c = 0;
        ctx.d = 0;
        ctx.e = 0;
        ctx.f = 0;
        ctx.g = 0;
        ctx.h = 0;
        for (i = 0; i < *(s16 *)((u8 *)p + 0x20); i++, e += 0xC) {
            ScriptCallWithArgs_302770(e, &ctx, 0);
        }
    }
}
