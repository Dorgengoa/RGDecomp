/* rgp:protos */
#define RGP_SELF_MapIdIndexGetMaxId_1ddbf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x8. */

typedef struct Obj_FUN_001ddbf0 {
    u8 pad000[0x8];
    s16 field;         /* +0x8 */
} Obj_FUN_001ddbf0;

s16 MapIdIndexGetMaxId_1ddbf0(Obj_FUN_001ddbf0 *o)
{
    return o->field;
}
