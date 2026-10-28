/* rgp:protos */
#define RGP_SELF_EvObjAreaFadePreUpdate_2f8df0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The `sltu/xori` pair is a MATERIALISED boolean: only the DOUBLE
   negation `!((f & K) != 0)` reaches it -- `!(f & K)`, `(f & K) != 0`
   compared against zero, and three static-inline helper spellings all
   collapse to the same two-words-short object (measured, one sweep). */

/*rgp*/

void EvObjAreaFadePreUpdate_2f8df0(u8 *p)
{
    s32 f;
    s32 a;

    EvObjPreUpdateBase_2f9930(p);
    f = *(s32 *)(p + 0xD0);
    a = !((f & 0x80000000) != 0);
    if (a != 0) {
        *(s32 *)(p + 0xD0) = f | 0x8000;
    }
}
