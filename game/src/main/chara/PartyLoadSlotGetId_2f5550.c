/* rgp:protos */
#define RGP_SELF_PartyLoadSlotGetId_2f5550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x0. */

typedef struct Obj_FUN_002f5550 {
    s16 field;         /* +0x00 */
} Obj_FUN_002f5550;

s16 PartyLoadSlotGetId_2f5550(Obj_FUN_002f5550 *o)
{
    return o->field;
}
