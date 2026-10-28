/* rgp:protos */
#define RGP_SELF_NodeObjHasCollBounds_18e040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xAC. */

typedef struct Obj_FUN_0018e040 {
    u8 pad000[0xAC];
    s32 field;         /* +0xAC */
} Obj_FUN_0018e040;

s32 NodeObjHasCollBounds_18e040(Obj_FUN_0018e040 *o)
{
    return o->field;
}
