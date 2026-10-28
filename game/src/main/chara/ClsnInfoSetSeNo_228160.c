/* rgp:protos */
#define RGP_SELF_ClsnInfoSetSeNo_228160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x18. */

typedef struct Obj_FUN_00228160 {
    u8 pad000[0x18];
    s32 field;         /* +0x18 */
} Obj_FUN_00228160;

void ClsnInfoSetSeNo_228160(Obj_FUN_00228160 *o, s32 value)
{
    o->field = value;
}
