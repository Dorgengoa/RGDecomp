/* rgp:protos */
#define RGP_SELF_IosGetFlags_1a1f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x38. */

typedef struct Obj_FUN_001a1f30 {
    u8 pad000[0x38];
    s16 field;         /* +0x38 */
} Obj_FUN_001a1f30;

s16 IosGetFlags_1a1f30(Obj_FUN_001a1f30 *o)
{
    return o->field;
}
