/* rgp:protos */
#define RGP_SELF_ModelObjGetCBlurAlphaMaybe_1ad5a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x458. */

typedef struct Obj_FUN_001ad5a0 {
    u8 pad000[0x458];
    f32 field;         /* +0x458 */
} Obj_FUN_001ad5a0;

f32 ModelObjGetCBlurAlphaMaybe_1ad5a0(Obj_FUN_001ad5a0 *o)
{
    return o->field;
}
