/* rgp:protos */
#define RGP_SELF_ItemGameRecAcquire_3d0520 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct NFUN_003d0520 { u8 b0 : 1; u8 b1 : 1; u8 rest : 6; };
struct PFUN_003d0520 { u8 pad000[0x14]; s16 f14; u8 pad016[0x2]; struct NFUN_003d0520 *f18; };
struct GFUN_003d0520 { u8 pad000[0x174]; void *f174; };

extern struct GFUN_003d0520 *D_004838F0 __attribute__((section(".sdata")));

/*rgp*/
/*rgp*/

s32 ItemGameRecAcquire_3d0520(struct PFUN_003d0520 *p)
{
    s32 a;
    struct NFUN_003d0520 *nn;

    if (D_004838F0 == 0) {
        return 0;
    }
    if (p->f18 != 0 && p->f18->b0 != 0) {
        return 1;
    }
    a = GameRecFindFreeInsectRecSlot_3ce0d0(D_004838F0->f174);
    nn = ((struct NFUN_003d0520 *)GameRecGetInsectRecSlot_3ce090(D_004838F0->f174, a));
    if (nn == 0) {
        return 0;
    }
    p->f14 = a;
    p->f18 = nn;
    nn->b0 = 1;
    p->f18->b1 = 0;
    return 1;
}
