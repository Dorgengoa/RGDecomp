/* rgp:protos */
#define RGP_SELF_InfoCfgModelCmd_1ab910 1
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

extern s32 D_0049D390;
extern s32 D_0049D398;
extern s32 D_0049D418;

s32 InfoCfgModelCmd_1ab910(s32 p0)
{
    s32 v68[2];
    s32 t0;
    s32 t1;
    s32 r0;
    s32 t2;
    s32 r1;
    s32 r2;
    s32 rv6;
    s32 r3;
    s32 r4;
    s32 r5;

    t0 = D_0049D390;
    t1 = D_0049D398;
    r0 = GetDrawCtx_15de80();
    t2 = D_0049D418;
    if (t1 == 0 || t2 == 0) {
        return 0;
    }
    r1 = SlotGetInt_15f720(p0);
    r2 = ((s32)ArchiveGetFileData_181dd0(t0, r1, 0));
    rv6 = 1;
    if (r2 == 0) {
        rv6 = 0;
    } else {
        v68[0] = 0;
        r3 = ModelResRelocate_14bfd0(v68, r2);
        r4 = ModelBuildFrames_1506c0(t2, v68, r0, t1);
        r5 = (ObjAllocPartArrays_1ac780(t2, 4, t1), (s32)0);
        rv6 = 1;
    }
    return rv6;
}
