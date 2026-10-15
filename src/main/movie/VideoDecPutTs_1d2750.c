#include "types.h"

struct T1D2750 { u8 pad000[0x48]; s32 f48; };
struct L1D2750 { u64 a; u64 b; s32 c; s32 d; };

extern const u8 D_004B3258[];
extern void ViBufPutTs_1d3b60(const u8 *t, struct L1D2750 *l);

void VideoDecPutTs_1d2750(struct T1D2750 *p, u64 a, u64 b, s32 c, s32 d)
{
    struct L1D2750 l;

    l.a = a;
    l.b = b;
    l.c = c - p->f48;
    l.d = d;
    ViBufPutTs_1d3b60(D_004B3258, &l);
}
