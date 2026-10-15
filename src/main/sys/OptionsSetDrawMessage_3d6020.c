#include "types.h"

/* Both arms own their store; the SET arm is the cold block reached
   by the goto.  Proven at OptionsSetEventLogEnabled_3d5f60. */

typedef struct Obj_FUN_003d6020 {
    u8 pad000[0x1C];
    s16 val;         /* +0x1C */
} Obj_FUN_003d6020;

void OptionsSetDrawMessage_3d6020(Obj_FUN_003d6020 *o, s32 on)
{
    if (on != 0) {
        goto set;
    }
    o->val = 0;
    return;
set:
    o->val = 1;
}
