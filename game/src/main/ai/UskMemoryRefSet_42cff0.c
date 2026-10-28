/* rgp:protos */
#define RGP_SELF_UskMemoryRefSet_42cff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x0. */

typedef struct Obj_FUN_0042cff0 {
    s32 field;         /* +0x00 */
} Obj_FUN_0042cff0;

void UskMemoryRefSet_42cff0(Obj_FUN_0042cff0 *o, s32 value)
{
    o->field = value;
}
