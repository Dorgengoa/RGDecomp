/* rgp:protos */
#define RGP_SELF_SwordTrailStop_2d7620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s16 at +0x0. */

typedef struct Obj_FUN_002d7620 {
    s16 field;         /* +0x00 */
} Obj_FUN_002d7620;

void SwordTrailStop_2d7620(Obj_FUN_002d7620 *o)
{
    o->field = 0;
}
