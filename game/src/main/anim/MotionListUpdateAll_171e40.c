/* rgp:protos */
#define RGP_SELF_MotionListUpdateAll_171e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct N171E40 { struct N171E40 *f00; };
struct T171E40 { u8 pad000[0x4]; struct N171E40 *f04; };

/*rgp*/

void MotionListUpdateAll_171e40(struct T171E40 *p, f32 x)
{
    struct N171E40 *n;
    void *e;

    n = p->f04;
    while (n != 0) {
        e = (u8 *)n + 0x10;
        if (e != 0) {
            MotionPlayerUpdate_172e00(e, x);
        }
        n = n->f00;
    }
}
