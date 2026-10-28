/* rgp:protos */
#define RGP_SELF_LightningBoltFade_2d68e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S2D6 {
    u8  pad000[0x90];
    f32 f90;
    f32 f94;
    u8  pad098[0x2A];
    s16 fC2;
} S2D6;

void LightningBoltFade_2d68e0(S2D6 *p)
{
    if (p->fC2 > 0) {
        p->f90 -= p->f94;
        if (p->f90 < 0.0f) {
            p->fC2 = 0;
        }
    }
}
