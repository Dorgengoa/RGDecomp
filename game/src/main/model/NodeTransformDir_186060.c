/* rgp:protos */
#define RGP_SELF_NodeTransformDir_186060 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Known-positive sibling shape of FrameTransformPoint_148f60 (byte-identical, in cunits):
   build the node's matrix into a local and push one vector through it. */

/*rgp*/
/*rgp*/

void NodeTransformDir_186060(void *node, Vec4 *out, const Vec4 *v)
{
    Mtx4 m __attribute__((aligned(16)));

    NodeCalcWorldMatrix_186130(node, &m);
    MtxMulDir_13c860(out, &m, v);
}
