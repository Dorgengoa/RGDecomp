/* rgp:protos */
#define RGP_SELF_NavGraphGetAreaId_310e80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x10C. */

typedef struct Obj_FUN_00310e80 {
    u8 pad000[0x10C];
    s16 field;         /* +0x10C */
} Obj_FUN_00310e80;

s16 NavGraphGetAreaId_310e80(Obj_FUN_00310e80 *o)
{
    return o->field;
}
