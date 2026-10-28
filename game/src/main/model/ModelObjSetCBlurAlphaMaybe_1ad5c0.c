/* rgp:protos */
#define RGP_SELF_ModelObjSetCBlurAlphaMaybe_1ad5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x458. */

typedef struct Obj_FUN_001ad5c0 {
    u8 pad000[0x458];
    f32 field;         /* +0x458 */
} Obj_FUN_001ad5c0;

void ModelObjSetCBlurAlphaMaybe_1ad5c0(Obj_FUN_001ad5c0 *o, f32 value)
{
    o->field = value;
}
