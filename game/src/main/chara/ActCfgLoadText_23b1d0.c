/* rgp:protos */
#define RGP_SELF_ActCfgLoadText_23b1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
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

extern u8 D_0044CA20[];
extern s32 D_00481EEC;
extern s32 D_00481EF8;

s32 ActCfgLoadText_23b1d0(s32 p0, s32 p1, s32 p2)
{
    u128 v40[237];
    s32 rv14;
    s32 r0;
    s32 t0;
    s32 r1;
    s32 t1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;
    s32 r8;
    s32 r9;
    s32 r10;
    s32 r11;
    s32 r12;
    s32 t2;
    s32 r13;

    rv14 = 1;
    if (p0 == 0) {
        rv14 = 0;
    } else {
        D_00481EF8 = p2;
        r0 = ((s32)GetActionMgr_1fdb50());
        t0 = D_00481EF8;
        r1 = (ActionMgrRemoveCharaRef_2340b0(r0, t0), (s32)0);
        t1 = D_00481EF8;
        r2 = (ActionMgrRemoveActionTable_233f80(r0, t1), (s32)0);
        r3 = ActionMgrGetHeap_234910(r0);
        r4 = MemStackGetUsed_1c6cf0(r3);
        D_00481EEC = 0;
        r5 = (ScriptArenaInit_23fed0(), (s32)0);
        r6 = (ActCfgTablesReset_23fdd0(), (s32)0);
        r7 = ((s32)TextReaderCtor_15f140(v40));
        r8 = (BuildKeywordHashTable_15f270(v40, D_0044CA20), (s32)0);
        r9 = (TextReaderOpen_15f1b0(v40, p0, p1), (s32)0);
        r10 = TextReaderParseAll_15f3f0(v40);
        r11 = (ScriptArenaFree_23fe90(), (s32)0);
        r12 = (ActCfgTablesReset_23fdd0(), (s32)0);
        t2 = D_00481EF8;
        r13 = ((s32)ActionMgrFindTableByScopeId_233c20(r0, t2));
        rv14 = 1;
    }
    return rv14;
}
