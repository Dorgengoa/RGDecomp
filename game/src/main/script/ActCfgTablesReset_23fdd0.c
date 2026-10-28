/* rgp:protos */
#define RGP_SELF_ActCfgTablesReset_23fdd0 1
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

extern s32 D_00481E70;
extern s32 D_00481E74;
extern s32 D_00481E78;
extern s32 D_00481E7C;
extern s32 D_00481E80;
extern s32 D_00481E84;
extern s32 D_00481E88;
extern s32 D_00481E8C;
extern s32 D_00481E90;
extern s32 D_00481E94;
extern s32 D_00481E98;
extern s32 D_00481E9C;
extern s32 D_00481EA0;
extern s32 D_00481EA4;
extern s32 D_00481EA8;
extern s32 D_00481EAC;
extern s32 D_00481EB0;
extern s32 D_00481EB4;
extern s32 D_00481EB8;
extern s32 D_00481EBC;
extern s32 D_00481EC0;
extern s32 D_00481EC4;
extern s32 D_00481EC8;
extern s32 D_00481ECC;
extern s32 D_00481ED0;
extern s32 D_00481ED4;
extern s32 D_00481ED8;
extern s32 D_00481EDC;
extern s32 D_00481EFC;
extern s32 D_00481F00;
extern u8 D_004BCDB0[];
extern u8 D_004BCDE0[];
extern u8 D_004BCE20[];

void ActCfgTablesReset_23fdd0(void)
{
    ScriptArenaReset_23ff10();
    D_00481EFC = 0;
    D_00481E90 = 0;
    D_00481E94 = 0;
    D_00481E98 = 0;
    D_00481E9C = 0;
    D_00481EA0 = 0;
    D_00481EA4 = 0;
    D_00481EA8 = 0;
    D_00481EAC = 0;
    D_00481EB0 = 0;
    D_00481EB4 = 0;
    D_00481EB8 = 0;
    D_00481EBC = 0;
    D_00481EC0 = 0;
    D_00481EC4 = 0;
    D_00481EC8 = 0;
    D_00481ECC = 0;
    D_00481ED0 = 0;
    D_00481ED4 = 0;
    D_00481ED8 = 0;
    D_00481EDC = 0;
    D_00481E70 = 0;
    D_00481E74 = 0;
    D_00481E78 = 0;
    D_00481E7C = 0;
    D_00481E80 = 0;
    D_00481E84 = 0;
    D_00481E88 = 0;
    D_00481E8C = 0;
    CharaNormalTableClear_225a80(D_004BCDB0);
    CharaTableClear_225740(D_004BCDE0);
    ActCfgTableReset_225160(D_004BCE20);
    D_00481F00 = 0;
}
