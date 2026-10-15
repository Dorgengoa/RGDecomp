#include "types.h"
/* insect 0x513E80 -- 8 B / 2 words.  `jr $31 / lh $2, 0x16($4)`:
 * a SIGNED halfword accessor (lh, not lhu -- the member is s16). */

typedef struct Obj {
    u8  pad00[0x16];
    s16 m16;                 /* +0x16 */
} Obj;

s16 insect_InsectTeamSlotGetEnemyRowMaybe_513e80(Obj *o)
{
    return o->m16;
}
