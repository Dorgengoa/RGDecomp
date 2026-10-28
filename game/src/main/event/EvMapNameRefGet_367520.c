/* rgp:protos */
#define RGP_SELF_EvMapNameRefGet_367520 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_00367520 {
    s32 field;         /* +0x00 */
} Obj_FUN_00367520;

s32 EvMapNameRefGet_367520(Obj_FUN_00367520 *o)
{
    return o->field;
}
