/* rgp:protos */
#define RGP_SELF_NavNodeSetLinkName_3118b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x10. */

typedef struct Obj_FUN_003118b0 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_003118b0;

void NavNodeSetLinkName_3118b0(Obj_FUN_003118b0 *o, s32 value)
{
    o->field = value;
}
