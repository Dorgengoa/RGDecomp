/* rgp:protos */
#define RGP_SELF_CharaNormalTableGetCount_225810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x2C. */

typedef struct Obj_FUN_00225810 {
    u8 pad000[0x2C];
    s16 field;         /* +0x2C */
} Obj_FUN_00225810;

s16 CharaNormalTableGetCount_225810(Obj_FUN_00225810 *o)
{
    return o->field;
}
