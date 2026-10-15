#include "types.h"
#include "vec.h"

/* Known-positive sibling shape of FrameTransformPoint_148f60 (byte-identical, in cunits):
   build the node's matrix into a local and push one vector through it. */

extern void XformGetUnscaledMatrix_2e7760(void *node, Mtx4 *out);
extern void MatMulVec4_1cb940(Vec4 *out, const Mtx4 *m, const Vec4 *v);

void XformTransformPointUnscaled_2e7550(void *node, Vec4 *out, const Vec4 *v)
{
    Mtx4 m;

    XformGetUnscaledMatrix_2e7760(node, &m);
    MatMulVec4_1cb940(out, &m, v);
}
