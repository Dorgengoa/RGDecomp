/* rgp:protos */
#define RGP_SELF_FrameGetWorldPos_148f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Pulls one row out of a matrix that FrameCalcWorldMatrix_148ff0 builds into a local.
   The frame is 0x60: 0x00 the `sq $16` save, 0x10 the return address, and
   0x20..0x60 the 64-byte matrix -- so the `lq $3, 0x50($29)` the reference
   ends on is row[3], the translation row. The copy has to be ONE lq/sq pair,
   which is what Vec4's alignment buys (see vec.h). */

/*rgp*/

void FrameGetWorldPos_148f30(void *self, Vec4 *out)
{
    Mtx4 m __attribute__((aligned(16)));

    FrameCalcWorldMatrix_148ff0(self, &m);
    *out = m.r[3];
}
