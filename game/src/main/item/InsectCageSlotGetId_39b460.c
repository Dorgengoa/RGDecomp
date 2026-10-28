/* rgp:protos */
#define RGP_SELF_InsectCageSlotGetId_39b460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x1C. */

typedef struct Obj_FUN_0039b460 {
    u8 pad000[0x1C];
    s16 field;         /* +0x1C */
} Obj_FUN_0039b460;

s16 InsectCageSlotGetId_39b460(Obj_FUN_0039b460 *o)
{
    return o->field;
}
