/* rgp:protos */
#define RGP_SELF_ScreenPosIsVisible_2dd0b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct B_002dd0b0 {
    u8 pad0[0xC];
    f32 fC;
    f32 f10;
} B_002dd0b0;

/*rgp*/

s32 ScreenPosIsVisible_2dd0b0(f32 *p)
{
    B_002dd0b0 *b;
    f32 x;
    f32 y;
    f32 z;
    b = ((B_002dd0b0 *)GetCameraDepthRange_2dd160());
    x = p[0];
    if (x < 0.0f) goto zeroA;
    if (x <= (f32)0xFFF) goto n1;
zeroA:
    return 0;
n1:
    y = p[1];
    if (y < 0.0f) goto zeroB;
    if (y <= (f32)0xFFF) goto n2;
zeroB:
    return 0;
n2:
    z = p[3];
    if (z < b->fC) goto zeroC;
    if (z <= b->f10) goto one;
zeroC:
    return 0;
one:
    return 1;
}
