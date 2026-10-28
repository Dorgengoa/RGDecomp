/* rgp:protos */
#define RGP_SELF_PartyFindSlotOfId_3c3070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

typedef struct O3c { u8 pad[0x190]; s16 a[3]; s16 b[7]; } O3c;
s32 PartyFindSlotOfId_3c3070(O3c *arg0, s32 arg1)
{
    s32 temp_2;
    s32 var_3;
    s32 var_5;
    s32 var_4;

    if (arg1 < 0) {
        return -1;
    }
    temp_2 = PartyCountMembers_3c2010((s32)arg0, 1, 1);
    var_5 = 0;
    for (var_4 = 0; var_4 < temp_2; var_4++, var_5++) {
        if (arg0->a[var_4] == arg1) {
            return var_5;
        }
    }
    for (var_3 = 0; var_3 < 7; var_3++, var_5++) {
        if (arg0->b[var_3] == arg1) {
            return var_5;
        }
    }
    return -1;
}
