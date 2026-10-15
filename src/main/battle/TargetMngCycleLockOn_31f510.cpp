#include "types.h"
#undef NULL
#define NULL 0
extern "C" {
typedef struct Vec4 { f32 x, y, z, w; } Vec4;
class Obj3bbBase {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual void d101();
    virtual void d102();
    virtual void d103();
    virtual void d104();
    virtual void d105();
    virtual void d106();
    virtual void d107();
    virtual void d108();
    virtual void d109();
    virtual void d110();
    virtual void d111();
    virtual void d112();
    virtual void d113();
    virtual void d114();
    virtual void d115();
    virtual void d116();
    virtual void d117();
    virtual void d118();
    virtual void d119();
    virtual void d120();
    virtual void d121();
    virtual void d122();
    virtual void d123();
    virtual void d124();
    virtual void d125();
    virtual void d126();
    virtual void d127();
    virtual void d128();
    virtual void d129();
    virtual void d130();
    virtual void d131();
    virtual void d132();
    virtual void d133();
    virtual void d134();
    virtual void d135();
    virtual void d136();
    virtual s32 IsActive();
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
void TargetMngSyncLeaderPose_320850(void);
Obj3bb *ObjMgrFindFiltered_3bb190(s32, s32, s32, s32, s32, s32 *, s32, s32);
extern f32 D_0047DCD8;

s32 TargetMngCycleLockOn_31f510(u8 *arg0, volatile s32 arg1) {
    s32 idx;
    s32 ids[67];
    Vec4 pos;
    Vec4 tgt;
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
    TargetMngSyncLeaderPose_320850();
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
    if (TargetRefResolve_2e5ed0(arg0 + 0xC0, 0) != 0 && TargetRefGetKind_2e7130(arg0 + 0xC0) == 4) {
        chr = TargetRefGetObjSlot_2e70e0(arg0 + 0xC0);
        curId = TargetRefGetId_2e7120(arg0 + 0xC0);
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
