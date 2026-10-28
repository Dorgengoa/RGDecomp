/* rgp:protos */
#define RGP_SELF_NamedCompListSetCount_312480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x8. */

typedef struct Obj_FUN_00312480 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_00312480;

void NamedCompListSetCount_312480(Obj_FUN_00312480 *o, s32 value)
{
    o->field = value;
}
