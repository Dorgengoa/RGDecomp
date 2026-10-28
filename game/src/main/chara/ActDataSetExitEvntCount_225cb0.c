/* rgp:protos */
#define RGP_SELF_ActDataSetExitEvntCount_225cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x22. */

typedef struct Obj_FUN_00225cb0 {
    u8 pad000[0x22];
    s16 field;         /* +0x22 */
} Obj_FUN_00225cb0;

void ActDataSetExitEvntCount_225cb0(Obj_FUN_00225cb0 *o, s16 value)
{
    o->field = value;
}
