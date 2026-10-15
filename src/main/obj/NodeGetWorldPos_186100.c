#include "types.h"
#include "vec.h"

/* Known-positive sibling shape of FrameGetWorldPos_148f30 (byte-identical, in cunits):
   pull the translation row out of a matrix built into a local. */

extern void NodeCalcWorldMatrix_186130(void *self, Mtx4 *out);

void NodeGetWorldPos_186100(void *self, Vec4 *out)
{
    Mtx4 m;

    NodeCalcWorldMatrix_186130(self, &m);
    *out = m.r[3];
}
