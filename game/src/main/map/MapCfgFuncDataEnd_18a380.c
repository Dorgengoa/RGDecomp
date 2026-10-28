/* rgp:protos */
#define RGP_SELF_MapCfgFuncDataEnd_18a380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004812D4;
extern s32 D_004812D8;
extern s32 D_004812DC;

s32 MapCfgFuncDataEnd_18a380(void)
{
    D_004812DC = 0;
    D_004812D8 = 0;
    D_004812D4 = (D_004812D4 + 1);
    return 1;
}
