/* rgp:protos */
#define RGP_SELF_ItemGameRecAcquire_3d1000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct NFUN_003d1000 { u8 b0 : 1; u8 b1 : 1; u8 rest : 6; };
struct PFUN_003d1000 { u8 pad000[0x14]; s16 f14; u8 pad016[0x2]; struct NFUN_003d1000 *f18; };
struct GFUN_003d1000 { u8 pad000[0x174]; void *f174; };

extern struct GFUN_003d1000 *D_004838F0 __attribute__((section(".sdata")));

/*rgp*/
/*rgp*/

s32 ItemGameRecAcquire_3d1000(struct PFUN_003d1000 *p)
{
    s32 a;
    struct NFUN_003d1000 *nn;

    if (D_004838F0 == 0) {
        return 0;
    }
    if (p->f18 != 0 && p->f18->b0 != 0) {
        return 1;
    }
    a = GameRecFindFreeCageSlot_3ce230(D_004838F0->f174);
    nn = ((struct NFUN_003d1000 *)GameRecGetCageSlot_3ce1f0(D_004838F0->f174, a));
    if (nn == 0) {
        return 0;
    }
    p->f14 = a;
    p->f18 = nn;
    nn->b0 = 1;
    p->f18->b1 = 0;
    return 1;
}
