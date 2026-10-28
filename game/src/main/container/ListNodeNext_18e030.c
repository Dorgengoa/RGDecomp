/* rgp:protos */
#define RGP_SELF_ListNodeNext_18e030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0018e030 {
    s32 field;         /* +0x00 */
} Obj_FUN_0018e030;

s32 ListNodeNext_18e030(Obj_FUN_0018e030 *o)
{
    return o->field;
}
