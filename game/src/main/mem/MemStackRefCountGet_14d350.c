/* rgp:protos */
#define RGP_SELF_MemStackRefCountGet_14d350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x24. */

typedef struct Obj_FUN_0014d350 {
    u8 pad000[0x24];
    s32 field;         /* +0x24 */
} Obj_FUN_0014d350;

s32 MemStackRefCountGet_14d350(Obj_FUN_0014d350 *o)
{
    return o->field;
}
