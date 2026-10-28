/* rgp:protos */
#define RGP_SELF_EvCmdBgmPlayTrack_260050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E8 { s32 a; s32 b; };

/*rgp*/
/*rgp*/

s32 EvCmdBgmPlayTrack_260050(struct E8 *p0, s32 p1)
{
    s32 r0;
    s32 v;

    v = 1;
    r0 = ScriptGetInt_26a2a0(p0++);
    if (p1 >= 2) {
        v = ScriptGetInt_26a2a0(p0);
    }
    BgmPlayTrack_2075e0(r0, (v != 0));
    return 1;
}
