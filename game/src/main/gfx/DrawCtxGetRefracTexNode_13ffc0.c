/* rgp:protos */
#define RGP_SELF_DrawCtxGetRefracTexNode_13ffc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x3BD8. */

typedef struct Obj_FUN_0013ffc0 {
    u8 pad000[0x3BD8];
    u8 sub[1];         /* +0x3BD8 */
} Obj_FUN_0013ffc0;

void *DrawCtxGetRefracTexNode_13ffc0(Obj_FUN_0013ffc0 *o)
{
    return o->sub;
}
