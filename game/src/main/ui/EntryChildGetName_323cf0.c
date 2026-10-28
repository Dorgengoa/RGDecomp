/* rgp:protos */
#define RGP_SELF_EntryChildGetName_323cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_00323cf0 {
    s32 field;         /* +0x00 */
} Obj_FUN_00323cf0;

s32 EntryChildGetName_323cf0(Obj_FUN_00323cf0 *o)
{
    return o->field;
}
