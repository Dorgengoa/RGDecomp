/* libdeasm dark7 2026-10-12: C staged by the PC-port session, __MWERKS__ branch kept,
 * port names respelled to the retail glabel names; header below is the port's own note. */
/* rg-missing: TaskStepJudgeObject_3135c0 (retail MAIN 0x003135C0, size 0x450)
 * why: a step of the task table D_0044ECF0 (TaskTableInit_27c310 <- GameSessionInit);
 * the snapshot has no C and its data names the entry TaskStepJudgeObject_3135c0.  Per frame:
 * rebuild the spatial grid around the player (SpatialGrid and SpatialMgr calls, the
 * HandleRegistryRef hit pass), then the chara-on-chara stomp judge (flag
 * 0x0020000000000000 charas landing on 0x0040000000000000 charas: flags, tint, SE 0xB5).
 * C++ because retail dispatches actor slot 0xC0 the mwcc C++ way ($t9).
 * `i = (s32)i;` and the `pp`/`pi` pointers only steer mwcc's CSE/register choice
 * (no effect on behaviour).
 * Checked: mwcc 3.0.1b210 -O4 -sdatathreshold 16 compiles this file to retail's 276
 * instructions (MATCH, out/missing-staged/README.md); the {0,0,0,1} initialiser
 * template equals retail .sdata D_0047F200..D_0047F20C. */
#include "types.h"
#include "vec.h"

class VJudgeActor {
public:
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual void _v3();
    virtual void _v4();
    virtual void _v5();
    virtual void _v6();
    virtual void _v7();
    virtual void _v8();
    virtual void _v9();
    virtual void _v10();
    virtual void _v11();
    virtual void _v12();
    virtual void _v13();
    virtual void _v14();
    virtual void _v15();
    virtual void _v16();
    virtual void _v17();
    virtual void _v18();
    virtual void _v19();
    virtual void _v20();
    virtual void _v21();
    virtual void _v22();
    virtual void _v23();
    virtual void _v24();
    virtual void _v25();
    virtual void _v26();
    virtual void _v27();
    virtual void _v28();
    virtual void _v29();
    virtual void _v30();
    virtual void _v31();
    virtual void _v32();
    virtual void _v33();
    virtual void _v34();
    virtual void _v35();
    virtual void _v36();
    virtual void _v37();
    virtual void _v38();
    virtual void _v39();
    virtual void _v40();
    virtual void _v41();
    virtual void _v42();
    virtual void _v43();
    virtual void _v44();
    virtual void _v45();
    virtual s32 IsBusy();
};
#define ACTOR_V0C0(o) (((VJudgeActor *)(o))->IsBusy())

struct JudgeChara {
    u8 pad0[0x3D0];
    u64 flags3D0;
    u8 pad3D8[0xA44 - 0x3D8];
    s32 flagsA44;
};


extern "C" {

extern s32 D_00482A24;
extern s32 D_00482A38;
extern u8 D_004E7DA0[];
extern f32 D_0045B080[];

void HandleHeapRefCompact_312870(void *);
void *GetGameData_1fede0(void);
void *GetCurrentScene_1f5be0(void);
void *ObjRecGetLiveObject_1c4a90(void *, s32);
void *MemStackHeapAllocFront_14dd10(void *, s32);
void MemStackHeapFree_14dcb0(void *, void *);
void VecAdd_13be20(Vec4 *, Vec4 *, Vec4 *);
void SpatialGridInit_316a60(void *, void *, s32, Vec4 *);
void HandleRegistryRefStepAll_3147d0(void *, void *, f32);
void SpatialGridSweepMapHits_3165c0(void *, s32);
void SpatialGridClear_316940(void *);
void SpatialMgrQuadTreeInit_3162f0(void *, void *, s32, Vec4 *, f32);
void HandleRegistryRefSubmitSpatial_3147c0(void *, void *);
void SpatialMgrCollideAll_315800(void *);
void HandleRegistryRefApplyHitsAll_3147b0(void *);
void SpatialMgrClear_315f20(void *);
void *GetActionMgr_1fdb50(void);
void *ActionMgrGetCharaList_233b40(void *);
u8 *DListGetHead_42ea60(void *);
u8 *DListGetNext_42eb30(void *);
s32 CharaGetBaseActionMode_213830(JudgeChara *);
s32 CharaGetId_214a80(JudgeChara *);
void *ActorFindById_3eb870(void *, s32);
void CharaGetPos_2388a0(JudgeChara *, Vec4 *);
f32 CharaGetCollHeight_2385f0(JudgeChara *);
f32 CharaGetCollRadius_2386a0(JudgeChara *);
void CharaGetVelocity_238890(JudgeChara *, Vec4 *);
void CharaGetPos_2388d0(JudgeChara *, Vec4 *);
f32 VecDistSqXZ_1cb390(Vec4 *, Vec4 *);
void CharaAddFlags_212460(JudgeChara *, u64);
void CharaRequestTint_213fd0(JudgeChara *, s32, s32, f32, f32, f32, f32, f32);
void GameSceneSoundSlot5PlaySeVol_1d05d0(void *, s32, f32);

void TaskStepJudgeObject_3135c0(void)
{
    void *gd;
    void *scene;
    u8 *obj;
    void *buf;
    void *heap;
    f32 k;
    f32 half;
    f32 r;
    f32 r2;
    s32 n;
    s32 i;
    s32 j;
    u8 *node;
    void *actor;
    void *mgr;
    JudgeChara **pp;
    JudgeChara **pi;

    HandleHeapRefCompact_312870(&D_00482A24);
    gd = GetGameData_1fede0();
    scene = GetCurrentScene_1f5be0();
    f32 center[4] __attribute__((aligned(16))) = {0.0f, 0.0f, 0.0f, 1.0f};
    obj = (u8 *)ObjRecGetLiveObject_1c4a90(scene, *(s16 *)(*(u8 **)((u8 *)gd + 0x18) + 0x18E));
    if (obj != 0) {
        *(u128 *)center = *(u128 *)(obj + 0x180);
    }
    heap = *(void **)((u8 *)scene + 0x180C);
    buf = MemStackHeapAllocFront_14dd10(heap, 0x2000);
    Vec4 box[2];
    VEC4_ZERO(box[1]);
    k = D_0045B080[0];
    VEC4_ZERO(box[0]);
    box[1].z = box[1].x = -100.0f * k;
    box[1].y = -50.0f * k;
    box[0].z = box[0].x = 100.0f * k;
    box[0].y = 50.0f * k;
    VecAdd_13be20(&box[1], &box[1], (Vec4 *)center);
    VecAdd_13be20(&box[0], &box[0], (Vec4 *)center);
    SpatialGridInit_316a60(D_004E7DA0, buf, 0x2000, box);
    HandleRegistryRefStepAll_3147d0(&D_00482A38, D_004E7DA0, 1.0f);
    SpatialGridSweepMapHits_3165c0(D_004E7DA0, 0x100);
    SpatialGridClear_316940(D_004E7DA0);
    SpatialMgrQuadTreeInit_3162f0(D_004E7DA0, buf, 0x2000, (Vec4 *)center, 100.0f * k);
    HandleRegistryRefSubmitSpatial_3147c0(&D_00482A38, D_004E7DA0);
    SpatialMgrCollideAll_315800(D_004E7DA0);
    HandleRegistryRefApplyHitsAll_3147b0(&D_00482A38);
    SpatialMgrClear_315f20(D_004E7DA0);
    MemStackHeapFree_14dcb0(heap, buf);

    JudgeChara *list[0xE0];
    mgr = GetActionMgr_1fdb50();
    n = 0;
    node = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(mgr));
    for (; node != 0; n++) {
        list[n] = (JudgeChara *)(node + 0x10);
        node = DListGetNext_42eb30(node);
    }

    Vec4 pos;
    Vec4 opos;
    Vec4 vel;
    half = 0.5f * k;
    for (i = 0; i < n; i++) {
        pp = &list[i];
        if (!((*pp)->flagsA44 & 0x80000) && ((*pp)->flags3D0 & 0x0020000000000000ULL) &&
            CharaGetBaseActionMode_213830((*pp)) == 0) {
            actor = ActorFindById_3eb870(gd, CharaGetId_214a80((*pp)));
            if (actor != 0 && ACTOR_V0C0(actor) == 0) {
                i = (s32)i;
                pi = &list[i];
                CharaGetPos_2388a0(*pi, &pos);
                pos.y += CharaGetCollHeight_2385f0(*pi) - half;
                r = (f64)CharaGetCollRadius_2386a0(*pi);
                r2 = r * r;
                for (j = 0; j < n; j++) {
                    if (i == j) {
                        continue;
                    }
                    pp = &list[j];
                    if ((*pp)->flagsA44 & 0x80000) {
                        continue;
                    }
                    if ((*pp)->flagsA44 & 0x40) {
                        continue;
                    }
                    if (!((*pp)->flags3D0 & 0x0040000000000000ULL)) {
                        continue;
                    }
                    CharaGetVelocity_238890((*pp), &vel);
                    CharaGetPos_2388d0((*pp), &opos);
                    if (!(pos.y <= opos.y)) {
                        continue;
                    }
                    if (pos.y < opos.y + vel.y) {
                        continue;
                    }
                    if (!(VecDistSqXZ_1cb390(&opos, &pos) <= r2)) {
                        continue;
                    }
                    CharaAddFlags_212460(*pi, 0x400000000000ULL);
                    CharaAddFlags_212460(*pp, 0x200000000000ULL);
                    CharaRequestTint_213fd0(*pi, 5, 2, 250.0f, 250.0f, 250.0f, 30.0f, 1.0f);
                    GameSceneSoundSlot5PlaySeVol_1d05d0(scene, 0xB5, 1.0f);
                }
            }
        }
    }
}

}

