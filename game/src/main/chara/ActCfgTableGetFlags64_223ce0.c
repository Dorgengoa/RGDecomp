/* rgp:protos */
#define RGP_SELF_ActCfgTableGetFlags64_223ce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s64 at +0x0. */

typedef struct Obj_FUN_00223ce0 {
    s64 field;         /* +0x00 */
} Obj_FUN_00223ce0;

s64 ActCfgTableGetFlags64_223ce0(Obj_FUN_00223ce0 *o)
{
    return o->field;
}
