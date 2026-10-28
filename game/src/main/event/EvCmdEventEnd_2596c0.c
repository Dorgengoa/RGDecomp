/* rgp:protos */
#define RGP_SELF_EvCmdEventEnd_2596c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdEventEnd_2596c0(s32 p0, s32 p1)
{
    s64 v28;
    s64 v20;
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(s64)]; char m1[0x8 + sizeof(s64)]; char m2[0x8]; char m3[0x10]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(s64) <= (0x8) && (0x0) >= 0 ? 1 : -1];
    
    s32 rv9;
    s32 r0;
    s32 r1;
    s32 rv8;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 rv7;
    s32 r5;
    s32 r6;

    if (p1 != 0) {
        rv9 = 0;
    } else {
        r0 = (ScriptArgInitInt_26a1b0(&v28, -1), (s32)0);
        r1 = EvCmdEventPlayerEnd_260f30();
        if (r1 == 0) {
            rv8 = 0;
        } else {
            r2 = (ScriptArgInitInt_26a1b0(&(*(s64 *)(rgp_blk1 + 0x0)), 6), (s32)0);
            r3 = (ScriptArgInitInt_26a1b0(&(*(s64 *)(rgp_blk1 + 0x8)), -1), (s32)0);
            r4 = EvCmdMesWinLoadFile_265c00(&(*(s64 *)(rgp_blk1 + 0x0)), 2);
            if (r4 == 0) {
                rv7 = 0;
            } else {
                r5 = (ScriptArgInitInt_26a1b0(&v20, 4), (s32)0);
                r6 = EvCmdEventStackPop_25d140(&v20);
                rv7 = (r6 != 0);
            }
            rv8 = rv7;
        }
        rv9 = rv8;
    }
    return rv9;
}
