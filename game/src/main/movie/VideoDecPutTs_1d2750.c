/* rgp:protos */
#define RGP_SELF_VideoDecPutTs_1d2750 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T1D2750 { u8 pad000[0x48]; s32 f48; };
struct L1D2750 { u64 a; u64 b; s32 c; s32 d; };

extern u8 D_004B3258[];
/*rgp*/

void VideoDecPutTs_1d2750(struct T1D2750 *p, u64 a, u64 b, s32 c, s32 d)
{
    struct L1D2750 l __attribute__((aligned(16)));

    l.a = a;
    l.b = b;
    l.c = c - p->f48;
    l.d = d;
    ViBufPutTs_1d3b60(D_004B3258, &l);
}
