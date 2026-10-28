/* rgp:protos */
#define RGP_SELF_MapAreaGetGroundTypeMaybe_1dceb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x88. */

typedef struct Obj_FUN_001dceb0 {
    u8 pad000[0x88];
    s16 field;         /* +0x88 */
} Obj_FUN_001dceb0;

s16 MapAreaGetGroundTypeMaybe_1dceb0(Obj_FUN_001dceb0 *o)
{
    return o->field;
}
