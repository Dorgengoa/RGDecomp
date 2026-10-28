/* rgp:protos */
#define RGP_SELF_MesWinSetNumVar0_2769c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x1C18. */

typedef struct Obj_FUN_002769c0 {
    u8 pad000[0x1C18];
    s32 field;         /* +0x1C18 */
} Obj_FUN_002769c0;

void MesWinSetNumVar0_2769c0(Obj_FUN_002769c0 *o, s32 value)
{
    o->field = value;
}
