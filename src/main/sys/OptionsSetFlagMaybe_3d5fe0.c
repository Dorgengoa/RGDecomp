#include "types.h"

/* Both arms own their store; the SET arm is the cold block reached
   by the goto.  Proven at OptionsSetEventLogEnabled_3d5f60. */

typedef struct Obj_FUN_003d5fe0 {
    u8 pad000[0x22];
    s16 val;         /* +0x22 */
} Obj_FUN_003d5fe0;

void OptionsSetFlagMaybe_3d5fe0(Obj_FUN_003d5fe0 *o, s32 on)
{
    if (on != 0) {
        goto set;
    }
    o->val = 0;
    return;
set:
    o->val = 1;
}
