#include "types.h"
/* insect 0x00512C80 -- 80 bytes, 20 instructions.
 *
 * `dsll32`/`dsra32 ..,24` is an explicit `(s8)` cast of an s32 local, not an
 * s8 local: the decremented value stays in a word register and is narrowed
 * only for the compare. */

typedef struct Obj {
    u8 pad00[0x4F];
    s8 m4F;                         /* +0x4F */
} Obj;

extern s32 insect_InsectPieceTestStatus_513280(Obj *o, s32 k);

void insect_InsectPieceUseSpecialCharge_512c80(Obj *o)
{
    s32 t;

    if (insect_InsectPieceTestStatus_513280(o, 0x20) == 0) {
        t = o->m4F - 1;
        o->m4F = t;
        if ((s8)t <= 0) {
            o->m4F = 0;
        }
    }
}
