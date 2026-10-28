/* rgp:protos */
#define RGP_SELF_MesWinIsNameShown_271380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x1DC4. */

typedef struct Obj_FUN_00271380 {
    u8 pad000[0x1DC4];
    s16 field;         /* +0x1DC4 */
} Obj_FUN_00271380;

s16 MesWinIsNameShown_271380(Obj_FUN_00271380 *o)
{
    return o->field;
}
