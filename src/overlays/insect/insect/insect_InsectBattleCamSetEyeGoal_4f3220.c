#include "types.h"
/* insect 0x004F3220 -- 136 bytes, 34 instructions, 14 float ops, no calls.
 *
 * Three parallel f32 arrays at +0x00 / +0x20 / +0x40 of one object, indexed by
 * the same scaled pointer, plus a scalar scale at +0x5FC8.  `c.le.s $f12,$f0`
 * with the VALUE in `fs` is the plain `t <= 0.0f` guard.
 */

typedef struct Obj {
    f32 m00[8];                     /* +0x00 */
    f32 m20[8];                     /* +0x20 */
    f32 m40[8];                     /* +0x40 */
    u8  pad60[0x5FC8 - 0x60];
    f32 m5FC8;                      /* +0x5FC8 */
} Obj;

void insect_InsectBattleCamSetEyeGoal_4f3220(Obj *o, f32 *src, s32 mode, f32 t)
{
    s32 i;

    if (t <= 0.0f) {
        t = 1.0f;
    }
    for (i = 0; i < 3; i++) {
        o->m20[i] = src[i];
        switch (mode) {
        case 0:
            o->m40[i] = t;
            break;
        case 2:
            o->m40[i] = (o->m20[i] - o->m00[i]) / t;
            break;
        }
        o->m40[i] = o->m40[i] * o->m5FC8;
    }
}
