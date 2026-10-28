/* rgp:protos */
#define RGP_SELF_EvMapObjDataSetNameRefCount_366ae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x2FA. */

typedef struct Obj_FUN_00366ae0 {
    u8 pad000[0x2FA];
    s16 field;         /* +0x2FA */
} Obj_FUN_00366ae0;

void EvMapObjDataSetNameRefCount_366ae0(Obj_FUN_00366ae0 *o, s16 value)
{
    o->field = value;
}
