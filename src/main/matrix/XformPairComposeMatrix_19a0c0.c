#include "types.h"
#include "vec.h"

/* Same family as XformPairComposeOffsetNoScale_199f60 / XformPairComposeOffset_19a010, but the matrix and the second
   temporary are the CALLER's buffers, so the frame is 0x70 and only three
   Vec4 locals live on the stack. */

extern void VecAdd_13be20(Vec4 *, const Vec4 *, const Vec4 *);
extern void VecMul_13bd40(Vec4 *, const Vec4 *, const Vec4 *);
extern void MatFromSRTVu0_13bc90(void *, const Vec4 *, const Vec4 *, const Vec4 *);

void XformPairComposeMatrix_19a0c0(u8 *p, void *d, void *s)
{
    Vec4 c;
    Vec4 b;
    Vec4 a;

    VecAdd_13be20(&c, (Vec4 *)(p + 0x10), (Vec4 *)(p + 0x60));
    VecAdd_13be20(&b, (Vec4 *)(p + 0x20), (Vec4 *)(p + 0x70));
    VecMul_13bd40(&a, (Vec4 *)(p + 0x30), (Vec4 *)(p + 0x80));
    MatFromSRTVu0_13bc90(d, &a, &b, &c);
    VecMul_13bd40((Vec4 *)s, (Vec4 *)(p + 0x40), (Vec4 *)(p + 0x90));
}
