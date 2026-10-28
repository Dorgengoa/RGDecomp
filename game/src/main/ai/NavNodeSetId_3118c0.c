/* rgp:protos */
#define RGP_SELF_NavNodeSetId_3118c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x18. */

typedef struct Obj_FUN_003118c0 {
    u8 pad000[0x18];
    s16 field;         /* +0x18 */
} Obj_FUN_003118c0;

void NavNodeSetId_3118c0(Obj_FUN_003118c0 *o, s16 value)
{
    o->field = value;
}
