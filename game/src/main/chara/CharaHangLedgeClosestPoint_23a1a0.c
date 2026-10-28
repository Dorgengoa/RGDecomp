/* rgp:protos */
#define RGP_SELF_CharaHangLedgeClosestPoint_23a1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T23A1A0 { u8 pad000[0x7C]; u32 f7C; };

/*rgp*/

s32 CharaHangLedgeClosestPoint_23a1a0(struct T23A1A0 *p, void *a, void *c)
{
    s32 ok;

    ok = !(p->f7C & 0x80000000);
    if (ok) goto run;
    return 0;
run:
    ClosestPointOnSegmentXZ_1c9e60(a, p, (u8 *)p + 0x10, c);
    return 1;
}
