/* rgp:protos */
#define RGP_SELF_XformTransformPointUnscaled_2e7550 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Known-positive sibling shape of FrameTransformPoint_148f60 (byte-identical, in cunits):
   build the node's matrix into a local and push one vector through it. */

/*rgp*/
/*rgp*/

void XformTransformPointUnscaled_2e7550(void *node, Vec4 *out, const Vec4 *v)
{
    Mtx4 m __attribute__((aligned(16)));

    XformGetUnscaledMatrix_2e7760(node, &m);
    MatMulVec4_1cb940(out, &m, v);
}
