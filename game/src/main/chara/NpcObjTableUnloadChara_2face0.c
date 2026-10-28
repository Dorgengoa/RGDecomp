/* rgp:protos */
#define RGP_SELF_NpcObjTableUnloadChara_2face0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC8];
    s16 mC8;
    s16 mCA;
};

s32 NpcObjTableUnloadChara_2face0(s32 p0, struct Obj0 *p1)
{
    s32 r0;
    s32 r1;
    s16 t0;
    s32 r2;
    s32 rv4;
    s16 t1;
    s32 r3;
    s32 r5;
    s32 r6;
    s32 r7;

    r0 = ((s32)GetStaticScene_1c6c70());
    r1 = ((s32)GetCharaResMgr_1fdb60());
    t0 = p1->mC8;
    if (t0 != -1) {
        r2 = ((short)CharaDataGetRefCount_1f0480(r1, t0));
        rv4 = r2;
        if (r2 <= 0) {
            t1 = p1->mC8;
            r3 = (CharaResReleaseCharaDataWithTexIds_1f0fb0(r1, t1), (s32)0);
            rv4 = r3;
        }
        p1->mCA = 0;
        r5 = ((unsigned short)NpcObjSetFlag_2fcd90(p1, 1, 0));
        r6 = ((unsigned short)NpcObjSetFlag_2fcd90(p1, 4, 0));
        r7 = ((unsigned short)NpcObjSetFlag_2fcd90(p1, 8, 0));
        return r7;
    }
    return r1;
}
