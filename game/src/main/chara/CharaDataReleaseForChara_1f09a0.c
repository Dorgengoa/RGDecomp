/* rgp:protos */
#define RGP_SELF_CharaDataReleaseForChara_1f09a0 1
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

s32 CharaDataReleaseForChara_1f09a0(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv4;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = ((unsigned char)IsPcCharaId_1f52d0(p1));
    rv4 = r0;
    if (r0 != 0) {
        r1 = ((s32)GetCharaDataMgr_1fdb70());
        r2 = PcDefGetCharaDataId_1f5060(p1);
        r3 = (CharaDataReleaseById_1ed850(r1, (r2 + -0x3DD)), (s32)0);
        rv4 = r3;
    }
    return rv4;
}
