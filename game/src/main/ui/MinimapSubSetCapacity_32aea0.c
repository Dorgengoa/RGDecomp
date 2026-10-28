/* rgp:protos */
#define RGP_SELF_MinimapSubSetCapacity_32aea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0xA. */

typedef struct Obj_FUN_0032aea0 {
    u8 pad000[0xA];
    s16 field;         /* +0xA */
} Obj_FUN_0032aea0;

void MinimapSubSetCapacity_32aea0(Obj_FUN_0032aea0 *o, s16 value)
{
    o->field = value;
}
