/* rgp:protos */
#define RGP_SELF_MenuIconAllTexLoadRequest_2057f0 1
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

extern s32 D_0047E5B0;
extern s32 D_0047E5B8;
extern u8 D_0047E5BC;

s32 MenuIconAllTexLoadRequest_2057f0(void)
{
    s32 t0;
    s32 rv5;
    s32 r0;
    s32 r1;
    s32 t1;
    s32 r2;
    s32 rv4;
    s32 r3;

    t0 = D_0047E5B8;
    rv5 = rv4;
    if (t0 >= 0) {
        rv5 = 0;
    } else {
        D_0047E5BC = 0;
        D_0047E5B8 = -1;
        r0 = ((s32)GetLoaderMgr_1f59d0());
        r1 = GetDrawCtxNameTable_15de40();
        t1 = D_0047E5B0;
        r2 = LoaderRequestFile_1cd870(r0, t1, 0);
        D_0047E5B8 = r2;
        rv4 = 0;
        if (r2 == -1) {
            rv4 = 1;
        } else {
            r3 = LoaderQueueAppendSeparator_1cd670(r0);
            rv4 = 0;
        }
        rv5 = rv4;
    }
    return rv5;
}
