/* rgp:protos */
#define RGP_SELF_EntryListGetCount_323680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x18. */

typedef struct Obj_FUN_00323680 {
    u8 pad000[0x18];
    s16 field;         /* +0x18 */
} Obj_FUN_00323680;

s16 EntryListGetCount_323680(Obj_FUN_00323680 *o)
{
    return o->field;
}
