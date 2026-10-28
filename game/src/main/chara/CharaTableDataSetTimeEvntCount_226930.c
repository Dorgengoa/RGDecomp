/* rgp:protos */
#define RGP_SELF_CharaTableDataSetTimeEvntCount_226930 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x26. */

typedef struct Obj_FUN_00226930 {
    u8 pad000[0x26];
    s16 field;         /* +0x26 */
} Obj_FUN_00226930;

void CharaTableDataSetTimeEvntCount_226930(Obj_FUN_00226930 *o, s16 value)
{
    o->field = value;
}
