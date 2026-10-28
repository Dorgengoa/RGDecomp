/* rgp:protos */
#define RGP_SELF_MapPartTableGetId_1de200 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x0. */

typedef struct Obj_FUN_001de200 {
    s16 field;         /* +0x00 */
} Obj_FUN_001de200;

s16 MapPartTableGetId_1de200(Obj_FUN_001de200 *o)
{
    return o->field;
}
