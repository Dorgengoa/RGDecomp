/* rgp:protos */
#define RGP_SELF_MinimapCalcQuadCornersMaybe_325150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 v[4]; } Q;
extern Q D_0047F470 __attribute__((section(".sdata")));
extern Q D_0047F480 __attribute__((section(".sdata")));

void MinimapCalcQuadCornersMaybe_325150(s32 pd0, f32 *o1, f32 *o2, s32 x, s32 y, f32 *sc, s32 rot, s32 w, s32 h, f32 p0, f32 p1)
{
    f32 A[4] __attribute__((aligned(16)));
    f32 B[4] __attribute__((aligned(16)));
    s32 i;
    f32 a0;
    f32 a1;
    f32 b0;
    f32 b1;

    *(Q *)A = D_0047F470;
    a0 = (f32)((1 - x) + w);
    a1 = (f32)((1 - y) + h);
    *(Q *)B = D_0047F480;
    b0 = (f32)(x + w);
    b1 = (f32)(y + h);
    A[0] = a0;
    A[1] = a1;
    B[0] = b0;
    B[1] = b1;
    if (rot != 0) {
        o1[0] = a0 * p1 - a1 * p0;
        o2[0] = b0 * p1 - b1 * p0;
        o1[1] = a0 * p0 + a1 * p1;
        o2[1] = b0 * p0 + b1 * p1;
    } else {
        for (i = 0; i < 3; i++) {
            o1[i] = A[i];
            o2[i] = B[i];
        }
    }
    if (sc != NULL) {
        for (i = 0; i < 2; i++) {
            o1[i] *= sc[i];
            o2[i] *= sc[i];
        }
    }
}
