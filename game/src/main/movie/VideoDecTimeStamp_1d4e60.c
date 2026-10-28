/* rgp:protos */
#define RGP_SELF_VideoDecTimeStamp_1d4e60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct L1D4E60 { u64 a; u64 b; u64 c; u64 d; };
struct T1D4E60 { u8 pad000[0x8]; u64 f08; u64 f10; };

extern u8 D_004B3258[];
/*rgp*/

s32 VideoDecTimeStamp_1d4e60(s32 a, struct T1D4E60 *p)
{
    struct L1D4E60 l __attribute__((aligned(16)));

    ViBufGetTs_1d3990(D_004B3258, &l);
    p->f08 = l.a;
    p->f10 = l.b;
    return 1;
}
