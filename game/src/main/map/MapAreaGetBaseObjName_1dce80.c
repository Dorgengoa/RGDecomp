/* rgp:protos */
#define RGP_SELF_MapAreaGetBaseObjName_1dce80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x78. */

typedef struct Obj_FUN_001dce80 {
    u8 pad000[0x78];
    s32 field;         /* +0x78 */
} Obj_FUN_001dce80;

s32 MapAreaGetBaseObjName_1dce80(Obj_FUN_001dce80 *o)
{
    return o->field;
}
