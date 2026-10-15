#include "types.h"
/* insect 0x513E90 -- 8 B / 2 words.  `jr $31 / lh $2, 0x14($4)`:
 * a SIGNED halfword accessor (lh, not lhu -- the member is s16). */

typedef struct Obj {
    u8  pad00[0x14];
    s16 m14;                 /* +0x14 */
} Obj;

s16 insect_InsectTeamSlotGetEnemyKeyMaybe_513e90(Obj *o)
{
    return o->m14;
}
