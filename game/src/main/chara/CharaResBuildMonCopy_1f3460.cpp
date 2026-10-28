/* rgp:protos */
#line 1
#include "types.h"

/* jalr $25 == C++ virtual dispatch; slot = 8 + 4*index. */

class VE {
    u8 pad_[0x1B0];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f44(f32 a0) { VCM(void, (void *, f32), 0x44, a0); }
};

class VB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f384() { return VCM0(s32, 0x384); }
};

struct St {
    s16 f0;
    s16 f2;
    s16 f4;
    u8  f6;
    u8  f7;
    u8  f8[4];
    char name[0x58];
    s16 f64;
};

struct P { u8 pad[0x6C]; s16 f6C; s16 f6E; s32 f70; };
struct Q { s32 f0; s32 f4; u8 pad8[0x20]; u8 f28; };
struct R { u8 pad[0x1C]; s32 f1C; };

extern "C" s32  GetCharaDataMgr_1fdb70(void);
extern "C" void GetCharaResMgr_1fdb60(void);
extern "C" s32  CharaDataGetLoadState_1ed5a0(s32, s16);
extern "C" P   *CharaDataFindById_1ed990(s32, s16);
extern "C" VE  *CharaDataGetNodeModel_1ed540(s32, s16, s32);
extern "C" s32  MemStackHeapAllocFront_14dd10(void *, s32);
extern "C" void MemStackClear_14dff0(char *);
extern "C" void MemStackInit_14d810(char *, s32, s32);
extern "C" u32  strlen(char *);
extern "C" char *strcpy(char *, char *);
extern "C" void GameSceneObjBindMaybe_1cfcd0(s32, s32, void *, s32);
extern "C" void ObjRecSetFlag2_1c3e80(s32, s32, s32);
extern "C" void ModelObjPlayMotionByName_1867a0(void *, char *, s32);
extern "C" Q   *ModelGetRootFrame_1511a0(void *);
extern "C" s32  ModelFindFrameIndexByName_151220(void *, char *);
extern "C" s32  ModelGetFrame_1511f0(void *, s32);
extern "C" void FrameSetDirty_14a5e0(Q *);
extern "C" s32  CharaDataGetKind4NodeDataMaybe_1ed460(s32, s16, s32, s32, s32);
extern "C" s32  MemStackAllocAligned64_14da10(char *, s32);
extern "C" s32  GetActionMgr_1fdb50(void);
extern "C" s32  ActionMgrFindById_233b50(s32, s32);
extern "C" s32  CharaGetAi_214a10(s32);
extern "C" void AiScriptLoad_2bbc50(s32, s32, s32, s32, s32);
extern "C" void AiResetState_2bbc30(s32);
extern "C" R   *GetGameData_1fede0(void);
extern "C" VB  *ObjFindById_3bb3a0(s32, s32);
extern "C" char D_0045B888[];
extern "C" char D_0045B890[];
extern "C" char D_0045B898[];

extern "C" void CharaResBuildMonCopy_1f3460(St *st, s32 ctx, void *heap)
{
    s32 h;
    VE *b;
    VE *c;
    s32 k;
    P *p;
    Q *q;
    VB *v;
    s32 r0;
    s32 r1;
    s32 r3;
    s32 r2;
    s32 t;

    h = GetCharaDataMgr_1fdb70();
    GetCharaResMgr_1fdb60();
    k = ((short)CharaDataGetLoadState_1ed5a0(h, st->f4));
    if (k == 2) {
        return;
    }
    if (k == 4) {
        st->f64 = 4;
        return;
    }
    b = 0;
    c = 0;
    p = CharaDataFindById_1ed990(h, st->f4);
    if (p != 0) {
        s32 ok = (p->f70 < 0) ^ 1;
        if (ok == 0) {
            b = CharaDataGetNodeModel_1ed540(h, st->f4, 0);
            if (b == 0) {
                st->f64 = 4;
                return;
            }
            p->f70 = st->f0;
            k = MemStackHeapAllocFront_14dd10(heap, 0x500);
            MemStackClear_14dff0(st->name);
            MemStackInit_14d810(st->name, k, 0x500);
            if (strlen(D_0045B888) <= 0xF) {
                strcpy(st->name, D_0045B888);
            }
            c = CharaDataGetNodeModel_1ed540(h, st->f4, 2);
            if (c == 0) {
                st->f64 = 4;
                return;
            }
        }
    }
    if (b != 0) {
        GameSceneObjBindMaybe_1cfcd0(ctx, st->f0, b, 0);
        ObjRecSetFlag2_1c3e80(ctx, 1, st->f0);
        ModelObjPlayMotionByName_1867a0(b, D_0045B890, 0);
        b->f44(0.0f);
        st->f6 = st->f6 | 1;
        GameSceneObjBindMaybe_1cfcd0(ctx, 0x9C, c, 0);
        ObjRecSetFlag2_1c3e80(ctx, 1, 0x9C);
        if (ModelGetRootFrame_1511a0(c) != 0) {
            t = ModelGetFrame_1511f0(b, ModelFindFrameIndexByName_151220(b, D_0045B898));
            q = ModelGetRootFrame_1511a0(c);
            q->f28 = 1;
            q->f4 = t;
            FrameSetDirty_14a5e0(q);
        }
        p = CharaDataFindById_1ed990(h, st->f4);
        if (p != 0) {
            p->f6C = p->f6C + 1;
        }
    }
    r0 = CharaDataGetKind4NodeDataMaybe_1ed460(h, st->f4, 0, 0, 0);
    r1 = MemStackAllocAligned64_14da10(st->name, 0x300);
    if (r0 != 0 && r1 == 0) {
        st->f64 = 4;
        return;
    }
    if (r0 != 0 && r1 != 0) {
        t = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), st->f0);
        if (t != 0) {
            t = CharaGetAi_214a10(t);
            if (t != 0) {
                AiScriptLoad_2bbc50(t, r0, r1, 0x300, 0);
                AiResetState_2bbc30(t);
            }
            st->f6 = st->f6 | 8;
        }
    }
    v = ObjFindById_3bb3a0(GetGameData_1fede0()->f1C, st->f0);
    if (v != 0 && v->f384() != 0) {
        r2 = CharaDataGetKind4NodeDataMaybe_1ed460(h, st->f4, 1, 0, 0);
        r3 = MemStackAllocAligned64_14da10(st->name, 0x100);
        if (r2 != 0 && r3 == 0) {
            st->f64 = 4;
            return;
        }
        if (r2 != 0 && r3 != 0) {
            t = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), st->f0);
            if (t != 0) {
                t = CharaGetAi_214a10(t);
                if (t != 0) {
                    AiScriptLoad_2bbc50(t, r2, r3, 0x100, 1);
                }
            }
        }
    }
    st->f6 = st->f6 | 0x80;
    st->f64 = 3;
}
