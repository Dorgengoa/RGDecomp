/* rgp:protos */
#define RGP_SELF_CharaGetCollRadius_2386a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S {
    u8 pad000[0x3F4];
    u8 *m3F4;
} S;

extern f32 D_0045B080;
extern f32 D_0047D28C;
extern f32 D_0047D1DC;

f32 CharaGetCollRadius_2386a0(S *p)
{
    f32 k;
    f32 lim;
    f32 v;
    u8 *q;

    k = D_0045B080;
    lim = D_0047D28C * k;
    q = p->m3F4;
    if (q != 0) {
        v = *(f32 *)(q + 0x4C8) * (D_0047D1DC * k);
    } else {
        v = 0.0f;
    }
    v = (v > lim) ? v : lim;
    return v;
}
