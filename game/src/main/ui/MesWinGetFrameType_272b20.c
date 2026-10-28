/* rgp:protos */
#define RGP_SELF_MesWinGetFrameType_272b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x86. */

typedef struct Obj_FUN_00272b20 {
    u8 pad000[0x86];
    s16 field;         /* +0x86 */
} Obj_FUN_00272b20;

s16 MesWinGetFrameType_272b20(Obj_FUN_00272b20 *o)
{
    return o->field;
}
