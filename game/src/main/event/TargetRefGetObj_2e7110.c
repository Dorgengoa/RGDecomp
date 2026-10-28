/* rgp:protos */
#define RGP_SELF_TargetRefGetObj_2e7110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_002e7110 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_002e7110;

s32 TargetRefGetObj_2e7110(Obj_FUN_002e7110 *o)
{
    return o->field;
}
