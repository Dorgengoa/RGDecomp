/* rgp:protos */
#define RGP_SELF_FrameSetParent_149e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T149E90 { u8 pad000[0x4]; struct T149E90 *f4; };

/*rgp*/

void FrameSetParent_149e90(struct T149E90 *p, struct T149E90 *q)
{
    if (p->f4 != 0) {
        return;
    }
    p->f4 = q;
    if (q == 0) {
        return;
    }
    FrameAddChild_149d70(q, p);
}
