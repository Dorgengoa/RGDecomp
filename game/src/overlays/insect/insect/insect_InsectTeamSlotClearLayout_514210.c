/* rgp:protos */
#define RGP_SELF_insect_InsectTeamSlotClearLayout_514210 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514210 -- 44 bytes, 11 instructions, a leaf with no frame.
 * The stored constant is `addiu $5,$0,0xFF`, i.e. 0xFF into a u8 array, not
 * -1 into an s8 one.
 */

typedef struct Obj {
    u8  pad00[0xA];
    u8  mA[5];                      /* +0x0A */
} Obj;

void insect_InsectTeamSlotClearLayout_514210(Obj *o)
{
    s32 i;

    for (i = 0; i < 5; i++) {
        o->mA[i] = 0xFF;
    }
}
