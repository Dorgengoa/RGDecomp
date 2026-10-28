/* rgp:protos */
#define RGP_SELF_PtrArrayIsAllocated_30d350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is the s32 at +0x0 non-zero? */

typedef struct Obj_FUN_0030d350 {
    s32 field;         /* +0x0 */
} Obj_FUN_0030d350;

u8 PtrArrayIsAllocated_30d350(Obj_FUN_0030d350 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
