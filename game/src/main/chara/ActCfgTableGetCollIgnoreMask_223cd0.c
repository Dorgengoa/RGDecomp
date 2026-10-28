/* rgp:protos */
#define RGP_SELF_ActCfgTableGetCollIgnoreMask_223cd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x10. */

typedef struct Obj_FUN_00223cd0 {
    u8 pad000[0x10];
    s16 field;         /* +0x10 */
} Obj_FUN_00223cd0;

s16 ActCfgTableGetCollIgnoreMask_223cd0(Obj_FUN_00223cd0 *o)
{
    return o->field;
}
