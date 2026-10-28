/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {
typedef struct Vec4 { f32 x, y, z, w; } Vec4;
class Obj3bbBase {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 IsActive() { return VCM0(s32, 0x22C); }
};
class Obj3bb : public Obj3bbBase {
public:
    s32 pad4;
    s32 pad8;
    s32 id;
};

f32 Atan2f_1291a8(f32, f32);
f32 WrapAngle_13c050(f32);
s32 ObjGetNthAttachPointPos_1ade20(s32, s32, s32, Vec4 *);
s32 ObjRecGetFlags_1c3d90(s32, s32, s32);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
s32 GetStaticScene_1c6c70(void);
s32 GetActionMgr_1fdb50(void);
void GetCharaResMgr_1fdb60(void);
u8 *GetGameData_1fede0(void);
u8 *ActionMgrFindById_233b50(s32, s32);
s32 TargetRefResolve_2e5ed0(u8 *, s32);
void TargetRefSetAttachPoint_2e65f0(u8 *, s32, s32, s32);
s32 TargetRefGetPos_2e6a60(u8 *, Vec4 *);
u8 *TargetRefGetObjSlot_2e70e0(u8 *);
s32 TargetRefGetId_2e7120(u8 *);
s32 TargetRefGetKind_2e7130(u8 *);
void TargetMngSyncLeaderPose_320850(void *);
Obj3bb *ObjMgrFindFiltered_3bb190(s32, s32, s32, s32, s32, s32 *, s32, s32);
extern f32 D_0047DCD8;

s32 TargetMngCycleLockOn_31f510(u8 *arg0, volatile s32 arg1) {
    s32 idx;
    s32 ids[67] __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Vec4 tgt __attribute__((aligned(16)));
    s32 count;
    s32 start;
    s32 best;
    s32 i;
    s32 mgr;
    u8 *chr;
    u8 *root;
    s32 curSub;
    f32 v;
    s32 tbl;
    s32 bestSub;
    Obj3bb *obj;
    s32 list;
    s32 j;
    s32 id;
    f32 baseAng;
    f32 bestVal;
    s32 curId;
    f32 sign;

    if (*(s32 *)(arg0 + 8) == 0) return 0;
    if (*(s32 *)(arg0 + 0) != 1) return 0;
    TargetMngSyncLeaderPose_320850((void *)arg0);
    mgr = GetStaticScene_1c6c70();
    GetCharaResMgr_1fdb60();
    tbl = GetActionMgr_1fdb50();
    root = GetGameData_1fede0();
    count = 0;
    start = -1;
    for (;;) {
        idx = -1;
        obj = ObjMgrFindFiltered_3bb190(*(s32 *)(root + 0x1C), -1, 1, 0, start, &idx, 0, 0);
        if (!obj || idx < 0) break;
        chr = ActionMgrFindById_233b50(tbl, obj->id);
        if (obj->IsActive() != 0) {
            if (chr != NULL && !(*(s32 *)(chr + 0xA44) & 0x40)) {
                ids[count++] = obj->id;
            }
        }
        start = idx + 1;
    }
    if (count <= 0) return 0;
    curId = -1;
    curSub = curId;
    if (TargetRefResolve_2e5ed0(arg0 + 0xC0, 0) != 0 && ((short)TargetRefGetKind_2e7130(arg0 + 0xC0)) == 4) {
        chr = TargetRefGetObjSlot_2e70e0(arg0 + 0xC0);
        curId = ((short)TargetRefGetId_2e7120(arg0 + 0xC0));
        curSub = *(s16 *)(chr + 0xA);
    }
    baseAng = 0.0f;
    if (TargetRefGetPos_2e6a60(arg0 + 0xC0, &pos) != 0) {
        baseAng = Atan2f_1291a8(pos.x - *(f32 *)(arg0 + 0x90), pos.z - *(f32 *)(arg0 + 0x98));
    }
    best = -1;
    bestVal = D_0047DCD8;
    bestSub = best;
    if (arg1 != 0) {
        sign = 1.0f;
    } else {
        sign = -1.0f;
    }
    for (i = 0; i < count; i++) {
        id = ids[i];
        if (ObjRecGetFlags_1c3d90(mgr, 1, id) & 0x20000) continue;
        list = ObjRecGetLiveObject_1c4a90(mgr, id);
        if (list == 0) continue;
        j = 0;
        while (ObjGetNthAttachPointPos_1ade20(list, 0x82, j, &tgt) != 0) {
            j++;
            if (id == curId && j - 1 == curSub) continue;
            v = sign * WrapAngle_13c050(Atan2f_1291a8(tgt.x - *(f32 *)(arg0 + 0x90), tgt.z - *(f32 *)(arg0 + 0x98)) - baseAng);
            if (v <= 0.0f) {
                v += D_0047DCD8;
            }
            if (v < bestVal) {
                best = id;
                bestVal = v;
                bestSub = j - 1;
            }
        }
    }
    if (best != -1) {
        TargetRefSetAttachPoint_2e65f0(arg0 + 0xC0, best, 0x82, bestSub);
        return 1;
    } else {
        return 0;
    }
}
}
