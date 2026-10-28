/* rgp:protos */
#define RGP_SELF_MinimapSubGetArray_32ae80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0032ae80 {
    s32 field;         /* +0x00 */
} Obj_FUN_0032ae80;

s32 MinimapSubGetArray_32ae80(Obj_FUN_0032ae80 *o)
{
    return o->field;
}
