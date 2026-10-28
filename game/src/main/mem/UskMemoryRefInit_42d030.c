/* rgp:protos */
#define RGP_SELF_UskMemoryRefInit_42d030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s32 at +0x0. */

typedef struct Obj_FUN_0042d030 {
    s32 field;         /* +0x00 */
} Obj_FUN_0042d030;

void UskMemoryRefInit_42d030(Obj_FUN_0042d030 *o)
{
    o->field = 0;
}
