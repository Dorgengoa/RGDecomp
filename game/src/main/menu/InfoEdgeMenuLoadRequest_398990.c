/* rgp:protos */
#define RGP_SELF_InfoEdgeMenuLoadRequest_398990 1
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

extern u8 D_00464390[];
extern s32 D_0047FF64;
extern s32 D_0047FF68;
extern s32 D_004835B0;
extern u8 D_004835B4;

s32 InfoEdgeMenuLoadRequest_398990(void)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = ((s32)GetLoaderMgr_1f59d0());
    D_0047FF64 = -1;
    D_0047FF68 = 0;
    D_004835B4 = 0;
    D_004835B0 = 0;
    r1 = LoaderRequestFile_1cd870(r0, D_00464390, 0);
    D_0047FF64 = r1;
    if (r1 != -1) {
        r2 = ((s32)GetWorldDataMgr_1fedf0());
        WorldDataMgrRelease_3f0320(r2, 1);
        WorldDataMgrSetPurposeSource_3f02b0(r2, 9, 0, 0);
        return (s32)LoaderQueueAppendSeparator_1cd670(r0);
        
    }
    return r1;
}
