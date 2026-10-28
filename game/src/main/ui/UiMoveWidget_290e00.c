/* rgp:protos */
#define RGP_SELF_UiMoveWidget_290e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R290e00 {
    u8  pad00[0x14];
    f32 f14;
    f32 f18;
    u8  pad1C[0x60 - 0x1C];
    f32 f60;
    f32 f64;
    f32 f68;
    f32 f6C;
    f32 f70;
    f32 f74;
    f32 f78;
    f32 f7C;
    s16 f80;
    s8  f82;
    s8  f83;
} R290e00;

/*rgp*/

void UiMoveWidget_290e00(s32 a0, s32 a1, s32 x, s32 y, s32 mode, f32 vx, f32 vy)
{
    R290e00 *r;

    r = ((R290e00 *)UiFindWidget_290460(a0, a1));
    if (r == 0) {
        return;
    }
    r->f60 = (f32)x;
    r->f64 = (f32)y;
    r->f80 = (s16)mode;
    r->f68 = vx;
    r->f6C = vy;
    if (mode == 2) {
        r->f68 = (r->f14 - r->f60) / vx;
        r->f6C = (r->f18 - r->f64) / vy;
    }
    if (mode == 3) {
        r->f7C = 0.0f;
        r->f78 = vx;
        r->f68 = (f32)x - r->f14;
        r->f6C = (f32)y - r->f18;
        r->f70 = 0.0f;
        r->f74 = 0.0f;
        if (r->f68 < 0.0f) {
            r->f82 = -1;
        } else {
            r->f82 = 1;
        }
        if (r->f6C < 0.0f) {
            r->f83 = -1;
        } else {
            r->f83 = 1;
        }
    }
}
