/* rgp:protos */
#define RGP_SELF_AiSetState_2bbc40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0xAC. */

typedef struct Obj_FUN_002bbc40 {
    u8 pad000[0xAC];
    s16 field;         /* +0xAC */
} Obj_FUN_002bbc40;

void AiSetState_2bbc40(Obj_FUN_002bbc40 *o, s16 value)
{
    o->field = value;
}
