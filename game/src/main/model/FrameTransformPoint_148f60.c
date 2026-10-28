/* rgp:protos */
#define RGP_SELF_FrameTransformPoint_148f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Builds the node's matrix into a local and pushes one vector through it.
   The prototype is not guessed: `CameraTrackUpdate_305960.cpp` already declares
   FrameTransformPoint_148f60(node, out, v) and calls it as FrameTransformPoint_148f60(node, &forward,
   &forward), and MtxMulPoint_13c890's argument order follows from that -- out, the
   matrix, the vector. Frame 0x70: two `sq` saves, the return address, and the
   0x40 matrix at 0x30. */

/*rgp*/
/*rgp*/

void FrameTransformPoint_148f60(void *node, Vec4 *out, const Vec4 *v)
{
    Mtx4 m __attribute__((aligned(16)));

    FrameCalcWorldMatrix_148ff0(node, &m);
    MtxMulPoint_13c890(out, &m, v);
}
