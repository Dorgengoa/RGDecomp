#include "types.h"

typedef struct Wave {
    u8 pad0[0xC];
    f32 t;          /* 0x0C */
    f32 period;     /* 0x10 */
    f32 phase;      /* 0x14 */
    s8 b18;         /* 0x18 */
    s8 kind;        /* 0x19 */
    s16 mode;       /* 0x1A */
    f32 f1C;        /* 0x1C */
} Wave;

extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern f32 WrapAngle_13c050(f32);
extern f32 D_0047D1FC;
extern f32 D_0047D804;

f32 CharaTintGetLevel_21f350(Wave *w)
{
    f32 r;
    s16 k;
    f32 t;
    f32 h;
    f32 q;

    r = 0.0f;
    if (w->b18 <= 0 && w->mode != 0) {
        if (w->mode == 4) {
            return 1.0f;
        }
        r = 0.5f * (1.0f - Cosf_128d30(WrapAngle_13c050(D_0047D804 * w->f1C / 30.0f)));
    } else {
        switch (w->kind) {
        case 1:
            r = Sinf_128fd0(WrapAngle_13c050(w->phase * (D_0047D1FC * (w->t / w->period))));
            r = (r < 0.0f) ? -r : r;
            break;
        case 2:
            r = Cosf_128d30(WrapAngle_13c050((w->phase - 0.5f) * (D_0047D1FC * (w->t / w->period))));
            r = (r < 0.0f) ? -r : r;
            break;
        case 3:
            h = 0.5f * w->period / w->phase;
            q = w->period / w->phase;
            if (w->period - q * (f32)(s32)(w->period / q) < h) {
                r = 0.0f;
            } else {
                r = 1.0f;
            }
            break;
        case 4:
            r = 1.0f;
            break;
        }
    }
    return r;
}
