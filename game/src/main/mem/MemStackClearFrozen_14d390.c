/* rgp:protos */
#define RGP_SELF_MemStackClearFrozen_14d390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s32 at +0x20. */

typedef struct Obj_FUN_0014d390 {
    u8 pad000[0x20];
    s32 field;         /* +0x20 */
} Obj_FUN_0014d390;

void MemStackClearFrozen_14d390(Obj_FUN_0014d390 *o)
{
    o->field = 0;
}
