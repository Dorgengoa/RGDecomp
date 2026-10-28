/* rgp:protos */
#define RGP_SELF_EvCmdStreamChanStart_25ce70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E8 { s32 a; s32 b; };

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdStreamChanStart_25ce70(struct E8 *p0, s32 p1)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r5;

    r0 = ((s32)GetLoaderMgr_1f59d0());
    rv3 = 1;
    if (p1 == 2) {
        r1 = ScriptGetInt_26a2a0(p0++);
        rv3 = r1;
    }
    r5 = ScriptGetCodeAddr_26a200(p0);
    StreamStartChan_1cda90(r0, rv3, r5, 0);
    return 1;
}
