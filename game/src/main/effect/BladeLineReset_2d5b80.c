/* rgp:protos */
#define RGP_SELF_BladeLineReset_2d5b80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s32 at +0x0. */

typedef struct Obj_FUN_002d5b80 {
    s32 field;         /* +0x00 */
} Obj_FUN_002d5b80;

void BladeLineReset_2d5b80(Obj_FUN_002d5b80 *o)
{
    o->field = 0;
}
