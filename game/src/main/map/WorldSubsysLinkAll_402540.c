/* rgp:protos */
#define RGP_SELF_WorldSubsysLinkAll_402540 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S402540 { u8 pad000[0x4]; void *f04; void *f08; u8 pad00C[0x4]; void *f10; };

/*rgp*/
/*rgp*/

s32 WorldSubsysLinkAll_402540(struct S402540 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    if (p->f08 != 0) {
        WorldSubsysLinkIds_404260(p->f08, p->f04, (int)rgp_a2, (int)rgp_a3);
    }
    if (p->f10 != 0) {
        WorldSubsysLinkIds_402870(p->f10, p->f04, 0, 0);
    }
    return 1;
}
