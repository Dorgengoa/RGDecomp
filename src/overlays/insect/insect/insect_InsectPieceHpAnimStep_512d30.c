#include "types.h"
/* insect 0x00512D30 -- 212 bytes, no calls.  A scroll stepper: f4D is the
 * signed velocity, f4E the dwell counter, f1A the position and f1C the
 * clamp. */

typedef struct Obj {
    u8  pad0000[0x1A];
    s16 f1A;                        /* +0x1A */
    s16 f1C;                        /* +0x1C */
    u8  pad001E[0x4D - 0x1E];
    s8  f4D;                        /* +0x4D */
    s8  f4E;                        /* +0x4E */
} Obj;

s32 insect_InsectPieceHpAnimStep_512d30(Obj *o)
{
    if (o->f4D == 0) {
        return 1;
    }
    o->f4E++;
    if (o->f4E >= 5) {
        if (o->f4D < 0) {
            o->f4D--;
        }
        if (o->f4D > 0) {
            o->f4D++;
        }
        o->f4E = 0;
    }
    o->f1A += o->f4D;
    if (o->f4D > 0) {
        if (o->f1C <= o->f1A) {
            o->f1A = o->f1C;
            o->f4D = 0;
            return 1;
        }
    } else if (o->f4D < 0) {
        if (o->f1C >= o->f1A) {
            o->f1A = o->f1C;
            o->f4D = 0;
            return 1;
        }
    }
    return 0;
}
