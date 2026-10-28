/* rgp:protos */
#define RGP_SELF_EvTargetSetIsEnabled_3368c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is the s8 at +0x116 non-zero? */

typedef struct Obj_FUN_003368c0 {
    u8 pad000[0x116];
    s8 field;         /* +0x116 */
} Obj_FUN_003368c0;

u8 EvTargetSetIsEnabled_3368c0(Obj_FUN_003368c0 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
