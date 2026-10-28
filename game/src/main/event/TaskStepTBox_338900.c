/* rgp:protos */
#define RGP_SELF_TaskStepTBox_338900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482C40;
extern u8 D_00482C4A;
extern s32 D_00482C4C;

void TaskStepTBox_338900(void)
{
    s32 r0;
    s32 r1;
    u8 t0;
    s32 t1;

    r0 = TreasureBoxPoolStep_338d40(&D_00482C40);
    r1 = GetGameMode_1f59c0();
    if (r1 == 6) {
        t0 = D_00482C4A;
        if ((((u64)(((s64)t0) << 0x3E)) >> 0x3F) != 0) {
            t1 = D_00482C4C;
            D_00482C4C = (t1 + 1);
            if ((t1 + 1) < 0x5A) {
                return;
            }
            D_00482C4C = 0;
            return;
        }
    }
    D_00482C4C = -1;
}
