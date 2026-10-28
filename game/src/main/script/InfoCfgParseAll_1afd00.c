/* rgp:protos */
#define RGP_SELF_InfoCfgParseAll_1afd00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void InfoCfgParseAll_1afd00(s32 p0, s32 p1)
{
    InfoCfgParseThunk_1ac1e0((int)p0, (int)p1);
    ParamScriptParse_1afb30(p0, p1);
}
