/* rgp:protos */
#define RGP_SELF_AiRouteCalcDirMaybe_2bd2c0 1
#include "port/game_protos.h"
#line 1
/* PARKED s17b: not attempted. Linked-list scan (DListGetHead_42ea60/DListGetNext_42eb30
   walk) comparing several CharaGetId_214a80/CharaGetAi_214a10 keys, then a 3-way
   vec-distance compare (VecDistSq_1cb3c0/SegmentProjectT_1ca340) picking between two
   candidate points. Several m2c `?` locals (spC0/spB0/spA0) are almost
   certainly the same small vec/point struct as neighboring matched units --
   worth checking sibling FUN_001cbxxx callers for the real type before
   drafting. Not attempted this lane. */
/* s49m: MATCH */
#include "types.h"
#include "vec.h"

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
/*rgp*/
extern f32 D_0047DB68;

s32 AiRouteCalcDirMaybe_2bd2c0(s32 arg0, s32 tgt, Vec4 *out, Vec4 *dst, f32 unused, f32 maxd)
{
    Vec4 posT __attribute__((aligned(16)));
    Vec4 posR __attribute__((aligned(16)));
    Vec4 posN __attribute__((aligned(16)));
    s32 p;
    s32 r;
    s32 it;
    s32 node;
    s32 x;
    s8 found;

    p = ((s32)GetActionMgr_1fdb50());
    r = ((s32)ActionMgrFindById_233b50(p, AiGetTargetCharaId_2c0fd0(arg0)));
    if (tgt == 0) {
        return r;
    }
    CharaGetPos_2388a0(tgt, &posT);
    if (r != 0) {
        CharaGetPos_2388a0(r, &posR);
    } else {
        VecSub_1cbd00(dst, out, &posT);
        VecNormalize_1cbb80(dst, dst);
        return 0;
    }
    found = 0;
    it = DListGetHead_42ea60(((s32)ActionMgrGetCharaList_233b40(p)));
    node = 0;
    while (it != 0) {
        node = it + 0x10;
        it = DListGetNext_42eb30(it);
        if (((short)CharaGetId_214a80(tgt)) == ((short)CharaGetId_214a80(node))) {
            continue;
        }
        if (((short)CharaGetId_214a80(r)) == ((short)CharaGetId_214a80(node))) {
            continue;
        }
        x = ((s32)CharaGetAi_214a10(node));
        if (((short)CharaGetId_214a80(r)) != AiGetTargetCharaId_2c0fd0(x)) {
            continue;
        }
        found = 1;
        CharaGetPos_2388a0(node, &posN);
        break;
    }
    if (found == 0 || maxd < VecDistSq_1cb3c0(&posR, &posN)) {
        VecSub_1cbd00(dst, out, &posT);
        VecNormalize_1cbb80(dst, dst);
        return r;
    }
    if (SegmentProjectT_1ca340(&posN, &posT, &posR) < D_0047DB68) {
        VecCopy_1cbe30(out, &posT);
    } else {
        VecCopy_1cbe30(out, &posN);
    }
    VecSub_1cbd00(dst, &posN, &posT);
    VecNormalize_1cbb80(dst, dst);
    return node;
}
