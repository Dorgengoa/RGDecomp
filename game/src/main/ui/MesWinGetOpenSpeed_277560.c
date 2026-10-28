/* rgp:protos */
#define RGP_SELF_MesWinGetOpenSpeed_277560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x98. */

typedef struct Obj_FUN_00277560 {
    u8 pad000[0x98];
    f32 field;         /* +0x98 */
} Obj_FUN_00277560;

f32 MesWinGetOpenSpeed_277560(Obj_FUN_00277560 *o)
{
    return o->field;
}
