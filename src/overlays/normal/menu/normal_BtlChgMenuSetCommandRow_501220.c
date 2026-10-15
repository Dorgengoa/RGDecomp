#include "types.h"
/* normal 0x00501220 -- one-line setter into the gp byte table at gp-0xCA8.
 * The table is ADDRESS-TAKEN (`addiu $3,$28,-0xCA8`), so it must be declared
 * SMALL (<= 8 B) to stay in small data; the read side is normal_BtlChgMenuGetCommandRow_501230. */

extern u8 D_004844C8[8];          /* gp - 0xCA8 */

void normal_BtlChgMenuSetCommandRow_501220(s32 i, u8 v)
{
    D_004844C8[i] = v;
}
