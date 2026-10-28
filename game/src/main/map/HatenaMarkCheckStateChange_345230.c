/* rgp:protos */
#define RGP_SELF_HatenaMarkCheckStateChange_345230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 {
    u8 pad000[0xC];
    u8 m0C;
    u8 m0D;
    u8 pad00E[0x93];
    u8 mA1_0 : 2;
    u8 mA1_2 : 1;
    u8 mA1_3 : 5;
};

void HatenaMarkCheckStateChange_345230(struct Obj0 *p0)
{
    u8 t0;
    u8 t1;

    t0 = p0->m0C;
    t1 = p0->m0D;
    if (t1 != t0) {
        if (t1 == 0) {
            if (t0 == 3) {
                return;
            }
        }
        if (t1 == 3) {
            if (t0 == 0) {
                return;
            }
        }
        p0->mA1_2 = 1;
    }
}
