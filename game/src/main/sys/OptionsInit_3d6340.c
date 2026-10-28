/* rgp:protos */
#define RGP_SELF_OptionsInit_3d6340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483938;
extern s32 D_0048393C;

void OptionsInit_3d6340(s32 p0)
{
    D_00483938 = 0;
    D_0048393C = 0;
    OptionsResetDefaults_3d62c0(p0);
}
