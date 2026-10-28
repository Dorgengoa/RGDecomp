/* rgp:protos */
#define RGP_SELF_LightningMgrCtorMaybe_2d6490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s32 at +0x0. */

typedef struct Obj_FUN_002d6490 {
    s32 field;         /* +0x00 */
} Obj_FUN_002d6490;

void LightningMgrCtorMaybe_2d6490(Obj_FUN_002d6490 *o)
{
    o->field = 0;
}
