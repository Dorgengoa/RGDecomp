#include "types.h"

typedef struct T312640 {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10;
} T312640;

extern s32 ActionWindowOverlaps_228450(void);

void MovCfgMoveItemEval_312640(T312640 *s, f32 *out, f32 x, f32 y)
{
    f32 lo;
    f32 hi;
    f32 b0;
    f32 b1;

    if (s->f00 >= s->f04 || ActionWindowOverlaps_228450() == 0) {
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = 0.0f;
        out[3] = 0.0f;
    } else {
        b0 = s->f00;
        lo = x;
        hi = lo + y;
        if (lo < b0) {
            lo = b0;
        }
        b1 = s->f04;
        if (hi > b1) {
            hi = b1;
        }
        if (lo < 0.0f) {
            lo = 0.0f;
        }
        if (hi > 1.0f) {
            hi = 1.0f;
        }
        hi = hi - lo;
        hi = hi / (b1 - b0);
        out[0] = hi * s->f08;
        out[1] = hi * s->f0C;
        out[2] = hi * s->f10;
        out[3] = 0.0f;
    }
}
