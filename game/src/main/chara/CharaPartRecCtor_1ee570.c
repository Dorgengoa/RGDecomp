/* rgp:protos */
#define RGP_SELF_CharaPartRecCtor_1ee570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaPartRecCtor_1ee570(s32 p0)
{
    s32 r2;

    ListNodeInit_1efa20(p0);
    MemStackCtor_14e030((p0 + 0xC));
    r2 = (CharaDataSubRecInit_1eeab0(p0), (s32)0);
    return p0;
}
