/* rgp:protos */
#define RGP_SELF_AiSetWaitCounterMaybe_2c0e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x29A. */

typedef struct Obj_FUN_002c0e90 {
    u8 pad000[0x29A];
    s16 field;         /* +0x29A */
} Obj_FUN_002c0e90;

void AiSetWaitCounterMaybe_2c0e90(Obj_FUN_002c0e90 *o, s16 value)
{
    o->field = value;
}
