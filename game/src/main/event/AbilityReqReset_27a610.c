/* rgp:protos */
#define RGP_SELF_AbilityReqReset_27a610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004D7C70;
extern s32 D_004D7C74;
extern s32 D_004D7C78;
extern u8 D_004D7C7C;
extern u8 D_004D7C8C[];

void AbilityReqReset_27a610(void)
{
    *(s32 *)&D_004D7C70 = -1;
    *(s32 *)&D_004D7C74 = -1;
    *(s32 *)&D_004D7C78 = 0;
    *(u8 *)&D_004D7C7C = 0;
    ExecInfoInit_3a7940(D_004D7C8C);
}
