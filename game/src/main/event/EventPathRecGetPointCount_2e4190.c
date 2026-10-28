/* rgp:protos */
#define RGP_SELF_EventPathRecGetPointCount_2e4190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x18. */

typedef struct Obj_FUN_002e4190 {
    u8 pad000[0x18];
    s16 field;         /* +0x18 */
} Obj_FUN_002e4190;

s16 EventPathRecGetPointCount_2e4190(Obj_FUN_002e4190 *o)
{
    return o->field;
}
