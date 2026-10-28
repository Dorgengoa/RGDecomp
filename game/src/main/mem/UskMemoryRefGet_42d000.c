/* rgp:protos */
#define RGP_SELF_UskMemoryRefGet_42d000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0042d000 {
    s32 field;         /* +0x00 */
} Obj_FUN_0042d000;

s32 UskMemoryRefGet_42d000(Obj_FUN_0042d000 *o)
{
    return o->field;
}
