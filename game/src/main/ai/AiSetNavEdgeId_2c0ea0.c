/* rgp:protos */
#define RGP_SELF_AiSetNavEdgeId_2c0ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x298. */

typedef struct Obj_FUN_002c0ea0 {
    u8 pad000[0x298];
    s16 field;         /* +0x298 */
} Obj_FUN_002c0ea0;

void AiSetNavEdgeId_2c0ea0(Obj_FUN_002c0ea0 *o, s16 value)
{
    o->field = value;
}
