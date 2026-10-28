/* rgp:protos */
#define RGP_SELF_EventPathSegGetFlags_2e47a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u16 at +0x0. */

typedef struct Obj_FUN_002e47a0 {
    u16 field;         /* +0x00 */
} Obj_FUN_002e47a0;

u16 EventPathSegGetFlags_2e47a0(Obj_FUN_002e47a0 *o)
{
    return o->field;
}
