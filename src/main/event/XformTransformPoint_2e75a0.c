#include "types.h"
#include "vec.h"

/* Known-positive sibling shape of FrameTransformPoint_148f60 (byte-identical, in cunits):
   build the node's matrix into a local and push one vector through it. */

extern void XformGetMatrix_2e7750(void *node, Mtx4 *out);
extern void MatMulVec4_1cb940(Vec4 *out, const Mtx4 *m, const Vec4 *v);

void XformTransformPoint_2e75a0(void *node, Vec4 *out, const Vec4 *v)
{
    Mtx4 m;

    XformGetMatrix_2e7750(node, &m);
    MatMulVec4_1cb940(out, &m, v);
}
