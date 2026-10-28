/* rgp:protos */
#define RGP_SELF_ActCfgTableSetNullCount_223c80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x60. */

typedef struct Obj_FUN_00223c80 {
    u8 pad000[0x60];
    s16 field;         /* +0x60 */
} Obj_FUN_00223c80;

void ActCfgTableSetNullCount_223c80(Obj_FUN_00223c80 *o, s16 value)
{
    o->field = value;
}
