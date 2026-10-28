/* rgp:protos */
#define RGP_SELF_EvScriptArgsFindMapObj_3026d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvScriptArgsFindMapObj_3026d0(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 rv8;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;

    r0 = ((s32)GetMapMgr_201a90());
    r1 = ((signed char)ScriptArgGetTag_302df0(p0));
    rv8 = r7;
    if (r1 == 2) {
        r2 = ScriptArgGetStr_302cb0(p0);
        r3 = ScriptArgGetStr_302cb0(p1);
        r4 = MapFindObjInAreaByName_1e4470(r0, r2, r3);
        rv8 = r4;
    } else {
        r5 = ScriptArgGetInt_302d70(p0);
        r6 = ScriptArgGetStr_302cb0(p1);
        r7 = MapFindObjInAreaById_1e44b0(r0, r5, r6);
        rv8 = r7;
    }
    return rv8;
}
