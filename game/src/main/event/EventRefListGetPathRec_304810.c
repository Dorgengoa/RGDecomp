/* rgp:protos */
#define RGP_SELF_EventRefListGetPathRec_304810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_00304810 {
    s32 field;         /* +0x00 */
} Obj_FUN_00304810;

s32 EventRefListGetPathRec_304810(Obj_FUN_00304810 *o)
{
    return o->field;
}
