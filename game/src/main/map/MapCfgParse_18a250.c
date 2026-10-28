/* rgp:protos */
#define RGP_SELF_MapCfgParse_18a250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
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

extern u8 D_0044A630[];
extern s32 D_00481240;
extern s32 D_00481250;
extern s32 D_00481254;
extern s32 D_00481258;
extern s32 D_0048125C;
extern s32 D_004812CC;
extern s32 D_004812D0;
extern s32 D_004812D4;
extern s32 D_004812D8;
extern s32 D_004812DC;
extern s32 D_004812E4;
extern s32 D_004812E8;

void MapCfgParse_18a250(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    u128 v40[237];
    f32 r4;

    D_0048125C = p3;
    D_004812E8 = p4;
    D_00481254 = 0;
    D_00481258 = 0;
    D_00481250 = p0;
    D_004812CC = 0;
    D_004812D0 = 0;
    D_004812D4 = 0;
    D_004812DC = 0;
    D_004812D8 = 0;
    D_004812E4 = 0;
    TextReaderCtor_15f140(v40);
    BuildKeywordHashTable_15f270(v40, D_0044A630);
    TextReaderOpen_15f1b0(v40, p1, p2);
    TextReaderParseAll_15f3f0(v40);
    r4 = VecLength_13d4a0(&D_00481240);
    if (r4 > 0.0f) {
        NodeSetTranslation_1866b0(p0, &D_00481240);
        return;
    }
}
