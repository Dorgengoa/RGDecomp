/* rgp:protos */
#define RGP_SELF_OptionsSetCursorMemory_3d5fc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Both arms own their store; the SET arm is the cold block reached
   by the goto.  Proven at OptionsSetEventLogEnabled_3d5f60. */

typedef struct Obj_FUN_003d5fc0 {
    u8 pad000[0x26];
    s16 val;         /* +0x26 */
} Obj_FUN_003d5fc0;

void OptionsSetCursorMemory_3d5fc0(Obj_FUN_003d5fc0 *o, s32 on)
{
    if (on != 0) {
        goto set;
    }
    o->val = 0;
    return;
set:
    o->val = 1;
}
