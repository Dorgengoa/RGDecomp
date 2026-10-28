/* rgp:protos */
#define RGP_SELF_SkyCfgParse_17e190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0044A4C0[];
extern s32 D_004811AC;
extern s32 D_004811B0;
extern s32 D_004811B4;

void SkyCfgParse_17e190(s32 p0, s32 p1, s32 p2)
{
    u128 v30[237];

    D_004811AC = p0;
    D_004811B0 = 0;
    D_004811B4 = 0;
    if (p1 != 0) {
        if (p2 != 0) {
            goto ok;
        }
    }
    return;
ok:
    TextReaderCtor_15f140(v30);
    BuildKeywordHashTable_15f270(v30, D_0044A4C0);
    TextReaderOpen_15f1b0(v30, p1, p2);
    TextReaderParseAll_15f3f0(v30);
}
