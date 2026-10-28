/* rgp:protos */
#define RGP_SELF_ActCfgTableSetMoveCount_223c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x5E. */

typedef struct Obj_FUN_00223c90 {
    u8 pad000[0x5E];
    s16 field;         /* +0x5E */
} Obj_FUN_00223c90;

void ActCfgTableSetMoveCount_223c90(Obj_FUN_00223c90 *o, s16 value)
{
    o->field = value;
}
