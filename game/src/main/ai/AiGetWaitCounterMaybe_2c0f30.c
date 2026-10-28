/* rgp:protos */
#define RGP_SELF_AiGetWaitCounterMaybe_2c0f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x29A. */

typedef struct Obj_FUN_002c0f30 {
    u8 pad000[0x29A];
    s16 field;         /* +0x29A */
} Obj_FUN_002c0f30;

s16 AiGetWaitCounterMaybe_2c0f30(Obj_FUN_002c0f30 *o)
{
    return o->field;
}
