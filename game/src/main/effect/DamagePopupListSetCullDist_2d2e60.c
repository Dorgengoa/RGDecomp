/* rgp:protos */
#define RGP_SELF_DamagePopupListSetCullDist_2d2e60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S2D2 {
    u8  pad000[8];
    f32 f08;
} S2D2;

extern f32 D_0045B080[];

void DamagePopupListSetCullDist_2d2e60(S2D2 *p, f32 v)
{
    f32 t;

    if (v < 0.0f) {
        p->f08 = -1.0f;
    } else {
        t = v * D_0045B080[0];
        p->f08 = t;
        t = t * t;
        p->f08 = t;
    }
}
