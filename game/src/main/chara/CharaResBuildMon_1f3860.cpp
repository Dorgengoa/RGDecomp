/* rgp:protos */
#line 1
#include "types.h"

/* jalr $25 == C++ virtual dispatch; slot = 8 + 4*index. */

class VE {
    u8 pad_[0x1B0];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f44(f32 a0) { VCM(void, (void *, f32), 0x44, a0); }
    
    
    
    
    void f58() { VCM0(void, 0x58); }
    void f5C() { VCM0(void, 0x5C); }
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
    void *f8;
    char name[0x28];
    s32 f34;
    u8  pad38[0x2C];
    s16 f64;
    u8  b0 : 1;
    u8  b1 : 7;
};

struct P { u8 pad[0x6C]; s16 f6C; s16 f6E; s32 f70; };
struct R { u8 pad[0x1C]; s32 f1C; };
struct M { u8 pad[0x2C]; s32 f2C; };
struct N { u8 pad[0x4FC]; s32 f4FC; u8 pad500[0x38]; s32 f538; s32 f53C; };

extern "C" void CharaResBuildMonCopy_1f3460(St *, s32, void *);
extern "C" s32  GetCharaDataMgr_1fdb70(void);
extern "C" void GetCharaResMgr_1fdb60(void);
extern "C" s32  CharaDataGetLoadState_1ed5a0(s32, s16);
extern "C" P   *CharaDataFindById_1ed990(s32, s16);
extern "C" VE  *CharaDataGetNodeModel_1ed540(s32, s16, s32);
extern "C" void *MemStackHeapAllocFront_14dd10(void *, s32);
extern "C" void MemStackHeapFree_14dcb0(void *, s32);
extern "C" void MemStackClear_14dff0(char *);
extern "C" void MemStackInit_14d810(char *, void *, s32);
extern "C" u32  strlen(char *);
extern "C" char *strcpy(char *, char *);
extern "C" void *RecStackPush_1c4240(s32, s32);
extern "C" M   *RecStackGetSlot_1c4330(s32, void *);
extern "C" void ModelObjExCtor_1c4920(void *, int, int, int);
extern "C" void Character2ResetMaybe_1aef80(void *);
extern "C" void ModelObjExCopy_1aff40(void *, void *, void *);
extern "C" void RecStackPop_1c4140(s32, void *);
extern "C" void *MemStackNew_14e230(s32, char *);
extern "C" s32  GetEffectMgr_2d9040(void);
extern "C" void GameSceneObjBindMaybe_1cfcd0(s32, s32, void *, s32);
extern "C" void ObjRecSetFlag2_1c3e80(s32, s32, s32);
extern "C" void ModelObjPlayMotionByName_1867a0(void *, char *, s32);
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
extern "C" char D_0045B8A8[];
extern "C" u8 D_00470F50[];
extern "C" s32 D_0047E180;

extern "C" void CharaResBuildMon_1f3860(St *st, s32 ctx, void *heap)
{
    u8 obj[0x790] __attribute__((aligned(16)));
    VE *e;
    P *p;
    void *buf;
    void *hnd;
    s32 h;
    VE *b;
    M *mo;
    N *nw;
    s32 sz;
    s32 n;
    s32 r0;
    s32 r1;
    s32 r3;
    s32 r2;
    s32 t;
    s32 u;
    VB *v;

    if (st->f2 == 0x2F11) {
        CharaResBuildMonCopy_1f3460(st, ctx, heap);
        return;
    }
    h = GetCharaDataMgr_1fdb70();
    GetCharaResMgr_1fdb60();
    t = ((short)CharaDataGetLoadState_1ed5a0(h, st->f4));
    if (t == 2) {
        return;
    }
    if (t == 4) {
        st->f64 = 4;
        return;
    }
    b = 0;
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
            buf = MemStackHeapAllocFront_14dd10(heap, 0x500);
            if (buf == 0) {
                st->f64 = 4;
                return;
            }
            MemStackClear_14dff0(st->name);
            MemStackInit_14d810(st->name, buf, 0x500);
            if (strlen(D_0045B888) <= 0xF) {
                strcpy(st->name, D_0045B888);
            }
        }
    }
    if (b == 0) {
        if ((e = CharaDataGetNodeModel_1ed540(h, st->f4, 0)) != 0) {
            if (st->f34 != 0) {
                MemStackHeapFree_14dcb0(heap, st->f34);
                MemStackClear_14dff0(st->name);
            }
            hnd = RecStackPush_1c4240(ctx, 0);
            mo = RecStackGetSlot_1c4330(ctx, hnd);
            if (mo == 0) {
                st->f64 = 4;
                return;
            }
            ModelObjExCtor_1c4920(obj, 0, 0, 0);
            *(void **)(obj + 0x1B0) = D_00470F50;
            Character2ResetMaybe_1aef80(obj);
            ModelObjExCopy_1aff40(e, obj, mo);
            sz = mo->f2C + 0x500;
            n = (s32)((u8 *)sz + 0x7A);
            ((VE *)obj)->f58();
            RecStackPop_1c4140(ctx, hnd);
            buf = MemStackHeapAllocFront_14dd10(heap, n);
            if (buf == 0) {
                st->f64 = 4;
                return;
            }
            MemStackClear_14dff0(st->name);
            MemStackInit_14d810(st->name, buf, n);
            if (strlen(D_0045B8A8) <= 0xF) {
                strcpy(st->name, D_0045B8A8);
            }
            nw = (N *)MemStackNew_14e230(0x790, st->name);
            if (nw != 0) {
                ModelObjExCtor_1c4920(nw, 0, 0, 0);
                *(void **)((u8 *)nw + 0x1B0) = D_00470F50;
            }
            st->f8 = nw;
            ((VE *)nw)->f5C();
            t = GetEffectMgr_2d9040() + 0x58;
            nw = (N *)st->f8;
            nw->f53C = t;
            if (t != 0) {
                u = D_0047E180;
                D_0047E180 = u + 1;
                nw->f538 = u;
            }
            ModelObjExCopy_1aff40(e, st->f8, st->name);
            nw = (N *)st->f8;
            nw->f4FC = -1;
            st->b0 = 1;
            b = (VE *)nw;
        }
    }
    if (b != 0) {
        GameSceneObjBindMaybe_1cfcd0(ctx, st->f0, b, 0);
        ObjRecSetFlag2_1c3e80(ctx, 1, st->f0);
        ModelObjPlayMotionByName_1867a0(b, D_0045B890, 0);
        b->f44(0.0f);
        st->f6 = st->f6 | 1;
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
            u = CharaGetAi_214a10(t);
            if (u != 0) {
                AiScriptLoad_2bbc50(u, r0, r1, 0x300, 0);
                AiResetState_2bbc30(u);
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
                u = CharaGetAi_214a10(t);
                if (u != 0) {
                    AiScriptLoad_2bbc50(u, r2, r3, 0x100, 1);
                }
            }
        }
    }
    st->f6 = st->f6 | 0x80;
    st->f64 = 3;
}
