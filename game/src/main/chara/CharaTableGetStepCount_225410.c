/* rgp:protos */
#define RGP_SELF_CharaTableGetStepCount_225410 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x30. */

typedef struct Obj_FUN_00225410 {
    u8 pad000[0x30];
    s16 field;         /* +0x30 */
} Obj_FUN_00225410;

s16 CharaTableGetStepCount_225410(Obj_FUN_00225410 *o)
{
    return o->field;
}
