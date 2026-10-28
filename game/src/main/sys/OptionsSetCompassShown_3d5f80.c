/* rgp:protos */
#define RGP_SELF_OptionsSetCompassShown_3d5f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Both arms own their store; the SET arm is the cold block reached
   by the goto.  Proven at OptionsSetEventLogEnabled_3d5f60. */

typedef struct Obj_FUN_003d5f80 {
    u8 pad000[0x2A];
    s16 val;         /* +0x2A */
} Obj_FUN_003d5f80;

void OptionsSetCompassShown_3d5f80(Obj_FUN_003d5f80 *o, s32 on)
{
    if (on != 0) {
        goto set;
    }
    o->val = 0;
    return;
set:
    o->val = 1;
}
