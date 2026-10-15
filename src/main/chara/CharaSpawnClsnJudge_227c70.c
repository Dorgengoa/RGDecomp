#include "types.h"

typedef struct {
    s32 pad0[4];
    u8 sub[0x84];
    f32 x, y, z;
    s32 w;
    s32 pad1[3];
    void *vt;
    u8 rest[0x80C];
} Big;

extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 StrEqualNonNull_1ca6c0(s32, void *);
extern s32 GetCurrentScene_1f5be0(void);
extern void *GetGameData_1fede0(void);
extern s32 CharaGetCurActionName_2123d0(s32);
extern s32 CharaGetActionKind_213840(s32);
extern s32 CharaGetTargetRef_214a30(s32);
extern s32 CharaGetId_214a80(s32);
extern s32 ActCfgTableFindClsnByName_222be0(s32, s32);
extern s32 ActCfgTableFindVertByName_222cd0(s32, s32);
extern s32 NodeRefObjMotionGateCloneAndRegister_228690(Big *);
extern s32 ActInfoClsnGetLinCount_230950(s32);
extern s32 ActInfoClsnGetPntCount_230960(s32);
extern s32 ActInfoClsnGetLinList_230970(s32);
extern s32 ActInfoClsnGetPntList_230980(s32);
extern s32 ActInfoClsnGetFlags_230990(s32);
extern s32 TargetRefResolve_2e5ed0(s32, s32);
extern s32 *TargetRefGetAttachFrame_2e70a0(s32);
extern s32 TargetRefGetId_2e7120(s32);
extern s32 TargetRefGetKind_2e7130(s32);
extern s32 TargetMngHasTargetId_313bf0(void);
extern void NodeRefObjMotionGateSet_318360(Big *, s32, s32, f32, f32);
extern void NodeRefObjMotionGateCtor_3183f0(Big *, s32, s32, s32, f32);
extern void NodeRefObjAddClsnLin_318c30(Big *, s32, s32, f32, f32, f32, f32);
extern void NodeRefObjAddClsnPnt_318ca0(Big *, s32, s32, f32, f32);
extern s32 NodeRefListAddAt_318d00(Big *, s32, s32, s32, s32, f32, f32, f32);
extern s32 NodeRefListAddDefault_318df0(Big *, s32, s32, s32, s32);
extern void ExecInfoInitFromObj_3a7790(void *, s32, s32);
extern void ExecInfoInitFromChara_3a7830(void *, s32, s32, s32, s32);
extern u8 D_0045D078[];
extern u8 D_0045D088[];
extern u8 D_0045D090[];
extern u8 D_00471AA0[];

s32 CharaSpawnClsnJudge_227c70(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg)
{
    Big big;
    s32 p;
    s32 ret;
    s32 x;
    s32 b;
    s32 h;
    s32 c;
    void *sub;
    s32 e;
    s32 i;
    s32 r;
    s32 n;
    s32 j;
    s32 id;
    s32 m;
    s32 a;
    s32 k;

    if (arg2 == 0 || arg1 == 0) {
        return -1;
    }
    h = ActCfgTableFindClsnByName_222be0(arg2, *(s32 *)(arg0 + 4));
    if (h == 0) {
        return -1;
    }
    id = CharaGetId_214a80(arg1);
    if (ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), id) == 0) {
        return -1;
    }
    NodeRefObjMotionGateCtor_3183f0(&big, 1, id, ActInfoClsnGetFlags_230990(h) | 1, 1800.0f);
    sub = (void *)((u32)big.sub);
    if (id >= 0 && id < 0xC) {
        k = -1;
        switch (CharaGetActionKind_213840(arg1)) {
        case 7:
        case 9:
        case 12:
            k = 0;
            break;
        case 8:
        case 10:
            k = 1;
            break;
        case 13:
        case 14:
            switch (id) {
            case 1:
                k = 0;
                if (StrEqualNonNull_1ca6c0(CharaGetCurActionName_2123d0(arg1), D_0045D078) == 0) {
                    break;
                }
            case 6:
                k = 1;
                break;
            default:
                k = 0;
                break;
            }
            break;
        case 11:
            k = 0;
            break;
        }
        if (StrEqualNonNull_1ca6c0(*(s32 *)(arg0 + 8), D_0045D088) != 0) {
            k = -1;
        }
        if (StrEqualNonNull_1ca6c0(*(s32 *)(arg0 + 8), D_0045D090) != 0) {
            k = -1;
        }
        ExecInfoInitFromChara_3a7830(sub, id, k, 0, *(s32 *)(arg0 + 8));
    } else if (id >= 0x80 && id < 0x9C) {
        ExecInfoInitFromObj_3a7790(sub, id, *(s32 *)(arg0 + 8));
    }
    NodeRefObjMotionGateSet_318360(&big, id, arg3, farg, *(f32 *)arg0);
    big.x = *(f32 *)(arg0 + 0xC);
    big.y = *(f32 *)(arg0 + 0x10);
    big.z = *(f32 *)(arg0 + 0x14);
    big.w = *(s32 *)(arg0 + 0x18);
    n = ActInfoClsnGetPntCount_230960(h);
    p = ActInfoClsnGetPntList_230980(h);
    for (i = 0; i < n; i++, p += 0x10) {
        e = ActCfgTableFindVertByName_222cd0(arg2, *(s32 *)(p + 8));
        if (e == 0) {
            continue;
        }
        x = -1;
        if (*(s32 *)(e + 8) != -0x1E) {
            x = NodeRefListAddAt_318d00(&big, id, *(s32 *)(e + 8), *(s32 *)(e + 4), -1, *(f32 *)(e + 0xC), *(f32 *)(e + 0x10), *(f32 *)(e + 0x14));
        } else {
            void *g = GetGameData_1fede0();
            if (*(s32 *)(arg1 + 0xA44) & 0x8000) {
                if (*(s16 *)(*(s32 *)((s32)g + 0x18) + 0x18E) == CharaGetId_214a80(arg1) && TargetMngHasTargetId_313bf0() != 0) {
                    c = CharaGetTargetRef_214a30(arg1);
                    if (TargetRefGetKind_2e7130(c) == 4 && TargetRefResolve_2e5ed0(c, 0) != 0) {
                        s32 *q = TargetRefGetAttachFrame_2e70a0(c);
                        x = NodeRefListAddDefault_318df0(&big, TargetRefGetId_2e7120(c), -1, *q, -1);
                    }
                }
            }
        }
        NodeRefObjAddClsnPnt_318ca0(&big, x, *(u8 *)(p + 0xC), *(f32 *)p, *(f32 *)(p + 4));
    }
    m = ActInfoClsnGetLinCount_230950(h);
    r = ActInfoClsnGetLinList_230970(h);
    for (j = 0; j < m; j++, r += 0x18) {
        a = ActCfgTableFindVertByName_222cd0(arg2, *(s32 *)(r + 8));
        if (a == 0) {
            continue;
        }
        b = ActCfgTableFindVertByName_222cd0(arg2, *(s32 *)(r + 0xC));
        if (b == 0) {
            continue;
        }
        x = NodeRefListAddAt_318d00(&big, id, *(s32 *)(a + 8), *(s32 *)(a + 4), -1, *(f32 *)(a + 0xC), *(f32 *)(a + 0x10), *(f32 *)(a + 0x14));
        NodeRefObjAddClsnLin_318c30(&big, x, NodeRefListAddAt_318d00(&big, id, *(s32 *)(b + 8), *(s32 *)(b + 4), -1, *(f32 *)(b + 0xC), *(f32 *)(b + 0x10), *(f32 *)(b + 0x14)), *(f32 *)r, *(f32 *)(r + 4), *(f32 *)(r + 0x10), *(f32 *)(r + 0x14));
    }
    ret = NodeRefObjMotionGateCloneAndRegister_228690(&big);
    big.vt = D_00471AA0;
    return ret;
}
