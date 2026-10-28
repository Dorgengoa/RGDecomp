/* rgp:protos */
#define RGP_SELF_TargetMngUnlock_31f4b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s32 at +0xC. */

typedef struct Obj_FUN_0031f4b0 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_0031f4b0;

void TargetMngUnlock_31f4b0(Obj_FUN_0031f4b0 *o)
{
    o->field = 0;
}
