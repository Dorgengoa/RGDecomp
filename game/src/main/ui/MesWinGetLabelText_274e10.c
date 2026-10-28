/* rgp:protos */
#define RGP_SELF_MesWinGetLabelText_274e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x1950. */

typedef struct Obj_FUN_00274e10 {
    u8 pad000[0x1950];
    s32 field;         /* +0x1950 */
} Obj_FUN_00274e10;

s32 MesWinGetLabelText_274e10(Obj_FUN_00274e10 *o)
{
    return o->field;
}
