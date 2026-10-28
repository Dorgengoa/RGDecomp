/* rgp:protos */
#define RGP_SELF_CharaGetEvObjContact_214990 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0xB5C. */

typedef struct Obj_FUN_00214990 {
    u8 pad000[0xB5C];
    u8 sub[1];         /* +0xB5C */
} Obj_FUN_00214990;

void *CharaGetEvObjContact_214990(Obj_FUN_00214990 *o)
{
    return o->sub;
}
