/* rgp:protos */
#define RGP_SELF_InsectCageMgrSetEnabled_39b180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0xA2. */

typedef struct Obj_FUN_0039b180 {
    u8 pad000[0xA2];
    u8 field;         /* +0xA2 */
} Obj_FUN_0039b180;

void InsectCageMgrSetEnabled_39b180(Obj_FUN_0039b180 *o, u8 value)
{
    o->field = value;
}
