/* rgp:protos */
#define RGP_SELF_MesWinSetPageFrames_271ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x1948. */

typedef struct Obj_FUN_00271ed0 {
    u8 pad000[0x1948];
    s32 field;         /* +0x1948 */
} Obj_FUN_00271ed0;

void MesWinSetPageFrames_271ed0(Obj_FUN_00271ed0 *o, s32 value)
{
    o->field = value;
}
