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

extern s32 GetActionMgr_1fdb50(s32);
extern s32 AiGetTargetCharaId_2c0fd0(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaGetPos_2388a0(s32, Vec4 *);
extern void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
extern void VecNormalize_1cbb80(Vec4 *, Vec4 *);
extern s32 ActionMgrGetCharaList_233b40(s32);
extern s32 DListGetHead_42ea60(s32);
extern s32 DListGetNext_42eb30(s32);
extern s32 CharaGetId_214a80(s32);
extern s32 CharaGetAi_214a10(s32);
extern f32 VecDistSq_1cb3c0(Vec4 *, Vec4 *);
extern f32 SegmentProjectT_1ca340(Vec4 *, Vec4 *, Vec4 *);
extern void VecCopy_1cbe30(Vec4 *, Vec4 *);
extern f32 D_0047DB68;

s32 AiRouteCalcDirMaybe_2bd2c0(s32 arg0, s32 tgt, Vec4 *out, Vec4 *dst, f32 unused, f32 maxd)
{
    Vec4 posT;
    Vec4 posR;
    Vec4 posN;
    s32 p;
    s32 r;
    s32 it;
    s32 node;
    s32 x;
    s8 found;

    p = GetActionMgr_1fdb50(arg0);
    r = ActionMgrFindById_233b50(p, AiGetTargetCharaId_2c0fd0(arg0));
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
    it = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(p));
    node = 0;
    while (it != 0) {
        node = it + 0x10;
        it = DListGetNext_42eb30(it);
        if (CharaGetId_214a80(tgt) == CharaGetId_214a80(node)) {
            continue;
        }
        if (CharaGetId_214a80(r) == CharaGetId_214a80(node)) {
            continue;
        }
        x = CharaGetAi_214a10(node);
        if (CharaGetId_214a80(r) != AiGetTargetCharaId_2c0fd0(x)) {
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
