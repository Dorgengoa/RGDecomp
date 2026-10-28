/* rgp:protos */
#define RGP_SELF_EvCmdMenuInsectResultOpen_25ef80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045F020[];
extern u8 D_0045F040[];

s32 EvCmdMenuInsectResultOpen_25ef80(void)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetLoadedOverlayId_1c3200();
    if (r0 != 5) {
        return 1;
    }
    r1 = TaskSetEnabled_27c2a0(1, D_0045F020);
    r2 = TaskSetEnabled_27c2a0(1, D_0045F040);
    return 1;
}
