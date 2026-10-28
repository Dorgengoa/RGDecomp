/* rgp:protos */
#define RGP_SELF_CharaGetSpeedScale_238240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x414. */

typedef struct Obj_FUN_00238240 {
    u8 pad000[0x414];
    f32 field;         /* +0x414 */
} Obj_FUN_00238240;

f32 CharaGetSpeedScale_238240(Obj_FUN_00238240 *o)
{
    return o->field;
}
