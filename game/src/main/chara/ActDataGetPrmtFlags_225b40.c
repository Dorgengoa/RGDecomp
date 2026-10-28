/* rgp:protos */
#define RGP_SELF_ActDataGetPrmtFlags_225b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s64 at +0x8. */

typedef struct Obj_FUN_00225b40 {
    u8 pad000[0x8];
    s64 field;         /* +0x8 */
} Obj_FUN_00225b40;

s64 ActDataGetPrmtFlags_225b40(Obj_FUN_00225b40 *o)
{
    return o->field;
}
