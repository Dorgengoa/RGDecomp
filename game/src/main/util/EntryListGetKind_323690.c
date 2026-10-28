/* rgp:protos */
#define RGP_SELF_EntryListGetKind_323690 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x16. */

typedef struct Obj_FUN_00323690 {
    u8 pad000[0x16];
    s16 field;         /* +0x16 */
} Obj_FUN_00323690;

s16 EntryListGetKind_323690(Obj_FUN_00323690 *o)
{
    return o->field;
}
