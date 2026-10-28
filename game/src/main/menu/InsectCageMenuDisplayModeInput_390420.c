/* rgp:protos */
#define RGP_SELF_InsectCageMenuDisplayModeInput_390420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483360;
extern u8 D_004B2570[];

s32 InsectCageMenuDisplayModeInput_390420(void)
{
    s32 r0;
    s32 rv9;
    s32 r1;
    s32 rv8;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 rv7;
    s32 r5;
    s32 r6;

    r0 = BitArrayTest_384320(&D_00483360, 6);
    rv9 = r0;
    if (r0 != 0) {
        r1 = PadIsTriggered_1839f0(D_004B2570, 4);
        rv8 = rv7;
        if (r1 != 0) {
            r2 = (InsectCageMenuDisplayModePrev_388e60(), (s32)0);
            r3 = (PlayMenuSe_289ef0(0xB), (s32)0);
            rv8 = r3;
        } else {
            r4 = PadIsTriggered_1839f0(D_004B2570, 8);
            rv7 = 0;
            if (r4 != 0) {
                r5 = (InsectCageMenuDisplayModeNext_388e70(), (s32)0);
                r6 = (PlayMenuSe_289ef0(0xB), (s32)0);
                rv7 = r6;
            }
            rv8 = rv7;
        }
        rv9 = rv8;
    }
    return 1;
}
