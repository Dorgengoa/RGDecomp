/* rgp:protos */
#define RGP_SELF_CharaTableSetStepCount_225400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x30. */

typedef struct Obj_FUN_00225400 {
    u8 pad000[0x30];
    s16 field;         /* +0x30 */
} Obj_FUN_00225400;

void CharaTableSetStepCount_225400(Obj_FUN_00225400 *o, s16 value)
{
    o->field = value;
}
