/* rgp:protos */
#define RGP_SELF_CharaClearActionGaugeUsed_214000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the u8 at +0xA28. */

typedef struct Obj_FUN_00214000 {
    u8 pad000[0xA28];
    u8 field;         /* +0xA28 */
} Obj_FUN_00214000;

void CharaClearActionGaugeUsed_214000(Obj_FUN_00214000 *o)
{
    o->field = 0;
}
