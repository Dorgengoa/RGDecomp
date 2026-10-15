#include "types.h"
/* insect 0x005129C0 -- 76 bytes, 19 instructions. */

typedef struct Buf {
    s32 f0;                         /* +0x000 */
    u8  pad04[0x5C - 0x4];
    s32 f5C;                        /* +0x05C */
    s32 f60;                        /* +0x060 */
    u8  pad64[0x3FC - 0x64];
    s32 f3FC;                       /* +0x3FC */
} Buf;

extern void func_14DCB0(s32 a, s32 b);

void insect_InsectModelMemReleaseHeap_5129c0(Buf *b)
{
    b->f0 = 0;
    if (b->f5C != 0) {
        if (b->f60 != 0) {
            func_14DCB0(b->f60, b->f5C);
            b->f5C = 0;
            b->f60 = 0;
            b->f3FC = 0;
        }
    }
}
