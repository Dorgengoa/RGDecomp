/* rgp:protos */
#define RGP_SELF_EvObjGetAreaId_2f8f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0xE2. */

typedef struct Obj_FUN_002f8f30 {
    u8 pad000[0xE2];
    s16 field;         /* +0xE2 */
} Obj_FUN_002f8f30;

s16 EvObjGetAreaId_2f8f30(Obj_FUN_002f8f30 *o)
{
    return o->field;
}
