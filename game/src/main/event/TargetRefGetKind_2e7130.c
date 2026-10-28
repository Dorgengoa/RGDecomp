/* rgp:protos */
#define RGP_SELF_TargetRefGetKind_2e7130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x0. */

typedef struct Obj_FUN_002e7130 {
    s16 field;         /* +0x00 */
} Obj_FUN_002e7130;

s16 TargetRefGetKind_2e7130(Obj_FUN_002e7130 *o)
{
    return o->field;
}
