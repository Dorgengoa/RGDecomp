/* rgp:protos */
#define RGP_SELF_NodeGetWorldPos_186100 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Known-positive sibling shape of FrameGetWorldPos_148f30 (byte-identical, in cunits):
   pull the translation row out of a matrix built into a local. */

/*rgp*/

void NodeGetWorldPos_186100(void *self, Vec4 *out)
{
    Mtx4 m __attribute__((aligned(16)));

    NodeCalcWorldMatrix_186130(self, &m);
    *out = m.r[3];
}
