/* rgp:protos */
#define RGP_SELF_AttackChainCfgParse_1f93c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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

extern u8 D_0044B620[];
extern s32 D_0047E4B4;
extern s32 D_0047E4B8;
extern s32 D_0047E4BC;
extern s32 D_0047E4C0;
extern u8 D_00481A98;
extern u8 D_004B86C0[];

u8 AttackChainCfgParse_1f93c0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    u128 v40[237];
    s32 r4;

    D_0047E4B4 = p2;
    D_0047E4BC = -1;
    D_0047E4C0 = -1;
    D_0047E4B8 = p3;
    D_00481A98 = 0;
    TextReaderCtor_15f140(v40);
    BuildKeywordHashTable_15f270(v40, D_0044B620);
    TextReaderOpen_15f1b0(v40, p0, p1);
    TextReaderParseAll_15f3f0(v40);
    r4 = ((short)AttackChainGetInputCount_382e90(D_004B86C0));
    return (p3 == r4);
}
