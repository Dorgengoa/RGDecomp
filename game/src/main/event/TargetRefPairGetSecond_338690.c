/* rgp:protos */
#define RGP_SELF_TargetRefPairGetSecond_338690 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x30. */

typedef struct Obj_FUN_00338690 {
    u8 pad000[0x30];
    u8 sub[1];         /* +0x30 */
} Obj_FUN_00338690;

void *TargetRefPairGetSecond_338690(Obj_FUN_00338690 *o)
{
    return o->sub;
}
