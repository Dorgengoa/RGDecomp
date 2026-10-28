/* rgp:protos */
#define RGP_SELF_ActInfoColPrmGetName_230910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_00230910 {
    s32 field;         /* +0x00 */
} Obj_FUN_00230910;

s32 ActInfoColPrmGetName_230910(Obj_FUN_00230910 *o)
{
    return o->field;
}
