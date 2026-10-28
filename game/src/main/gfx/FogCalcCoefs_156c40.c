/* rgp:protos */
#define RGP_SELF_FogCalcCoefs_156c40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void FogCalcCoefs_156c40(f32 *arg0, f32 *arg1) {
    f32 p1;
    f32 p2;
    f32 a;
    f32 v4;
    f32 v0;
    f32 b;

    b = arg0[6];
    v0 = arg0[0];
    v4 = arg0[1];
    p2 = 255.0f * (1.0f - b);
    a = arg0[5];
    p1 = 255.0f * (1.0f - a);
    arg1[1] = p1;
    arg1[2] = p2;
    arg0[4] = (p1 - p2) / (v0 - v4);
    arg0[7] = (v4 * p1 - v0 * p2) / (v4 - v0);
    arg1[3] = arg0[4];
    arg1[0] = arg0[7];
}
