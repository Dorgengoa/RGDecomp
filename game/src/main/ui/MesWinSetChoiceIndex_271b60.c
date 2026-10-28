/* rgp:protos */
#define RGP_SELF_MesWinSetChoiceIndex_271b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x1C24. */

typedef struct Obj_FUN_00271b60 {
    u8 pad000[0x1C24];
    s32 field;         /* +0x1C24 */
} Obj_FUN_00271b60;

void MesWinSetChoiceIndex_271b60(Obj_FUN_00271b60 *o, s32 value)
{
    o->field = value;
}
