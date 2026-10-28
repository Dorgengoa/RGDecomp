/* rgp:protos */
#define RGP_SELF_InsectCageAdjTableParse_391720 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void memset(s32, s32, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047FF00;
extern s32 D_00483430;
extern s16 D_00483434;

void InsectCageAdjTableParse_391720(s32 p0, s32 p1, s32 p2)
{
    u128 v40[237];
    s32 r0;

    r0 = ((s32)MemStackNew_14e1b0(0xC00, p0));
    D_00483430 = r0;
    memset(r0, 0, 0xC00);
    D_00483434 = 0;
    TextReaderCtor_15f140(v40);
    BuildKeywordHashTable_15f270(v40, &D_0047FF00);
    TextReaderOpen_15f1b0(v40, p1, p2);
    TextReaderParseAll_15f3f0(v40);
    InsectCageRecTableParse_391320(p0, p1, p2);
}
