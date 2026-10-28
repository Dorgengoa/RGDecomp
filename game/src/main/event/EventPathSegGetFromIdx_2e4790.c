/* rgp:protos */
#define RGP_SELF_EventPathSegGetFromIdx_2e4790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x2. */

typedef struct Obj_FUN_002e4790 {
    u8 pad000[0x2];
    s16 field;         /* +0x2 */
} Obj_FUN_002e4790;

s16 EventPathSegGetFromIdx_2e4790(Obj_FUN_002e4790 *o)
{
    return o->field;
}
