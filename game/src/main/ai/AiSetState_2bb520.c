/* rgp:protos */
#define RGP_SELF_AiSetState_2bb520 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0xAC. */

typedef struct Obj_FUN_002bb520 {
    u8 pad000[0xAC];
    s16 field;         /* +0xAC */
} Obj_FUN_002bb520;

void AiSetState_2bb520(Obj_FUN_002bb520 *o, s16 value)
{
    o->field = value;
}
