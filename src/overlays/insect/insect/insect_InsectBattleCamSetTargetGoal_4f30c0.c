#include "types.h"
/* insect 0x004F30C0 -- 136 bytes, 34 instructions, a leaf with no frame.
 * Three parallel f32[3] members at +0x10 / +0x30 / +0x50 and a scale at
 * +0x5FC8.  The inner dispatch is a `beq` INTO the arm (case 2) plus a
 * `beql` INTO the arm (case 0), so the compare chain 2/0 is the REVERSE of
 * the source case order 0/2.
 */

typedef struct Obj {
    u8  pad00[0x10];
    f32 m10[3];                     /* +0x10 */
    u8  pad1C[0x30 - 0x1C];
    f32 m30[3];                     /* +0x30 */
    u8  pad3C[0x50 - 0x3C];
    f32 m50[3];                     /* +0x50 */
    u8  pad5C[0x5FC8 - 0x5C];
    f32 m5FC8;                      /* +0x5FC8 */
} Obj;

void insect_InsectBattleCamSetTargetGoal_4f30c0(Obj *o, f32 *src, s32 mode, f32 v)
{
    s32 i;

    if (v <= 0.0f) {
        v = 1.0f;
    }
    for (i = 0; i < 3; i++) {
        o->m30[i] = src[i];
        switch (mode) {
        case 0:
            o->m50[i] = v;
            break;
        case 2:
            o->m50[i] = (o->m30[i] - o->m10[i]) / v;
            break;
        }
        o->m50[i] = o->m50[i] * o->m5FC8;
    }
}
