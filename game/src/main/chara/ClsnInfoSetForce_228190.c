/* rgp:protos */
#define RGP_SELF_ClsnInfoSetForce_228190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0xC. */

typedef struct Obj_FUN_00228190 {
    u8 pad000[0xC];
    f32 field;         /* +0xC */
} Obj_FUN_00228190;

void ClsnInfoSetForce_228190(Obj_FUN_00228190 *o, f32 value)
{
    o->field = value;
}
