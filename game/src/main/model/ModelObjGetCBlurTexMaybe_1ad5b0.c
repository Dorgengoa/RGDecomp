/* rgp:protos */
#define RGP_SELF_ModelObjGetCBlurTexMaybe_1ad5b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x454. */

typedef struct Obj_FUN_001ad5b0 {
    u8 pad000[0x454];
    s32 field;         /* +0x454 */
} Obj_FUN_001ad5b0;

s32 ModelObjGetCBlurTexMaybe_1ad5b0(Obj_FUN_001ad5b0 *o)
{
    return o->field;
}
