/* rgp:protos */
#define RGP_SELF_EntryListGetCurIndex_3238b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x1A. */

typedef struct Obj_FUN_003238b0 {
    u8 pad000[0x1A];
    s16 field;         /* +0x1A */
} Obj_FUN_003238b0;

s16 EntryListGetCurIndex_3238b0(Obj_FUN_003238b0 *o)
{
    return o->field;
}
