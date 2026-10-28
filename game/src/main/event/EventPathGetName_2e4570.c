/* rgp:protos */
#define RGP_SELF_EventPathGetName_2e4570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_002e4570 {
    s32 field;         /* +0x00 */
} Obj_FUN_002e4570;

s32 EventPathGetName_2e4570(Obj_FUN_002e4570 *o)
{
    return o->field;
}
