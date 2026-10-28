/* rgp:protos */
#define RGP_SELF_EvScriptCmdMapObjRegister_2ffa30 1
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

extern s32 D_0047F0C0;
extern s32 D_0047F0C4;
extern s32 D_0048286C;
extern s32 D_00482874;
extern u8 D_004E6B80[];

s32 EvScriptCmdMapObjRegister_2ffa30(s32 p0, s32 p1)
{
    s32 rv4;
    s32 t0;
    s32 t1;
    s32 r2;
    s32 t2;
    s32 t3;
    s32 r3;

    rv4 = 1;
    if (p1 != 0) {
        rv4 = 0;
    } else {
        t0 = D_0048286C;
        EvMapObjDataSetNameRefCount_366ae0(D_004E6B80, t0);
        t1 = D_00482874;
        EvMapObjDataSetNodeCount_366ab0(D_004E6B80, t1);
        r2 = ((s32)GetEventObjMgr_2d1960());
        t2 = D_0047F0C0;
        t3 = D_0047F0C4;
        r3 = EventObjMgrCreateMapObj_2ea010(r2, t2, t3, D_004E6B80);
        rv4 = 1;
    }
    return rv4;
}
