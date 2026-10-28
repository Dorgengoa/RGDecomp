/* rgp:protos */
#define RGP_SELF_NavNodeGetId_3119c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x18. */

typedef struct Obj_FUN_003119c0 {
    u8 pad000[0x18];
    s16 field;         /* +0x18 */
} Obj_FUN_003119c0;

s16 NavNodeGetId_3119c0(Obj_FUN_003119c0 *o)
{
    return o->field;
}
