#include "types.h"
#include "vec.h"

/* Known-positive sibling shape of FrameTransformPoint_148f60 (byte-identical, in cunits):
   build the node's matrix into a local and push one vector through it. */

extern void NodeCalcWorldMatrix_186130(void *node, Mtx4 *out);
extern void MtxMulPoint_13c890(Vec4 *out, const Mtx4 *m, const Vec4 *v);

void NodeTransformPoint_1860b0(void *node, Vec4 *out, const Vec4 *v)
{
    Mtx4 m;

    NodeCalcWorldMatrix_186130(node, &m);
    MtxMulPoint_13c890(out, &m, v);
}
