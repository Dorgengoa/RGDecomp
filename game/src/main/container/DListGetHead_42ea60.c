/* rgp:protos */
#define RGP_SELF_DListGetHead_42ea60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0042ea60 {
    s32 field;         /* +0x00 */
} Obj_FUN_0042ea60;

s32 DListGetHead_42ea60(Obj_FUN_0042ea60 *o)
{
    return o->field;
}
