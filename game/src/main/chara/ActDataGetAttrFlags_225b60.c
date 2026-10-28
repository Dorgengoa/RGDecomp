/* rgp:protos */
#define RGP_SELF_ActDataGetAttrFlags_225b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s64 at +0x0. */

typedef struct Obj_FUN_00225b60 {
    s64 field;         /* +0x00 */
} Obj_FUN_00225b60;

s64 ActDataGetAttrFlags_225b60(Obj_FUN_00225b60 *o)
{
    return o->field;
}
